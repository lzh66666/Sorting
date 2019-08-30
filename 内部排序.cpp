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

//-----------------------------˳���Ļ����ṹ--------------------------------------
 
#define MAXSIZE 20			//һ������ʾ����С˳������󳤶� 

typedef int KeyType;		//����ؼ�������Ϊ�������� 
typedef int InfoType; 		//������������������� 

typedef struct{
	KeyType key;			//�ؼ����� 
	InfoType otherinfo;		//���������� 
}RcdType;					//��¼���� 

typedef struct{
	RcdType r[MAXSIZE+1];		//r[0]���û������ڱ���Ԫ 
	int length;					//˳����� 
}SqList;						//˳������� 

//------------------------------˳���L�Ľ���----------------------------------------- 

Status CreateSqList(SqList &L){
	int i; 
	printf("������Ҫ������˳���ĳ��ȣ�\n");
	scanf("%d",&L.length);
	printf("������˳����ֵ(�Կո����)\n");
	for(i=1;i<=L.length;++i){
		scanf("%d",&L.r[i].key);
		L.r[i].otherinfo=i;
	}
	return OK; 
} 
//----------------------------˳���L�����-------------------------------------------- 

void PrintSqList(SqList L)
{ 
	int i;
	printf("key  ord\n");
	for(i=1;i<=L.length;i++)
    	printf("%d %4d\n",L.r[i].key,L.r[i].otherinfo);
	printf("\n");
}

//------------------------------ֱ�Ӳ�������-------------------------------------------

Status InsertSort(SqList &L){
	//��˳���L��ֱ�Ӳ�������
	int j;
	for(int i=2;i<=L.length;++i){
		if(LT(L.r[i].key,L.r[i-1].key)){		//"<",�轫L.r[i]���������ӱ� 
			L.r[0]=L.r[i];						//����Ϊ�ڱ�
			for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
				L.r[j+1]=L.r[j];				//��¼����
			L.r[j+1]=L.r[0];					//���뵽��ȷλ�� 
		}
	}
	return OK; 
} 

//------------------------------�۰��������----------------------------------------------- 
Status BInsertSort(SqList &L){
	//��˳���L���۰�������� 
	int i,low,high,m; 
	for(i=2;i<=L.length;++i){
		L.r[0]=L.r[i];		//��L.r[i]�ݴ浽L.r[0] 
		low=1;
		high=i-1;
		while(low<=high){			//��r[low...high]���۰������������λ�� 
			m=(low+high)/2;			//�۰� 
			if(LT(L.r[0].key,L.r[m].key))		//������ڵͰ��� 
				high=m-1;
			else								//������ڸ߰��� 
				low=m+1;
		}
		for(int j=i-1;j>=high+1;--j)			//��¼���� 
			L.r[j+1]=L.r[j];
		L.r[high+1]=L.r[0];						//���� 
	} 
	return OK;
} 

//------------------------------��������------------------------------------------------- 
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

//----------------------------��������----------------------------------------------------- 
int Partition(SqList &L,int low,int high){
	//����˳���L���ӱ�r[low..high]�ļ�¼�������¼��λ��������������λ�ã���ʱ����ǰ(��)�ļ�¼������(С)���� 
	KeyType pivotkey;
	L.r[0]=L.r[low];				//���ӱ�ĵ�һ����¼�������¼ 
	pivotkey=L.r[low].key;			//�����¼�ؼ��� 
	while(low<high){				//�ӱ�����˽�������м�ɨ�� 
		while(low<high && L.r[high].key>=pivotkey)
			--high;
		L.r[low]=L.r[high];			//��������С�ļ�¼�Ƶ��Ͷ�
		while(low<high && L.r[low].key<=pivotkey) 
			++low;
		L.r[high]=L.r[low];			//���������ļ�¼�Ƶ��߶�
	} 
	L.r[low]=L.r[0];				//�����¼��λ 
	return low; 					//��������λ�� 
} 

void QSort(SqList &L,int low,int high){
	//��˳���L�е�������L.r[low..high]����������
	int pivotloc;
	if(low<high){		//���ȴ���1 
		pivotloc=Partition(L,low,high);		//��L.r[low...high]һ��Ϊ��
		QSort(L,low,pivotloc-1);			//�Ե��ӱ�ݹ�����pivotloc������λ�� 
		QSort(L,pivotloc+1,high); 			//�Ը��ӱ�ݹ����� 
	} 
} 

Status QuickSort(SqList &L){
	//��˳���L����������
	QSort(L,1,L.length); 
	return OK;
} 

//--------------------------------------��ѡ������------------------------------------ 
Status SelectSort(SqList &L){
	RcdType temp;
	int k;
	for(int i=1;i<L.length;++i){		//ѡ���iС�ļ�¼����������λ 
		k=i;
		for(int j=i+1;j<=L.length;++j)		//��L.r[i..L.lengh]��ѡ��key��С�ļ�¼ 
			if(L.r[k].key>L.r[j].key)
				k=j;
		if(i!=k){						//���k(j)����¼���� 
			temp=L.r[i];
			L.r[i]=L.r[k];
			L.r[k]=temp;
		} 
	}
	return OK;
} 

//------------------------------------������------------------------------------------------
//��ѡ�����������ѡ����������� 
typedef SqList HeapType;	//�Ѳ���˳���洢��ʾ 

void HeapAdjust(HeapType &H,int s,int m){
	//��֪H.r[s..m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵö��壬����������H.r[s]
	//�Ĺؼ��֣�ʹH.r[s..m]��Ϊһ���󶥶�(�����м�¼�Ĺؼ��ֶ���)
	RcdType rc;
	rc=H.r[s];
	for(int j=2*s;j<=m;j*=2){		//��key�ϴ�ĺ��ӽ������ɸѡ
		if(j<m && LT(H.r[j].key,H.r[j+1].key)) 
			++j;						//jΪkey�ϴ�ļ�¼���±�
	    if(!LT(rc.key,H.r[j].key))		//rcӦ����λ��s�� 
			break;
		H.r[s]=H.r[j];
		s=j; 
	}
	H.r[s]=rc; 
}

Status HeapSort(HeapType &H){
	//��˳���H���ж����� 
	int i;
	RcdType temp;
	for(i=H.length/2;i>0;--i)			//��H.r[1..H.length]���ɴ󶥶�
		HeapAdjust(H,i,H.length);
	for(i=H.length;i>1;--i){
		temp=H.r[1];				//����ջ��¼�͵�ǰδ������������HR[1..i]�����һ����¼���� 
		H.r[1]=H.r[i];
		H.r[i]=temp;
		HeapAdjust(H,1,i-1);		//��H.r[1..i-1]���µ���Ϊ�󶥶� 
	} 
	return OK;
}
 

//-----------------------------------2-·�鲢����-----------------------------------------------

void Merge(RcdType SR[],RcdType TR[],int i,int m,int n){
	//�������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
	int j,k;
	for(j=m+1,k=i;i<=m && j<=n;++k){		//��SR�м�¼��С����ز���TR 
		if(LQ(SR[i].key,SR[j].key))
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	} 
	if(i<=m){								//��ʣ���SR[i..m]���Ƶ�TR 
		for(int n1=k,n2=i;n1<=n && n2<=m; n1++,n2++)
			TR[n1]=SR[n2];
    }
	if(j<=n){								//��ʣ���SR[j..n]���Ƶ�TR
		for(int n1=k,n2=j;n1<=n && n2<=n; n1++,n2++)	
			TR[n1]=SR[n2];
	}
} 

void Msort(RcdType SR[],RcdType TR1[],int s,int t){
	//��SR[s..t]�鲢ΪTR1[s..t]��
	RcdType TR2[MAXSIZE];
	int m;
	if(s==t)
		TR1[s]=SR[s];
	else{
	    m=(s+t)/2;		//��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
		Msort(SR,TR2,s,m);			//�ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
		Msort(SR,TR2,m+1,t);		// �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
		Merge(TR2,TR1,s,m,t);		//��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t] 
	} 
}
Status MergeSort(SqList &L){
	//��˳���L���鲢����
	Msort(L.r,L.r,1,L.length);
	return OK; 
}

//---------------------------------------ϣ������--------------------------------------------------- 

void ShellInsert(SqList &L,int dk){
	//��˳���L��һ��ϣ�����򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ����������޸�
	//1��ǰ���¼λ��������dK��������1��
	//2��r[0]ֻ���ݴ浥Ԫ�������ڱ�����j<=0ʱ������λ�����ҵ���
	int j;
	for(int i=dk+1;i<=L.length;++i){
		if(LT(L.r[i].key,L.r[i-dk].key)){			//�轫L.r[i]�������������ӱ� 
			L.r[0]=L.r[i];							//�ݴ���L.r[0]
			for(j=i-dk; j>0 && LT(L.r[0].key,L.r[j].key);j-=dk)
				 L.r[j+dk]=L.r[j];					//��¼���ƣ����Ҳ���λ��
			L.r[j+dk]=L.r[0];						//���� 
		}
	} 
} 
//49 38 65 97 76 13 27 49 55 4
//Status ShellSort(SqList &L){
//	//����������dtla[0..t-1]��˳���L��ϣ������
//	int dlta[L.length];
//	for(int k=0;k<L.length;++k){
//		int t = L.length - k + 1;
//		printf("%d ",t);
//		dlta[k] = (int)pow(2.0,t)-1;
//		printf("%d\n",dlta[k]);
//	}
//	for(int k=0;k<L.length;++k){
//		ShellInsert(L,dlta[k]);			//һ������Ϊdlta[k]�Ĳ�������
//	} 
//	return OK; 
//} 

Status ShellSort(SqList &L){
	//����������dtla[0..t-1]��˳���L��ϣ������
	//��С��������,ֱ�Ӳ������������ 
	int dlta[] = {17,15,13,9,7,4,3,2,1};
	for(int k=0;k<L.length;++k){
		ShellInsert(L,dlta[k]);			//һ������Ϊdlta[k]�Ĳ�������
	} 
	return OK; 
}

//-----------------------------2_·��������-------------------------------------------
//�۰������������ϸĽ��� 
Status P2_InsertSort(SqList &L){											
	int i,j,first,final;
	RcdType d[MAXSIZE];					
	d[0]=L.r[1];											//��L�ĵ�1����¼Ϊd���ź���ļ�¼(��λ��[0]) 
	first=final=0;											//first��final�ֱ�ָʾd���ź���ļ�¼�ĵ�1�������1����¼��λ�� 
	for(i=2;i<=L.length;++i)
	{															//���ν�L�ĵ�2�������1����¼����d�� 
		if (L.r[i].key<d[first].key)
		{														//�����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d�����Ԫ��) 
			first=(first-1+L.length)%L.length;					//��dΪѭ������ 
			d[first]=L.r[i];
		}
		else if(L.r[i].key>d[final].key)
		{							//�����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d�����Ԫ��) 
			final=final+1;
			d[final]=L.r[i];
		}
		else{						//�����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��) 
			j=final++;				//�ƶ�d��β��Ԫ���Ա㰴������¼ 
			while(L.r[i].key<d[j].key)
			{
				d[(j+1)%L.length]=d[j];
				j=(j-1+L.length)%L.length;
			}
			d[j+1]=L.r[i];
		}
	}
	for(i=1;i<=L.length;i++) 					//��d����L.r 
		L.r[i]=d[(i+first-1)%L.length]; 		//���Թ�ϵ  
	return OK;
}

//----------------------------����ѡ������-----------------------------------
//��ѡ������ĸĽ�. 
Status TreeSort(SqList &L){
	int i,j,j1,k,k1,l,n=L.length;
	RcdType *t;
	
	l=(int)ceil(log(n)/log(2))+1; 				//��ȫ�������Ĳ��� 
	k=(int)pow(2,l)-1; 							//l����ȫ�������Ľ������  
	k1=(int)pow(2,l-1)-1; 						//l-1����ȫ�������Ľ������ 
	t=(RcdType*)malloc(k*sizeof(RcdType)); 		//����������˳��洢�ṹ  
	
	for(i=1;i<=n;i++) 							//��L.r����Ҷ�ӽ�� 
		t[k1+i-1]=L.r[i];
		
	for(i=k1+n;i<k;i++) 						//�������Ҷ�ӵĹؼ��ָ������ 
		t[i].key=INT_MAX;
		
	j1=k1;
	j=k;
	
	while(j1){ 									//����Ҷ�ӽ�㸳ֵ
		for(i=j1;i<j;i+=2)
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
		j=j1;
		j1=(j1-1)/2;
	}
	
	for(i=0;i<n;i++){
		L.r[i+1]=t[0]; 							//����ǰ��Сֵ����L.r[i] 
		j1=0;
		
		for(j=1;j<l;j++) 						//�������ҽ��t[0]��Ҷ���е����j1 
			t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		
		t[j1].key=INT_MAX;
		while(j1){
			j1=(j1+1)/2-1; 						//���Ϊj1�Ľ���˫�׽����� 
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	
	free(t);
	return OK;
}

//---------------------------------�ؼ��ֵļ�¼----------------------------------------- 

void Rearrange(SqList &L,int adr[]) 		//�Ĵ˾�(����) 
{	//adr������̬����L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼�� 
	//���㷨��adr����L.r��ʹ�������㷨10.18(L�������б�) 
	int i,j,k;
	for(i=1;i<L.length;++i)				//�Ĵ˾�(����) 
	if(adr[i]!=i)
	{
		j=i;
		L.r[0]=L.r[i];				//�ݴ��¼(*L).r[i] 
		while(adr[j]!=i){					//����(*L).r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ 
			k=adr[j];
			L.r[j]=L.r[k];
			adr[j]=j;
			j=k; 							//��¼����λ 
		}
		L.r[j]=L.r[0];
		adr[j]=j;
	}
}

void Menu(void)
{
	printf("\t\t             ========================        \n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |--------|     �����ڲ�����      |-------|\n");
	printf("\t\t   |        |                       |       |\n");
	printf("\t\t   |         ========================       |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |            ��ѡ����Ĳ�������        |\n");
	printf("\t\t   |            [1]˳���Ĵ���             |\n");
	printf("\t\t   |            [2]ֱ�Ӳ�������             |\n");
	printf("\t\t   |            [3]�۰��������             |\n");
	printf("\t\t   |            [4]��������(��������)       |\n");
	printf("\t\t   |            [5]��������                 |\n");
	printf("\t\t   |            [6]��ѡ������             |\n");
	printf("\t\t   |            [7]������                   |\n");
	printf("\t\t   |            [8]2-·�鲢����             |\n");
	printf("\t\t   |            [9]ϣ������                 |\n");
	printf("\t\t   |            [10]2_·��������            |\n");
	printf("\t\t   |            [11]����ѡ������            |\n");
	printf("\t\t   |            [12]�˳�                    |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 ��ӭ�޸�               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("��ѡ����Ҫ���еĲ���(1/2/3/4/5/6/7/8/9/10/11/12):");
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
					printf("�����ɹ���\n"); 
				Menu();
				break;
			case 2:
				printf("ֱ�Ӳ��������Ľ��Ϊ��\n");
				InsertSort(L);
				PrintSqList(L);
				Menu();
				break;
			case 3:
				printf("�۰���������Ľ��Ϊ��\n");
				BInsertSort(L); 
				PrintSqList(L);
				Menu();
				break;	
			case 4:
				printf("���������Ľ��Ϊ��\n");
				BubbleSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 5:
				printf("���������Ľ��Ϊ��\n");
				QuickSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 6:
				printf("��ѡ�������Ľ��Ϊ��\n");
				SelectSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 7:
				printf("�������Ľ��Ϊ��\n");
				HeapSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 8:
				printf("�鲢�����Ľ��Ϊ��\n");
				MergeSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 9:
				printf("ϣ�������Ľ��Ϊ��\n");
				ShellSort(L);
				PrintSqList(L);
				Menu();
				break;
			case 10:
				printf("2_·���������Ľ��Ϊ��\n");
				P2_InsertSort(L);
				PrintSqList(L);
				Menu();
				break;	
			case 11:
				printf("����ѡ�������Ľ��Ϊ��\n");
				TreeSort(L);
				PrintSqList(L);
				Menu();
				break;
			default:
				printf("��������,����������!\n");
				Menu();
				break;		
		}
		scanf("%d",&i);
	} 
	return 0;
}
