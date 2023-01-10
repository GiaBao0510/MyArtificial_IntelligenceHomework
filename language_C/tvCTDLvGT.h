#include<stdio.h>
/*---------Cau truc du lieu--------------*/
	#define maxlength 100
	#define TRONG -9999
	typedef int ViTri; 
	//1.Hang doi
		typedef struct{
			int data[maxlength];
			ViTri front,rear;
		}Queue;
		//Khoi tao
		void makeQueue(Queue *Q){
			Q->front = 0;
			Q->rear = -1;
		}
		//Kiem tra hang doi rong
		int emptyQueue(Queue Q){
			return Q.front > Q.rear;
		}
		//Tra ve vi tri dau hang doi
		int front(Queue Q){
			return Q.data[Q.front];
		}
		//Them phan tu vao cuoi hang doi
		void enterQueue(Queue *Q,int x){
			Q->rear++;
			Q->data[Q->rear]=x;
		}
		//Xoa phan tu o dau hang doi
		void deleteQueue(Queue *Q){
			Q->front++;
		}
	//2.Ngan xep
		typedef struct{
			int data[maxlength];
			int top;
		}stack;
		//Khoi tao
		void makeStack(stack *S){
			S->top=0;
		} 
		//Kiem tra ngan xep rong
		int emptyStack(stack s){
			return s.top==0;
		}
		//Kiem tra ngan xep day
		int fullStack(stack s){
			return s.top==maxlength;
		}
		//Them phan tu vao cuoi ngan xep
		void pushStack(stack *s,int x){
			if(fullStack(*s)){
				printf("\nNgan xep day.Khong the them\n");
			}else{
				s->data[s->top]=x;
				s->top++;	
			}
		}
		//xoa phan tu o dau ngan xep
		void popStack(stack *s){
			if(emptyStack(*s)){
				printf("\nNgan xep day.Khong the xoa\n");
			}else{
				s->top--;
			}
		}
		//Lay phan tu o dau ngan xep
		int topValue(stack s){
			return s.data[s.top-1];
		}
	//3.Danh sach
		typedef struct{
			ViTri last;
			int data[maxlength];
		}list;
		//Khoi tao
		void makeNullList(list *l){
			l->last=0;
		}
		//kiem tra danh sach rong
		int emptyList(list l){
			return l.last==0;
		}
		//Kiem tra danh sach day
		int fullList(list l){
			return l.last==maxlength;
		}
		//Tra ve vi tri dau danh sach
		int firstList(list l){
			return 1;
		}
		//Tra ve vi tri sau phan tu cuoi cung
		int endList(list l){
			return l.last+1;
		}
		//tra ve vi tri dung truoc vi tri can tim
		int previous(ViTri P,list l){
			return P-1;
		}
		//tra ve vi tri dung sau vi tri can tim
		int next(ViTri P,list l){
			return P+1;
		}
		//Tra ve gia tri cua phan tu tai vi tri p
		int retrieve(ViTri P,list l){
			if(emptyList(l)){
				printf("\n\tDanh sach rong.\n");
				return -1;
			}
			return l.data[P-1];
		}
		//Xac dinh vi tri cua phan tu co gia tri X
		int locate(int x,list l){
			ViTri T=firstList(l);//T=0
			while(!emptyList(l)){
				if(l.data[T] == x){
					return T+1;
					break;
				}
				T=next(T,l);
			}
			printf("\n\tKhong tim thay vi tri na co gia tri la: %d\n",x);
			return -1;
		}
		//Them phan tu co gia tri x tai vi tri p trong list
		void InsertList(int x,ViTri P,list *l){
			if(P < 1||P > l->last+1){
				printf("\nVi tri khong hop le.");
			}else{
				if(fullList(*l)){
					printf("\nDanh sach day khong thr them");
				}else{
					ViTri i;
					for(i=l->last+1;i>P;i--){
						l->data[i] = l->data[i-1];
					}
					l->data[P-1]=x;
					l->last++;
				}
			}
		}
		//Xoa phan tu tai vi tri P ra khoi danh sach
		void deleteList(ViTri P,list *l){
			if(emptyList(*l)){
				printf("\n\tDanh sach rong\n");
			}else{
				if(P < 1||P > l->last+1){
					printf("\nVi tri khong hop le.");
				}else{
					ViTri i;
					for(i=P-1;i<l->last-1;i++){
						l->data[i]=l->data[i+1];
					}
					l->last--;
				}
			}
		}
	//4.Danh sach uu tien
		//Tao doi tuong luu tru khoa va gia tri
		typedef struct{
			int key,	//Khoa
				value;	//Gia tri cua khoa
		}DataPList;
		//Danh sach uu tien
		typedef struct{
			int last;	//Vi tri
			DataPList data[maxlength];	//Gom co khoa va gia tri cua khoa
		}PList;
		//1.Khoi tao 
		void makeNull_PriorityList(PList *L){
			L->last =0; 
		}
		//2.Kiem tra xem danh sach co rong khong
		int empty_PriorityList(PList L){
			return L.last==0;
		}
		//3.Kiem tra xem danh sach day chua
		int full_PriorityList(PList L){
			return L.last == maxlength-1;
		}
		//4.Tra ve vi tri dau danh sach
		int first_PriorityList(PList L){
			return 1;
		}
		//5.Tra ve vi tri sau phan tu cuoi cung
		int end_PriorityList(PList L){
			return L.last+1;
		}
		//6.Tra ve vi tri phan tu dung truoc vi tri P
		int previous_PriorityList(PList L,int P){
			return P-1; 
		}
		//7.Tra ve vi tri phan tu sau truoc vi tri P
		int Next_PriorityList(PList L,int P){
			return P+1; 
		}
		//8.Tra ve gia tri khoa tai vi tri P
		int retrieveKey(PList L,int P){
			if(empty_PriorityList(L)){
				printf("\nDanh sach rong.\n");
				return TRONG;
			}
			return L.data[P-1].key;
		}
		//9.Tra ve gia tri khoa tai vi tri P
		int retrieveValue(PList L,int P){
			if(empty_PriorityList(L)){
				printf("\nDanh sach rong.\n");
				return TRONG;
			}
			return L.data[P-1].value;
		}
		//Sap xep lai danh sach
			//Ham swap
			void swapDataPList(DataPList *A,DataPList *B){
				DataPList temp = *A;
				*A = *B;
				*B = temp;
			}
			//Ham sap xep noi bot
			void BubbleSortPriorityList(PList *L){
				int i,j;
				for(i=first_PriorityList(*L) ; i != end_PriorityList(*L) ; i=Next_PriorityList(*L,i)){
					//printf("\n\t\t%d: key[%d]: %d",i,L->data[i-1].key,L->data[i-1].value);
					for(j=end_PriorityList(*L)-1; j>i; j=previous_PriorityList(*L,j)){
						//printf("\n\t%d: key[%d]: %d -- key[%d]: %d",j,L->data[j-1].key,L->data[j-1].value,L->data[j-2].key,L->data[j-2].value);
						if(L->data[j-1].value < L->data[j-2].value){
							swapDataPList(&L->data[j-1],&L->data[j-2]);
						}
					}
				}
			}
		//10.Xen Phan tu co khoa K mang gia tri V vao vi tri P vao danh sach L
		void Insert_PriorityList(int key,int value,int P,PList *L){
			if(full_PriorityList(*L)){
				printf("\n\tDanh sach day.\n");
			}else{
				if(P<1 || P>L->last+1){
					printf("\n\tVi tri khong hop le.\n");
				}
				else{
					int i;
					for(i = L->last+1 ; i>P ; i--){
						L->data[i].key = L->data[i-1].key;
						L->data[i].value = L->data[i-1].value;
					}
					L->data[P-1].key = key;
					L->data[P-1].value = value;
					L->last++;
					BubbleSortPriorityList(L);
				}
			}
		}
		//11.Xoa phan thu tai vi tri P ra khoi danh sach
		void delete_PriorityList(int P,PList *L){
			if(empty_PriorityList(*L)){
				printf("\n\tDanh sach rong.\n");
			}else{
				if(P<1 || P>L->last+1){
					printf("\n\tVi tri khong hop le.\n");
				}
				else{
					int i;
					for(i=P-1;i<L->last-1;i++){
						L->data[i].key = L->data[i+1].key;
						L->data[i].value = L->data[i+1].value;
					}
					L->last--;
					BubbleSortPriorityList(&*L);
				}
			}
		}
