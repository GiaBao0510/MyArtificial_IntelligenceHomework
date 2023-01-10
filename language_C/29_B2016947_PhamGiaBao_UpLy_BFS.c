#include<stdio.h>
#include<stdlib.h>
#define soLuongLy 6			//So luong ly hien tai(0,1,2,3,4,5)
#define goal 111111			//Muc dich can tim
#define firstState 101010	//Trang thai dau
typedef struct{
	int gtriLY[soLuongLy],	//Luu gia tri cua tung ly (1: ly up | 0: ly chua up )
		stt_Ly[soLuongLy];	//Danh dau so thu tu cua tung ly
}status;
//Khoi tao trang thai rong: tat ca cac ly deu up
void MakeNullStatus(status *ST){
	int i;
	for(i=0;i<soLuongLy;i++){
		ST->gtriLY[i] = 0;
	}
}
//khoi tao gan trang thai bat dau vao gia tri cac ly
void InitializationStatus(status *ST){
	int i;
	int SL=soLuongLy - 1;		//Luu so luong (0,1,2,3,4,5)
	int current = firstState;	//Luu tam thoi trang thai dau
	for(i=0;i<soLuongLy;i++){
		ST->stt_Ly[i]=i;
		ST->gtriLY[SL]=(current % 10);
		current/=10;
		SL--;
	}
}
//In trang thai cua cac ly
void printState(status ST){
	int i;
	printf("\nCac trang thai ly: \t");
	for(i = 0;i<soLuongLy;i++){
		printf("%3d",ST.gtriLY[i]);
	}
}
//Thay doi trang thai cua Ly: la ta thay doi ba ly ke nhau trong so 6 ly
/*current la trang thai tam thoi chi hien thi trang thai cua cac ly
  result la trang thai dung de luu ket qua*/
void changeStatus(status current,status *result, int number1){
	int number2 = number1 + 1,	//ly thu 2
		number3 = number1 + 2;	//ly thu 3
	(current.gtriLY[number1] == 1)? (result->gtriLY[number1] = 0):(result->gtriLY[number1] = 1); //Neu ly 1 up thi mo. Nguoc lai thi up
	(current.gtriLY[number2] == 1)? (result->gtriLY[number2] = 0):(result->gtriLY[number2] = 1); //Neu ly 2 up thi mo. Nguoc lai thi up
	(current.gtriLY[number3] == 1)? (result->gtriLY[number3] = 0):(result->gtriLY[number3] = 1); //Neu ly 3 up thi mo. Nguoc lai thi up
	//printf("\nNumber1: %d \t Number2: %d \t Number3: %d",result->gtriLY[number1],result->gtriLY[number2],result->gtriLY[number3]);
}
//Chuyen doi trang thai thanh so nguyen
int convertStateToInterger(status ST){
	int kq = 0;
	int i;
	for(i=0;i<soLuongLy;i++){
		kq = (kq * 10) + ST.gtriLY[i];
	}
	return kq;
}
//Chuyen doi so nguyen thanh trang thai
status convertIntegerToState(int integer){
	status ST;
	int i;
	for(i=soLuongLy-1;i>=0;i--){
		ST.gtriLY[i] =(integer %10);
		integer/=10;
	}
	return ST;
}
//kiem tra ham muc tieu
int checkGoal(int value){
	if(value == goal){
		return 1;
	}
	return 0;
}
//Sao chep trang thai cua cac ly khac
void copyOtherState(status current,status *result){
	int i;
	for(i=0;i<soLuongLy;i++){
		result->gtriLY[i] = current.gtriLY[i];
	}
}
	const char *action[] = {"Trang thai dau","Thay doi trang thai ly co so thu tu 0,1,2","Thay doi trang thai ly co so thu tu 1,2,3",
"Thay doi trang thai ly co so thu tu 2,3,4","Thay doi trang thai ly co so thu tu 3,4,5"};
		//Cau truc cay luu tru trang thai cua cac ly
	struct tree{
		int gt_CacLy,
			soHanhDong;
		struct tree *next;
	};
	typedef struct tree *node;
	//Khoi tao nut
	node MakeNullNode(){
		node head;
		head = NULL;
		return head;
	}
	//Gan tri vao nut
	node CreateNode(int giatri,int opt){
		node temp = (node)malloc(sizeof(node));
		temp->gt_CacLy = giatri;
		temp->soHanhDong = opt;
		temp->next = NULL;
		return temp;
	}
	//Chen nut vao dau
	node insertHead(node head,int giatri,int opt){
		node temp = CreateNode(giatri,opt);
		if(head == NULL){
			head = temp;
		}else{
			temp->next = head;
			head = temp;
		}
		return head;
	}
	//Gan gia tri vao nut
		//Hang doi luu tru cac nut
	#define maxlength 100
	typedef struct{
		node data[maxlength];
		int front, rear;
	}Queue;
	//Khoi tao hang doi
	void makeNullQueue(Queue *Q){
		Q->front = Q->rear = -1;
	}
	//Kiem tra hang doi rong
	int emptyQueue(Queue Q){
		return(Q.front < 0 || Q.rear < 0);
	}
	//Kiem tra hang doi day
	int fullQueue(Queue Q){
		return(Q.rear - Q.front +1)%maxlength == 0;
	}
	//Them phan tu vao cuoi hang doi
	void InsertNode(Queue *Q,node X){
		if(fullQueue(*Q)){
			printf("\nHang doi day.\n");
		}else{
			if(emptyQueue(*Q)){
				Q->front = 0;
			}
			(Q->rear++)%maxlength;
			Q->data[Q->rear] = X;
		}
	}
	//Lay phan tu o dau hang doi
	void deleteQueue(Queue *Q){
		if(emptyQueue(*Q)){
			printf("\nHang doi rong.\n");
		}else{
			if(Q->rear == Q->front){
				makeNullQueue(Q);
			}else{
				(Q->front++)%maxlength;
			}
		}
	}
	//xem nut o dau hang doi
	node FrontNode(Queue Q){
		return Q.data[Q.front];
	}
	//Kiem tra xem trang thai cac ly tren da ton tai trong hang doi chua
	int findState(Queue Q,int value){
		while(!emptyQueue(Q)){
			if(FrontNode(Q)->gt_CacLy == value){
				return 1; //ti thay
			}else{
				deleteQueue(&Q);
			}
		}
		return 0; //tim thay 
	}
	//TN
	node BFS(status *result){
		//Cac bien
		status temp;
		int vl;
		Queue open,closed;
		node root;
		int gtri_ly,
			valueInt,
			lan = 0;
		//Khoi tao
		makeNullQueue(&open);
		makeNullQueue(&closed);
		InitializationStatus(result);
		gtri_ly = convertStateToInterger(*result);	//Chuyen trang thai ve dang so nguyen
		root = insertHead(root,gtri_ly,0);
		//Day nut goc vao danh sach open
		InsertNode(&open,root);
		MakeNullStatus(result); 					//Dat lai gia tri cac ly chua up
			//printf("\n%d",TopIndex(open)->gt_CacLy);
		//Lap
		while(!emptyQueue(open)){
			//Lay trang thai dau ra khoi ngan xep
			node Fnode = FrontNode(open);
			InsertNode(&closed,Fnode);
			deleteQueue(&open);
			//kiem tra co phai la muc tieu khong
			if(checkGoal(Fnode->gt_CacLy) == 1){
				return Fnode;
			}
			//chuyen doi
			temp = convertIntegerToState(Fnode->gt_CacLy);
			//Lap de tim trang thai moi
			for(vl = 0; vl < soLuongLy-2 ; vl++){
				copyOtherState(temp,result);		//Sao chep trang thai ket qua giong voi trang thai temp
				changeStatus(temp,result,vl);		//thay doi trang thai cac ly ke nhau
				valueInt = convertStateToInterger(*result);
				//kiem tra xem co phai la trang thai moi khong?
				if(findState(open,valueInt) == 0 && findState(closed,valueInt) == 0){
					node Snode =(node)malloc(sizeof(node));
					Snode->gt_CacLy = valueInt;
					Snode->soHanhDong = vl+1;
					Snode->next = Fnode;
					InsertNode(&open,Snode);//Day vao danh sach open
				}
			}
			lan++;
		}	
		return NULL;
	} 
	//in trang thai
	void DuongDi(node P){
		node vl;
		node kq = MakeNullNode();
		if(P == NULL){
			printf("\n\n\tKhong tim thay ket qua.");
			return;
		}
		for(vl = P ;vl != NULL; vl = vl->next){
			kq = insertHead(kq,vl->gt_CacLy,vl->soHanhDong);
		}
		//in
		node lap;
		status saveState;
		for(lap = kq; lap!= NULL;lap= lap->next){
			printf("\n%s:",action[lap->soHanhDong]);
			saveState = convertIntegerToState(lap->gt_CacLy);
			printState(saveState);
		}
	}
int main(){
	status ST,temp;
	node h1 = BFS(&ST);
	DuongDi(h1);
}
