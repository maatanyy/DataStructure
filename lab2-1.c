#include <stdio.h>
int main()
{
char charType;      //변수 선언
int integerType;  //
float floatType;  
double doubleType;
printf("practice git\n");

printf("[----- [Noh Min Sung] [2018038076] -----]\n");
printf("Size of char: %ld byte\n",sizeof(charType));         //char형 변수 charType 크기는 1바이트
printf("Size of int: %ld bytes\n",sizeof(integerType));      //int형 변수 integerType 크기는 4바이트
printf("Size of float: %ld bytes\n",sizeof(floatType));      //float형 변수 floatType 크기는 4바이트
printf("Size of double: %ld bytes\n",sizeof(doubleType));    //double형 변수 doubleType 크기는 8바이트
printf("-----------------------------------------\n");
printf("Size of char: %ld byte\n",sizeof(char));             //char형 데이터타입 크기는 1바이트
printf("Size of int: %ld bytes\n",sizeof(int));              //int형 데이터타입 크기는 4바이트
printf("Size of float: %ld bytes\n",sizeof(float));          //float형 데이터타입 크기는 4바이트
printf("Size of double: %ld bytes\n",sizeof(double));        //double형 데이터타입 크기는 8바이트
printf("-----------------------------------------\n");
printf("Size of char*: %ld byte\n",sizeof(char*));           //char형 포인터 크기는 4byte, vscode win32로 구성되어 4byte로 뜸
printf("Size of int*: %ld bytes\n",sizeof(int*));            //int형 포인터 크기는 4byte, vscode win32로 구성되어 4byte로 뜸
printf("Size of float*: %ld bytes\n",sizeof(float*));        //float형 포인터 크기는 4byte, vscode win32로 구성되어 4byte로 뜸
printf("Size of double*: %ld bytes\n",sizeof(double*));      //double형 포인터 크기는 4byte, vscode win32로 구성되어 4byte로 뜸
return 0;
}
