#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

#define EMPTY '#'
#define WPAWN 'P'
#define BPAWN 'p'
#define WKING 'K'
#define BKING 'k'
#define WQUEEN 'Q'
#define BQUEEN 'q'
#define WKNIGHT 'N'
#define BKNIGHT 'n'
#define WBISHOP 'B'
#define BBISHOP 'b'
#define WROOK 'R'
#define BROOK 'r'
#define SIZE 8

#define PAWN(c) (c == WPAWN || c == BPAWN)
#define KING(c) (c == WKING || c == BKING)
#define QUEEN(c) (c == WQUEEN || c == BQUEEN)
#define KNIGHT(c) (c == WKNIGHT || c == BKNIGHT)
#define BISHOP(c) (c == WBISHOP || c == BBISHOP)
#define ROOK(c) (c == WROOK || c == BROOK)
#define NEIG(x,y) for (int x = -1; x <= 1; ++x) for (int y = -1; y <= 1; ++y)
#define INSIDE(x,y) (0 <= x && x < SIZE && 0 <= y && y < SIZE)

int knx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int kny[8] = {2, -2, 2, -2, 1, -1, 1, -1};

vector<char> options = {
    WQUEEN, WKNIGHT, WBISHOP, WROOK
};

bool is_white(char piece){
    return 'A' <= piece && piece <= 'Z';
}

bool threat(vector<string> &board, int x, int y, bool white){
    auto piece = board[x][y];
    
    if (piece == EMPTY || KING(piece) || PAWN(piece)) 
        return false;

    if (is_white(piece) != white) 
        return false;

    if (ROOK(piece)){
        NEIG(dx, dy) if (abs(dx) + abs(dy) == 1){
            for (int k = 1; ;++k){
                int nx = x + k * dx, ny = y + k * dy;
                if (INSIDE(nx, ny)){
                    if (KING(board[nx][ny]) && is_white(board[nx][ny]) != white)
                        return true;
                    else if (board[nx][ny] != EMPTY)
                        break;                        
                }
                else break;
            }
        }
        return false;
    }

    if (BISHOP(piece)){
        NEIG(dx, dy) if (abs(dx) == 1 && abs(dy) == 1){
            for (int k = 1; ;++k){
                int nx = x + k * dx, ny = y + k * dy;
                if (INSIDE(nx, ny)){
                    if (KING(board[nx][ny]) && is_white(board[nx][ny]) != white)
                        return true;
                    else if (board[nx][ny] != EMPTY)
                        break;                        
                }
                else break;
            }
        }
        return false;
    }

    if (QUEEN(piece)){
        NEIG(dx, dy) if (abs(dx) != 0 || abs(dy) != 0){
            for (int k = 1; ;++k){
                int nx = x + k * dx, ny = y + k * dy;
                if (INSIDE(nx, ny)){
                    if (KING(board[nx][ny]) && is_white(board[nx][ny]) != white)
                        return true;
                    else if (board[nx][ny] != EMPTY)
                        break;                        
                }
                else break;
            }
        }
        return false;
    }

    if (KNIGHT(piece)){
        for (int t = 0; t < 8; ++t){
            int dx = knx[t], dy = kny[t];
            int nx = x + dx, ny = y + dy;
            if (INSIDE(nx, ny)){
                if (KING(board[nx][ny]) && is_white(board[nx][ny]) != white)
                    return true;
            }
        }
        return false;
    }

    return false;
}

bool ok(vector<string> &board){
    bool white_win = false;
    bool black_win = false;

    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            white_win |= threat(board, i, j, true);
            black_win |= threat(board, i, j, false);
        }
    }

    return white_win && !black_win;
}

int solve(vector<string> board){
    int answer = 0;
    for (int i = 0; i < SIZE; ++i){
        if (board[1][i] == WPAWN && board[0][i] == EMPTY){
            board[1][i] = EMPTY;
            for (auto piece : options){
                board[0][i] = piece;
                answer += ok(board);
            }
            board[1][i] = WPAWN;
            board[0][i] = EMPTY;
        }
    }
    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t-->0){
        vector<string> board(8);

        for (int i = 0; i < 8; ++i)
            cin >> board[i];

        cout << solve(board) << endl;
    }

    return 0;
}