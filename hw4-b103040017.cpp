/*
    Author: B103040017 廖頡叡
    Date: Sept. 19,2022
    Purpose:西洋棋騎士(knight)走完棋盤的順序(using recursion)
*/
#include<bits/stdc++.h>
using namespace std;
bool able;  //確定棋盤是否能走訪完
int **square=NULL;  //作為棋盤的dynamic 2D array
int moverow[8]={-2,-1,1,2,2,1,-1,-2};   //騎士下一步走的row
int movecol[8]={1,2,2,1,-1,-2,-2,-1};   //騎士下一步走的col
void travel(int n,int x,int y,int step){    //n是棋盤是n*n的,x跟y為(i,j),step為目前走的步數
    int nextx,nexty;    //下一步的(i,j)
    square[x][y]=step;  //讓目前位置為現在走的步數
    if(step==n*n){  //當走完時
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<right<<setw(3)<<square[i][j]; //輸出各位置的順序
            }
            cout<<endl;
        }
        able=true;  //讓棋盤的狀態已走訪完畢
    }
        
    else{
        if(!able){  //如果已走訪完的話，就不用做了也避免記憶體溢位
            for(int i=0;i<8;i++){
            nextx=x+moverow[i]; //讓nextx為走了k1~k8後的row座標
                nexty=y+movecol[i]; //讓nexty為走了k1~k8後的col座標
                if(nextx>=0 && nextx<n && nexty>=0 && nexty<n && square[nextx][nexty]==0){  //如果(i,j)沒有超出界線以及該位置的值為0
                    travel(n,nextx,nexty,step+1);   //做下一步的動作
                }
            }
            square[x][y]=0; //若沒有找到下一步的話，將現在位置改為0
        }
        
    }
}

void plate(int n){  //棋盤本身
    square=NULL;
    int step=1;   //初始步數
    int x=0,y=0;    //初始(i,j)座標
    square=new int*[n]; //讓棋盤為n讓棋盤為n*n的dynamic 2D array
    for(int i=0;i<n;i++){
        square[i]=new int[n];
    }
    for(int i=0;i<n;i++){   //初始化棋盤，讓其值皆為0
        for(int j=0;j<n;j++){
            square[i][j]=0;
        }
    }
    able=false; //設棋盤還沒走完
    travel(n,0,0,1);
    if(!able){  //如果結束後仍為false，代表棋盤無法走訪完畢
        cout<<"no solution"<<endl;   //輸出no solution
    }
    for(int i=0;i<n;i++){   //刪除棋盤的值
        delete [] square[i];
    }
    delete [] square;
}
int main(){
    for(int i=1;i<=6;i++){  //輸出1*1到6*6的棋盤走訪結果
        cout<<i<<endl;
        plate(i);
    }
    return 0;
}