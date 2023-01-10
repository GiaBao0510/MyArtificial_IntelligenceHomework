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
		//Ngan xep luu tru cac nut
	#define maxlength 100
	typedef struct{
		node data[maxlength];
		int top;
	}stack;
	//Khoi tao ngan xep rong
	void makeNullStack(stack *S){
		S->top = maxlength;
	}
	//Kiem tra ngan xep co rong khong
	int emptyStack(stack S){
		return (S.top == maxlength);
	}
	//Kiem tra ngan xep co day khong
	int fullStack(stack S){
		return (S.top == 0);
	}
	//Day 1 phan tu vao ngan xep
	void pushStack(stack *S,node X){
		if(fullStack(*S)){
			printf("\nNgan xep day\n");
		}else{
			S->top--;
			S->data[S->top] = X;
		}
	}
	//Xoa 1 phan tu dau ngan xep
	void popStack(stack *S){
		if(emptyStack(*S)){
			printf("\nNgan xep rong\n");
		}else{
			S->top++;
		}
	}
	//Lay phan tu dau ngan xep
	node TopIndex(stack S){
		return S.data[S.top];
	}
	//Tim kiem xem gia tri cua cac lu trong 1 nut co ton tai trong danh sach khong
	int findStatus(stack S,int gtX){
		while(!emptyStack(S)){
			if(TopIndex(S)->gt_CacLy == gtX){
				return 1; //Tim thay
			}else{
				popStack(&S);
			}
		}
		return 0; //Khong tim thay
	}
	//TN
	node DFS(status *result){
		//Cac bien
		status temp;
		int vl;
		stack open,closed;
		node root;
		int gtri_ly,
			valueInt,
			lan = 0;
		//Khoi tao
		makeNullStack(&open);
		makeNullStack(&closed);
		InitializationStatus(result);
		gtri_ly = convertStateToInterger(*result);	//Chuyen trang thai ve dang so nguyen
		root = insertHead(root,gtri_ly,0);
		//Day nut goc vao danh sach open
		pushStack(&open,root);
		MakeNullStatus(result); 					//Dat lai gia tri cac ly chua up
			//printf("\n%d",TopIndex(open)->gt_CacLy);
		//Lap
		while(!emptyStack(open)){
			//Lay trang thai dau ra khoi ngan xep
			node Fnode = TopIndex(open);
			pushStack(&closed,Fnode);
			popStack(&open);
			printf("\n\n\tDuyet: %d\n",Fnode->gt_CacLy);
			//kiem tra co phai la muc tieu khong
			if(checkGoal(Fnode->gt_CacLy) == 1){
				return Fnode;
			}
			//chuyen doi
			printf("\n\t%d.Xet: ",lan);
			temp = convertIntegerToState(Fnode->gt_CacLy);
			printState(temp);
			//Lap de tim trang thai moi
			for(vl = 0; vl < soLuongLy-2 ; vl++){
				copyOtherState(temp,result);
				changeStatus(temp,result,vl);
				valueInt = convertStateToInterger(*result);
				printf("\n%d. Kiem tra: %d",lan,valueInt);
				//kiem tra xem co phai la trang thai moi khong?
				if(findStatus(open,valueInt) == 0 && findStatus(closed,valueInt) == 0){
					printf("\n\t--------Trang thai moi: %d",valueInt);
					status thu = convertIntegerToState(valueInt);
					printState(thu);
					node Snode =(node)malloc(sizeof(node));
					Snode->gt_CacLy = valueInt;
					Snode->soHanhDong = vl+1;
					Snode->next = Fnode;
					pushStack(&open,Snode);//Day vao danh sach open
				}
			}
			lan++;
		}	
		return NULL;
	}
	//in trang thai
	void DuongDi(node P){
		node vl;
		stack KQ;
		makeNullStack(&KQ);
		if(P == NULL){
			printf("\n\n\tKhong tim thay ket qua.");
			return;
		}
		for(vl = P ;vl != NULL; vl = vl->next){
			printf("\n %d - %d",vl->soHanhDong,vl->gt_CacLy);
			pushStack(&KQ,vl);
		}
		//in
		status kq;
		while(!emptyStack(KQ)){
			printf("\n\n\t%s :",action[TopIndex(KQ)->soHanhDong]);
			kq = convertIntegerToState(TopIndex(KQ)->gt_CacLy);
			printState(kq);
			popStack(&KQ);
		}
	}
int main(){
	status ST,temp;
	node P = DFS(&ST);
	DuongDi(P);	
}
