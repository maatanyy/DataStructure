#include <stdio.h>
struct student1 {     //구조체 student1선언
	char lastName;   //char형 이름 선언
	int studentId;  //int형 id선언
	char grade;      //char형 등급선언
};

typedef struct {      //typedef struct student2 선언, 사용할때 struct안붙여도됨
	char lastName;     //char형 이름 선언
	int studentId;      //int형 id선언
	char grade;         //char형 등급선언
}student2;

int main() {
	printf("[----- [노민성/noh min sung] [2018038076] -----]");
	struct student1 st1 = { 'A',100,'A' };        //struct student1형 st1선언후 초기화
	printf("st1.lastName = %c\n",st1.lastName);     //A출력됨
	printf("st1.studentId = %d\n", st1.studentId);    //100출력됨
	printf("st1.grade= %c\n", st1.grade);           //A출력됨
	student2 st2 = { 'B',200,'B' };      //student2형 st2선언후 초기화(struct안붙여도됨)

	printf("\nst2.lastName = %c\n", st2.lastName);     //B출력됨
	printf("st2.studentId = %d\n", st2.studentId);      //200출력됨
	printf("st2.grade= %c\n", st2.grade);             //B출력됨
	student2 st3; //student2형 st3선언

	st3 = st2;      //st2의 정보를 st3에 넣어줌
	printf("\nst3.lastName = %c\n", st3.lastName);       //st2의 이름인 B출력
	printf("st3.studentId = %d\n", st3.studentId);       //st2의 아이디인 200
	printf("st3.grade= %c\n", st3.grade);                 //st2의 등급인 B출력
	/* equality test */
	/*
	* if(st3 == st2)
	* printf("equal\n");
	* else
	* printf("not equal\n");
	*/
	return 0;

}