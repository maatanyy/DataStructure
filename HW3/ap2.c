#include<stdio.h>
#include<stdlib.h>    //malloc함수 쓰기위해 

void main() {
    printf("[----- [노민성/noh min sung] [2018038076] -----]");
    int list[5];     //크기가 5인 list배열 선언
    int* plist[5];   //크기가 5인 포인터형 배열 plist선언

    list[0] = 10;    //list[0]=10대입
    list[1] = 11;    //list[1]=11대입

    plist[0] = (int*)malloc(sizeof(int));   //plist[0] 동적할당

    printf("list[0] \t= %d\n", list[0]);     //10이 출력된다
    printf("address of list \t= %p\n", list);  //배열의 주소가 출력된다
    printf("address of list[0] \t= %p\n", &list[0]);  //배열의 첫번째인덱스의 주소는배열의주소다
    printf("address of list + 0 \t= %p\n", list + 0);  //배열의주소가출력된다
    printf("address of list + 1 \t= %p\n", list + 1);  //인트형이니까 배열의첫주소에서 4byte이동된값이나온다
    printf("address of list + 2 \t= %p\n", list + 2);   //인트형이니까 배열의첫주소에서 4*2byte이동된값이나온다
    printf("address of list + 3 \t= %p\n", list + 3);   //인트형이니까 배열의첫주소에서 4*3byte이동된값이나온다
    printf("address of list + 4 \t= %p\n", list + 4);    //인트형이니까 배열의첫주소에서 4*4byte이동된값이나온다
    printf("address of list[4] \t= %p\n", &list[4]);     //list[4]의주소가 출력된다 list+4를 출력했을 때랑 값이 같다

    free(plist[0]);   //동적할당해제
}