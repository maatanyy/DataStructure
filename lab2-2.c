#include <stdio.h>
int main()
{
    printf("\n"); 
int i;             //int 형 i 선언
int *ptr;          //포인터 ptr 선언
int **dptr;       //더블 포인터 dptr 선언
i = 1234;           //i의 값에 1234 대입
printf("[----- [Noh Min Sung] [2018038076] -----]\n");   //이름 학번 추가
printf("[checking values before ptr = &i] \n");      //ptr에 i의 주소 넣기 전 출력하겠다.
printf("value of i == %d\n", i);             //i의 값 출력
printf("address of i == %p\n", &i);         //i의 주소 출력
printf("value of ptr == %p\n", ptr);         //ptr의 값(가리키는)
printf("address of ptr == %p\n", &ptr);      //ptr의 주소값  
ptr = &i; /* ptr is now holding the address of i */
printf("\n[checking values after ptr = &i] \n");        //ptr에 i의 주소 넣은 후 출력하겠다.
printf("value of i == %d\n", i);            // i 값 출력
printf("address of i == %p\n", &i);      //i의 주소 출력
printf("value of ptr == %p\n", ptr);     //ptr이 가리키는 곳 즉 i의 주소
printf("address of ptr == %p\n", &ptr);    //ptr의 주소
printf("value of *ptr == %d\n", *ptr);    //ptr이 가르키는 곳에 들어있는 값 출력
dptr = &ptr; /* dptr is now holding the address of ptr */
printf("\n[checking values after dptr = &ptr] \n");     //dptr에 ptr의 주소를 넣어준다.
printf("value of i == %d\n", i);          //i의 값
printf("address of i == %p\n", &i);         //i의 주소
printf("value of ptr == %p\n", ptr);          // ptr이 가리키는 값
printf("address of ptr == %p\n", &ptr);        //  ptr의 주소
printf("value of *ptr == %d\n", *ptr);          //  ptr이 가르키는 곳에 있는 곳의 값
printf("value of dptr == %p\n", dptr);          //  dptr이 가르키는 곳 값, ptr의 주소가 들어있음
printf("address of ptr == %p\n", &dptr);         //  dptr의 주소
printf("value of *dptr == %p\n", *dptr);        //   dptr이 가르키는 곳에 들어있는 값
printf("value of **dptr == %d\n", **dptr);        //  dptr이 가르키는 주소가 가르키는 곳에 들어있는 값
*ptr = 7777; /* changing the value of *ptr */
printf("\n[after *ptr = 7777] \n");               //   ptr이 가르키는 주소 안에있는값을 7777로 바꾼다
printf("value of i == %d\n", i);                 //     i의 값, 위의 식에의해 7777로바뀜
printf("value of *ptr == %d\n", *ptr);            //    ptr이 가르키는 주소안에있는  값 ,즉 i값 7777
printf("value of **dptr == %d\n", **dptr);        //   dptr이 가르키는 주소가 가르키는 곳에있는값,즉 i
**dptr = 8888; /* changing the value of **dptr */
printf("\n[after **dptr = 8888] \n");            //    dptr이 가르키는 주소가 가르키는 주소안에 값을 8888로 바꿈,즉 i를 의미
printf("value of i == %d\n", i);                 //     i의값8888
printf("value of *ptr == %d\n", *ptr);           //     ptr이 가르키는 주소 안에 있는 값,8888
printf("value of **dptr == %d\n", **dptr);       //     dptr이 가르키는 주소가 가르키는 주소 안에 있는 값 , i
return 0;
}