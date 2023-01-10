#include<stdio.h>
#include<stdlib.h>
#include<stack>					//Them thu vien ngan xep(trong c++)
using namespace std; 			//La 1 goi chua cac thuc the duoc dung trong c++
#define MaximunSizeOfBottle_X 9	//kich co toi da cua binh x
#define MaximunSizeOfBottle_Y 4	//kich co toi da cua binh y
#define Empty 0
#define goal 6
typedef struct{
	int x,	//Trang thai binh X 
		y;	//Trang thai binh Y
}state;
//Ham xay dung	
	//Ham lam khoi tao trang thai
	void makeNullState(state *ST){
		ST->x = ST->y = 0; //binh rong
	}
	//ham gan gia tri vao tran gthai
	void assignState(state *ST,int A,int B){
		ST->x = A;
		ST->y = B;
	}
	//Ham sao chep trang thai khac
	void copyOtherState(state current,state *result){
		result->x = current.x;
		result->y = current.y;
	}
//In trang thai
	void printState(state ST){
		printf("\n[X]: %d -- [Y]: %d",ST.x,ST.y);
	}
//So sanh xem hai trang thai co giong nhau khong?
	int compareSate(state A,state B){
		return (A.x == B.x && A.y == B.y);
	}
//Ham max va min
	int max(int a,int b){
		return (a>b)? a:b;
	}
	int min(int a,int b){
		return (a<b)? a:b;
	}
//Cac hanh dong{current: chi ra trang thai hien tai cua cac binh nuoc; result: dung de luu ket trang thai}
	//1.Lam day binh X
	int fillingBottle_X(state current,state *result){
		if(current.x < MaximunSizeOfBottle_X){ //neu binh X chua day
			result->x = MaximunSizeOfBottle_X;
			result->y = current.y;
			return 1;
		}
		return 0;
	}
	//2.Lam day binh Y
	int fillingBottle_Y(state current,state *result){
		if(current.y < MaximunSizeOfBottle_Y){	//Neu binh Y chua day
			result->y = MaximunSizeOfBottle_Y;
			result->x = current.x;
			return 1;
		}
		return 0;
	}
	//3.Lam rong binh X
	int emptyTheBottle_X(state current,state *result){
		if(current.x > Empty){	//Neu bunh X chua rong
			result->x = Empty;
			result->y = current.y;
			return 1;
		}
		return 0;
	}
	//4.Lam rong binh Y
	int emptyTheBottle_Y(state current,state *result){
		if(current.y > Empty){
			result->y = Empty;
			result->x = current.x;	
			return 1;
		}
		return 0;
	}
	//5.Do binh X sang binh y
	int poutJar_X_into_Jar_Y(state current,state *result){
		//Neu binh X khong rong va binh Y chua day
		if(current.x > Empty && current.y < MaximunSizeOfBottle_Y){
			result->x = max(current.x - (MaximunSizeOfBottle_Y - current.y) , Empty);
			result->y = min(current.x + current.y, MaximunSizeOfBottle_Y);
			return 1;
		}
		return 0;
	}
	//6.Do binh Y sang binh X
	int poutJar_Y_into_Jar_X(state current,state *result){
		//Neu binh Y khong rong va binh X chua day
		if(current.y > Empty && current.x < MaximunSizeOfBottle_X){
			result->y = max(current.y - (MaximunSizeOfBottle_X  - current.x), Empty);
			result->x = min(current.x + current.y,MaximunSizeOfBottle_X);
			return 1;
		}
		return 0;
	}
//Ham kiem tra co phai la dich can tim hay khong
	int checkGoal(state A){
		return (A.x == goal);
	}
//Ham goi hanh dong
	int callOpenration(state current, state *result,int opt){
		switch(opt){
			case 1: return fillingBottle_X(current,result); 	// Lam day X
			case 2: return fillingBottle_Y(current,result); 	//lam day y
			case 3: return emptyTheBottle_X(current,result); 	// lam rong X
			case 4: return emptyTheBottle_Y(current,result); 	//Lam rong Y
			case 5: return poutJar_X_into_Jar_Y(current,result);//Do X sang Y
			case 6: return poutJar_Y_into_Jar_X(current,result);//Do Y sang X
			default: printf("\n!Loi goi hanh dong khong hop le.");
			return 0;
		}
	}
//Ham dien ta hanh dong
	const char *action[] = {"Trang thai ban dau","Lam day binh X","Lam day binh Y","Lam rong binh X",
"Lam rong binh Y","Do binh X sang binh Y","Do binh Y sang binh X"};
//Cau truc luu tru duong di
	struct tree{
		state TH;
		int operation;	//Hanh dong so may
		struct tree* next;
	};
	typedef struct tree* node;
	//Khoi tao nut
	node makeNullNode(){
		node head;
		head = NULL;
		return head;
	}
	//Gan gia tri cho 1 nut
	node createNode(state ST,int opt){
		node temp = (node)malloc(sizeof(node));
		temp->operation =opt;
		temp->TH = ST;
		temp->next = NULL;
		return temp;
	}
	//Day nut vao dau danh sach lien ket
	node addHead(node head,state ST,int opt){
		node temp = createNode(ST,opt);
		if(head == NULL){
			head = temp;
		}else{
			temp->next = head;
			head = temp;
		}
		return head;
	}
//Ham tim xep trang thai co trong ngan xep khong?
	int FindState(state ST,stack<node> NX){
		while(!NX.empty()){//Su dung phuong thuc kiem tra ngan xep rong 
			if(compareSate(NX.top()->TH,ST) == 1){
				return 1;
			}else{
				NX.pop();
			}
		}
		return 0;
	}
//Giai bai toan
	node DFS(state result){
		//Tao bien
		stack<node> open,closed;
		node root;
		int opt;
		//Khoi tao
		root = makeNullNode();
		makeNullState(&result);
		//Cap nhat cha
		root = addHead(root,result,0);
		//Day nut dau tien vao ngan xep open
		open.push(root);
		//Lap
		while(!open.empty()){
			//Lay diem dau ra khoi open va day vao closed
			node Fnode = open.top();
			open.pop();
			closed.push(Fnode);
			printf("\n\n\t\tDuyet: [A]: %d -- [B]: %d\n",Fnode->TH.x,Fnode->TH.y);
			//Kiem tra dieu kien
			if(checkGoal(Fnode->TH) == 1){
				return Fnode;
			}
			//Goi cac phep toan
			for(opt = 1;opt<=6;opt++){
				state current ;
				makeNullState(&current);
				printf("\n\thanh dong thu: %d",opt);
				//Goi lan luot tung trang thai
				if(callOpenration(Fnode->TH,&current,opt) == 1){
					//Da ton tai trang thai nay roi
					if(FindState(current,open) == 1 || FindState(current,closed) == 1){
						continue;
					}
					printf("\n------------Trang thai moi:");
					printState(current);
					node Snode = (node)malloc(sizeof(node));
					Snode->TH = current;
					Snode->operation = opt;
					Snode->next = Fnode;
					open.push(Snode);
				}
			}
		}	
		return NULL; 
	}
//In Duong di
	void cachGiai(node P){
		stack<node> ds;
		node Q;
		for(Q  =P;Q!=NULL;Q = Q->next){
			ds.push(Q);
		}
		while(!ds.empty()){
			printf("\n%s: [A]: %d -- [B]: %d",action[ds.top()->operation],ds.top()->TH.x,ds.top()->TH.y);
			ds.pop();
		} 
	}
int main(){
	state h1;
	node P = DFS(h1);
	cachGiai(P);
	return 0;
}
