#include<stdio.h>
#include<stdlib.h>
#define maxA 9
#define maxB 4
typedef struct{
	int A,//Binh A chua toi da 9 lit
		B;//Binh B chua toi da 4 lit
}state;
//Trang thai ban dau
void makeNullState(state *st){
	st->A = st->B = 0;
}
//In trang thai
void printState(state st){
	printf("\nA: %d -- B: %d",st.A,st.B);
}
//Lam day binh A
void bottleA_isFull(state *st){
	st->A=maxA;
}
//Lam day binh B
void bottleB_isFull(state *st){
	st->B=maxB;
}
//Lam rong binh A
void bottleA_isEmpty(state *st){
	st->A=0;
}
//Lam rong binh B
void bottleB_isEmpty(state *st){
	st->B=0;
}
//Do binh A sang binh B
void pourJarA_intoJarB(state *st){
	//Neu binh B chua day hoac binh A chua rong
	if(st->B < maxB || st->A > 0){//Neu binh a day hoac binh b rong thi dung
		int tamA = st->A,
			tamB = st->B;
		st->A -= (maxB-st->B);
		//Neu ket qua tren st->B la am thi dat lai rong
		if(st->A < 0){
			st->A=0;
		}
		//Neu sau phep tinh kia ca 2 binh dieu rong hoac chi co binh B la rong thi cho binh A cong cho trang thai ban dau cua binh B
		if((st->B == 0 && st->A == 0) || st->A == 0){
			st->B+=tamA;
		}
		//Neu do binh B vao binh A ma khong bi tran thi thuc hien
		else if( (tamB += (maxA-st->A)) <= maxB){
			st->B+= (maxA-st->A);
		}//Neu binh B rong va Kq binh B bi tran thi dat binh B day
		else if(st->B == 0 && (tamB += (maxA-st->A)) > maxB ){
			st->B = maxB;
		}
		//Nguoc lai neu bi tran thi thuc hien do binh B vao A
		else if((tamB += (maxA-st->A)) > maxB){
			st->B += st->A;
		}
		//Neu sau cac phep toan tren ma B bi tran thi dat lai cho binh B day
		if(st->B > maxB){
			st->B = maxB;
		}
	}
}
//Do binh B sang binh A
void pourJarB_intoJarA(state *st){
	//Neu binh a chua day hoac binh b chua rong thi dung
	if(st->A < maxA || st->B > 0){
		int tamA = st->A,
			tamB = st->B;
		st->B -= (maxA-st->A);
		//Neu ket qua tren st->B la am thi dat lai rong
		if(st->B < 0){
			st->B=0;
		}
		//Neu sau phep tinh kia ca 2 binh dieu rong hoac chi co binh B la rong thi cho binh A cong cho trang thai ban dau cua binh B
		if((st->A == 0 && st->B == 0) || st->B == 0){
			st->A+=tamB;
		}
		//Neu binh A rong va Kq binh A bi trang thi dat binh A day
		else if(st->A == 0 && (tamA += (maxB-st->B)) > maxA ){
			st->A = maxA;
		}
		//Nguoc lai neu bi tran thi thuc hien do binh B vao A
		else if((tamB += (maxA-st->A)) > maxB){
			st->A += st->B;
		}
		//Neu sau cac phep toan tren ma A bi tran thi dat lai cho binh anh day
		if(st->A > maxA){
			st->A = maxA;
		}
	}
}
//Kiem tra ham muc tieu
int Goal(state st){
	return (st.A == 6);
}
//truyen gia tri vao trang thai
void assignValue(state *st,int u,int v){
	st->A=u;
	st->B=v;
}
//Sao chep sau
void copyState(state *main,state support){
	main->A = support.A;
	main->B = support.B;
}
//Lay gia tri binh A
int getValueA(state st){
	return st.A;
}
//Lay gia tri binh B
int getValueB(state st){
	return st.B;
}
		//Danh sach dung de luu tap cac trang thai cua
	#define maxlength 100
	typedef struct{
		int last;				//Do dai danh sach
		state data[maxlength];	//Trang thai trong danh sach
		int opt[maxlength];		//Luu tru buoc thuc hien
	}listState;
	//danh sach rong
	void makeNullList(listState *LS){
		LS->last=0;
	}
	//Kiem tra danh sach co rong khong
	int emptyList(listState LS){
		return LS.last==0;
	}
	//Kiem tra danh sach co day khong
	int fullList(listState LS){
		return LS.last==maxlength;
	}
	//Tra ve vi tri dau tien trong danh sach
	int firstList(listState LS){
		return 1;
	}
	//Tra ve vi tri sau phan tu cuoi cung
	int endList(listState LS){
		return LS.last+1;
	}
	//Day phan tu vao cuoi danh sach
	void pushList(listState *LS,int x,int y,int step){
		if(fullList(*LS)){
			printf("\nDanh sach day\n");
			return;
		}else{
			LS->last++;
			LS->data[LS->last].A = x;
			LS->data[LS->last].B = y;
			LS->opt[LS->last] = step;
		}
	}
	//Lay gia tri cua binh A tai vi tri P trong danh sach L
	int retrieve_bottleA(listState LS,int P){
		if(P<1 || P>LS.last+1){
			printf("Vi tri khong hop le.");
			return -1; 
		}
		return LS.data[P].A;
	}
	//Lay gia tri cua binh B tai vi tri P trong danh sach L
	int retrieve_bottleB(listState LS,int P){
		if(P<1 || P>LS.last+1){
			printf("Vi tri khong hop le.");
			return -1; 
		}
		return LS.data[P].B;
	}
	//In buoc thuc hien tai vi tri P trong danh sach
	int stepInList(listState LS,int P){
		if(P<1 || P>endList(LS)){
			printf("Vi tri khong hop le.");
			return -1;
		}
		return LS.opt[P];
	}
	//Dao nguoc danh sach
	void reverseList(listState *LS){
		listState temp = *LS;
		int i;
		int j = firstList(*LS);
		for(i=endList(temp)-1 ; i>=firstList(temp) ; i--){
			LS->data[j].A = temp.data[i].A;
			LS->data[j].B = temp.data[i].B;
			LS->opt[j] = temp.opt[i];
			j++;
			if(j == endList(*LS)){
				break;
			}
		}
	}
	//So sanh trang thai co trong danh sach trang thai khong
	int compareState(listState LS,int x,int y){
		int r = endList(LS) -1,
			l = firstList(LS);
		while(r>=l){
			int m1 = (r+l)/2,
				m2 = m1 + (r+l)/4;
			if(retrieve_bottleA(LS,l) == x && retrieve_bottleB(LS,l) == y){
				return 1;//Vay trang thai nay da co trong danh sach
			}
			if(retrieve_bottleA(LS,m1) == x && retrieve_bottleB(LS,m1) == y){
				return 1;//Vay trang thai nay da co trong danh sach
			}
			if(retrieve_bottleA(LS,m2) == x && retrieve_bottleB(LS,m2) == y){
				return 1;//Vay trang thai nay da co trong danh sach
			}
			if(retrieve_bottleA(LS,r) == x && retrieve_bottleB(LS,r) == y){
				return 1;//Vay trang thai nay da co trong danh sach
			}
			r--;
			l++;
		}
		return 0;//Nguoc lai vay trang thai nay khong ton tai
	}
		//Hang doi dung de duyet cac trang thai chua xuat hien trong danh sach
	typedef struct{
		state data[maxlength];
		int front,rear;
	}QueueState;
	//Tao hang doi rong
	void makeNullQueue(QueueState *Q){
		Q->front = Q->rear = -1;
	}
	//Kiem tra hang doi co rong
	int emptyQueue(QueueState Q){
		return (Q.front <  0 || Q.rear < 0);
	}
	//Kiem tra hang doi co day khong
	int fullQueue(QueueState Q){
		return (Q.rear - Q.front + 1)%maxlength == 0;
	}
	//Them trang thai vao hang doi
	void pushQueue(QueueState *Q,int x,int y){
		if(fullQueue(*Q)){
			printf("\nDanh sach day\n");
		}else{
			if(emptyQueue(*Q)){
				Q->front=0;
			}
			(Q->rear+=1)%maxlength;
			Q->data[Q->rear].A = x;
			Q->data[Q->rear].B = y;
		}
	}
	//Lay trang thai binh A o dau hang doi
	int Front_bottleA(QueueState Q){
		return Q.data[Q.front].A;
	}
	//Lay trang thai binh B o dau hang doi
	int Front_bottleB(QueueState Q){
		return Q.data[Q.front].B;
	}
	//Lay trang thai dau ra khoi hang doi
	void deleteFront(QueueState *Q){
		if(emptyQueue(*Q)){
			printf("\nHang doi rong\n");
		}else{
			if(Q->front == Q->rear){
				makeNullQueue(Q);
			}else{
				(Q->front++)%maxlength;
			}
		}
	}
	//Mang nay dung de luu tru cac buoc thuc hien
	const char *action[] ={"Trang thai dau","Lam rong binh A","Lam rong binh B"
	,"Lam day binh A","Lam day binh B","Do binh A sang binh B","Do binh B sang binh A"};
	//Cau truc cha dung de luu tru vet
	typedef struct{
		state data;	//Luu tru trang thai cac binh
		int	stt,	//Luu tru so thu tu trang thai
			p,		//Luu trang thai cha dua tren si thu tu
			opt;	//Luu tru buoc thuc hien o tung trang thai
	}history;
	//Do dai ghi vet
	int length = 0;
	//Giai bai toan
	void GB(state *st,history P[100],listState L){
		//Cac bien ho tro
		state temp;
		QueueState Q;
		int valueA,
			valueB;
		int vl = 0;//Dem so lan lap
		//1.Khoi tao
		makeNullList(&L);
		makeNullQueue(&Q);
		makeNullState(st);
		//2.Day trang thai dau vao danh sach trang thai va hang doi trang thai
		pushList(&L,getValueA(*st),getValueB(*st),0);
		pushQueue(&Q,getValueA(*st),getValueB(*st));
		//3.Cap nhat lich su ghi vet cho trang thai dau
		P[vl].data.A = getValueA(*st);
		P[vl].data.B = getValueB(*st);
		P[vl].stt = 0;	//Trang thai dau co so thu tu la 0
		P[vl].p = -1;	//Trang thai dau co cha la -1
		P[vl].opt = 0;	//Trang thai dau
		//4. Lap khi gap muc tieu hoac hang doi rong thi dung
		while(!emptyQueue(Q)){
			//1. lay trang thai dau ra khoi hang doi
			temp.A = Front_bottleA(Q);
			temp.B = Front_bottleB(Q);
			printf("\n\n\tDuyet [A]: %d -- [B]: %d\n",temp.A,temp.B);
			deleteFront(&Q);
			//2.Kiem tra dieu kieu co phai la ham muc tieu khong
			if(Goal(temp) == 1){
				break;
			}
			//3.thuc hien cac hanh dong
				//1.Lam rong binh A
				copyState(st,temp);
				bottleA_isEmpty(st);
				valueA = getValueA(*st);//Lay trang thai binh A
				valueB = getValueB(*st);//Lay trang thai binh B
				printf("\nLam rong binh A: [A]: %d -- [B]: %d",valueA,valueB);
				if(compareState(L,valueA,valueB) != 1){
					printf("\n---------trang thai moi [A]: %d -- [B]: %d",valueA,valueB);
					length++;//Tang do dai cua vet
					//Cap nhat lai vet
					P[length].data.A = valueA;
					P[length].data.B = valueB;
					P[length].stt = length;
					P[length].p = P[vl].stt;
					P[length].opt = 1;
					//Day vao danh sach va hang doi
					pushList(&L,valueA,valueB,P[length].opt);
					pushQueue(&Q,valueA,valueB);
				}
					//2.Lam rong binh B
				copyState(st,temp);
				bottleB_isEmpty(st);
				valueA = getValueA(*st);//Lay trang thai binh A
				valueB = getValueB(*st);//Lay trang thai binh B
				printf("\nLam rong binh B: [A]: %d -- [B]: %d",valueA,valueB);
				if(compareState(L,valueA,valueB) != 1){
					printf("\n---------trang thai moi [A]: %d -- [B]: %d",valueA,valueB);
					length++;//Tang do dai cua vet
					//Cap nhat lai vet
					P[length].data.A = valueA;
					P[length].data.B = valueB;
					P[length].stt = length;
					P[length].p = P[vl].stt;
					P[length].opt = 2;
					//Day vao danh sach va hang doi
					pushList(&L,valueA,valueB,P[length].opt);
					pushQueue(&Q,valueA,valueB);
				}
					//3.Lam day binh A
				copyState(st,temp);
				bottleA_isFull(st);
				valueA = getValueA(*st);//Lay trang thai binh A
				valueB = getValueB(*st);//Lay trang thai binh B
				printf("\nLam day binh A: [A]: %d -- [B]: %d",valueA,valueB);
				if(compareState(L,valueA,valueB) != 1){
					printf("\n---------trang thai moi [A]: %d -- [B]: %d",valueA,valueB);
					length++;//Tang do dai cua vet
					//Cap nhat lai vet
					P[length].data.A = valueA;
					P[length].data.B = valueB;
					P[length].stt = length;
					P[length].p = P[vl].stt;
					P[length].opt = 3;
					//Day vao danh sach va hang doi
					pushList(&L,valueA,valueB,P[length].opt);
					pushQueue(&Q,valueA,valueB);
				}
					//4.Lam day binh B
				copyState(st,temp);
				bottleB_isFull(st);
				valueA = getValueA(*st);//Lay trang thai binh A
				valueB = getValueB(*st);//Lay trang thai binh B
				printf("\nLam day binh B: [A]: %d -- [B]: %d",valueA,valueB);
				if(compareState(L,valueA,valueB) != 1){
					printf("\n---------trang thai moi [A]: %d -- [B]: %d",valueA,valueB);
					length++;//Tang do dai cua vet
					//Cap nhat lai vet
					P[length].data.A = valueA;
					P[length].data.B = valueB;
					P[length].stt = length;
					P[length].p = P[vl].stt;
					P[length].opt = 4;
					//Day vao danh sach va hang doi
					pushList(&L,valueA,valueB,P[length].opt);
					pushQueue(&Q,valueA,valueB);
				}
					//5.Do binh A sang binh B
				copyState(st,temp);
				pourJarA_intoJarB(st);
				valueA = getValueA(*st);//Lay trang thai binh A
				valueB = getValueB(*st);//Lay trang thai binh B
				printf("\nDo binh A sang binh B: [A]: %d -- [B]: %d",valueA,valueB);
				if(compareState(L,valueA,valueB) != 1){
					printf("\n---------trang thai moi [A]: %d -- [B]: %d",valueA,valueB);
					length++;//Tang do dai cua vet
					//Cap nhat lai vet
					P[length].data.A = valueA;
					P[length].data.B = valueB;
					P[length].stt = length;
					P[length].p = P[vl].stt;
					P[length].opt = 5;
					//Day vao danh sach va hang doi
					pushList(&L,valueA,valueB,P[length].opt);
					pushQueue(&Q,valueA,valueB);
				}
					//6.Do binh B sang binh A
				copyState(st,temp);
				pourJarB_intoJarA(st);
				valueA = getValueA(*st);//Lay trang thai binh A
				valueB = getValueB(*st);//Lay trang thai binh B
				printf("\nDo binh B sang binh A: [A]: %d -- [B]: %d",valueA,valueB);
				if(compareState(L,valueA,valueB) != 1){
					printf("\n---------trang thai moi [A]: %d -- [B]: %d",valueA,valueB);
					length++;//Tang do dai cua vet
					//Cap nhat lai vet
					P[length].data.A = valueA;
					P[length].data.B = valueB;
					P[length].stt = length;
					P[length].p = P[vl].stt;
					P[length].opt = 6;
					//Day vao danh sach va hang doi
					pushList(&L,valueA,valueB,P[length].opt);
					pushQueue(&Q,valueA,valueB);
				}
			vl++;
		}	
	}
	//In lich su duyet
	void print_history(history P[]){
		printf("\nLich su duyet:\n");
		int i;
		for(i=0;i<length;i++){
			printf("\nx: %d\t--\ty: %d\t--\tstt: %d\t\t--\tp: %d\toption: %d",P[i].data.A,P[i].data.B,P[i].stt,P[i].p,P[i].opt);
		}
		
	}
	//In ra cay
	void CacBuocThucHien(history P[]){
		//Tao danh sach
		listState DS;
		makeNullList(&DS);
		int doDai = length-1;
		int stt;
		do{
			stt =P[doDai].stt;
			//printf("\nDodai: %d -- [A]: %d -- [B]: %d",doDai,P[stt].data.A,P[stt].data.B);
			//Day vao danh sach
			pushList(&DS,P[stt].data.A,P[stt].data.B,P[stt].opt);
			doDai = P[doDai].p;	
		}while(doDai>=0);
		//dao nguoc danh sach
		reverseList(&DS);
		int vtri;
		for(vtri = firstList(DS); vtri != endList(DS); vtri++){
			printf("\n%s [A]: %d - [B]: %d",action[stepInList(DS,vtri)],retrieve_bottleA(DS,vtri),retrieve_bottleB(DS,vtri));
		}
	}
int main(){
	state st;
	listState DS;
	history p[100];
	GB(&st,p,DS);
	CacBuocThucHien(p);
	return 0;
}
