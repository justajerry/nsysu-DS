/*
    Author: B103040017 廖頡叡
    Date: Sept. 7,2022  更正日期: Sept. 14,2022
    Purpose:以C++製作一個「集合」類別 (set class)，使其能進行「聯集」、「交集」、「差集」、「包含」、「屬於」等五種運算
*/
#include <bits/stdc++.h>
using namespace std;
class Tset{ //集合
    public:
        Tset(){}    //constructor
        Tset(char str[]){   //constructor when there's a c_string
            for(int i=0;i<strlen(str);i++){ //copy string
               a[i]=str[i]; 
            }
        }
        bool check(char c){ //check if character c is in the set
            for(int i=0;i<strlen(a);i++){
                if(c==a[i]) return true;    //if yes, return true
            }
            return false;   //if not, return false
        }
        friend const Tset operator +(Tset a,Tset b);    //overloading +
        friend const Tset operator -(Tset a,Tset b);    //overloading -
        friend const Tset operator *(Tset a, Tset b);   //overloading *
        friend bool operator >=(Tset a, Tset b);    //overloading >=
        friend ostream& operator <<(ostream& op,const Tset T);  //overloading <<
    private:
        char a[256]={0};    //the string in the set
};
void test(char str[]){  //delete duplicated parts and sort the remaining characters
    bool check[256]={false}; //check whether certain character has appeared
    char fin[256]={0};  //the string after sorted
    char temp;  //for swapping
    for(int i=0;i<strlen(str);i++){ //delete duplicated part
        if(check[str[i]])   continue;   //if the character has appeared once, don't move
        else{   //if not, put the character in fin and leave a mark on check
            check[str[i]]=true;
            fin[strlen(fin)]=str[i];
        }
    }
    for(int i=0;i<strlen(fin)-1;i++){   //bubble-sort
        for(int j=0;j<strlen(fin)-i-1;j++){
            if(fin[j]>fin[j+1]){    
                temp=fin[j];
                fin[j]=fin[j+1];
                fin[j+1]=temp;
            }
        }
    }
    strcpy(str,fin);    //let the string in main copy the finalized string 
}
int main(){
    char str1[256],str2[256],c; //string for A and B set, and char x 
    int times;  //the number of test cases
    cout<<"start!"<<endl;   //inform us that the program is ready
    cin>>times; //input the number of test cases
    cin.ignore();   //*****因為cin只能拿走值，緩衝區的\n還在，所以如果直接getline的話會不能輸入
    for(int i=0;i<times;i++){   //run each test case
        cin.getline(str1,256,'\n');
        cin.getline(str2,256,'\n'); //input strings
        cin>>c;
        cin.ignore();   //*****因為cin只能拿走值，緩衝區的\n還在，所以如果直接getline的話會不能輸入
        test(str1); //delete duplicated parts and sort
        test(str2); //delete duplicated parts and sort
        Tset A(str1),B(str2);   //making A set and B set
        cout<<"Test case "<<i+1<<endl;
        cout<<"A: "<<A<<endl;   //print A set
        cout<<"B: "<<B<<endl;   //print B set
        cout<<"A+B: "<<A+B<<endl;   //print the union of A and B 
        cout<<"A*B: "<<A*B<<endl;   //print the intersection of A and B
        cout<<"A-B: "<<A-B<<endl;   //print the difference of A and B
        cout<<"B-A: "<<B-A<<endl;   //print the difference of B and A
        if(A>=B){   //check if A contains B
            cout<<"A contains B"<<endl;
        }
        else{
            cout<<"A does not contain B"<<endl;
        }
        if(B>=A){   //check if B contains A
            cout<<"B contains A"<<endl;
        }
        else{
            cout<<"B does not contain A"<<endl;
        }
        if(A.check(c))  cout<<"'"<<c<<"' is in A"<<endl;    //check if char x is in set A
        else    cout<<"'"<<c<<"' is not in A"<<endl;
        if(B.check(c))  cout<<"'"<<c<<"' is in B"<<endl;    //check if char x is in set B
        else    cout<<"'"<<c<<"' is not in B"<<endl;
        memset(str1,0,256); //清空陣列
        memset(str2,0,256);
    }
    
    return 0;
}
const Tset operator +(Tset a,Tset b){
    char str[256]={0};  //the finalized string
    bool check; //see if there're same characters between a and b
    strcpy(str,a.a);    //copy string of a to str
    for(int i=0;i<strlen(b.a);i++){
        check=true; 
        for(int j=0;j<strlen(a.a);j++){
            if(b.a[i]==a.a[j])  check=false;    //if there's the same character, don't put it in str
        }
        if(check){
            str[strlen(str)]=b.a[i];
        }
    }
    return Tset(str);   //return a Tset with a finalized str
}
const Tset operator -(Tset a,Tset b){
    char str[256]={0};  //the finalized string
    bool check; //see if there're same characters between a and b
    for(int i=0;i<strlen(a.a);i++){
        check=true;
        for(int j=0;j<strlen(b.a);j++){
            if(a.a[i]==b.a[j]){
                check=false;    //if there's the same character, don't put it in str
                break;
            }
        }
        if(check){
            str[strlen(str)]=a.a[i];
        }
    }
    return Tset(str);
}
const Tset operator *(Tset a,Tset b){
    char str[256]={0};  //the finalized string
    for(int i=0;i<strlen(a.a);i++){
        for(int j=0;j<strlen(b.a);j++){
            if(a.a[i]==b.a[j]){ //if there's the same character, put it in str
                str[strlen(str)]=a.a[i];
                break;
            }  
        }
    }
    return Tset(str);
}
bool operator >=(Tset a,Tset b){
    bool check; //check if a contains b
    if(strlen(a.a)<strlen(b.a)){    //if a is smaller than b, there's no way that a contains b
        check=false;
    }
    else{
        for(int i=0;i<strlen(b.a);i++){
            check=false;
            for(int j=0;j<strlen(a.a);j++){
                if(b.a[i]==a.a[j]){
                    check=true;
                    break;
                }
            }
            if(!check)  break;  //if characters in b is not in a, a doesn't contains B
        }
    }
    return check;
}
ostream& operator <<(ostream& op,const Tset T){ //print Tset
    op<<"{"<<T.a<<"}";
}