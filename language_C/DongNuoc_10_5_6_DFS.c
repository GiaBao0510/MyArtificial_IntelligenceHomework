#include<stdio.h>
#include<stdlib.h>
#define tankCapacity_A 10	//Suc chua binh A la 10
#define tankCapacity_B 5	//Suc chua binh B la 5
#define tankCapacity_C 6	//Suc chua binh C la 6
#define empty 0
#define goal 8
//Cau truc trang thai
	typedef struct{
		int A,B,C;
	}state;
	//Khoi tao
	void makeNullState(state *st){
		st->A = 10;
		st->B = st->C = 0;
	}
	//Gan gia tri
	void assignState(state *st,int x,int y,int z){
		st->A = x;
		st->B = y;
		st->C = z;
	}
	//Copy trang thai khac
	void copyOtherState(state current,state *result){
		result->A = current.A;
		result->B = current.B;
		result->C = current.C;
	}
	//In trang thai
	void printState(state st){
		printf("\n[A]: %d --- [B]: %d --- [C]: %d",st.A,st.B,st.C);
	}
	//Kiem trang trang thai dich
	int checkGoal(state st){
		return (st.A == goal);
	}
	//So sanh hai trang thai
	int compareState(state X,state Y){
		return (X.A == Y.A && X.B == Y.B && X.C == Y.C);
	}
//Ham min & max
	int max(int a,int b){
		return (a>b)? a:b;
	}
	int min(int a,int b){
		return (a<b)? a:b;
	}	
//Cac phep toan
	//1.Do binh A vao binh B
	int pourBottleA_intoBottleB(state current,state *result){
		//Neu binh A khong rong va binh b chua day
		if(current.A > empty && current.B < tankCapacity_B){
			result->A = max(current.A - (tankCapacity_B - current.B),empty);
			result->B = min(current.A + current.B, tankCapacity_B);
			result->C = current.C;
			return 1;
		}
		return 0;
	}
	//2.Do binh A vao binh C
	int pourBottleA_intoBottleC(state current,state *result){
		//Neu binh A khong rong va binh C chua day
		if(current.A > empty && current.C < tankCapacity_C){
			result->A = max(current.A - (tankCapacity_C - current.C),empty);
			result->C = min(current.A + current.C, tankCapacity_C);
			result->B = current.B;
			return 1;
		}
		return 0;
	}
	//3.Do binh B vao binh A
	int pourBottleB_intoBottleA(state current,state *result){
		//Neu binh B khong rong va binh a chua day
		if(current.B > empty && current.A < tankCapacity_A){
			result->B = max(current.B - (tankCapacity_A - current.A),empty);
			result->A = min(current.B + current.A , tankCapacity_A);
			result->C = current.C;
			return 1;
		}
		return 0;
	}
	//4.Do binh B vao binh C
	int pourBottleB_intoBottleC(state current,state *result){
		//Neu binh B khong rong va binh c chua day
		if(current.B > empty && current.C < tankCapacity_C){
			result->B = max(current.B - (tankCapacity_C - current.C),empty);
			result->C = min(current.B + current.C , tankCapacity_C);
			result->A = current.A;
			return 1;
		}
		return 0;
	}
	//5. do binh C vao binh A
	int pourBottleC_intoBottleA(state current,state *result){
		//Neu binh C khong rong va binh A chua Day
		if(current.C > empty && current.A < tankCapacity_A){
			result->C = max(current.C - (tankCapacity_A - current.A) , empty);
			result->A = min(current.C + current.A,tankCapacity_A);
			result->B = current.B;
			return 1;
		}
		return 0;
	}
	//6. do binh C vao binh B
	int pourBottleC_intoBottleB(state current,state *result){
		//Neu binh C khong rong va binh B chua Day
		if(current.C > empty && current.B < tankCapacity_B){
			result->C = max(current.C - (tankCapacity_B - current.B) , empty);
			result->B = min(current.C + current.B,tankCapacity_B);
			result->A = current.A;
			return 1;
		}
		return 0;
	}
//Bien toan cuc dung de dien ta hanh dong
	const char *action[] = {"Trang thai dau","Do binh A sang binh B","Do binh A sang binh C","Do binh B sang binh A","Do binh B sang binh C","Do binh C sang binh A","Do binh C sang binh B"};
//Ham goi hanh dong
	int callOperation(state current,state *result,int opt){
		switch(opt){
			case 1: return pourBottleA_intoBottleB(current,result);
			case 2: return pourBottleA_intoBottleC(current,result);
			case 3: return pourBottleB_intoBottleA(current,result);
			case 4: return pourBottleB_intoBottleC(current,result);
			case 5: return pourBottleC_intoBottleA(current,result);
			case 6: return pourBottleC_intoBottleB(current,result);
			default: printf("\nLoi");
			return 0;
		}
	}
//Cau truc cau luu truu duong di
	struct tree{
		state TH;
		int operation;
		struct tree *next;
	};
	typedef struct tree *node;
	//khoi tao
	node makeNullNode(){
		node head = NULL;
		return head; 
	}
	//Gan gia tri vao nut
	node createNode(state St,int opt){
		node temp = (node)malloc(sizeof(node));
		temp->TH = St;
		temp->operation = opt;
		temp->next = NULL;
		return temp;
	}
	//Chen nut vao dau danh sach lien ket
	node insertHead(node head,state St,int opt){
		node tam = createNode(St,opt);
		if(head == NULL){
			head = tam;
		}else{
			tam->next = head;
			head = tam;
		}
		return head;
	}
//Ngan xep
	#define maxlength 100
	typedef struct{
		int top;
		node data[maxlength];
	}stack;
	//Khoi tao
	void makeNull(stack *S){
		S->top = maxlength;
	}
	//Kiem tra ngan xep rong
	int Empty(stack S){
		return S.top == maxlength;
	}
	//Kiem tra ngan xep day
	int full(stack S){
		return S.top == 0;
	}
	//Day 1 phan tu vao ngan xep
	void push(stack *S,node X){
		if(full(*S)){
			printf("\nNgan xep day\n");
		}else{
			S->top--;
			S->data[S->top] = X;
		}
	}
	//Xoa 1 phan tu ra khoi ngan xep
	void pop(stack *S){
		if(Empty(*S)){
			printf("\nNgan xep rong\n");
		}else{
			S->top++;
		}
	}
	//Lay phan tu dau ngan xep
	node top(stack S){
		return S.data[S.top];
	}
	//Kiem tra trang thai da ton tai trong ngan xep
	int compareStateInStack(stack S,state X){
		while(!Empty(S)){
			if(compareState(X, top(S)->TH) == 1){
				return 1;	//Da ton tai
			}else{
				pop(&S);
			}
		}
		return 0; //Khong ton tai
	}
//Duyet Bai toan theo chieu sau
	node DFS(state result){
		//Them bien
		node root;
		stack open,closed;
		state current;
		int opt;
		//Khoi tao
		makeNullState(&result);
		root = makeNullNode();
		makeNull(&open);
		makeNull(&closed);
		//Cap phat cho nut root
		root = insertHead(root,result,0);
		//Them nut root vao danh sach open
		push(&open,root);
		//lap
		while(!Empty(open)){
			//lay nut dau ra khoi open ,Dua vao closed
			node Fnode = top(open);
			pop(&open);
			push(&closed,Fnode);
			//Kiem tra dieu kien
			if(checkGoal(Fnode->TH) == 1){
				return Fnode;
			}
			//Sao chep trang thai hien tai
			copyOtherState(Fnode->TH,&current);
			printf("\n\n\t\tDuyet [A]: %d -- [B]: %d --- [C]: %d\n",current.A,current.B,current.C);
			//Goi cac hanh dong
			for(opt = 1;opt <=6;opt ++){
				//Hanh dong hop le
				printf("\nLap %d",opt);
				if(callOperation(current,&result,opt) == 1){
					printf("\n\tXet trang thai: [A]: %d -- [B]: %d --- [C]: %d",result.A,result.B,result.C);
					//Kiem tra xem co phai trang thai moi
					if(compareStateInStack(open,result) == 1 || compareStateInStack(closed,result) == 1){
						continue; 
					}
					printf("\n\t-------trang thai moi: [A]: %d -- [B]: %d --- [C]: %d",result.A,result.B,result.C);
					node Snode = (node)malloc(sizeof(node));
					Snode->TH = result;
					Snode->operation = opt;
					Snode->next = Fnode;
					//day nut co trang thai moi vao danh sach open
					push(&open,Snode);
				}
			}
		}
		return NULL; //khong tim thay
	}
	//In duong di
	void cachGiai(node P){
		stack KQ;
		makeNull(&KQ);
		for(P;P != NULL; P = P->next){
			push(&KQ,P);
		}
		while(!Empty(KQ)){
			printf("\n%s: ",action[top(KQ)->operation]);
			printState(top(KQ)->TH);
			pop(&KQ);
		}
	}		
int main(){
	state h1,h2,h3;
	node P;
	P = DFS(h1);
	cachGiai(P);
}
