#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
typedef int Status; 

//-----------------------------顺序表的基本结构--------------------------------------
 
#define MAXSIZE 20			//一个用做示例的小顺序表的最大长度 

typedef int KeyType;		//定义关键字类型为整数类型 
typedef int InfoType; 		//定义其它数据项的类型 

typedef struct{
	KeyType key;			//关键字项 
	InfoType otherinfo;		//其他数据项 
}RcdType;					//记录类型 

typedef struct{
	RcdType r[MAXSIZE+1];		//r[0]闲置或用作哨兵单元 
	int length;					//顺序表长度 
}SqList;						//顺序表类型 

//------------------------------顺序表L的建立----------------------------------------- 

Status CreateSqList(SqList &L){
	int i; 
	printf("请输入要创建的顺序表的长度：\n");
	scanf("%d",&L.length);
	printf("请输入顺序表的值(以空格隔开)\n");
	for(i=1;i<=L.length;++i){
		scanf("%d",&L.r[i].key);
		L.r[i].otherinfo=i;
	}
	return OK; 
} 
//----------------------------顺序表L的输出-------------------------------------------- 

void PrintSqList(SqList L)
{ 
	int i;
	printf("key  ord\n");
	for(i=1;i<=L.length;i++)
    	printf("%d %4d\n",L.r[i].key,L.r[i].otherinfo);
	printf("\n");
}

//------------------------------直接插入排序-------------------------------------------

Status InsertSort(SqList &L){
	//对顺序表L作直接插入排序
	int j;
	for(int i=2;i<=L.length;++i){
		if(LT(L.r[i].key,L.r[i-1].key)){		//"<",需将L.r[i]插入有序子表 
			L.r[0]=L.r[i];						//复制为哨兵
			for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
				L.r[j+1]=L.r[j];				//记录后移
			L.r[j+1]=L.r[0];					//插入到正确位置 
		}
	}
	return OK; 
} 

//------------------------------折半插入排序----------------------------------------------- 
Status BInsertSort(SqList &L){
	//对顺序表L作折半插入排序 
	int i,low,high,m; 
	for(i=2;i<=L.length;++i){
		L.r[0]=L.r[i];		//将L.r[i]暂存到L.r[0] 
		low=1;
		high=i-1;
		while(low<=high){			//在r[low...high]中折半查找有序插入的位置 
			m=(low+high)/2;			//折半 
			if(LT(L.r[0].key,L.r[m].key))		//插入点在低半区 
				high=m-1;
			else								//插入点在高半区 
				low=m+1;
		}
		for(int j=i-1;j>=high+1;--j)			//记录后移 
			L.r[j+1]=L.r[j];
		L.r[high+1]=L.r[0];						//插入 
	} 
	return OK;
} 

//------------------------------起泡排序------------------------------------------------- 
Status BubbleSort(SqList &L){
	int change;
	RcdType temp;
	for(int i=L.length,change=TRUE;i>1 && change;--i){
		change=FALSE;
		for(int j=1;j<i;j++){
			if(LT(L.r[j+1].key,L.r[j].key)){
				temp=L.r[j];
				L.r[j]=L.r[j+1];
				L.r[j+1]=temp;
				change=TRUE;
			}
		}
	}
	return OK;
} 

//----------------------------快速排序----------------------------------------------------- 
int Partition(SqList &L,int low,int high){
	//交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并返回其所在位置，此时在它前(后)的记录均不大(小)于它 
	KeyType pivotkey;
	L.r[0]=L.r[low];				//用子表的第一个记录作枢轴记录 
	pivotkey=L.r[low].key;			//枢轴记录关键字 
	while(low<high){				//从表的两端交替地向中间扫描 
		while(low<high && L.r[high].key>=pivotkey)
			--high;
		L.r[low]=L.r[high];			//将比枢轴小的记录移到低端
		while(low<high && L.r[low].key<=pivotkey) 
			++low;
		L.r[high]=L.r[low];			//将比枢轴大的记录移到高端
	} 
	L.r[low]=L.r[0];				//枢轴记录到位 
	return low; 					//返回枢轴位置 
} 

void QSort(SqList &L,int low,int high){
	//对顺序表L中的子序列L.r[low..high]作快速排序
	int pivotloc;
	if(low<high){		//长度大于1 
		pivotloc=Partition(L,low,high);		//将L.r[low...high]一分为二
		QSort(L,low,pivotloc-1);			//对低子表递归排序，pivotloc是数轴位置 
		QSort(L,pivotloc+1,high); 			//对高子表递归排序 
	} 
} 

Status QuickSort(SqList &L){
	//对顺序表L作快速排序。
	QSort(L,1,L.length); 
	return OK;
} 

//--------------------------------------简单选择排序------------------------------------ 
Status SelectSort(SqList &L){
	RcdType temp;
	int k;
	for(int i=1;i<L.length;++i){		//选择第i小的记录，并交换到位 
		k=i;
		for(int j=i+1;j<=L.length;++j)		//在L.r[i..L.lengh]中选择key最小的记录 
			if(L.r[k].key>L.r[j].key)
				k=j;
		if(i!=k){						//与第k(j)个记录交换 
			temp=L.r[i];
			L.r[i]=L.r[k];
			L.r[k]=temp;
		} 
	}
	return OK;
} 

//------------------------------------堆排序------------------------------------------------
//简单选择排序和树形选择排序的升级 
typedef SqList HeapType;	//堆采用顺序表存储表示 

void HeapAdjust(HeapType &H,int s,int m){
	//已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆得定义，本函数调整H.r[s]
	//的关键字，使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言)
	RcdType rc;
	rc=H.r[s];
	for(int j=2*s;j<=m;j*=2){		//沿key较大的孩子结点向下筛选
		if(j<m && LT(H.r[j].key,H.r[j+1].key)) 
			++j;						//j为key较大的记录的下标
	    if(!LT(rc.key,H.r[j].key))		//rc应插在位置s上 
			break;
		H.r[s]=H.r[j];
		s=j; 
	}
	H.r[s]=rc; 
}

Status HeapSort(HeapType &H){
	//对顺序表H进行堆排序。 
	int i;
	RcdType temp;
	for(i=H.length/2;i>0;--i)			//把H.r[1..H.length]建成大顶堆
		HeapAdjust(H,i,H.length);
	for(i=H.length;i>1;--i){
		temp=H.r[1];				//将堆栈记录和当前未经排序子序列HR[1..i]中最后一个记录交换 
		H.r[1]=H.r[i];
		H.r[i]=temp;
		HeapAdjust(H,1,i-1);		//将H.r[1..i-1]重新调整为大顶堆 
	} 
	return OK;
}
 

//-----------------------------------2-路归并排序-----------------------------------------------

void Merge(RcdType SR[],RcdType TR[],int i,int m,int n){
	//将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
	int j,k;
	for(j=m+1,k=i;i<=m && j<=n;++k){		//将SR中记录由小到大地并入TR 
		if(LQ(SR[i].key,SR[j].key))
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	} 
	if(i<=m){								//将剩余的SR[i..m]复制到TR 
		for(int n1=k,n2=i;n1<=n && n2<=m; n1++,n2++)
			TR[n1]=SR[n2];
    }
	if(j<=n){								//将剩余的SR[j..n]复制到TR
		for(int n1=k,n2=j;n1<=n && n2<=n; n1++,n2++)	
			TR[n1]=SR[n2];
	}
} 

void Msort(RcdType SR[],RcdType TR1[],int s,int t){
	//将SR[s..t]归并为TR1[s..t]。
	RcdType TR2[MAXSIZE];
	int m;
	if(s==t)
		TR1[s]=SR[s];
	else{
	    m=(s+t)/2;		//将SR[s..t]平分为SR[s..m]和SR[m+1..t]
		Msort(SR,TR2,s,m);			//递归地将SR[s..m]归并为有序的TR2[s..m]
		Msort(SR,TR2,m+1,t);		// 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
		Merge(TR2,TR1,s,m,t);		//将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] 
	} 
}
Status MergeSort(SqList &L){
	//对顺序表L作归并排序。
	Msort(L.r,L.r,1,L.length);
	return OK; 
}

//---------------------------------------希尔排序--------------------------------------------------- 

void ShellInsert(SqList &L,int dk){
	//对顺序表L作一趟希尔排序。本算法是和一趟直接插入排序相比，做了以下修改
	//1、前后记录位置增量是dK，而不是1；
	//2、r[0]只是暂存单元，不是哨兵。当j<=0时，插入位置已找到。
	int j;
	for(int i=dk+1;i<=L.length;++i){
		if(LT(L.r[i].key,L.r[i-dk].key)){			//需将L.r[i]插入有序增量子表 
			L.r[0]=L.r[i];							//暂存在L.r[0]
			for(j=i-dk; j>0 && LT(L.r[0].key,L.r[j].key);j-=dk)
				 L.r[j+dk]=L.r[j];					//记录后移，查找插入位置
			L.r[j+dk]=L.r[0];						//插入 
		}
	} 
} 
//49 38 65 97 76 13 27 49 55 4
//Status ShellSort(SqList &L){
//	//按增量序列dtla[0..t-1]对顺序表L作希尔排序。
//	int dlta[L.length];
//	for(int k=0;k<L.length;++k){
//		int t = L.length - k + 1;
//		printf("%d ",t);
//		dlta[k] = (int)pow(2.0,t)-1;
//		printf("%d\n",dlta[k]);
//	}
//	for(int k=0;k<L.length;++k){
//		ShellInsert(L,dlta[k]);			//一趟增量为dlta[k]的插入排序
//	} 
//	return OK; 
//} 

Status ShellSort(SqList &L){
	//按增量序列dtla[0..t-1]对顺序表L作希尔排序。
	//缩小增量排序,直接插入排序的升级 
	int dlta[] = {17,15,13,9,7,4,3,2,1};
	for(int k=0;k<L.length;++k){
		ShellInsert(L,dlta[k]);			//一趟增量为dlta[k]的插入排序
	} 
	return OK; 
}

//-----------------------------2_路插入排序-------------------------------------------
//折半插入排序基础上改进的 
Status P2_InsertSort(SqList &L){											
	int i,j,first,final;
	RcdType d[MAXSIZE];					
	d[0]=L.r[1];											//设L的第1个记录为d中排好序的记录(在位置[0]) 
	first=final=0;											//first、final分别指示d中排好序的记录的第1个和最后1个记录的位置 
	for(i=2;i<=L.length;++i)
	{															//依次将L的第2个～最后1个记录插入d中 
		if (L.r[i].key<d[first].key)
		{														//待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素) 
			first=(first-1+L.length)%L.length;					//设d为循环向量 
			d[first]=L.r[i];
		}
		else if(L.r[i].key>d[final].key)
		{							//待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素) 
			final=final+1;
			d[final]=L.r[i];
		}
		else{						//待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素) 
			j=final++;				//移动d的尾部元素以便按序插入记录 
			while(L.r[i].key<d[j].key)
			{
				d[(j+1)%L.length]=d[j];
				j=(j-1+L.length)%L.length;
			}
			d[j+1]=L.r[i];
		}
	}
	for(i=1;i<=L.length;i++) 					//把d赋给L.r 
		L.r[i]=d[(i+first-1)%L.length]; 		//线性关系  
	return OK;
}

//----------------------------树形选择排序-----------------------------------
//简单选择排序的改进. 
Status TreeSort(SqList &L){
	int i,j,j1,k,k1,l,n=L.length;
	RcdType *t;
	
	l=(int)ceil(log(n)/log(2))+1; 				//完全二叉树的层数 
	k=(int)pow(2,l)-1; 							//l层完全二叉树的结点总数  
	k1=(int)pow(2,l-1)-1; 						//l-1层完全二叉树的结点总数 
	t=(RcdType*)malloc(k*sizeof(RcdType)); 		//二叉树采用顺序存储结构  
	
	for(i=1;i<=n;i++) 							//将L.r赋给叶子结点 
		t[k1+i-1]=L.r[i];
		
	for(i=k1+n;i<k;i++) 						//给多余的叶子的关键字赋无穷大 
		t[i].key=INT_MAX;
		
	j1=k1;
	j=k;
	
	while(j1){ 									//给非叶子结点赋值
		for(i=j1;i<j;i+=2)
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
		j=j1;
		j1=(j1-1)/2;
	}
	
	for(i=0;i<n;i++){
		L.r[i+1]=t[0]; 							//将当前最小值赋给L.r[i] 
		j1=0;
		
		for(j=1;j<l;j++) 						//沿树根找结点t[0]在叶子中的序号j1 
			t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		
		t[j1].key=INT_MAX;
		while(j1){
			j1=(j1+1)/2-1; 						//序号为j1的结点的双亲结点序号 
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	
	free(t);
	return OK;
}

//---------------------------------关键字的记录----------------------------------------- 

void Rearrange(SqList &L,int adr[]) 		//改此句(类型) 
{	//adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 
	//本算法按adr重排L.r，使其有序。算法10.18(L的类型有变) 
	int i,j,k;
	for(i=1;i<L.length;++i)				//改此句(类型) 
	if(adr[i]!=i)
	{
		j=i;
		L.r[0]=L.r[i];				//暂存记录(*L).r[i] 
		while(adr[j]!=i){					//调整(*L).r[adr[j]]的记录到位直到adr[j]=i为止 
			k=adr[j];
			L.r[j]=L.r[k];
			adr[j]=j;
			j=k; 							//记录按序到位 
		}
		L.r[j]=L.r[0];
		adr[j]=j;
	}
}

void Menu(void)
{
	printf("\t\t             ========================        \n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |--------|     各种内部排序      |-------|\n");
	printf("\t\t   |        |                       |       |\n");
	printf("\t\t   |         ========================       |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |            请选择你的操作排序：        |\n");
	printf("\t\t   |            [1]顺序表的创建             |\n");
	printf("\t\t   |            [2]直接插入排序             |\n");
	printf("\t\t   |            [3]折半插入排序             |\n");
	printf("\t\t   |            [4]交换排序(起泡排序)       |\n");
	printf("\t\t   |            [5]快速排序                 |\n");
	printf("\t\t   |            [6]简单选择排序             |\n");
	printf("\t\t   |            [7]堆排序                   |\n");
	printf("\t\t   |            [8]2-路归并排序             |\n");
	printf("\t\t   |            [9]希尔排序                 |\n");
	printf("\t\t   |            [10]2_路插入排序            |\n");
	printf("\t\t   |            [11]树形选择排序            |\n");
	printf("\t\t   |            [12]退出                    |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 欢迎修改               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("请选择你要进行的操作(1/2/3/4/5/6/7/8/9/10/11/12):");
}

int main(int argc,char **argv){
//	49 38 65 97 76 13 27 49 55 4
	Menu();
	int i;
	SqList L;
	scanf("%d",&i);
	while(i!=12){
		switch(i){
			case 1:
				if(CreateSqList(L))
					printf("创建成功！\n"); 
				Menu();
				break;
			case 2:
				printf("直接插入排序后的结果为：\n");
				InsertSort(L);
				PrintSqList(L);
				Menu();
				break;
			case 3:
				printf("折半插入排序后的结果为：\n");
				BInsertSort(L); 
				PrintSqList(L);
				Menu();
				break;	
			case 4:
				printf("起泡排序后的结果为：\n");
				BubbleSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 5:
				printf("快速排序后的结果为：\n");
				QuickSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 6:
				printf("简单选择排序后的结果为：\n");
				SelectSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 7:
				printf("堆排序后的结果为：\n");
				HeapSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 8:
				printf("归并排序后的结果为：\n");
				MergeSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 9:
				printf("希尔排序后的结果为：\n");
				ShellSort(L);
				PrintSqList(L);
				Menu();
				break;
			case 10:
				printf("2_路插入排序后的结果为：\n");
				P2_InsertSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 11:
				printf("树形选择排序后的结果为：\n");
				TreeSort(L);
				PrintSqList(L);
				Menu();
				break;
			default:
				printf("输入有误,请重新输入!\n");
				Menu();
				break;		
		}
		scanf("%d",&i);
	} 
	return 0;
}
