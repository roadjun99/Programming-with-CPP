#include "MineSweeper.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>

using namespace std;

// �ִ� 26����� ��� (A~Z)
static const int MAX_ROW_LABEL = 26;

// ���� ���� ��� ���� ����
static int** MineMapMask = nullptr;
static int** MineMapLabel = nullptr;
static int nx = 10, ny = 10; // �⺻ ũ��
static int nBomb = 10;
static clock_t tStart;

enum LabalType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };

// ���� �Լ���
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

// ���� �޸� ���� �� �� ũ��� ���� �Ҵ�
static void allocateBoard(int w, int h) {
    // ���� �޸� ����
    if (MineMapMask) {
        for (int i = 0; i < ny; i++) {
            delete[] MineMapMask[i];
        }
        delete[] MineMapMask;
        MineMapMask = nullptr;
    }
    if (MineMapLabel) {
        for (int i = 0; i < ny; i++) {
            delete[] MineMapLabel[i];
        }
        delete[] MineMapLabel;
        MineMapLabel = nullptr;
    }

    // �� ũ�� ����
    nx = w;
    ny = h;

    // ���� �Ҵ�
    MineMapMask = new int* [ny];
    MineMapLabel = new int* [ny];
    for (int row = 0; row < ny; row++) {
        MineMapMask[row] = new int[nx];
        MineMapLabel[row] = new int[nx];
    }
}

// �ֺ� ���� �� ���
static int countNbrBombs(int x, int y) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++) {
        for (int xx = x - 1; xx <= x + 1; xx++) {
            if (isValid(xx, yy) && label(xx, yy) == Bomb) {
                count++;
            }
        }
    }
    return count;
}

// ���� �ʱ�ȭ
static void initBoard(int w, int h, int totalBombs) {
    // ���ϴ� ũ��� ���� �Ҵ�
    allocateBoard(w, h);

    srand((unsigned)time(NULL));
    // ��� ĭ ����ũ=Hide, label=0
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            mask(c, r) = Hide;
            label(c, r) = 0;
        }
    }

    nBomb = totalBombs;

    // ���� ��ġ
    for (int i = 0; i < nBomb; i++) {
        int rx, ry;
        do {
            rx = rand() % nx;
            ry = rand() % ny;
        } while (label(rx, ry) != Empty);
        label(rx, ry) = Bomb;
    }

    // ���� ���� ĭ�� ���� ���� �� ���
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            if (label(c, r) == Empty) {
                label(c, r) = countNbrBombs(c, r);
            }
        }
    }
}

// �ı�(dig)
static void dig(int x, int y) {
    if (!isValid(x, y)) return;
    if (mask(x, y) == Open) return;

    mask(x, y) = Open;
    // �� ĭ�̸� �ֺ��� ���
    if (label(x, y) == Empty) {
        for (int yy = y - 1; yy <= y + 1; yy++) {
            for (int xx = x - 1; xx <= x + 1; xx++) {
                if (!(xx == x && yy == y)) {
                    dig(xx, yy);
                }
            }
        }
    }
}

// ��� �ȱ�
static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide) {
        mask(x, y) = Flag;
    }
}

// ���� ��� ����
static int getFlagCount() {
    int count = 0;
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            if (mask(c, r) == Flag) count++;
        }
    }
    return count;
}

// ���� ���
static void printBoard() {
    system("cls");
    int fCount = getFlagCount();
    printf(" �߰�:%2d ��ü:%2d\n\n", fCount, nBomb);

    // �� �ε����� 1~nx
    // �ڸ����� �þ �� ������ ���� (nx>=100? "%4d" : "%3d") ������ ���� ����
    // ���⼱ 3ĭ ������ ����
    printf("    ");
    for (int c = 1; c <= nx; c++) {
        printf("%3d", c);
    }
    printf("\n");

    // �� ���̺� (A,B,C,...). �ִ� 26������ ���
    // ���� ny>26�̸� ���� ���� �ʿ�
    for (int r = 0; r < ny; r++) {
        if (r < 26) {
            printf("%3c", 'A' + r);
        }
        else {
            // 26 �Ѿ�� ? ǥ�� or AA, AB.. �� �߰�����
            printf(" ??");
        }

        for (int c = 0; c < nx; c++) {
            if (mask(c, r) == Hide) {
                printf("%3s", "��");
            }
            else if (mask(c, r) == Flag) {
                printf("%3s", "��");
            }
            else {
                if (isBomb(c, r))      printf("%3s", "��");
                else if (isEmpty(c, r)) printf("%3s", ".");
                else                   printf("%3d", label(c, r));
            }
        }
        printf("\n");
    }
}

// ���� ���� üũ
static int checkDone() {
    int closedCount = 0;
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            // ���� ������ ���� ĭ
            if (mask(c, r) != Open) {
                closedCount++;
            }
            else if (isBomb(c, r)) {
                // ���ڰ� ���� ĭ => ����
                return -1;
            }
        }
    }
    // ���� ĭ�� ���� ���� ������ ����
    return (closedCount == nBomb) ? 1 : 0;
}

// ����� �Է� ��ǥ
static bool getPos(int& x, int& y) {
    printf("\n(�� A~Z, �� 1~%d). ���: 'P'\n", nx);
    printf("��) \"P C 7\", \"B 10\" ��\n�Է� -> ");

    char line[64];
    if (!fgets(line, sizeof(line), stdin)) {
        return false;
    }

    // �빮�ڷ�
    for (char* p = line; *p; p++) {
        if (*p >= 'a' && *p <= 'z') {
            *p = toupper(*p);
        }
    }

    bool isFlag = false;
    char rowCh;
    int colN;

    // ������ ��ū 3�� ���� (ex. "P C 7", "B 10")
    char t1[16] = { 0 }, t2[16] = { 0 }, t3[16] = { 0 };
    int n = sscanf_s(line, "%s %s %s",
        t1, (unsigned)_countof(t1),
        t2, (unsigned)_countof(t2),
        t3, (unsigned)_countof(t3));
    if (n == 0) return false;

    // ���
    if (strcmp(t1, "P") == 0) {
        isFlag = true;
        if (n < 3) {
            printf("�Է� ����\n");
            return false;
        }
        rowCh = t2[0];
        colN = atoi(t3);
    }
    else {
        // �ı�
        rowCh = t1[0];
        if (n < 2) {
            printf("�Է� ����\n");
            return false;
        }
        colN = atoi(t2);
    }

    // A->0, B->1... �� ny<=26 ����
    y = rowCh - 'A';
    x = colN - 1; // 1-based �� 0-based
    return isFlag;
}

// ���� ���� ����
void playMineSweeper(int w, int h, int totalBomb) {
    // ���ϴ� ũ��(w,h)�� ���ڼ�(totalBomb)�� �ʱ�ȭ
    initBoard(w, h, totalBomb);

    // �ð� ����
    tStart = clock();
    while (true) {
        printBoard();

        int x, y;
        bool isFlag = getPos(x, y);
        if (!isValid(x, y)) {
            printf("������ ������ϴ�!\n");
            continue;
        }

        if (isFlag) mark(x, y);
        else dig(x, y);

        int st = checkDone();
        if (st != 0) {
            // ���� ����
            printBoard();
            clock_t tEnd = clock();
            double d = (double)(tEnd - tStart) / CLOCKS_PER_SEC;

            // ������ ����
            double score = (5000.0 - d * 12.0) + (double)nBomb * 50.0;

            printf("\n�ҿ�ð�: %.2f��\n", d);
            printf("����: %.2f\n", score);

            if (st < 0) {
                printf("����: ���� ����!\n");
            }
            else {
                printf("����: Ž�� ����!\n");
                addRanking(nBomb, d, score); // ��ŷ ó��
            }
            break;
        }
    }
}
