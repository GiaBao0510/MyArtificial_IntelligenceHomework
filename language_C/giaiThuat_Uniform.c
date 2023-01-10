#include<stdio.h>
#include"tvCTDLvGT.h"
#define maxvertices 50
typedef struct{
	int n,m;
	int L[maxvertices][maxvertices];
}Graph;
//Khoi tao
void createGraph(Graph *G){
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			G->L[i][j]=0;
		}
	}
}
//Them cung
void AddEdges(Graph *G,int u,int v,int w){
	G->L[u][v]=w;
}
//Doc do thi tu file
void readGraphFromFile(Graph *G){
	FILE *f = fopen("dataGraph.txt","r");
	fscanf(f,"%d %d",&G->n,&G->m);//Doc dinh va cung
	createGraph(G);	//Khoi tao ma gran
	int i,u,v,w;
	for(i=1;i<=G->m;i++){
		fscanf(f,"%d %d %d",&u,&v,&w);
		AddEdges(G,u,v,w);
	}
	fclose(f);
}
//In ma tran
void PrintGraph(Graph G){
	int i,j;
	printf("\n\tMa tran cap %d:",G.n);
	for(i=1;i<=G.n;i++){
		printf("\n%d: ",i);
		for(j=1;j<=G.n;j++){
			printf("%3d",G.L[i][j]);
		}
	}
}
//Hang doi uu tien
	#define maxlength 100
	typedef struct{
		int vertice[maxlength];	//Dinh
		int value[maxlength];	//Gia tri tai dinh
		int front,rear;
	}PQueue;
	//1.Tao hang doi
	void makeNullQueue(PQueue *PQ){
		PQ->front = PQ->rear =-1;
	}
	//2.Kiem tra hang doi co rong khong
	int emptyPQueue(PQueue PQ){
		return (PQ.front == -1 || PQ.rear == -1);
	}
	//3.Kiem tra han doi day
	int fullPQueue(PQueue PQ){
		return (PQ.rear - PQ.front +1)%maxlength == 0;
	}
	//4.Xoa dau hang doi
	void deletePQueue(PQueue *PQ){
		if(emptyPQueue(*PQ) == 1){
			printf("\nHang doi rong.Khong the xoa");
		}else{
			if(PQ->front == PQ->rear){
				makeNullQueue(PQ);
			}else{
				PQ->front=(PQ->front+1)%maxlength;
			}
		}
	}
	//Ham Hoan doi vi tri cac gia tri trong hang doi
	void Swap(int *A,int *B){
		int temp = *A;
		*A = *B;
		*B = temp;
	}
	//Ham sap xep noi bot
	void bubbleSortPriorityQueue(PQueue *PQ){
		int i,j;
		for(i=PQ->front ; i != PQ->rear;i++){
			for(j=PQ->rear ; j>i ; j--){
				if(PQ->value[j-1] > PQ->value[j]){//So sanh gia tri tai 2 dinh 
					Swap(&PQ->vertice[j-1],&PQ->vertice[j]);	//Hoan doi vi tri dinh
					Swap(&PQ->value[j-1],&PQ->value[j]);//Hoan doi gia tri tal dinh
				}
			}
		}
	}
	//5.Them dinh x co gia tri v vao cuoi hang doi
	void EnterPQueue(int x,int v,PQueue *PQ){
		if(fullPQueue(*PQ)==1){
			printf("\nHang doi day.Khong the them");
		}else{
			if(emptyPQueue(*PQ) == 1){
				PQ->front = 0;
			}
			PQ->rear=(PQ->rear+1)%maxlength;
			PQ->vertice[PQ->rear]=x;
			PQ->value[PQ->rear]=v;	
			bubbleSortPriorityQueue(PQ);//Sap xep lai cac gia tri ben trong hang doi uu tien
		}
	}
	//6.Tra ve dinh
	int FrontVertice(PQueue PQ){
		return PQ.vertice[PQ.front];	
	}
	//7.Tra va vi tri cua dinh
	int FrontValue(PQueue PQ){
		return PQ.value[PQ.front];	
	}
//Danh sach cac nua bac ngoai cua dinh x
list NuaBacNgoai(Graph G,int x){
	list ds;
	makeNullList(&ds);
	int i;
	for(i=1;i<=G.n;i++){
		if(G.L[x][i]!=0){
			InsertList(i,endList(ds),&ds);
		}
	}
	return ds;
}
//Xem cac nua bac ngoai cua cac dinh
void DSNuaBacNgoai(Graph G){
	int i,j;
	for(i=1;i<=G.n;i++){
		list DS = NuaBacNgoai(G,i);
		printf("\n%d: ",i);
		for(j=firstList(DS) ; j!=endList(DS) ; j=next(j,DS)){
			printf("%3d",retrieve(j,DS));
		}
	}
}	
//Cac bien ho tro
	#define infinity 9999999
	typedef struct{
		int pi,		//Luu tru gia tri duong di tu cua dinh
			P,		//Luu tru cha cua dinh
			mark;	//Danh dau dinh duoc duyet hay khong
	}SupportVariable;
	SupportVariable SV[maxvertices];
//Giai thuat tim kiem gia thanh dong nhat
	list GT(Graph G,int s){
		list dskq;	//Luu tru ket qua da duyet
		PQueue PQ;	//Hang doi
		//Khoi tao
		makeNullList(&dskq);
		makeNullQueue(&PQ);
		int i;
		for(i=1;i<=G.n;i++){
			SV[i].mark=0;		//Ban dau tat ca cac dinh deu khong co nhan
			SV[i].pi=infinity;
			SV[i].P=-1;			//Ban dau tat ca cac dinh deu khong co cha
		}
		//Bat dau voi dinh S
		SV[s].P=0;
		SV[s].pi=0;//Diem xuat phat
		EnterPQueue(s,SV[s].pi,&PQ);	//them dinh s vao hang doi
		//Bat dau duyet
		while(!emptyPQueue(PQ)){
			int dinhU = FrontVertice(PQ),//lay diem ra khoi hang doi
				gtriU = FrontValue(PQ);//Gia tri tai dinh do
			deletePQueue(&PQ);
			//1.Kiem tra xem dinh nay co duoc duyet hay chua
			if(SV[dinhU].mark == 1){
				continue;
			}
			//2.Neu chua duyet thi ta duyet no
			SV[dinhU].mark = 1;
			InsertList(dinhU,endList(dskq),&dskq);
			//3.Kiem tra xem cac dinh ke cua no co duoc duyet hay khong
			list dske = NuaBacNgoai(G,dinhU);
			int v,dinhV;
			for(v=firstList(dske) ; v!=endList(dske) ; v=next(v,dske)){
				dinhV = retrieve(v,dske);
				if(SV[dinhV].mark == 0 && SV[dinhV].pi > (gtriU+G.L[dinhU][dinhV]) ){
					SV[dinhV].pi = (gtriU+G.L[dinhU][dinhV]); //Cap nhat lai
					SV[dinhV].P = dinhU; //Cap phat cha
					EnterPQueue(dinhV,SV[dinhV].pi,&PQ);
				}
			}
		}
		return dskq;
	}
			
int main(){
	Graph G;
	readGraphFromFile(&G);
	PrintGraph(G);
	int i;
	list L = GT(G,1);
	printf("\n");
	for(i = firstList(L) ; i != endList(L) ; i = next(i,L)){
		printf("%3d ",retrieve(i,L));
		if(i < endList(L)-1){
			printf(" ->");
		}
	}
	printf("\n\tChi Tiet: ");
	for(i=1;i<=G.n;i++){
		printf("\n[%d]. pi: %d - P: %d",i,SV[i].pi,SV[i].P);
	}
	return 0;
}
/*Code cuc vai von luon may ong a*/
