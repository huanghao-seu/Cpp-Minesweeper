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
int count_mines(int x,int y){
    int dx[8]={1,1,1,0,0,-1,-1,-1};
    int dy[8]={1,0,-1,1,-1,1,0,-1};
    int count=0;
    for(int d=0;d<8;d++){
        int nx=x+dx[d];
        int ny=y+dy[d];
        if(nx>=0&&nx<ROW&&ny>=0&&ny<COL){
            if(mine_map[nx][ny]==1){
                count++;
            }
        }
    }
    return count;
}

int main() {
    init();
    printBoard();
    bool isPlaying=true;
    int nMine=ROW*COL-MINES;
    while(isPlaying){
       int x,y;
       cin>>x>>y;
       if(x>=0&&x<ROW&&y>=0&&y<COL) {
//-----------中雷了
        if(mine_map[x][y]==1){
        isPlaying=0;
        cout<<"Game Over"<<endl;
        view_map[x][y]='*';
        printBoard();
       }
//-----------未中雷
       else{
         if (view_map[x][y] == '#') {
             int tem = count_mines(x,y);
             view_map[x][y] = tem + '0';
             printBoard();
             nMine--;
         } else {
             cout << "这个格子已经被翻开过啦！" << endl;
         }
       }
    }
      else{
        cout<<"无效"<<endl;
        continue;}
//---------- 胜利条件
      if(nMine==0){
        isPlaying=0;
        cout<<"You Win"<<endl;
        printBoard();
      }
}

    return 0;
}
