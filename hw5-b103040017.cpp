/*
    Author: B103040017 廖頡叡
    Date: Sept. 28,2022
    Purpose:設計一個程式，可以處理兩個多項式之加法與乘法
*/
#include <bits/stdc++.h>
using namespace std;
class num{  //儲存單一係數和次方
    public:
        num(){} //constructor
        num(int c,int e){   //constructor   
            co=c;
            ex=e;
        }
        int co; //coefficient
        int ex; //exponent
        num *next=NULL; //下一項
        num *last=NULL; //上一項
};
class poly{ //多項式本身
    public:
        num *tail=NULL; //最前方的節點
        num *head=NULL; //最後方的節點
        friend poly operator +(poly a,poly b);  //overload +
        friend poly operator *(poly a,poly b);  //overload *
        void insert(num n){ //插入新的節點(多項式)
            if(head == NULL){   //當目前仍未有任何多項式時
                head = new num(n.co,n.ex);
                tail = head;
            }
            else if(tail == head){  //當最前方=最後方
                if(n.ex > tail->ex){
                    num *temp=new num(n.co,n.ex);
                    head->next=temp;
                    temp->last=head;
                    head=temp;
                }
                else if(n.ex < tail->ex){
                    num *temp=new num(n.co,n.ex);
                    tail->last=temp;
                    temp->next=tail;
                    tail=temp;
                }
                else{   //如果次方一樣，則係數相加就好
                    tail->co +=n.co;
                }
            }
            else{   //當有兩個多項式以上時
                num *current;
                current=tail;
                while(current){ //找出要插入的節點位置
                    if(n.ex > current->ex)
                        current = current->next;
                    else    break;
                }
                if(current == NULL){    //當次方是最大時
                    num *temp = new num(n.co,n.ex);
                    temp->last=head;
                    head->next=temp;
                    head = temp;
                }
                else if(n.ex == current->ex){   //如果次方一樣，則係數相加就好
                    current->co+=n.co;
                }
                else if(current==tail){ //當次方是最小時
                    num *temp = new num(n.co,n.ex);
                    temp->next=tail;
                    tail->last=temp;
                    tail = temp;
                }
                else{   //介於兩個多項式之間
                    num *temp = new num(n.co,n.ex);
                    temp->next = current;
                    temp->last = current->last;
                    current->last->next = temp;
                    current->last = temp;
                }
            }
        }
        num* deletenode(num *cur){  //刪除多項式
            if(cur == head && cur == tail){ //當刪除的節點是最後一個時
                num *temp;
                temp = head;
                head = NULL;    //reset head
                tail = NULL;    //reset tail 
                delete temp;
                return NULL;    //回傳NULL
            }
            if(cur == tail){    // 當是最前面的節點時
                num *temp;
                temp = tail;
                tail = tail->next;  //讓tail指到下一個多項式
                tail->last=NULL;    //清空目前tail的上一個
                delete temp;
                return tail;    //回傳tail的位置
            }
            else if(cur == head){   // 當是最後面的節點時
                num *temp;
                temp = head;
                head = head->last;  //讓head指到上一個多項式
                head->next=NULL;    //清空目前head的下一個
                delete temp;
                return head;    //回傳head的位置
            }
            else{   //其他狀況(兩邊都有其他節點)
                num *temp;
                temp = cur;
                cur->last->next = cur->next;    
                cur->next->last = cur->last;
                cur = cur->next;
                //cur->last=NULL;
                delete temp;
                return cur; //回傳原本cur的下一個位置
            }
        }
        void check(){   //有係數為0的刪掉
            num *current;
            current = tail; //從最前面開始檢查
            while(current){
                if(current->co==0){
                    current = deletenode(current);
                }
                else{
                    current = current->next;
                }
            }
        }
        void print(num *cur){   //輸出多項式
            if(tail == NULL){
                cout<<"0 0"<<endl;
                return;
            }
            if(cur->next)   print(cur->next);
            cout<<cur->co<<" "<<cur->ex<<endl;
        }
        void reset(){   //重置多項式
            while(tail){
                tail = deletenode(tail);
            }
            head = NULL;
        }
};
int main(){
    int p,x,y,q,times=1;    //第一組的項數，係數，次方，第二組的項數，第幾次
    poly A,B,C,D;   //A、B為前兩組，C、D為相加以及相乘後的結果
    while(1){
        cin>>p; //輸入第一組的項數
        for(int i=0;i<p;i++){
            cin>>x>>y;  //輸入係數和次方
            num N(x,y);
            A.insert(N);    //插入多項式
        }
        if(p!=0){   //若不是空的多項式，檢查係數有沒有0
            A.check();
        }
        cin>>q; //輸入第二組的項數
        if(p==0 && q==0){   //當第一組的項數跟第二組的項數皆為0時，結束程式
            cout<<"End!!"<<endl;
            break;
        }
        for(int i=0;i<q;i++){
            cin>>x>>y;  //輸入係數和次方
            num N(x,y);
            B.insert(N);    //插入多項式
        }
        if(q!=0){   //若不是空的多項式，檢查係數有沒有0
            B.check();
        }
        C=A+B;  //相加
        D=A*B;  //相乘
        cout<<"Case"<<times<<": "<<endl;    //第幾次測試
        cout<<"ADD"<<endl;  
        C.print(C.tail);    //輸出相加後的結果
        cout<<"MULTIPLY"<<endl;
        D.print(D.tail);    //輸出相乘後的結果
        A.reset();  //重置A
        B.reset();  //重置B
        times++;   
    }
    return 0;
}
poly operator +(poly a,poly b){
    poly P; //用來相加的空多項式
    num *tempb,*tempa;
    tempb=b.tail;
    tempa=a.tail;
    while(tempa!=NULL){
        num N(tempa->co,tempa->ex);
        P.insert(N);    //插入多項式
        tempa=tempa->next;
    }
    while(tempb!=NULL){
        num N(tempb->co,tempb->ex);
        P.insert(N);    //插入多項式
        tempb=tempb->next;
    }
    P.check();  //刪掉係數為0的多項式
    return P;
}
poly operator *(poly a,poly b){
    poly P; //用來相乘的空多項式
    num *tempa,*tempb;
    tempa=a.tail;
    int c,e;
    while(tempa!=NULL){
        tempb=b.tail;
        while(tempb!=NULL){
            c=tempa->co*tempb->co;
            e=tempa->ex+tempb->ex;
            num N(c,e);
            P.insert(N);    //插入多項式
            tempb=tempb->next;
        }
        tempa=tempa->next;
    }
    P.check();  //刪掉係數為0的多項式
    return P;
}