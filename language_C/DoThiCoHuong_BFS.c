#include<stdio.h>
#include"tvCTDLvGT.h"
#define maxvertices 50
typedef struct{
	int n,m;
	int A[maxvertices][maxvertices];
}graph;
//Khoi tao
void MakeNullGraph(graph *G){
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			G->A[i][j]=0;
		}
	}
}
//Them cung do thi co huong
void addEdges(graph *G,int u,int v,int w){
	G->A[u][v]=w;
}
//Nhap
void ReadGraphFromFile(graph *G){
	FILE *f = fopen("dataGraph.txt","r");
	fscanf(f,"%d %d",&G->n,&G->m);//Doc dinh va cung
	MakeNullGraph(G);	//Khoi tao do thi
	int i=1,u,v,w;
	for(i;i<=G->m;i++){
		fscanf(f,"%d %d %d",&u,&v,&w);
		addEdges(G,u,v,w);
	}
	fclose(f);
}
//In do thi
void printGraph(graph G){
	int i,j;
	for(i=1;i<=G.n;i++){
		printf("%d: ",i);
		for(j=1;j<=G.n;j++){
			printf("%3d",G.A[i][j]);
		}
		printf("\n");
	}
}
//Danh sach nua bac ngoai cua dinh x
list nuaBacNgoai(int x,graph G){
	list l;
	makeNullList(&l);
	int i;
	for(i=1;i<=G.n;i++){
		if(G.A[x][i]!= 0){
			InsertList(i,endList(l),&l);
		}
	}
	return l;
}
//Danh sach nua bac ngoai cua tat ca cac dinh
void dsNuaBacNgoai(graph G){
	int i,j;
	printf("\n\tDanh sach nua bac ngoai cua cac dinh:\n\n");
	for(i=1;i<=G.n;i++){
		list DS = nuaBacNgoai(i,G);
		printf("%d: ",i);
		for(j=firstList(DS) ; j!=endList(DS) ; j=next(j,DS)){
			printf("%3d",retrieve(j,DS));
		}
		printf("\n");
	}
}
//Danh sach luu cac dinh da duyet theo chieu rong bat dau tu dinh x nao do
list BFS(int x,graph *G,int parent[]){
	//1.Khoi tao tat ca cac dinh dieu chua duoc duyet
	int i,mark[G->n];
	for(i=1;i<=G->n;i++){
		mark[i]=0;
	}
	list dsDD; //Danh sach cac dinh da duoc duyet
	makeNullList(&dsDD);
	Queue hd;	//Dung hang doi de duyet cac dinh theo chieu rong
	makeQueue(&hd);
	//2.Dua dinh bat dau vao stack va cap phat cha cho no
	enterQueue(&hd,x);
	parent[x] = 0;//Day la dinh bat dau
	while(!emptyQueue(hd)){
		//1.Lay dinh dau trong hang doi ra
		int u = front(hd); 
		deleteQueue(&hd);
		//2.Kiem tra xem no da duoc duyet chua.Neu da duyet roi thi bo qua cac cau lenh ben duoi
		if(mark[u] == 1){
			continue;
		}
		//3.Neu chua duoc duyet thi.Ta duyet no, dua vao danh sach va kiem tra cac dinh xung quanh de dua vao hang doi va duyet no
		mark[u] = 1;
		InsertList(u,endList(dsDD),&dsDD);
		list NBN = nuaBacNgoai(u,*G);
		int v;
		for(v=firstList(NBN) ; v !=endList(NBN) ; v=next(v,NBN)){
			if(mark[retrieve(v,NBN)]==0){//Neu dinh ke chua duyet thi dua vao Hang doi
				enterQueue(&hd,retrieve(v,NBN));
				parent[retrieve(v,NBN)] = u;//Cap phat cha
			}
		} 
	}
	//Tra ve danh sach da duoc duyet
	return dsDD;
}
int main(){
	graph G;
	ReadGraphFromFile(&G);
	printGraph(G);
	int parent[G.n];
	//Khoi tao vet cua cac dinh
	int i;
	for(i=1;i<=G.n;i++){
		parent[i] = -1;
	}
	printf("\nThu tu cac dinh da duyet theo chieu rong:\n");
	list duyet = BFS(1,&G,parent);
	for(i=firstList(duyet) ; i != endList(duyet) ; i=next(i,duyet)){
		printf("\n%d.Duyet: %d",i,retrieve(i,duyet));
	}
	printf("\n\tCha cua cac dinh:\n");
	for(i=1;i<=G.n;i++){
		printf("\n%d: %d",i,parent[i]);
	}
}
