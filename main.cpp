#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

const int ROW=9,COL=9,MINES=10;
vector<vector<int>> mine_map(ROW ,vector<int>(COL,0));
vector<vector<char>> view_map(ROW, vector<char>(COL, '#'));

void init() {
    srand(time(0));
    int placed = 0;
    while (placed < MINES) {
        int r = rand() % ROW;
        int c = rand() % COL;
        if (mine_map[r][c] == 0) {
            mine_map[r][c] = 1;
            placed++;
        }
    }
}
void printBoard() {
    cout << "  ";
    for(int j=0; j<COL; j++) cout <<setw(2)<< j ;
    cout << "\n";
    for (int i = 0; i < ROW; i++) {
        cout <<setw(2)<< i;
        for (int j = 0; j < COL; j++) {
            cout <<setw(2)<< view_map[i][j];
        }
        cout << endl;
    }
}
int main() {
    init();
    printBoard();

    return 0;
}
