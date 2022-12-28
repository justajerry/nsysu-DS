/*
    Author: B103040017 廖頡叡
    Date: Oct. 2,2022
    Purpose:給予一串數字，找出所有出現次數為奇數之數字
*/
#include <bits/stdc++.h>
using namespace std;
vector<int> Left,Right;
class node{ //節點
    public:
        node(){}    //constructor
        node(int v){    //constructor
            value=v;
            left=NULL;
            right=NULL;
        }
        node* left=NULL;    //左子樹
        node* right=NULL;   //右子樹
        int value;  //在節點的值
};
node *root=NULL;    //樹根
node* deletenode(node *current,int key){    //刪除相同值的節點
    if(current == NULL){    //已是空指標的話
        return current; //return NULL
    }
    if(current->value < key){   //如果值比現在的節點的value還高的話，往右子樹繼續尋找
        current->right= deletenode(current->right,key);
    }
    else if(current->value > key){  //如果值比現在的節點的value還小的話，往左子樹繼續尋找
        current->left = deletenode(current->left,key);
    }
    else{   //找到的話，有不同狀況
        if(current->left==NULL && current->right==NULL){    //沒有child的時候
            return NULL;
        }
        else if(current->right == NULL){    //只有左子樹的時候  
            node *temp;
            temp = current->left;
            delete current;
            return temp;
        }
        else if(current->left == NULL){ //只有右子樹的時候
            node *temp;
            temp = current->right;
            delete current;
            return temp;
        }
        node *travel;   //當左右都有時
        travel = current->right;
        while(travel->left){
            travel = travel->left;  //找到右子樹中最小的那個
        }
        current->value = travel->value; //將值傳給現在的節點
        current->right = deletenode(current->right,travel->value);    //刪除右子樹中最小的那個節點
    }
    return current;
}
void insert(int value){ //插入新的節點
    if(root==NULL){ //當樹根沒節點時
        root = new node(value); //將新的給樹根
    }
    else{
        node *current=root;
        node *parent=NULL;
        while(current!=NULL){   //從root開始找到位置
            if(value>current->value){   //如果值比現在的節點的value還高的話，往右子樹繼續尋找
                parent=current;
                current=current->right;
            }
            else if(value<current->value){  //如果值比現在的節點的value還小的話，往左子樹繼續尋找
                parent=current;
                current=current->left;
            }
            /*parent = current;
            current = value < current->value ? current->left : current->right; */   //同學教的酷酷寫法
            else if(value == current->value){   //值一樣的話，刪除目前節點
                root = deletenode(root,value);
                return;
            }
        }
        if(value > parent->value){  //值比parent的值大的話，插入在右子樹中 
            parent->right = new node(value);
        }
        else if(value < parent->value){ //值比parent的值小的話，插入在左子樹中
            parent->left = new node(value);
        }
    }
}
void printbinarytree(node *cur){    //inorder
    int l=0,r=0;
    if(cur == NULL){    //空的就不做任何動作
        return;
    }
    printbinarytree(cur->left); //印出左子樹 
    if(cur->left)   l=cur->left->value ; //將樹根的left存進vector中
    if(cur->right)   r=cur->right->value;    //將樹根的right存進vector中
    Left.push_back(l);
    Right.push_back(r);
    cout << cur->value << " ";  //印出樹根
    printbinarytree(cur->right);    //印出右子樹
}
void resetree(){    //刪除目前的binary tree
    while(root){
        root = deletenode(root,root->value);
    }
}
int main(){
    int n;
    root = NULL;    //initial 
    bool first=true;    //如果是第一次的話，不跳行
    while(cin>>n){
        if(n==-1){  //輸入結束時
            if(first)
                cout<<"node: ";
            else
                cout<<"\nnode: ";
            printbinarytree(root);  //印出binary tree
            cout<<endl;
            cout<<"left: "; //印出每個節點的left
            for(int i=0;i<Left.size();i++){
                cout<<Left[i]<<" ";
            }
            cout<<endl;
            cout<<"right: "; //印出每個節點的right
            for(int i=0;i<Right.size();i++){
                cout<<Right[i]<<" ";
            }
            cout<<endl;
            Left.clear();   //清除存left的vector
            Right.clear();   //清除存right的vector
            resetree(); //重置binary tree
            first=false;
            continue;
        }
        insert(n);  //插入目前的值
    }
    
    return 0;
}