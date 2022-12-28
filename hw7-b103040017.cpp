/*
    Author: B103040017 廖頡叡
    Date: Oct. 16,2022
    Purpose:測試五種排序(sorting)演算法的執行效率
    A類:2(insertion sort)
    B類:1(heapsort)
    C類:2(radixsort)
*/
#include<bits/stdc++.h>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#define ll long long int
#define NUM 100000 //設定測資數量
using namespace std;
int *test;  //測資
void createinput(){
    srand(time(NULL));
    ofstream op;    //把值輸入在input.txt中
    op.open("input.txt");
    for(int i=0;i<NUM;i++){
        int n = rand()%1000+1;  //亂數分配
        op<<n<<endl;
    }
    cout<<"input complete"<<endl;
    op.close();
}
void getinput(){
    ifstream ip;    //把值輸入在input.txt中
    test = new int[NUM];
    ip.open("input.txt");
    for(int i=0;i<NUM;i++){
        ip>>test[i];
    }
}
void swap(int &a, int& b){  //交換兩者間的值
    int temp;
    temp=a;
    a=b;
    b=temp;
}
void passvalue(int a[],int N){  //將input中的值分配給各個sorting中
    for(int i=0;i<N;i++){
        a[i]=test[i];
    }
}
void print(int array[],int num,ofstream& op){   //將sorted後的值輸出在output檔中
    for(int i=0;i<num;i++){
        op<<array[i]<<endl;
    }
}
void insertionsort(int array[],int num,ofstream &op){   //插入排序法
    int temp;
    for(int i=1;i<num;i++){
        temp = array[i];    
        for(int j=i-1;j>=0;j--){
            if(array[j]>array[j+1]){
                swap(array[j],array[j+1]);
            }
            else    break;
        }
    }
    op<<"Insertion sort: "<<endl;
    print(array,num,op);
    cout<<"Insertion OK"<<endl; //輸出可行且完成
}
void heapify(int a[],int N,int i){	//build maxheap
	int largest = i;     //將目前的index當成最大的
	int l = 2*i+1;  //left child's index
	int r = 2*i+2;  //right child's index

	if(l<N && a[l]>a[largest]){ //如果左邊的值比自己大,將largest給他的index
		largest = l;
	}

	if(r<N && a[r]>a[largest]){ //如果右邊的值比自己大,將largest給他的index
		largest = r;
	}

	if(largest != i){   //如果largest有變動的話，將原本的值跟largest的交換
		swap(a[i],a[largest]);
		heapify(a,N,largest);   //並繼續從largest做一樣的動作
	}
}
void buildmaxheap(int a[],int N){   //build maxheap
	for(int i=N/2-1;i>=0;i--){  //從最大index的parent開始
		heapify(a,N,i);
	}
}
void heapsort(int a[],int N,ofstream& op){
	buildmaxheap(a,N);  //先做出maxheap
	for(int i=N-1;i>=0;i--){    //將每個最大的值放到後面
		swap(a[0],a[i]);    
		heapify(a,i,0); //再重新找出下一個最大值
	}
    op<<"Heap sort:"<<endl;
    print(a,N,op);
    cout<<"Heap OK"<<endl;
}
int getmax(int a[],int n){  //找出陣列裡的最大值
    int max=-1;
    for(int i=0;i<n;i++){
        if(a[i]>max)    max=a[i];
    }
    return max;
}
void lsd(int a[],int n,int exp){    //Least Significant Digit
    int *out = new int[n];
    int count[10]={0},i;
    for(i=0;i<n;i++){
        count[(a[i]/exp)%10]++; 
    }
    for(i=1;i<10;i++){
        count[i]+=count[i-1];   //it will contail actual position of this digit in output
    }
    for(i=n-1;i>=0;i--){    //從上層搬下來
        out[count[(a[i]/exp)%10]-1] = a[i];
        count[(a[i]/exp)%10]--; //遞減
    }
    for(i=0;i<n;i++){   //將排列好的數值給原陣列
        a[i]=out[i];
    }
    delete []out;
}
void radixsort(int a[],int N,ofstream& op){ //radix sort
    int max;
    max = getmax(a,N);  
    for(int ex=1;ex<=max;ex*=10){   //不超過max的情況下在每一個位數排序
        lsd(a,N,ex);
    }
    op<<"Radix sort:"<<endl;
    print(a,N,op);
    cout<<"Radix OK"<<endl;
}
int cmp(const void* a,const void* b){   //qsort所需的compare function
    return *(int*) a - *(int*) b;
}
int main(){
    int *ins,*heap,*rad,*q,*s,N=NUM;    //各排序法的陣列跟測資數量
    clock_t start,end;  //計算排序時間
    createinput();
    ofstream op;    //輸出在檔案的pointer
    getinput(); //將input.txt的值抓出來
    //insertion sort
    ins = new int[N];
    passvalue(ins,N);   //傳給要進行insertion sort的array
    op.open("outputA.txt");
    start = clock();
    insertionsort(ins,N,op);    //insertion sort
    end = clock();
    delete []ins;   //刪除陣列避免溢位
    cout<<"Insertion takes "<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl; //輸出排序時間
    op.close();

    //heap sort
    heap = new int[N];
    passvalue(heap,N);  //傳給要進行heap sort的array
    op.open("outputB.txt");
    start = clock();
    heapsort(heap,N,op);    //heap sort
    end = clock();
    delete []heap;   //刪除陣列避免溢位
    cout<<"Heap takes "<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl; //輸出排序時間
    op.close();

    //radix sort
    rad = new int[N];
    passvalue(rad,N);  //傳給要進行radix sort的array
    op.open("outputC.txt");
    start = clock();
    radixsort(rad,N,op);    //radix sort
    end = clock();
    delete []rad;   //刪除陣列避免溢位
    cout<<"Radix takes "<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl; //輸出排序時間
    op.close();

    //qsort
    q = new int[N];
    passvalue(q,N);  //傳給要進行qsort的array
    op.open("outputD.txt");
    start = clock();
    qsort(q,N,sizeof(q[0]),cmp);    //qsort
    end = clock();
    op<<"Q sort:"<<endl;
    print(q,N,op);
    cout<<"Q OK"<<endl;
    delete []q;   //刪除陣列避免溢位
    cout<<"Qsort takes "<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl; //輸出排序時間
    op.close();

    //sort
    s = new int[N];
    passvalue(s,N);  //傳給要進行sort的array
    op.open("outputE.txt");
    op<<"Sort: "<<endl;
    start = clock();
    sort(q,q+N);    //sort
    end = clock();
    print(q,N,op);
    cout<<"Sort OK"<<endl;
    delete []s;   //刪除陣列避免溢位
    cout<<"Sort takes "<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl; //輸出排序時間
    op.close();

    delete []test;   //刪除存放測資的陣列
    return 0;
}