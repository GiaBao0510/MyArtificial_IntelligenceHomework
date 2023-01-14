#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Luu trang thai
	const char *TrangThaiDau[] = {"1","1","1","0","2","2","2",NULL};
	const char *TrangThaiCuoi[] = {"2","2","2","0","1","1","1",NULL};
//Cau truc luu tru trang thai cua bai toan
	#define soPhienDa 7
	typedef struct{
		int viTri[soPhienDa];	
		/*Mo ta:
			- vi tri 0 den 6: 
			so ech vang o vi tri tu 0,1,2 
			phien da o vi tri thu 3
			so ech cam o vi tri thu 4 5 6*/
		
	}state;
//khoi tao: ban dau tat ca cac phien da chua co con ech nao
	void makeNUllState(state *st){
		int i;
		for(i=0;i<soPhienDa;i++){
			st->viTri[i]=0;
		}
	}
//Trang thai dau: gom cac con vech vang va cam da vao vi tri
	void firstState(state *st){
		int i=0;
		while(TrangThaiDau[i] != NULL){
			st->viTri[i] = atoi(TrangThaiDau[i]);
			i++;
		}
	}
//Trang thai dich: gom cac con vech vang va cam da vao dung vi tri can tim
	void goalState(state *st){
		int i=0;
		while(TrangThaiCuoi[i] != NULL){
			st->viTri[i] = atoi(TrangThaiCuoi[i]);
			i++;
		}
	}
//In trang thai
	void printState(state st){
		int i;
		printf("\n");
		for(i=0;i<soPhienDa;i++){
			printf("%3d",st.viTri[i]);
		}
	}
//so sanh 2 trang thai
	int compareState(state A,state B){
		int r = soPhienDa-1,
			l = 0;
		while(r>l){
			if(A.viTri[r] != B.viTri[r]){	//Hai trang thai khac nhau
				return 1;
			}
			if(A.viTri[l] != B.viTri[l]){	//Hai trang thai khac nhau
				return 1;
			}
		}
		return 0;	//Hai trang thai giong nhau
	}
//sao chep trang thai khac
	void copyState(state current,state *result){
		int i;
		for(i=0;i<soPhienDa;i++){
			result->viTri[i] = current.viTri[i];
		}
	}
int main(){
	state st1,st2;
	goalState(&st1);
	firstState(&st2);
	printState(st1);
	printf("\n%d" ,compareState(st1,st2));
	return 0;	
}
