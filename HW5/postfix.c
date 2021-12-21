/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen=0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽괄호 */
	rparen = 9,  /* ) 오른쪽괄호*/
	times = 7,   /* * 곱셈*/
	divide = 6,  /* 나누기 */
	plus = 5,    /* 더하기*/
	minus = 4,   /* -빼기 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스텍 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택*/

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과물 저장 */

void postfixpush(char x);   //postfix로 push
char postfixPop();         //postfix에서 pop
void evalPush(int x);    //계산할 때 사용할 Push

int evalPop();           //계산할 때 사용할 Pop
void getInfix();         //변환할 식을 입력 받는 함수
precedence getToken(char symbol);  //문자를 받아서 어떤거인지 리턴 (,),+등
precedence getPriority(char x);    //문자를 받아서 token함수 리턴
void charCat(char* c);     //전환한 식을 계속 이어가는 함수
void toPostfix();         //postfix로 전환시키는 함수
void debug();            //정보를 나타내주는 함수
void reset();             //리셋시키는 함수
void evaluation();        //변환된식의 계산을 하는 함수

int main()
{
	printf("[----- [노민성] [2018038076] -----]\n");
	char command;


	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //어떤명령을 수행 할지 입력 받음

		switch(command) {
		case 'i': case 'I':  // i누를시 getInfix()함수 출력
			getInfix();
			break;
		case 'p': case 'P':  // p누를시 toPostfix()함수 출력
			toPostfix();
			break;
		case 'e': case 'E':   //e 누를시 evaluation()함수 출력
			evaluation();
			break;
		case 'd': case 'D':    //d 누를시 debug()함수 출력
			debug();
			break;
		case 'r': case 'R':   //r 누를시 reset()함수 출력
			reset();
			break;
		case 'q': case 'Q':  //q 누를시 break;
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //q입력받을때 까지 반복

	return 1;
}

void postfixPush(char x)   //Push 구현 top하나 증가시키고 추가해줌
{
    postfixStack[++postfixStackTop] = x;
}


char postfixPop()   //POP구현 top=-1(비어있다)가 아니면 하나 pop하고 top--
{
    char x;
    if(postfixStackTop == -1)          //스택이 비어있지 않으면
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];   
    }
    return x;
}

void evalPush(int x)      // 계산용 스택에 push구현  postfixPush과 내용은 같음
{
    evalStack[++evalStackTop] = x;
}

int evalPop()         // 계산용 스택에 pop구현  postfixPop과 내용은 같음
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력 받는다.
 * infixExp에는 입력된 값을 저장한다
 */


void getInfix()            //정보를 받는 함수, 변환할 식을 입력 받음
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)    //symbol을 입력받아서 어떤거인지 switch문을 통해 구별후 그 값에 맞는 것 return해줌
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)   //x를 받아서 gettoken함수 리턴해줌 precedence형
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아 postfixExp에 추가
 */

void charCat(char* c)  //toPostfix()함수에서 값을 받아서 postfixExp에 저장할때쓰는 함수
{
	if (postfixExp == '\0')      //비어있으면 복사
		strncpy(postfixExp, c, 1);
	else                            //비어있지 않으면
		strncat(postfixExp, c, 1);  //문자열을 이어붙임
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다
 * 변경된 postfix는 postFixExp에 저장된다
 */

void toPostfix()
{
	
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	char y;

	/* exp를 증가시키면서 문자를 읽고 postfix로 변경**/
	while(*exp != '\0')
	{
	    x=*exp;

		switch(getPriority(x))
		{
		case operand: charCat(&x);    //문자면 바로 postfixExp에 넣어줌
					 	break;           //switch문 탈출

					  
        case lparen: postfixPush(x);   // (면 스택에 push
						break;         //switch문 탈출


		case rparen: while(getPriority(postfixStack[postfixStackTop])!=lparen)  //오른쪽 괄호가 나오면 (가 나올 때까지 반복문 써서
		                                                                        //stack에 있는거 pop해서 postfixExp에 넣어줌
		                  {
                            y = postfixPop();  // postfixPop()해서 꺼내서 y에 저장
							charCat(&y);  
		                  }postfixPop();  // 마지막에 ( pop해줌
						  break;       //switch문 탈출

		default :   if(getPriority(x)>getPriority(postfixStack[postfixStackTop])){ //우선순위가 스택의 탑보다 높으면
			            postfixPush(x);	 //스택에 push해줌
						break;           //switch문 탈출
		                }

				    else if (getPriority(x)<getPriority(postfixStack[postfixStackTop])){  // 우선순위가 스택의 탑보다 낮으면
					    y=postfixPop();	  // 탑에서하나를 pop해주고
        			    charCat(&y);	  // charCat함수로 이동시켜 변환하고 있는 식에적용
						postfixPush(x);   // 새로운건(x) push해줌
						break;      // switch문 탈출
				        }

				    else {   // 우선순위가 동등하면 pop&push 해준다.
					y=postfixPop();	  // 탑에서하나를 pop해주고
        			charCat(&y);	 // charCat함수로 이동시켜 변환하고 있는 식에적용
					postfixPush(x);  // 새로운건(x) push해줌
					break;  // switch문 탈출
				    }
		}
		/* 필요한 로직 완성*/	
		exp++;  // 다음 문자 가르키게함
	}

	/* 필요한 로직 완성 */
	while (postfixStackTop!= -1){   // 스택의 top이 -1이 아니면 즉 비어있지 않으면
		y=postfixPop();    // pop해줌
		charCat(&y);        // charCat이용해서 변환하고 있는식에 알맞게 적용
	}
}


void debug()    // 각종 상태 정보를 보여주는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);  // 어떤식 입력 받았나 보여줌
	printf("postExp =  %s\n", postfixExp); // 후위변환한 식 출력
	printf("eval result = %d\n", evalResult);  //계산결과 출력

	printf("postfixStack : "); 
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);  //postfixStack안에 있는 인덱스 출력

	printf("\n");

}

void reset()  //초기화 하는 함수
{
	infixExp[0] = '\0';   //	infixExp[0] = '\0'으로 초기화
	postfixExp[0] = '\0';  //  postfixExp[0] = '\0'으로 초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++)  //스택에 값도 다 없애줌
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;  // 스택처음상태인 top=-1로 설정
	evalStackTop = -1;    //  스택처음상태인 top=-1로 설정
	evalResult = 0;   //결과도 0으로 초기화
}

void evaluation()   //변환된 식을 계산하는 함수
{
	/* postfixExp,evalStack을 이용한 계산 */
	char *exp = postfixExp;  //변환된 postfixExp를 가르키게함
	char x,y,z; 
	while(*exp != '\0'){	//*exp는 문자열의 한 글자인데 '\0'즉 마지막까지 반복문써서 검사
		x=*exp;  //주소안에 있는 값 즉 글자하나를 x에 넣어줌

		if(getPriority(x)==operand){   //만약 operand이면
			x = x-'0';        //'0'을 빼야 숫자로된 값을 얻을 수 있음 
			evalPush(x);      //이 값을 evalpush를 이용해 push  먼저pop한게 연산의 앞에와야함
		}

		else if(getPriority(x)==plus){  //만약 plus면
			y=evalPop();        //pop해서 값 저장
			z=evalPop();        //pop해서 값 저장
			evalPush(z+y);  //이 값을 evalpush를 이용해 push  먼저pop한게 연산의 앞에와야함
		} 

		else if(getPriority(x)==minus){ // 만약 minus면
			y=evalPop();   //pop해서 값 저장
			z=evalPop();     //pop해서 값 저장
			evalPush(z-y);  //이 값을 evalpush를 이용해 push  먼저pop한게 연산의 앞에와야함
		}

		else if(getPriority(x)==times){  // 만약 times면
			y=evalPop();    //pop해서 값 저장
			z=evalPop();    //pop해서 값 저장
			evalPush(z*y);  //이 값을 evalpush를 이용해 push  먼저pop한게 연산의 앞에와야함
		}

		else if(getPriority(x)==divide){  // 만약 divide면
			y=evalPop();    //pop해서 값 저장
			z=evalPop();    //pop해서 값 저장
			evalPush(z/y);  //이 값을 evalpush를 이용해 push  먼저pop한게 연산의 앞에와야함
		}
		exp++;  //다음을 가르키도록 증가시킴
	}

	evalResult=evalPop();  //마지막에 pop하면 계산결과가 나옴
}
