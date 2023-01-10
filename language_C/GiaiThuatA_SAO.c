#include<stdio.h>
#include"tvCTDLvGT.h"
	#define MaxVertices 100
	#define negativeIfinity -9999999
	typedef struct{
		int n,	//Dinh
			m;	//Cung
		int L[MaxVertices][MaxVertices];	
	}Graph;
	//Khoi tao ma tran
	void createGraph(Graph *G){
		int i,j;
		for(i=1;i<=G->n;i++){
			for(j=1;j<=G->n;j++){
				G->L[i][j]=0;
			}
		}
	}
	//Them cung
	void addEdge(Graph *G,int u,int v,int w){
		G->L[u][v]=w;
	}
	//Kiem tra lien ke
	int checkNeighBour(Graph G,int u,int v,int w){
		return G.L[u][v]!=0;
	}
	//Cau truc luu tru trang thai cua tung dinh
	typedef struct{
		float g[MaxVertices],			//Luu tru khoang cach tu dinh goc den dinh dang xet
			h[MaxVertices],			//Luu tru gia tri cua cac dinh
			f[MaxVertices];			//F = h + g
		int	parent[MaxVertices],	//Luu tru cha cua cac dinh
			mark[MaxVertices];		//Danh dau trang thai cua cac dinh: 
			/* -1: chua co trong open va closed
				0: co trong open
				1: co trong closed
			*/
	}element;
	//Doc do thi tu file
	void readFromFile(Graph *G,element *E){
		FILE *f = fopen("dataGraphA_star.txt","r");
		fscanf(f,"%d %d",&G->n,&G->m);
		//Khoi tao ma tran
		createGraph(G);
		int i,u,v,w;
		//Doc so cung
		for(i=1;i<=G->m;i++){
			fscanf(f,"%d %d %d",&u,&v,&w);
			addEdge(G,u,v,w);
		} 
		//Doc gia tri cac dinh .Dong thoi khoi tao cac yeu to cua dinh
		float gtri;
		for(i=1;i<=G->n;i++){
			fscanf(f,"%f",&gtri);
			E->h[i] = gtri;
			E->f[i]=0;
			E->g[i]=0;
			E->mark[i] = -1;
			E->parent[i] = -1;
		}
		fclose(f);
	}
	//In ma tran
	void printGraph(Graph G){
		int i,j;
		printf("\n\tMa tran cap %d",G.n);
		for(i=1;i<=G.n;i++){
			printf("\n%d:",i);
			for(j=1;j<=G.n;j++){
				printf("%3d",G.L[i][j]);
			}
		}
	}
	//In cac yeu to cua cac dinh
	void PrintElement(Graph G,element E){
		int i;
		printf("\n\n\tDinh\tg\th\tf\tp\tmark\n");
		for(i=1;i<=G.n;i++){
			printf("\n\t%d:\t%.2f\t%.2f\t%.2f\t%d\t%d",i,E.g[i],E.h[i],E.f[i],E.parent[i],E.mark[i]);
		}
	}
	//Luu tat ca cac dinh ke cua 1 dinh
	list dinhKe(Graph G,int x){
		int i;
		list ds;
		makeNullList(&ds);
		for(i=1;i<=G.n;i++){
			if(G.L[x][i]!=0){
				InsertList(i,endList(ds),&ds);
			}
		}
		return ds;
	}
	//Liet ke cac dinh ke cua 1 dinh
	void lietKeCacDinhKe(Graph G){
		int i,j;
		for(i=1;i<=G.n;i++){
			list ds = dinhKe(G,i);
			printf("\n%d:",i);
			for(j=firstList(ds);j!=endList(ds);j=next(j,ds)){
				printf("%3d",retrieve(j,ds));
			}
		}
	}
	//Giai thuat A*
	void GT_A_sao(Graph G,element *E,int start,int end){
		//1.Khoi tao voi dinh bat dau
		E->mark[start] = 0;	//O trong open
		E->f[start] = E->g[start] + E->h[start];
		E->parent[start] = 0; //Dinh root
		//2.Day dinh start vao danh sach
		list DS;
		makeNullList(&DS);
		InsertList(start,endList(DS),&DS);
		//3.Khong biet so lan lap
		do{
			// Neu danh sach rong thi dung
			if(emptyList(DS)){
				break;
			}
			else{
				//Tim dinh trong open va co Fmin
				int i,Fmin,dinhTam,vitri;
				for(i=firstList(DS);i!=endList(DS);i=next(i,DS)){
					int ptu = retrieve(i,DS);
					Fmin = negativeIfinity;
					if(E->f[ptu] > Fmin){
						Fmin = E->f[ptu];
						dinhTam = ptu;
						vitri=i;
						//printf("\n\tVi tri: %d - dinh tam: %d - Fmin: %d - ptu: %d",vitri,dinhTam,Fmin,ptu);
					}
	
				}
				//printf("\n\t\tDinh duoc chon: %d\n",dinhTam);
				//Danh dau duyet dinh tam
				E->mark[dinhTam] = 1;
				deleteList(vitri,&DS);//Lay dinh tam ra khoi danh sach
				//Tim dinh ke cua dinh tam
				list dsKe = dinhKe(G,dinhTam);
				for(i=firstList(dsKe); i!=endList(dsKe);i=next(i,dsKe)){
					int V =retrieve(i,dsKe);
					float G0;
					//Neu V khong co trong open hay close
					if(E->mark[V] == -1){
						G0 = E->g[dinhTam] + G.L[dinhTam][V];
						E->g[V] = G0;
						E->f[V] = E->g[V] + E->h[V];
						E->parent[V] = dinhTam;	//Cap nhat cha
						//Dua vao open
						E->mark[V] = 0; 
						InsertList(V,endList(DS),&DS);
					}
					//Neu V thuoc open hoac closed
					if(E->mark[V] == 0 || E->mark[V] == 1){
						G0 = E->g[dinhTam] + G.L[dinhTam][V];
						//Cap nhat lai
						if(G0 < E->g[V]){
							E->g[V] = G0;
							E->f[V] = E->g[V] + E->h[V];
							//Cap nhat cha va dua vao open
							E->parent[V] = dinhTam;
							E->mark[V]=0;
							InsertList(V,endList(DS),&DS);
						}
					}
				}
			}
		}while(1); 
	}
int main(){
	Graph G;
	element E;
	readFromFile(&G,&E);
	printGraph(G);
	PrintElement(G,E);
//	int s,e;
//	printf("\n\nNhap dinh bat dau: "); scanf("%d",&s);
//	printf("Nhap dinh can tim: "); scanf("%d",&e);
//	GT_A_sao( G, &E, s, e);
	GT_A_sao( G, &E, 1, G.n);
	PrintElement(G,E);
	return 0;
}
