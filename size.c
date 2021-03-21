#include<stdio.h>
#include<stdlib.h>

int main(void) {
	int** x;      //더블형 포인터 x선언
	printf("sizeof(x)=%lu\n", sizeof(x));  //8이나옴 주소를 저장하고 있는게 64bit machine에서 8바이트이기 때문
	printf("sizeof(*x)=%lu\n", sizeof(*x));  //8이나옴 주소를 저장하고 있는게 64bit machine에서 8바이트이기 때문
	printf("sizeof(**x)=%lu\n", sizeof(**x));  //4가 나옴 인티저를 저장하기 때문에 4바이트가 크기이므로 4가나옴
	return 0;
}
