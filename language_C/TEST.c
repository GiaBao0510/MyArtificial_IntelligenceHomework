#include<stdio.h>
#include<stdlib.h>
#define tankCapacity_A 10	//Suc chua binh A la 10 lit
#define tankCapacity_B 2	//Suc chua binh B la 2 lit
#define tankCapacity_C 5	//Suc chua binh C la 5 lit
#define tankCapacity_D 6	//Suc chua binh D la 6 lit
#define empty 0
#define goal 8				//Muc tieu la dong duoc 8 lit
//Cau truc luu tru trang thai cac binh
	typedef struct{
		int A,B,C,D;	//Cac binh A,B,C,D
	}state;
	//Khoi tao do day binh A va cac binh con lai thi lam rong 
	void makeNull(state *St){
		St->A = tankCapacity_A;
		St->B = St->C = St->D = 0;
	}
//Ham Gan gia tri
	void assignState(state *St,int x,int y,int z,int r){
		St->A = x;
		St->B = y;
		St->C = z;
		St->D = r;
	}
//Ham copy trang thai khac
	void copyOtherStatus(state current,state *result){
		result->A = current.A;
		result->B = current.B;
		result->C = current.C;
		result->D = current.D;
	}
//Ham in trang thai
	void printState(state St){
		printf("\n[A]: %d -- [B]: %d -- [C]: %d -- [D]: %d",St.A,St.B,St.C,St.D);
	}
//Ham min & max
	int max(int a,int b){
		return (a>b)? a:b;
	}
	int min(int a,int b){
		return (a<b)? a:b;
	}
//Cac phep toan(current: la chi trang thai hien tai cua bai toan .Con )
	//1.Do binh A sang binh B
	int pourBottleA_IntoBottleB()	
