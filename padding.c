#include <stdio.h>

struct student {
	char lastName[13];      /*13bytes*/
	int studentId;          /*4bytes*/
	short grade;           /*12ytes*/
};

int main(void) {

	struct student pst;

	printf("size of student= %ld\n", sizeof(struct student));  //24가 출력됨 원래라면 13+4+2=19가 
    //출력되어야하나 padding 때문 (13+3)+(4)+(2+2)=24바이트
	//패딩은 컴파일러에 따라 다름 gcc컴파일러는 패딩을함
	printf("size of int = %ld\n", sizeof(int));       //4가 출력됨
	printf("size of short = %ld\n", sizeof(short));   //2가 출력됨

	return 0;
}
