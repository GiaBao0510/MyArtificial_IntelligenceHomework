#include<stdio.h>
#include<stdlib.h>
#define tankCapacity_x 9	//Dung tich chua binh X la 9 lit
#define tankCapacity_y 4	//Dung tich chua binh Y la 4 lit
#define empty 0				//La rong
#define goal 6				//Muc tieu can dong nuoc
#define Maxlength 100
//Khai bao cau truc trang thai
typedef struct{
	int x,	//Luong nuoc trong binh X
		y;	//Luong nuoc trong binh Y
}state;
//Khoi tao
void MakeNullState(state *st){
	st->x = st->y = 0;
}
//In trang thai
void PrintState(state st){
	printf("\n[X]: %d \t [Y]: %d",st.x,st.y);
}
//So sanh hai trang thai xem chung co bang nhau hay khong
int compareState(state A,state B){
	return (A.x == B.x && A.y == B.y);
}
//Kiem tra luong nuoc trong binh X co dung voi muc tieu chua
int goalCheck(state st){
	return (st.x == 6);
}
//Cac hanh dong tren hai binh X va Y(current la trang thai hien tai con result la trang thai duoc luu sao khi thuc hien cac phep toan)
	//1. lam day binh X
	int fillTankX(state current,state *result){
		//Neu binh X chua day thi do day binh X
		if(current.x < tankCapacity_x){
			result->x = tankCapacity_x;
			result->y = current.y;
			return 1;
		}
		return 0;	//That bai
	}
	//2. lam day binh Y
	int fillTankY(state current,state *result){
		if(current.y < tankCapacity_y){
			result->y = tankCapacity_y;
			result->x = current.x;
			return 1;
		}
		return 0;
	}
	//3. Lam rong binh X
	int emptyTheJarX(state current,state *result){
		//Neu binh X chua rong thi lam rong
		if(current.x > empty){
			result->x = empty;
			result->y = current.y;
			return 1;
		}
		return 0;	//That bai
	}
	//4.Lam rong binh Y
	int emptyTheJarY(state current,state *result){
		if(current.y > empty){
			result->y = empty;
			result->x = current.x;
			return 1; 
		}
		return 0;
	}
		//Ham max va ham Min
	int max(int a,int b){
		return (a>b)? a:b;
	}	
	int min(int a,int b){
		return (a<b)? a:b;
	}
	//5.Do binh X sang binh Y
	int pourJarX_into_JarY(state current,state *result){
		//Neu binh nuoc X khong rong va binh Y chua day
		if(current.x > empty && current.y < tankCapacity_y){
			//Neu ket qua cua binh X la am thi dat no la rong
			result->x = max(current.x - (tankCapacity_y - current.y),empty);
			//Neu ket qua binh Y lon hon suc chua thi dat binh Y la day
			result->y = min(current.x + current.y , tankCapacity_y);
		}
	}
	//6. Do binh Y sang binh X
	int pourJarY_into_JarX(state current,state *result){
		if(current.y > empty && current.x < tankCapacity_x){
			result->y = max(current.y - (tankCapacity_x - current.x),empty);
			result->x = min(current.x + current.y, tankCapacity_x);
		}
	}
//Goi cac phep toan trang thai(current: la trang thai hien tai; result: la trang thai ket qua; option: la thu tu cac phep toan duoc dung)
int call_operator(state current,state *result,int option){
	switch(option){
		case 1: return fillTankX(current,result);
		case 2: return fillTankY(current,result);
		case 3: return emptyTheJarX(current,result);
		case 4: return emptyTheJarY(current,result);
		case 5: return pourJarX_into_JarY(current,result);
		case 6: return pourJarY_into_JarX(current,result);
		default: printf("Error calls operators");
		return 0;
	}
}
//Dinh nghia hang chuoi in ra cac hanh dong
const char *action[] = {"First state","Fill tank X","Fill tank Y","Empty the jar X",
"Empty the jar Y","Pour jar X into jar Y","Pour jar Y into jar X"};	
//Cau truc dinh de xay dung cay tim kiem
typedef struct Node{
	state st;				//Luu tru trang thai trong binh
	struct Node *parent;	//Luu tru cha cua trang thai hien tai
	int no_function;		//Luu tru so cua hang dong da thuc hien
}Node;
//Cau truc ngan xep de luu trang thai da duyet/ dang duyet
typedef struct{
	Node *Element[Maxlength];
	int topindex;
}stack;
//Lam ngan xep rong
void MakeNullStack(stack *S){
	S->topindex = Maxlength;
}
//Kiem tra ngan xep co rong khong
int EmptyStack(stack S){
	return S.topindex == Maxlength;
}
//Kiem tra ngan xep co day khong
int FullStack(stack S){
	return S.topindex == 0;
}
//them phan tu X vao ngan xep
void PushStack(Node *x, stack *S){
	if(FullStack(*S)){
		printf("\nNgan xep day.");
	}else{
		S->topindex--;
		S->Element[S->topindex];
	}
}
//Xoa phan tu o dau ngan xep
void PopStack(stack *S){
	if(EmptyStack(*S)){
		printf("\nNgan xep rong.");
	}else{
		S->topindex++;
	}
}
//Lap phan tu o dau ngan xep
Node* Top(stack S){
	if(EmptyStack(S)){
		printf("\nNgan xep rong.");
		return NULL;
	}else{
		return S.Element[S.topindex];
	}
}
//Kiem tra xem trang thai da ton tai trong ngan sep hay chua
int find_state(state st,stack open){
	while(!EmptyStack(open)){
		//Ta so sanh hai trang hai .Neu bang nhau thi no da ton tai trong ngan xep
		if(compareState(Top(open)->st, st) == 1){
			return 1;
		}
		PopStack(&open);
	}
	return 0;
}
//Duyet theo chieu sau trong cay tim kiem trang thai
Node *DFS(state State){
	//Khai bao StackOpen va StackClosed
	stack open,closed;
	MakeNullStack(&open);
	MakeNullStack(&closed);
	//Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));//cap phat bo nho
	root->st = State;
	root->parent = NULL;
	root->no_function = 0;
	//Day nut dau vao Ngan xep Open
	PushStack(root,&open); 
	while(!EmptyStack(open)){
		//Lay 1 dinh trong ngan xep ra
		Node *node = Top(open);
		PopStack(&open);
		PushStack(node,&closed);
		//Kiem tra xem dinh vua lay ra co phai la nut goc khong
		if(goalCheck(node->st)){
			return node;
		}
		int opt;
		//Goi cac phep toan trang thai tren
		for(opt = 1;opt<=6;opt++){
			state newST;
			MakeNullState(&newST);
			if(call_operator(node->st,&newST,opt)){
				//Neu trang thai nay da ton tai trong open hoac closed thi bo qua
				if(find_state(newST,open) || find_state(newST,closed)){
					continue;
				}
				//Neu la trang thai moi thi bo vao danh sach open
				Node *newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->parent = node;
				newNode->st = newST;
				PushStack(newNode,&open);
			}
		}		
	}
	return NULL;
}
//In ket qua chuyen nuoc dat den muc tieu
void print_waysToGetGoal(Node *node){
	stack StackPrint;
	MakeNullStack(&StackPrint);
	//Duyet nguoc ve cha
	while(node->parent!=NULL){
		PushStack(node,&StackPrint);
		node = node->parent;
	}
	PushStack(node,&StackPrint);
	int no_Action;
	//In ra thu tu hanh dong chuyen nuoc
	while(!EmptyStack(StackPrint)){
		printf("\nAction[%d]: %s ",no_Action,action[Top(StackPrint)->no_function]);
		PrintState(Top(StackPrint)->st);
		PopStack(&StackPrint);
		no_Action++;
	}
} 
int main(){
	state current;
	current.x=0;
	current.y=0;
	Node *p = DFS(current);
	print_waysToGetGoal(p);
	return 0;
}
