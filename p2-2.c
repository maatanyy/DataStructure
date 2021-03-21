#include <stdio.h>

void print1(int* ptr, int rows);  //print1함수 선언

int main() {
    printf("[----- [노민성/noh min sung] [2018038076] -----]");
    int one[] = { 0,1,2,3,4 };   //배열one 선언후 0,1,2,3,4로 값 초기화

    printf("one      = %p\n", one);     //배열의이름은 주소니까 배열의 주소나옴
    printf("&one     = %p\n", &one);     //배열의 주소 출력
    printf("&one[0]  = %p\n", &one[0]);   //배열의첫번째값의 주소는 배열의 주소
    printf("\n");

    print1(&one[0], 5);     //print1함수의 인자로 배열one의 주소와 5전달

    return 0;
}
void print1(int* ptr, int rows) {     //포인터 ptr은 배열one의 주소 가르킴, row에 5대입
    int i;      //인트형 변수 i 선언
    printf("Address \t         Contents\n");       //출력  
    for (i = 0; i < rows; i++)        //i=0;i<5;i++  ,5번반복
 printf("%p \t %5d\n", ptr + i, *(ptr + i));      //ptr+i는 배열i번째 인덱스의 주소를 나타내고 ,*(ptr+i)는 그주소안에 들어있는 값을나타냄
    printf("\n");
}

