/*
    Author: B103040017 廖頡叡
    Date: 11. 30,2022
    Purpose:以Huffman演算法製作一個檔案壓縮與解壓縮之軟體
*/
#include<bits/stdc++.h>
#include<queue>
#include<algorithm>
#include<fstream>
#define uchar unsigned char //使用unsigned char讀data跟輸出
#define MAX 10000001    //避免容量太大
using namespace std;
class node{
    public:
        node(){}    //constructor
        node(int f,uchar c,node* l,node* r){    //constructor
            fre=f;  //frequency
            ch=c;   //the character in the node
            left=l; //left child
            right=r;    //right child
        }
        int fre;    //frequency
        uchar ch;   //the character in the node
        node *left=NULL,*right=NULL;    //left and right child
};
vector<node*> freq; //合併成huffman tree用的vector
map<uchar,int> f;   //存每個unsigned char出現的頻率
map<uchar,string> out;  //每個unsigned char 對應到的編碼 for compress
node *root=NULL ,*cur=NULL; //decompress逆推回huffman tree的root,記現在所在節點的cur
map<uchar,string> table;    //從encode table中讀取每個unsigned char 對應到的編碼 for decompress
vector<uchar> data;
uchar in[MAX]={0};  //讀檔案裡的unsigned char
FILE *infile,*outfile;  //input and output file
string decodestr;   //將壓縮後的檔案還原成編碼後的結果
bool cmp(node* a,node* b){  //sort用的compare function
    return a->fre == b->fre ? a->ch < b->ch : a->fre < b->fre;  //比頻率大小，如果頻率一樣，比字元順序
}
void printnode(int f,string s,node *cur){   //將每個unsigned char編碼
    if(!cur->left && !cur->right){  //如果對到了leaf node，那此unsigned char的編碼為s
        out[cur->ch] = s;
    }
    if(cur->left)   printnode(f,s+"0",cur->left);   //向左加0    
    if(cur->right)   printnode(f,s+"1",cur->right); //向右加0
}
void buildtree(){   //逆推huffman tree
    root = new node(0,' ',0,0); //新增root
    for(auto i : table){    //從encode table 中逆推
        cur = root;
        string str = i.second;  //目前字元的編碼
        for(int j=0;j<str.size();j++){  //從root 尋訪
            if(str[j]=='0'){
                if(!cur->left){ //如果node不存在的話，新增一個
                    cur->left = new node(0,' ',0,0);
                }
                cur = cur->left;
            }
            if(str[j]=='1'){
                if(!cur->right){    //如果node不存在的話，新增一個
                    cur->right = new node(0,' ',0,0);
                }
                cur = cur->right;
            }
        }
        cur->ch = i.first;  //存字元
    }
}
void compress(char ifname[],char ofname[]){ //壓縮
    int fsize;  //檔案大小
    infile = fopen(ifname,"rb");    
    outfile = fopen(ofname,"wb");
    if(!infile){    //不存在的話，退出
        cout<<"The input file can't be found"<<endl;
        return;
    }
    //get the size of file(byte)
    fseek(infile,0,SEEK_END);
    fsize = ftell(infile);
    rewind(infile);
    if(fsize > MAX){    //if the size exceeds the limit
        cout<<"exceed limit"<<endl;
        return;
    }
    fread(in,1,fsize,infile);   // 讀檔案，將資料傳給in陣列
    for(int i=0;i<fsize;i++){
        f[in[i]]++; //計算頻率
    }
    for(auto i : f){
        node *newnode = new node(i.second,i.first,nullptr,nullptr);
        freq.push_back(newnode);    //分別將每個字元以及頻率記在vector中
    }
    while(freq.size()>1){   //合併成huffman tree
        sort(freq.begin(),freq.end(),cmp);
        node *l,*r;
        int ls=0,rs=1;
        if(freq[0]->ch > freq[1]->ch){
            ls=1; rs=0;
        }
        l = freq[ls];
        r = freq[rs];
        int co = l->fre+r->fre;
        node *in = new node(co,l->ch,l,r);  //兩個節點合併後的node
        for(int i=0;i<2;i++)    freq.erase(freq.begin());   //刪除原先的兩個node
        freq.push_back(in); //新增合併後的node
    }
    int aftercompress=0,header=0;   //計算壓縮後的大小以及encode table的大小
    double comrate; //壓縮率
    string code=""; //編碼後的data
    printnode(1,"",freq[0]);
    for(auto i : out){
        cout<<i.first<<"="+i.second<<endl;  //print the encode table on the standard output
        header+=(i.second.size()+3);    //sizeof(char) + sizeof('=') + i.second.size()
    }
    for(int i=0;i<fsize;i++){
        code+=out[in[i]];   //形成編碼後的結果
    }
    aftercompress+=code.size(); //編碼後的大小
    header+=30; //預設header的size
    comrate = 100.0*(header + aftercompress/8 + (aftercompress%8>0))/fsize; //算壓縮率
    fprintf(outfile,"%4d %8d %8d %6.2lf\n",out.size(),fsize,aftercompress/8 + (aftercompress%8>0),comrate); //將需要的資料輸出在output file裡
    printf("\n%s: %d Bytes\nAfter compression: %d Bytes\nCompressed rate: %lf\n",ifname,fsize,header + aftercompress/8 + (aftercompress%8>0),comrate);
    for(auto i : out){
        fprintf(outfile,"%c=%s\n",i.first,i.second.c_str());    //輸出encode table到output file裡
    }
    uchar ch;   //存壓縮後的character
    for(int i=0;i<aftercompress;i+=8){
        ch = stoul(code.substr(i,8),nullptr,2); //將8bytes的string壓縮成2進制的unsigned char
        fprintf(outfile,"%c",ch);   //輸出到檔案裡
    }
    cout<<"compression finished"<<endl; //壓縮成功
    fclose(infile); //關檔案
    fclose(outfile);    //關檔案
}
void decode(int csize){ //還原成編碼
    decodestr="";
    int i;
    char lastbyte[9];
    for(i=0 ;i<csize-1;i++){
        for(int j=7;j>=0;j--){
            decodestr += ((in[i] & 1<<j) ? '1' : '0');  //對應每個位置是0 or 1  
        }
    }
    itoa(in[i],lastbyte,2); //因為最後一個character可能長度不到8，所以獨立處理
    decodestr+=lastbyte;
}
void decompress(char ifname[],char ofname[]){   //解壓縮
    int fsize,encoded,csize;    //檔案大小、encode table的字元數量、壓縮後的大小
    double comrate; //壓縮率
    char code[32];  //記encode table 的編碼
    uchar origin;   //記encode table的字元
    string str="";  //原檔案的data
    infile = fopen(ifname,"rb");
    outfile = fopen(ofname,"wb");
    if(!infile){    //不存在的話，退出
        cout<<"The input file can't be found"<<endl;
        return;
    }
    fscanf(infile,"%d %d %d %lf",&encoded,&fsize,&csize,&comrate);  //讀取檔案大小、encode table的字元數量、壓縮後的大小和壓縮率
    fgetc(infile);  //避免讀到緩衝區
    for(int i=0;i<encoded;i++){
        fscanf(infile,"%c=%s",&origin,&code);   //讀取encode table的資料
        fgetc(infile);  //避免讀到緩衝區
        table.insert(make_pair(origin,code));   //以pair的形式push到map中
    }
    cout<<"encode table:"<<endl;
    for(auto i:table){
        printf("%c = %s\n",i.first,i.second.c_str());   //print encode table on the standard output
    }
    fread(in,1,csize,infile);   //讀取壓縮後的data
    decode(csize);  //還原成編碼後的結果
    buildtree();    //逆推huffman tree
    cur = root; 
    for(int i=0;i<decodestr.size();i++){    //從root開始找到還原的字元並存在str中
        if(decodestr[i]=='0'){
            cur = cur->left;
        }
        else if(decodestr[i]=='1'){
            cur = cur->right;
        }
        if(!cur->left && !cur->right){
            str+=cur->ch;
            cur = root;
        }
    }
    fwrite(str.data(),1,fsize,outfile); //還原成原檔案
    cout<<"uncompressed"<<endl; //解壓縮成功
    fclose(infile); //關檔案
    fclose(outfile); //關檔案
}
int main(int argc, char* argv[]){
    /*huffman -c -i infile -o outfile, argc需等於6, argv[1]需等於-c(壓縮) or -u(解壓縮)
    argv[2]需等於-i,argv[4]需等於-o                               */
    if(argc != 6){  //不符合格式
        cout<<"Error!"<<endl;
    }
    else{
        if(!strcmp(argv[1],"-c")){  //需符合格式
            if(!strcmp(argv[2],"-i")){  //需符合格式
                if(!strcmp(argv[4],"-o")){  //需符合格式
                    compress(argv[3],argv[5]);  //壓縮
                }
                else{
                    cout<<"-o not found"<<endl;
                }
            }
            else{
                cout<<"-i not found"<<endl;
            }
        }
        else if(!strcmp(argv[1],"-u")){  //需符合格式
            if(!strcmp(argv[2],"-i")){  //需符合格式
                if(!strcmp(argv[4],"-o")){  //需符合格式
                    decompress(argv[3],argv[5]);    //解壓縮
                }
                else{
                    cout<<"-o not found"<<endl;
                }
            }
            else{
                cout<<"-i not found"<<endl;
            }
        }
    }
    return 0;
}