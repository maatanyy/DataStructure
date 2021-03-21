#include<stdio.h>
#define MAX_SIZE 100      //MAX_SIZE 100으로 정의

float sum(float list[], int);  //sum함수 선언
float input[MAX_SIZE], answer;   //float 형 배열 input, float형 answer선언
int i;  //int형 변수 i 선언

void main(void)
{
	for (i = 0; i < MAX_SIZE; i++)   //i=0;i<MAX_SIZE;i++반복문 시행 
		input[i] = i;       //input[i]에 i를 넣어줌
	answer = sum(input, MAX_SIZE);     //answer는 sum함수에 input과 MAX_SIZE를 인자로 넣어줘서 구함
	printf("The sum is : % f\n", answer);  //answer값 출력
}

float sum(float list[], int n)  //잘보면 input을 인자로 받음 즉 list[]안에 배열의 주소를 가지고 있어서 input을 가르킴
{
	int i;        //int형 i 선언
	float tempsum = 0;   //float 형 tempsum선언 
	for (i = 0; i < n; i++)     //반복문을 통해 tempsum구해주고 그값 리턴
		tempsum += list[i];  //i를 증가시키며 더해줌
	return tempsum;
}
