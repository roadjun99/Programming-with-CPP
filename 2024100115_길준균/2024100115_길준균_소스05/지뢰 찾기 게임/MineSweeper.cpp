#include "MineSweeper.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>

using namespace std;

// 최대 26행까지 허용 (A~Z)
static const int MAX_ROW_LABEL = 26;

// 전역 변수 대신 정적 변수
static int** MineMapMask = nullptr;
static int** MineMapLabel = nullptr;
static int nx = 10, ny = 10; // 기본 크기
static int nBomb = 10;
static clock_t tStart;

enum LabalType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };

// 접근 함수들
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

// 기존 메모리 해제 → 새 크기로 동적 할당
static void allocateBoard(int w, int h) {
    // 기존 메모리 해제
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

    // 새 크기 설정
    nx = w;
    ny = h;

    // 동적 할당
    MineMapMask = new int* [ny];
    MineMapLabel = new int* [ny];
    for (int row = 0; row < ny; row++) {
        MineMapMask[row] = new int[nx];
        MineMapLabel[row] = new int[nx];
    }
}

// 주변 지뢰 수 계산
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

// 보드 초기화
static void initBoard(int w, int h, int totalBombs) {
    // 원하는 크기로 동적 할당
    allocateBoard(w, h);

    srand((unsigned)time(NULL));
    // 모든 칸 마스크=Hide, label=0
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            mask(c, r) = Hide;
            label(c, r) = 0;
        }
    }

    nBomb = totalBombs;

    // 지뢰 배치
    for (int i = 0; i < nBomb; i++) {
        int rx, ry;
        do {
            rx = rand() % nx;
            ry = rand() % ny;
        } while (label(rx, ry) != Empty);
        label(rx, ry) = Bomb;
    }

    // 지뢰 없는 칸은 인접 지뢰 수 계산
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            if (label(c, r) == Empty) {
                label(c, r) = countNbrBombs(c, r);
            }
        }
    }
}

// 파기(dig)
static void dig(int x, int y) {
    if (!isValid(x, y)) return;
    if (mask(x, y) == Open) return;

    mask(x, y) = Open;
    // 빈 칸이면 주변도 재귀
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

// 깃발 꽂기
static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide) {
        mask(x, y) = Flag;
    }
}

// 현재 깃발 개수
static int getFlagCount() {
    int count = 0;
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            if (mask(c, r) == Flag) count++;
        }
    }
    return count;
}

// 보드 출력
static void printBoard() {
    system("cls");
    int fCount = getFlagCount();
    printf(" 발견:%2d 전체:%2d\n\n", fCount, nBomb);

    // 열 인덱스는 1~nx
    // 자릿수가 늘어날 수 있으니 폭은 (nx>=100? "%4d" : "%3d") 등으로 조절 가능
    // 여기선 3칸 폭으로 예시
    printf("    ");
    for (int c = 1; c <= nx; c++) {
        printf("%3d", c);
    }
    printf("\n");

    // 행 레이블 (A,B,C,...). 최대 26까지만 허용
    // 만약 ny>26이면 별도 로직 필요
    for (int r = 0; r < ny; r++) {
        if (r < 26) {
            printf("%3c", 'A' + r);
        }
        else {
            // 26 넘어가면 ? 표시 or AA, AB.. 등 추가로직
            printf(" ??");
        }

        for (int c = 0; c < nx; c++) {
            if (mask(c, r) == Hide) {
                printf("%3s", "□");
            }
            else if (mask(c, r) == Flag) {
                printf("%3s", "¤");
            }
            else {
                if (isBomb(c, r))      printf("%3s", "※");
                else if (isEmpty(c, r)) printf("%3s", ".");
                else                   printf("%3d", label(c, r));
            }
        }
        printf("\n");
    }
}

// 게임 종료 체크
static int checkDone() {
    int closedCount = 0;
    for (int r = 0; r < ny; r++) {
        for (int c = 0; c < nx; c++) {
            // 아직 열리지 않은 칸
            if (mask(c, r) != Open) {
                closedCount++;
            }
            else if (isBomb(c, r)) {
                // 지뢰가 열린 칸 => 실패
                return -1;
            }
        }
    }
    // 닫힌 칸이 지뢰 수와 같으면 성공
    return (closedCount == nBomb) ? 1 : 0;
}

// 사용자 입력 좌표
static bool getPos(int& x, int& y) {
    printf("\n(행 A~Z, 열 1~%d). 깃발: 'P'\n", nx);
    printf("예) \"P C 7\", \"B 10\" 등\n입력 -> ");

    char line[64];
    if (!fgets(line, sizeof(line), stdin)) {
        return false;
    }

    // 대문자로
    for (char* p = line; *p; p++) {
        if (*p >= 'a' && *p <= 'z') {
            *p = toupper(*p);
        }
    }

    bool isFlag = false;
    char rowCh;
    int colN;

    // 간단히 토큰 3개 추출 (ex. "P C 7", "B 10")
    char t1[16] = { 0 }, t2[16] = { 0 }, t3[16] = { 0 };
    int n = sscanf_s(line, "%s %s %s",
        t1, (unsigned)_countof(t1),
        t2, (unsigned)_countof(t2),
        t3, (unsigned)_countof(t3));
    if (n == 0) return false;

    // 깃발
    if (strcmp(t1, "P") == 0) {
        isFlag = true;
        if (n < 3) {
            printf("입력 오류\n");
            return false;
        }
        rowCh = t2[0];
        colN = atoi(t3);
    }
    else {
        // 파기
        rowCh = t1[0];
        if (n < 2) {
            printf("입력 오류\n");
            return false;
        }
        colN = atoi(t2);
    }

    // A->0, B->1... 단 ny<=26 전제
    y = rowCh - 'A';
    x = colN - 1; // 1-based → 0-based
    return isFlag;
}

// 실제 게임 실행
void playMineSweeper(int w, int h, int totalBomb) {
    // 원하는 크기(w,h)와 지뢰수(totalBomb)로 초기화
    initBoard(w, h, totalBomb);

    // 시간 측정
    tStart = clock();
    while (true) {
        printBoard();

        int x, y;
        bool isFlag = getPos(x, y);
        if (!isValid(x, y)) {
            printf("범위를 벗어났습니다!\n");
            continue;
        }

        if (isFlag) mark(x, y);
        else dig(x, y);

        int st = checkDone();
        if (st != 0) {
            // 게임 종료
            printBoard();
            clock_t tEnd = clock();
            double d = (double)(tEnd - tStart) / CLOCKS_PER_SEC;

            // 점수는 예시
            double score = (5000.0 - d * 12.0) + (double)nBomb * 50.0;

            printf("\n소요시간: %.2f초\n", d);
            printf("점수: %.2f\n", score);

            if (st < 0) {
                printf("실패: 지뢰 폭발!\n");
            }
            else {
                printf("성공: 탐색 성공!\n");
                addRanking(nBomb, d, score); // 랭킹 처리
            }
            break;
        }
    }
}
