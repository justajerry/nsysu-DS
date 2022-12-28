/*
    Author: B103040017 廖頡叡
    Date: Sept. 12,2022
    Purpose:西洋棋騎士(knight)走完棋盤的順序
*/
#include<bits/stdc++.h>
using namespace std;
class knight{   //騎士路徑類別
    public:
        knight(){}  //constructor
        knight(int x,int y,int s){  //constructor
            i=x;
            j=y;
            k=s;
        }
        int i;  //row
        int j;  //cal
        int k;  //走的方位
        knight *next=NULL;  //下一個走的方向及路線
};
knight *tail=NULL;  //stack的最上方
void push(int i,int j,int k){   //堆疊到stack上方
    if(tail==NULL){
        knight *temp=new knight(i,j,k);
        tail=temp;
    }
    else{
        knight *temp=new knight(i,j,k);
        temp->next=tail;
        tail=temp;
    }
}
knight pop(){   //抽出最上方的走過路徑
    int x,y,k;
    x=tail->i;
    y=tail->j;
    k=tail->k;
    tail=tail->next;
    return knight(x,y,k);    //回傳上一步的路徑
}
bool isempty(){ //判斷stack裡是不是空的
    if(tail==NULL){ 
        return true;    //從tail的位址判斷，是NULL的話就回傳true
    }
    return false;   //有位址的話就回傳false
}
int next(int **square,int n,int x,int y,int l){ //下一步能走的方位(照數字順序)，l是上一步走的路線，如果是走第一次的話，l=0
    if(x-2>=0 && y+1<n && square[x-2][y+1]==0 && 1>l)  return 1;
    if(x-1>=0 && y+2<n && square[x-1][y+2]==0 && 2>l)  return 2;
    if(x+1<n && y+2<n && square[x+1][y+2]==0 && 3>l)  return 3;
    if(x+2<n && y+1<n && square[x+2][y+1]==0 && 4>l)  return 4;
    if(x+2<n && y-1>=0 && square[x+2][y-1]==0 && 5>l)  return 5;
    if(x+1<n && y-2>=0 && square[x+1][y-2]==0 && 6>l)  return 6;
    if(x-1>=0 && y-2>=0 && square[x-1][y-2]==0 && 7>l)  return 7;
    if(x-2>=0 && y-1>=0 && square[x-2][y-1]==0 && 8>l)  return 8;
    return 0;
}
void plate(int n){
    int **square;   //棋盤的動態二維陣列
    int step=1,last=0,time=0;   //步數,上一步走的路線
    int x=0,y=0;    //現在的row & cal
    tail=NULL;  //初始化stack
    square=new int*[n]; //做出n*n的動態二維陣列
    knight temp;    //暫時存pop出來的knight類別
    bool able=true; //判斷棋盤能不能走完
    for(int i=0;i<n;i++){
        square[i]=new int[n];   //做出n*n的動態二維陣列
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            square[i][j]=0; //初始化n*n的動態二維陣列
        }
    }
    square[0][0]=1; //讓(0,0)為第一步
    while(step<n*n && able){    //當還沒走到最後一步且棋盤能走完
        switch (next(square,n,x,y,last))    //根據下一步的順序做出不一樣的動作
        {
            case 1: //K1
                push(x,y,1);    //將現在的座標跟K1 push 到 stack 裡
                x-=2;   //移動座標到下一步的位置
                y+=1;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;  
                break;
            case 2: //K2
                push(x,y,2);    //將現在的座標跟K2 push 到 stack 裡
                x-=1;   //移動座標到下一步的位置
                y+=2;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            case 3: //K3
                push(x,y,3);    //將現在的座標跟K3 push 到 stack 裡
                x+=1;   //移動座標到下一步的位置
                y+=2;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            case 4: //K4
                push(x,y,4);    //將現在的座標跟K4 push 到 stack 裡
                x+=2;   //移動座標到下一步的位置
                y+=1;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            case 5: //K5
                push(x,y,5);    //將現在的座標跟K5 push 到 stack 裡
                x+=2;   //移動座標到下一步的位置
                y-=1;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            case 6: //K6
                push(x,y,6);    //將現在的座標跟K6 push 到 stack 裡
                x+=1;   //移動座標到下一步的位置
                y-=2;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            case 7: //K7
                push(x,y,7);    //將現在的座標跟K7 push 到 stack 裡
                x-=1;   //移動座標到下一步的位置
                y-=2;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            case 8: //K8
                push(x,y,8);    //將現在的座標跟K8 push 到 stack 裡
                x-=2;   //移動座標到下一步的位置
                y-=1;
                step++; //做下一步的記號(步數)
                last=0; //用在next的int l，第一次的初始值為0
                square[x][y]=step;
                break;
            default: //無路可走
                if(isempty()){  //如果stack已經是空的話，代表此棋盤無解
                    able=false;
                }
                else{   //沒有的話就從stack pop出上一步的座標以及前進方向
                    temp=pop();
                    square[x][y]=0;
                    x=temp.i;
                    y=temp.j;
                    last=temp.k;
                    step--;
                }
                break;

        }
        
    }
    if(able){   //迴圈結束後有走完的話輸出結果
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<right<<setw(3)<<square[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else{   //反之則輸出no solution
        cout<<"no solution"<<endl;
    }
    for(int i=0;i<n;i++){   //清空dynamic 2D array
        delete [] square[i];
    }
    delete [] square;
    while(!isempty()){  //清空stack
        pop();
    }
}
int main(){
    for(int i=1;i<=6;i++){  //輸出1~6的走訪結果
        cout<<i<<endl;
        plate(i);
    }
    return 0;
}