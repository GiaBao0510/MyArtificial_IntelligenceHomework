#include<stdio.h>
#include<stdlib.h>
#define MaxBottle_X 9
#define MaxBottle_Y 4
#define goal 6
#define empty 0
typedef struct{
	int x,	//Trang thai binh X
		y;	//Trang thai binh Y
}state;
//Khoi tao
void MakeNullState(state *S){
	S->x = S->y = empty;
}
//In trang thai
void PrintState(state S){
	printf("\n[A]: %d -- [B]: %d",S.x,S.y);
}
//kiem tra phai trang thai dich
int CheckGoal(state S){
	return (S.x == goal);
}
//Gan gia tri vao trang thai
void AssignState(state *S, int X, int Y){
	S->x = X;
	S->y = Y;
}
//Copy trang thai khac
void CopyOtherState(state *result, state current){
	result->x = current.x;
	result->y = current.y;
}
//So sanh hai trang thai
int CompareState(state A, state B){
	return(A.x == B.x && B.y == A.y);
}
//Ham Max va ham min
int max(int a,int b){
	return (a>b)? a:b;
}
int min(int a,int b){
	return (a<b)? a:b;
}
		//Cac hanh dong
	//1. La day binh X
	void BottleFilling_X(state current,state *result){
		result->x = MaxBottle_X;
		result->y = current.y;
	}
	//2. lam day binh Y
	void BottleFilling_Y(state current,state *result){
		result->y = MaxBottle_Y;
		result->x = current.x;

	}
	//3. Lam rong binh X
	void emptyTheBollte_X(state current,state *result){
		result->x = empty;
		result->y = current.y;
	}
	//4.Lam rong binh Y
	void emptyTheBollte_Y(state current,state *result){
		result->y = empty;
		result->x = current.x;

	}
	//5.Do binh X sang binh Y
	void PourJarX_intoJarY(state current,state *result){
		//Neu binh X khac rong va binh Y chua day
		if(current.x > empty && current.y < MaxBottle_Y){
			result->x = max(current.x - (MaxBottle_Y - current.y), empty);
			result->y = min(current.x + current.y, MaxBottle_Y);
		}else{
			CopyOtherState(result,current);
		}
	}
	//6.Do binh Y sang binh X
	void PourJarY_intoJarX(state current,state *result){
		if(current.y > empty && current.x < MaxBottle_X){
			result->y = max(current.y - (MaxBottle_X - current.x), empty);
			result->x = min(current.x + current.y, MaxBottle_X);
		}else{
			CopyOtherState(result,current);
		}
	}
	//Hien thi thao tac hang dong
	const char *action[] = {"Trang thai dau","Lam day binh X","Lam day binh Y","Lam rong binh X",
"Lam rong binh Y","Do binh X sang binh Y","Do binh Y sang binh X"};
	//Cau truc xay dung cay duong di trang thai
	struct tree{
		int option;	//So cua hanh dong
		struct tree *parent;
		state TH;
	};
	typedef struct tree *node;
	//Khoi tao nut
	node makeNullNode(){
		node head;
		head = NULL;
		return head;
	}
	//Tao 1 nut
	node CreateNode(state st,int opt){
		node temp;
		temp = (node)malloc(sizeof(node));
		temp->TH = st;
		temp->option= opt;
		temp->parent = NULL;
		return temp;
	}
	//Them 1 nut vao dau danh sach
	node AddHead(node head,state st,int opt){
		node temp= CreateNode(st,opt);
		if(head == NULL){
			head = temp;
		}else{
			temp->parent = head;
			head = temp;
		}
		return head;
	}
	//Hang doi luu tru cac nut
	#define maxlength 100
	typedef struct{
		int front,rear;
		node data[maxlength];
	}Queue;
	//Khoi tao
	void MakeNullQueue(Queue *Q){
		Q->front = Q->rear = -1;
	}
	//Kiem hang doi co rong khong
	int EmptyQueue(Queue Q){
		return (Q.front < 0 || Q.rear < 0);
	}
	//Kiem tra hang doi co day khong
	int FullQueue(Queue Q){
		return (Q.rear - Q.front + 1)%maxlength == 0;
	}
	//them nut vao hang doi
	void InsertQueue(node X, Queue *Q){
		if(FullQueue(*Q)){
			printf("\nHang doi day\n");
		}else{
			if(EmptyQueue(*Q)){
				Q->front++;
			}
			(Q->rear+=1)%maxlength;
			Q->data[Q->rear] = X;
		}
	}
	//Xoa phan tu khoi hang doi
	void deleteQueue(Queue *Q){
		if(EmptyQueue(*Q)){
			printf("\nHang doi rong\n");
		}else{
			if(Q->rear == Q->front){
				MakeNullQueue(Q);
			}else{
				(Q->front+=1)%maxlength;
			}	
		}
	}
	//In phan tu dau
	node Front(Queue Q){
		return Q.data[Q.front];
	}
	//Kiem tra xem trang thai co trong hang doi khong
	int compareStateInTheQueue(Queue Q,state X){
		while(!EmptyQueue(Q)){
			if(CompareState(Front(Q)->TH,X) == 1){
				return 1;
			}
			deleteQueue(&Q);
		}
		return 0;//khong tim thay
	}
	//GB
	node BFS(state ST){
		//Bien ho tro
		node root;
		Queue open,closed;
		int vl;
		//KHoi tao
		root = makeNullNode();
		MakeNullQueue(&open);
		MakeNullQueue(&closed);
		MakeNullState(&ST);
		//Cap nhat nut goc
		root = AddHead(root,ST,0);
		//Day nut dau tien vao hang doi
		InsertQueue(root,&open);
		//Lap
		while(!EmptyQueue(open)){
			//lay trang thai dau ra khoi phan tu
			node Fnode = Front(open);
			//printf("\n\n\t\tDuyet: [A]: %d -- [B]: %d\n",Fnode->TH.x,Fnode->TH.y);
			deleteQueue(&open);
			InsertQueue(Fnode,&closed);
			//Kiem tra dieu kien
			if(CheckGoal(Fnode->TH) == 1){
				return Fnode;
			}
			//Cac phep toan
				//1.Lam day binh X
			BottleFilling_X(Fnode->TH,&ST);
			//printf("\n%d.Lam day binh X: [A]: %d -- [B]: %d",vl,ST.x,ST.y);
			if(compareStateInTheQueue(open,ST) != 1 && compareStateInTheQueue(closed,ST) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",ST.x,ST.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->option = 1;
				Snode->TH = ST;
				Snode->parent =Fnode;
				InsertQueue(Snode,&open);
			}
				//2.Lam day binh Y
			BottleFilling_Y(Fnode->TH,&ST);
			//printf("\n%d.Lam day binh Y: [A]: %d -- [B]: %d",vl,ST.x,ST.y);
			if(compareStateInTheQueue(open,ST) != 1 && compareStateInTheQueue(closed,ST) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",ST.x,ST.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->option = 2;
				Snode->TH = ST;
				Snode->parent =Fnode;
				InsertQueue(Snode,&open);
			}	
				//3.Lam rong binh X
			emptyTheBollte_X(Fnode->TH,&ST);
			//printf("\n%d.Lam rong binh X: [A]: %d -- [B]: %d",vl,ST.x,ST.y);
			if(compareStateInTheQueue(open,ST) != 1 && compareStateInTheQueue(closed,ST) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",ST.x,ST.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->option = 3;
				Snode->TH = ST;
				Snode->parent =Fnode;
				InsertQueue(Snode,&open);
			}
				//4.Lam rong binh Y
			emptyTheBollte_Y(Fnode->TH,&ST);
			//printf("\n%d.Lam rong binh Y: [A]: %d -- [B]: %d",vl,ST.x,ST.y);
			if(compareStateInTheQueue(open,ST) != 1 && compareStateInTheQueue(closed,ST) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",ST.x,ST.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->option = 4;
				Snode->TH = ST;
				Snode->parent =Fnode;
				InsertQueue(Snode,&open);
			}
				//5.Do binh X sang binh Y
			PourJarX_intoJarY(Fnode->TH,&ST);
			//printf("\n%d.Do binh X sang binh Y: [A]: %d -- [B]: %d",vl,ST.x,ST.y);
			if(compareStateInTheQueue(open,ST) != 1 && compareStateInTheQueue(closed,ST) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",ST.x,ST.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->option = 5;
				Snode->TH = ST;
				Snode->parent =Fnode;
				InsertQueue(Snode,&open);
			}
				//6.Do binh X sang binh Y
			PourJarY_intoJarX(Fnode->TH,&ST);
			//printf("\n%d.Do binh Y sang binh X: [A]: %d -- [B]: %d",vl,ST.x,ST.y);
			if(compareStateInTheQueue(open,ST) != 1 && compareStateInTheQueue(closed,ST) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",ST.x,ST.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->option = 6;
				Snode->TH = ST;
				Snode->parent =Fnode;
				InsertQueue(Snode,&open);
			}
			vl++;
		}
		return NULL;
	}
	//In duong di
	typedef struct{
		state st;
		int option;
	}KetQua;
	void duongDi(node P){
		KetQua KQ[maxlength];
		int dem=0;
		node vl;
		for(vl = P;vl != NULL ;vl= vl->parent){
			KQ[dem].st.x = vl->TH.x;
			KQ[dem].st.y = vl->TH.y;
			KQ[dem].option = vl->option;
			dem++;
		}
		int i;
		for(i=dem-1;i>=0;i--){
			printf("\n%s [A]: %d -- [B]: %d",action[KQ[i].option],KQ[i].st.x,KQ[i].st.y);
		}
	}
int main(){
	node P;
	state h1;
	P = BFS(h1);
	duongDi(P);
	return 0;
}
