#include <stdio.h>
#include <stdlib.h>
void main()
{
       printf("[----- [노민성/noh min sung] [2018038076] -----]");
       int list[5];   //list 배열 선언
       int *plist[5]={NULL,};    //포인터형 배열 plist 선언후 초기화

       plist[0] = (int *)malloc(sizeof(int));  //plist 동적할당

       list[0]=1;  //list[0] 의 값에 1대입
       list[1]=100;   //list[1] 의 값에 100 대입

       *plist[0]=200;   //plist[0]이 가르키는 곳에 200을 대입한다
      
       printf("value of list[0] = %d\n", list[0]);         //list[0]의 값은 1이다
       printf("address of list[0]         = %p\n", &list[0]);   //배열첫번째 인덱스의 주소는 배열의 주소를 의미한다
       printf("value of list              = %p\n", list);       //배열의 이름은 배열의 주소를 의미한다
       printf("address of list (&list)    = %p\n", &list);      //배열 이름의 주소값은 배열의 주소를 의미한다

       printf("--------------------------------\n\n");
       printf("value of list[1]          = %d\n", list[1]);   //list[1] 값은 100이다.
       printf("address of list[1]        = %p\n", &list[1]);   //list[1]의 주소가 출력된다
       printf("value of *(list+1)        = %d\n", *(list+1));   //list+1의 주소가 가르키는 값이니 list[1]값인 100이 출력된다
       printf("address of list+1         = %p\n", list+1);     //list[1]의 주소가 출력된다
       printf("--------------------------------\n\n");
       printf("value of *plist[0]  =%d\n",*plist[0]);      //plist가 가르키는 값이니 200이 출력된다
       printf("&plist[0]           =%p\n",&plist[0]);      //plist의 주소가출력된다
       printf("&plist              =%p\n",&plist);         //plist의 주소가출력된다
       printf("plist               =%p\n",plist);          //plist의 주소가출력된다
       printf("plist[0]            =%p\n",plist[0]);       //plist[0]이 가르키고 있는 곳의 주소가 출력된다
       printf("plist[1]            =%p\n",plist[1]);       //plist[0]번만 malloc을 통해 받았으므로 나머지값은 0이출력된다
       printf("plist[2]            =%p\n",plist[2]);       //plist[0]번만 malloc을 통해 받았으므로 나머지값은 0이출력된다
       printf("plist[3]            =%p\n",plist[3]);       //plist[0]번만 malloc을 통해 받았으므로 나머지값은 0이출력된다
       printf("plist[4]            =%p\n",plist[4]);       //plist[0]번만 malloc을 통해 받았으므로 나머지값은 0이출력된다
       free(plist[0]);   //동적할당을 해제해준다.
}