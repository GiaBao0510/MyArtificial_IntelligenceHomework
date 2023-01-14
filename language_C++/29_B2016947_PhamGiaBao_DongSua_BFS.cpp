#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;
#define tankCapacity_A 10
#define tankCapacity_B 5
#define tankCapacity_C 6
#define Empty 0
#define goal 8
//Cau truc luu tru trang thai
	typedef struct{
		int a,b,c;
	}state;
	//Khoi tao: ban dau binh A chua day binh va cac binh con lai thi rong
	void stateInitialization(state *st){
		st->a = tankCapacity_A;
		st->b = st->c = Empty;
	}
	//Hien thi trang thai
	void PrintState(state st){
		printf("\n[A]: %d -- [B]: %d -- [C]: %d",st.a,st.b,st.c);
	}
	//sao chep trang thai khac
	void CopyOtherState(state current,state *result){
		result->a = current.a;
		result->b = current.b;
		result->c = current.c;
	}
	//So sanh 2 trang thai
	int CompareState(state X,state Y){
		return (X.a == Y.a && X.b == Y.b && X.c == Y.c);
	}
	//Gan tung trang thai vao tung ly
	void AssignState(state *st,int x,int y,int z){
		st->a = x;
		st->b = y;
		st->c = z;
	}
	//Kiem tra trang thai dich
	int CheckGoal(state st){
		return (st.a == goal);
	}
//Ham min va max
	int max(int a,int b){
		return (a>b)? a:b;
	}
	int min(int a,int b){
		return (a<b)? a:b;
	}
//Cac phep toan
	//1.Do binh A sang binh B
	int pourJarA_intoJarB(state current,state *result){
		//Neu binh A chua rong a binh B chua day
		if(current.a > Empty && current.b < tankCapacity_B){
			result->a = max(current.a - (tankCapacity_B - current.b),Empty);
			result->b = min(current.a + current.b,tankCapacity_B);
			result->c = current.c;
			return 1;
		}
		return 0;
	}
	//2.Do binh A sang binh C
	int pourJarA_intoJarC(state current,state *result){
		if(current.a > Empty && current.c < tankCapacity_C){
			result->a = max(current.a - (tankCapacity_C - current.c),Empty);
			result->c = min(current.a + current.c,tankCapacity_C);
			result->b = current.b;
			return 1;
		}
		return 0;
	}
	//3.Do binh B sang A
	int pourJarB_intoJarA(state current,state *result){
		//Neu binh B chua rong va binh A chua day 
		if(current.b > Empty && current.a < tankCapacity_A){
			result->b = max(current.b - (tankCapacity_A - current.a), Empty);
			result->a = min(current.b + current.a, tankCapacity_A);
			result->c = current.c;
			return 1;
		}
		return 0;
	}
	//4.Do binh B sang C
	int pourJarB_intoJarC(state current,state *result){
		//Neu binh B chua rong va binh C chua day 
		if(current.b > Empty && current.c < tankCapacity_C){
			result->b = max(current.b - (tankCapacity_C - current.c), Empty);
			result->c = min(current.b + current.c, tankCapacity_C);
			result->a = current.a;
			return 1;
		}
		return 0;
	}
	//5.Do binh C sang binh A
	int pourJarC_intoJarA(state current,state *result){
		//Neu binh C chua rong va binh A chua day
		if(current.c > Empty && current.a < tankCapacity_A){
			result->c = max(current.c - (tankCapacity_A - current.a),Empty);
			result->a = min(current.c + current.a,tankCapacity_A);
			result->b = current.b;
			return 1;
		}
		return 0;
	}
	//6.Do binh C sang binh B
	int pourJarC_intoJarB(state current,state *result){
		if(current.c > Empty && current.b < tankCapacity_B){
			result->c = max(current.c - (tankCapacity_B - current.b),Empty);
			result->b = min(current.c + current.b,tankCapacity_B);
			result->a = current.a;
			return 1;
		}
		return 0;
	}
//Ham goi hanh dong
	int CallOperation(state current,state *result,int opt){
		switch(opt){
			case 1: return pourJarA_intoJarB(current,result);
			case 2: return pourJarA_intoJarC(current,result);
			case 3: return pourJarB_intoJarA(current,result);
			case 4: return pourJarB_intoJarC(current,result);
			case 5:  return pourJarC_intoJarA(current,result);
			case 6: return pourJarC_intoJarB(current,result);
			default: printf("\nLoi goi hanh dong khong hop le.");
			return 0;
		}
	}
//Cau truc nut de luu tru duong di
	#define maxlength 100
	struct tree{
		state TH;
		int option;
		struct tree *next;
	};
	typedef struct tree *node;
	//Khoi tao nut
	node makeNullNode(){
		node head = NULL;
		return head;
	}
	//gan gia tri vao 1 nut
	node createNode(state ST,int opt){
		node temp = (node)malloc(sizeof(node));
		temp->TH = ST;
		temp->option = opt;
		temp->next = NULL;
		return temp;
	}
	//Day nut vao dau danh sach lien ket
	node pushNode(node head,state ST,int opt){
		node temp = createNode(ST,opt);
		if(head == NULL){
			head= temp;
		}else{
			temp->next = head;
			head = temp;
		}
		return head;
	}
//Kiem tra trang thai co ton tai trong ngan xep khong
	int checkStateInQueue(queue<node> S,state X){
		while(!S.empty()){
			if(CompareState(S.front()->TH, X) == 1){
				return 1;//tim thay
			}
			else{
				S.pop();
			}
		}
		return 0; //khong tim thay
	}
//Mang dien ta hanh dong
const char *action[] = {"Trang thai dau","Do binh A sang binh B","Do binh A sang binh C","Do binh B sang binh A",
"Do binh B sang binh C","Do binh C sang binh A","Do binh C sang binh B"};
//Giai bai toan
	node DFS(state result){
		//Tao cac bien
		queue<node> open,closed;
		int opt;
		state current;
		node root;
		//Khoi tao
		root = makeNullNode();
		stateInitialization(&result);
		//Gan trang thai dau vao nut root
		root = pushNode(root,result,0);
		//Day nut goc vao ngan xep open
		open.push(root);
		//lap
		while(!open.empty()){
			//Lay trang thai dau ra khoi ngan xep open va day vao closed
			node Fnode = open.front();
			open.pop();
			closed.push(Fnode);
			CopyOtherState(Fnode->TH,&current);
			//printf("\n\n\t\tDuyet: [A]: %d -- [B]: %d -- [C]: %d\n",current.a,current.b,current.c);
			//Kiem tra co phai trang thai dich khong
			if(CheckGoal(Fnode->TH) == 1){
				return Fnode;
			}
			//Goi cac hanh dong
			for(opt = 1; opt <=6; opt++){
				//goi hanh dong cu the
				//printf("\n\n%d.Xet:",opt);
				if(CallOperation(current,&result,opt) == 1){
					//PrintState(result);
					if(checkStateInQueue(open,result) == 1 || checkStateInQueue(closed,result) == 1){
						continue; //Da ton tai => bo qua
					}
					//printf("\n------------Trang thai moi: ");
					//PrintState(result);
					node Snode = (node)malloc(sizeof(node));
					Snode->TH = result;
					Snode->option = opt;
					Snode->next = Fnode;
					//Day vao danh sach open
					open.push(Snode);
				}
			}
		}
	}
	//Cau truc luu ket qua
	typedef struct{
		state ST;
		int opt;
	}KetQua;
	void cachGiai(node P){
		node Q;
		int num=0;
		KetQua KQ[maxlength];
		for(Q = P; Q != NULL ; Q = Q->next){
			CopyOtherState(Q->TH,&KQ[num].ST);
			KQ[num].opt = Q->option;
			num++;
		}
		int i;
		for(i=num-1;i>=0;i--){
			printf("\n%s:",action[KQ[i].opt]);
			PrintState(KQ[i].ST);
		}
	}
int main(){
	state h1,h2;
	node P = DFS(h1);
	cachGiai(P);
}
