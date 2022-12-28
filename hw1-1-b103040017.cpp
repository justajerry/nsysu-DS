/*
    Author: B103040017 廖頡叡
    Date: Sept. 5,2022
    Purpose:製作N階(N為奇數)的魔方陣(magic square)
*/
#include <bits/stdc++.h>
using namespace std;
void magic(int num){    //製作num階的魔方陣
    int N=num*num;  //總共走的部署
    int **p;    //魔方陣的2維陣列
    p=new int*[num];
    for(int i=0;i<num;i++){
        p[i]=new int[num];  //讓2D array的各長度=num
    }
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            p[i][j]=0;  //初始化 讓所有陣列裡的數字都是沒有放任何數字的狀態
        }
    }
    int half=(num-1)/2; //設定第一步
    p[0][half]=1;   //讓最上面的row中間處放1
    int k=2,x=0,y=half; //k=現在要放置的數字 x跟y為row跟col的座標
    while(k<=N){    //製作魔方陣
        int nextx=x-1;
        int nexty=y-1;  //先假設下一步為(x-1,y-1)
        if(nextx<0)   nextx=num-1;  //如果x-1會超出邊界的話 讓他到最後一行
        if(nexty<0)   nexty=num-1;  //如果y-1會超出邊界的話 讓他到最後面
        if(p[nextx][nexty]==0){ //(x-1,y-1)如果沒有被放數字 就讓它是k
            p[nextx][nexty]=k;
        }
        else{   //如果有的話 就放在目前位置的正下方
            nextx=x+1;
            if(nextx==num)    nextx=0;     //如果x+1會超出邊界的話 讓他到第一行
            nexty=y;
            p[nextx][nexty]=k;
        }
        x=nextx;    
        y=nexty;       //換成剛剛放置k的座標
        k++;
    }
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            cout<<right<<setw(3)<<p[i][j]<<" "; //輸出魔方陣
        }
        cout<<endl;
    }
    for(int i=0;i<num;i++){
        delete [] p[i];
    }
    delete [] p;    //防止記憶體崩潰 
}
int main(){
    for(int i=1;i<=9;i+=2){ //輸出1 3 5 7 9 階的魔方陣
        cout<<i<<endl;
        magic(i);
    }
    return 0;   
}