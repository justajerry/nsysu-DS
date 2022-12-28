/*
    Author: B103040017 廖頡叡
    Date: Sept. 5,2022
    Purpose:：印出1到N之間所有整數之階乘(factorial)，N<=50
*/
#include<bits/stdc++.h>
using namespace std;
void mult(int array[],int size,int num){    //讓每個元素裡的數值進行乘法運算
    for(int i=0;i<size;i++){
        array[i]*=num;
    }
}
void carry(int array[],int size){   //讓每個元素裡的大於10的數值進位
    for(int i=0;i<size-1;i++){
        if(array[i]>=10){
            array[i+1]+=array[i]/10;    //大於10就進位
            array[i]=array[i]%10;   //讓數值裡的個位數留著
        } 
    }
}
void factorial(int num){
    int *p; //存放每個位數的數值
    double N=0; //存log10 num!的數值
    int size;   //存放num!的位數
    for(auto i=1;i<num;i++){
        N+=log10(i);    //計算log10 num!的數值
    }
    if(N!=0)    size=ceil(N);   //num值的整數+1等於位數
    else    size=1;
    p=new int[size];    
    for(int i=0;i<size;i++){
        p[i]=0; //初始化
    }
    if(num>=1)  p[0]=1; //讓個位數的數值先等於1
    for(int i=1;i<=num;i++){
        mult(p,size,i); //進行運算以及進位的動作
        carry(p,size);
    }
    cout<<num<<"!=";
    for(int i=size-1;i>=0;i--){
        cout<<p[i]; //輸出每個位數的數值
    }
    cout<<endl;
}
int main(){
    int n;  //存放測資
    vector<int> fact;   //存放每個輸入的側資
    cout<<"input the number"<<endl;
    while(cin>>n){
        if(n==0)    break;  //0的話就進下一步
        fact.push_back(n);
    }
    for(int i=0;i<fact.size();i++){
        for(int j=1;j<=fact[i];j++){    //從1進行到n
            factorial(j);   //輸出結果
        }
        cout<<endl;
    }

    return 0;
}