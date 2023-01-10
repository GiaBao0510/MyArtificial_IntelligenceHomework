#include<stdio.h>
#include<stdlib.h>
#define maxBinhX 9
#define maxBinhY 4
#define empty 0
#define goal 6
typedef struct{
	int x,
		y;
}state;
//Khoi tao
void makeNullState(state *ST){
	ST->x = ST->y = 0;
}
//Hien thi trang thai
void printState(state ST){
	printf("\n[X]: %d -- [Y]: %d",ST.x,ST.y);
}
//Gan gia tri vao trang thai
void assignState(state *ST,int a,int b){
	if(a <= maxBinhX && b <= maxBinhY){
		ST->x = a;
		ST->y = b;
	}
}
//Sao chep trang thai khac
void copyOtherState(state *main,state temp){
	main->x = temp.x;
	main->y = temp.y;
}
//So sanh giua 2 trang thai 
int compareState(state A,state B){
	return (A.x == B.x && A.y == B.y);
}
//Ham goal
int checkGoal(state X){
	return (X.x == goal);
}
/*	current: la  trang thai hien hanh dung de cua cac binh dang xet
	result: la trang thai dung de luu ket qua*/
//Ham max va min
int Max(int a,int b){
	return (a>b)? a:b;
}
int Min(int a,int b){
	return (a<b)? a:b;
}	 
//1.Lam day binh X
void fullBottle_X(state current,state *result){
	result->x = maxBinhX;
	result->y = current.y;
}
//2.Lam day binh Y
void fullBottle_Y(state current,state *result){
	result->y = maxBinhY;
	result->x = current.x;
}
//3.Lam rong binh X
void emptyBottle_X(state current,state *result){
	result->x = empty;
	result->y = current.y;
}
//4.Lam rong binh Y
void emptyBottle_Y(state current,state *result){
	result->y = empty;
	result->x = current.x;
}
//5.Do binh X sang binh Y
void pourJarX_intoJarY(state current,state *result){
	//neu binh X chua rong va binh Y chua day
	if(current.x > empty && current.y < maxBinhY){
		result->x = Max(current.x - (maxBinhY - current.y) , empty);
		result->y = Min(current.x + current.y, maxBinhY);
	}else{
		copyOtherState(result,current);
	}
}
//6.Do binh Y sang binh X
void pourJarY_intoJarX(state current,state *result){
	//neu binh Y chua rong va binh X chua day
	if(current.y > empty && current.x < maxBinhX){
		result->y = Max(current.y - (maxBinhX - current.x) , empty);
		result->x = Min(current.x + current.y, maxBinhX);
	}else{
		copyOtherState(result,current);
	}
}
//Mang action dung de mieu ta hang dong
const char* action[] = {"First state","pour water full X","pour water full Y","pour water empty X",
"pour water empty Y","pour water X to Y","pour water Y to X"};
	//Cau truc dung de xay dung cay trang thai
	struct Tree{
		state st;
		int option;
		struct Tree *parent;
	};
	typedef struct Tree *node;
	//Khoi tao
	node MakeNullNode(){
		node head;
		head = NULL;
		return head;
	}
	//Gan gia tri vao nut
	node createNode(state ST,int opt){
		node temp;
		temp = (node)malloc(sizeof(node));
		temp->option = opt;
		temp->st = ST;
		temp->parent = NULL;
		return temp;
	}
	//Day nut vao cuoi danh sach
	node pushNode(node head,state ST,int opt){
		node temp = createNode(ST,opt);
		if(head == NULL){
			head = temp;
		}else{
			node P = head;
			while(P->parent != NULL){
				P = P->parent;
			}
			P->parent = temp;
		}
		return head;
	}
	//Ngan xep dung de luu cac trang thai
	#define maxlength 100
	typedef struct{
		node data[maxlength];
		int top;
	}stack;
	//Ngan xep rong
	void makeNullStack(stack *S){
		S->top = maxlength;
	} 
	//Kiem tra ngan xep rong
	int emptyStack(stack s){
		return s.top == maxlength;
	}
	//Kiem tra ngan xep day
	int fullStack(stack s){
		return s.top == 0;
	}
	//Them 1 nut vao trong ngan xep
	void pushStack(stack *S, node x){
		if(fullStack(*S)){
			printf("\nNgan xep day\n");
			return;
		}else{
			S->top--;
			S->data[S->top] = x;
		}
	}
	//Lay 1 phan tu ra khoi ngan xep
	void popStack(stack *S){
		if(emptyStack(*S)){
			printf("\nNgan xep rong\n");
			return;
		}else{
			S->top++;
		}
	}
	//Xem phan tu o dau ngan xep
	node TopIndex(stack S){
		if(emptyStack(S)){
			printf("\nNgan xep rong\n");
			return NULL;
		}else{
			return S.data[S.top];
		}
	}
	//Ham so sanh xem trang thai da ton tai trong ngan xep chua
	int compareStateStack(stack S, state X){
		while(!emptyStack(S)){
			if(compareState(S.data[S.top]->st,X) == 1){
				return 1;//tim thay
			}
			popStack(&S);
		}
		return 0;
	}
	//Giai bai toan theo chieu sau
	node DFS(state ST){
		int vl=0;
		//Cac bien ho tro
		node root;
		state temp;
		stack open,closed;	//Open: luu nut dang duyet, Closed: luu nut da duyet
		//1.Khoi tao
		makeNullStack(&open);
		makeNullStack(&closed);
		makeNullState(&ST);
		makeNullState(&temp);
		root = MakeNullNode();
		//2.Cap nhat cha
		root = pushNode(root,ST,0);//Co trang thai dau la 0
		//3.Them nut day vao ngan xep
		pushStack(&open,root);
		//4. Lap khi nao gap dich hoac ngan xep rong thi ngung			
		while(!emptyStack(open)){
			//Lay dinh dau ra khoi open
			node Fnode = TopIndex(open); 
			//printf("\n\n\t\t\tDuyet: [A]: %d -- [B]: %d\n",Fnode->st.x,Fnode->st.y);
			popStack(&open);
			pushStack(&closed,Fnode);
			//2.Kiem tra phai la dinh thi dung lai
			if(checkGoal(Fnode->st) == 1){
				return Fnode; //dung . Tra ve danh sach lien ket da luu tru trang thai
			}
			//3. thuc hien cac phep toan
				//1.Lam day binh X
			fullBottle_X(Fnode->st,&ST);
			copyOtherState(&temp,ST);
			//printf("\n%d.Lam day binh X: [A]: %d -- [B]: %d",vl,temp.x,temp.y);
			//Neu so sanh trang thai khong co trong ngan xeop open hay closed thi la trang thai moi
			if(compareStateStack(open,temp) != 1 && compareStateStack(closed,temp) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",temp.x,temp.y);
				//Cap nhat trang thai cha
				node Snode = (node)malloc(sizeof(node));	//Cap phat bo nho
				Snode->st = temp;							//Them trang thai moi
				Snode->option=1;							//Hanh dong lam day binh X
				Snode->parent = Fnode;						//Cha cua no la Fnode
				//Day vao ngan xep open
				pushStack(&open,Snode); 
			}
				//2.Lam day binh Y
			fullBottle_Y(Fnode->st,&ST);
			copyOtherState(&temp,ST);
			//printf("\n%d.Lam day binh Y: [A]: %d -- [B]: %d",vl,temp.x,temp.y);
			//Neu so sanh trang thai khong co trong ngan xeop open hay closed thi la trang thai moi
			if(compareStateStack(open,temp) != 1 && compareStateStack(closed,temp) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",temp.x,temp.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->st = temp;
				Snode->option=2;
				Snode->parent = Fnode;
				pushStack(&open,Snode); //Day vao ngan xep open
			}
				//3.Lam rong binh X
			emptyBottle_X(Fnode->st,&ST);
			copyOtherState(&temp,ST);
			//printf("\n%d.Lam day rong X: [A]: %d -- [B]: %d",vl,temp.x,temp.y);
			//Neu so sanh trang thai khong co trong ngan xeop open hay closed thi la trang thai moi
			if(compareStateStack(open,temp) != 1 && compareStateStack(closed,temp) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",temp.x,temp.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->st = temp;
				Snode->option=3;
				Snode->parent = Fnode;
				pushStack(&open,Snode); //Day vao ngan xep open
			}
				//4.Lam rong binh Y
			emptyBottle_Y(Fnode->st,&ST);
			copyOtherState(&temp,ST);
			//printf("\n%d.Lam rong binh Y: [A]: %d -- [B]: %d",vl,temp.x,temp.y);
			//Neu so sanh trang thai khong co trong ngan xeop open hay closed thi la trang thai moi
			if(compareStateStack(open,temp) != 1 && compareStateStack(closed,temp) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",temp.x,temp.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->st = temp;
				Snode->option=4;
				Snode->parent = Fnode;
				pushStack(&open,Snode); //Day vao ngan xep open
			}
				//5.Do binh X vao binh Y
			pourJarX_intoJarY(Fnode->st,&ST);
			copyOtherState(&temp,ST);
			//printf("\n%d.Do binh X vao binh Y: [A]: %d -- [B]: %d",vl,temp.x,temp.y);
			//Neu so sanh trang thai khong co trong ngan xeop open hay closed thi la trang thai moi
			if(compareStateStack(open,temp) != 1 && compareStateStack(closed,temp) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",temp.x,temp.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->st = temp;
				Snode->option=5;
				Snode->parent = Fnode;
				pushStack(&open,Snode); //Day vao ngan xep open
			}
				//6.Do binh Y vao binh X
			pourJarY_intoJarX(Fnode->st,&ST);
			copyOtherState(&temp,ST);
			//printf("\n%d.Do binh Y vao binh X: [A]: %d -- [B]: %d",vl,temp.x,temp.y);
			//Neu so sanh trang thai khong co trong ngan xeop open hay closed thi la trang thai moi
			if(compareStateStack(open,temp) != 1 && compareStateStack(closed,temp) != 1){
				//printf("\n\t----Trang thai moi: [A]: %d -- [B]: %d",temp.x,temp.y);
				node Snode = (node)malloc(sizeof(node));
				Snode->st = temp;
				Snode->option=6;
				Snode->parent = Fnode;
				pushStack(&open,Snode); //Day vao ngan xep open
			}
			vl++;	  
		}
		return NULL;//Khong tim thay phuong an
	}
	//In duong di
	void duongDi(node root){
		//Su dung ngan xep de luu ket qua
		stack KQ;
		makeNullStack(&KQ);
		node Q = (node)malloc(sizeof(node));
		for(Q = root; Q != NULL ; Q = Q->parent){
			pushStack(&KQ,Q);
		}
		//In ket qua
		while(!emptyStack(KQ)){
			printf("\n%s: [A]: %d -- [B]: %d",action[KQ.data[KQ.top]->option],KQ.data[KQ.top]->st.x,KQ.data[KQ.top]->st.y);
			popStack(&KQ);
		}
	}
int main(){
	state h1,h2;
	node P = DFS(h1);
	duongDi(P);
	return 0;
}
