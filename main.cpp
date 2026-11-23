#include<iostream>
#include<vector>
#include<iomanip>
#include <chrono>
using namespace std;

const int ROW=9,COL=9,MINES=10;
int nMine=ROW*COL-MINES;
vector<vector<int>> mine_map(ROW ,vector<int>(COL,0));
vector<vector<char>> view_map(ROW, vector<char>(COL, '#'));
const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

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
void expand(int x,int y,int&nMine){
     if (x < 0 || x >= ROW || y < 0 || y >= COL) return;
     if (view_map[x][y] != '#' || mine_map[x][y] == 1) return;
     int tem=count_mines(x,y);
     view_map[x][y] = tem + '0';
     nMine--;
     if(tem==0){
        for(int d=0;d<8;d++){
          int nx=x+dx[d];
          int ny=y+dy[d];
          if(nx>=0&&nx<ROW&&ny>=0&&ny<COL){
          expand(nx,ny,nMine);
          }
        }
     }
}

int main() {
    init();
    printBoard();
    //计时
    auto start_time = chrono::steady_clock::now();
    bool isPlaying=true;
    while(isPlaying){
       int x,y;
       char op;
       cout << "输入 行 列 操作(O排雷/F插旗): ";
       cin>>x>>y>>op;
       if(x>=0&&x<ROW&&y>=0&&y<COL) {
          if(op=='O'){
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
                expand(x,y,nMine);
                printBoard();
              } else {
                cout << "这个格子已经被翻开过啦！" << endl;
              }
            }
        }
        else if(op=='F'){
            if(view_map[x][y]=='#'){
                view_map[x][y]='F';
            }
            else if(view_map[x][y]=='F'){
                view_map[x][y]='#';
            }
            else{
                cout << "已经翻开的格子不能插旗！" << endl;
            }
            printBoard();
            continue;
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
       // --- 计算并显示时间 ---
        auto current_time = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(current_time - start_time);
        int total_seconds = duration.count();

        cout << "⏱️ 当前用时: " << total_seconds / 60 << "分 " << total_seconds % 60 << "秒" << endl;
        cout << "---------------------------------" << endl;
}

    return 0;
}
