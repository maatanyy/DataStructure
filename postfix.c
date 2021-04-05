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

/* stack ������ �켱����, lparen=0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���ʰ�ȣ */
	rparen = 9,  /* ) �����ʰ�ȣ*/
	times = 7,   /* * ����*/
	divide = 6,  /* ������ */
	plus = 5,    /* ���ϱ�*/
	minus = 4,   /* -���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ����*/

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixpush(char x);   //postfix�� push
char postfixPop();         //postfix���� pop
void evalPush(int x);    //����� �� ����� Push

int evalPop();           //����� �� ����� Pop
void getInfix();         //��ȯ�� ���� �Է� �޴� �Լ�
precedence getToken(char symbol);  //���ڸ� �޾Ƽ� ������� ���� (,),+��
precedence getPriority(char x);    //���ڸ� �޾Ƽ� token�Լ� ����
void charCat(char* c);     //��ȯ�� ���� ��� �̾�� �Լ�
void toPostfix();         //postfix�� ��ȯ��Ű�� �Լ�
void debug();            //������ ��Ÿ���ִ� �Լ�
void reset();             //���½�Ű�� �Լ�
void evaluation();        //��ȯ�Ƚ��� ����� �ϴ� �Լ�

int main()
{
	printf("[----- [��μ�] [2018038076] -----]\n");
	char command;


	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //������ ���� ���� �Է� ����

		switch(command) {
		case 'i': case 'I':  // i������ getInfix()�Լ� ���
			getInfix();
			break;
		case 'p': case 'P':  // p������ toPostfix()�Լ� ���
			toPostfix();
			break;
		case 'e': case 'E':   //e ������ evaluation()�Լ� ���
			evaluation();
			break;
		case 'd': case 'D':    //d ������ debug()�Լ� ���
			debug();
			break;
		case 'r': case 'R':   //r ������ reset()�Լ� ���
			reset();
			break;
		case 'q': case 'Q':  //q ������ break;
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //q�Է¹����� ���� �ݺ�

	return 1;
}

void postfixPush(char x)   //Push ���� top�ϳ� ������Ű�� �߰�����
{
    postfixStack[++postfixStackTop] = x;
}


char postfixPop()   //POP���� top=-1(����ִ�)�� �ƴϸ� �ϳ� pop�ϰ� top--
{
    char x;
    if(postfixStackTop == -1)          //������ ������� ������
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];   
    }
    return x;
}

void evalPush(int x)      // ���� ���ÿ� push����  postfixPush�� ������ ����
{
    evalStack[++evalStackTop] = x;
}

int evalPop()         // ���� ���ÿ� pop����  postfixPop�� ������ ����
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է� �޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�
 */


void getInfix()            //������ �޴� �Լ�, ��ȯ�� ���� �Է� ����
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)    //symbol�� �Է¹޾Ƽ� ������� switch���� ���� ������ �� ���� �´� �� return����
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

precedence getPriority(char x)   //x�� �޾Ƽ� gettoken�Լ� �������� precedence��
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾� postfixExp�� �߰�
 */

void charCat(char* c)  //toPostfix()�Լ����� ���� �޾Ƽ� postfixExp�� �����Ҷ����� �Լ�
{
	if (postfixExp == '\0')      //��������� ����
		strncpy(postfixExp, c, 1);
	else                            //������� ������
		strncat(postfixExp, c, 1);  //���ڿ��� �̾����
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�
 * ����� postfix�� postFixExp�� ����ȴ�
 */

void toPostfix()
{
	
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	char y;

	/* exp�� ������Ű�鼭 ���ڸ� �а� postfix�� ����**/
	while(*exp != '\0')
	{
	    x=*exp;

		switch(getPriority(x))
		{
		case operand: charCat(&x);    //���ڸ� �ٷ� postfixExp�� �־���
					 	break;           //switch�� Ż��

					  
        case lparen: postfixPush(x);   // (�� ���ÿ� push
						break;         //switch�� Ż��


		case rparen: while(getPriority(postfixStack[postfixStackTop])!=lparen)  //������ ��ȣ�� ������ (�� ���� ������ �ݺ��� �Ἥ
		                                                                        //stack�� �ִ°� pop�ؼ� postfixExp�� �־���
		                  {
                            y = postfixPop();  // postfixPop()�ؼ� ������ y�� ����
							charCat(&y);  
		                  }postfixPop();  // �������� ( pop����
						  break;       //switch�� Ż��

		default :   if(getPriority(x)>getPriority(postfixStack[postfixStackTop])){ //�켱������ ������ ž���� ������
			            postfixPush(x);	 //���ÿ� push����
						break;           //switch�� Ż��
		                }

				    else if (getPriority(x)<getPriority(postfixStack[postfixStackTop])){  // �켱������ ������ ž���� ������
					    y=postfixPop();	  // ž�����ϳ��� pop���ְ�
        			    charCat(&y);	  // charCat�Լ��� �̵����� ��ȯ�ϰ� �ִ� �Ŀ�����
						postfixPush(x);   // ���ο��(x) push����
						break;      // switch�� Ż��
				        }

				    else {   // �켱������ �����ϸ� pop&push ���ش�.
					y=postfixPop();	  // ž�����ϳ��� pop���ְ�
        			charCat(&y);	 // charCat�Լ��� �̵����� ��ȯ�ϰ� �ִ� �Ŀ�����
					postfixPush(x);  // ���ο��(x) push����
					break;  // switch�� Ż��
				    }
		}
		/* �ʿ��� ���� �ϼ�*/	
		exp++;  // ���� ���� ����Ű����
	}

	/* �ʿ��� ���� �ϼ� */
	while (postfixStackTop!= -1){   // ������ top�� -1�� �ƴϸ� �� ������� ������
		y=postfixPop();    // pop����
		charCat(&y);        // charCat�̿��ؼ� ��ȯ�ϰ� �ִ½Ŀ� �˸°� ����
	}
}


void debug()    // ���� ���� ������ �����ִ� �Լ�
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);  // ��� �Է� �޾ҳ� ������
	printf("postExp =  %s\n", postfixExp); // ������ȯ�� �� ���
	printf("eval result = %d\n", evalResult);  //����� ���

	printf("postfixStack : "); 
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);  //postfixStack�ȿ� �ִ� �ε��� ���

	printf("\n");

}

void reset()  //�ʱ�ȭ �ϴ� �Լ�
{
	infixExp[0] = '\0';   //	infixExp[0] = '\0'���� �ʱ�ȭ
	postfixExp[0] = '\0';  //  postfixExp[0] = '\0'���� �ʱ�ȭ

	for(int i = 0; i < MAX_STACK_SIZE; i++)  //���ÿ� ���� �� ������
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;  // ����ó�������� top=-1�� ����
	evalStackTop = -1;    //  ����ó�������� top=-1�� ����
	evalResult = 0;   //����� 0���� �ʱ�ȭ
}

void evaluation()   //��ȯ�� ���� ����ϴ� �Լ�
{
	/* postfixExp,evalStack�� �̿��� ��� */
	char *exp = postfixExp;  //��ȯ�� postfixExp�� ����Ű����
	char x,y,z; 
	while(*exp != '\0'){	//*exp�� ���ڿ��� �� �����ε� '\0'�� ���������� �ݺ����Ἥ �˻�
		x=*exp;  //�ּҾȿ� �ִ� �� �� �����ϳ��� x�� �־���

		if(getPriority(x)==operand){   //���� operand�̸�
			x = x-'0';        //'0'�� ���� ���ڷε� ���� ���� �� ���� 
			evalPush(x);      //�� ���� evalpush�� �̿��� push  ����pop�Ѱ� ������ �տ��;���
		}

		else if(getPriority(x)==plus){  //���� plus��
			y=evalPop();        //pop�ؼ� �� ����
			z=evalPop();        //pop�ؼ� �� ����
			evalPush(z+y);  //�� ���� evalpush�� �̿��� push  ����pop�Ѱ� ������ �տ��;���
		} 

		else if(getPriority(x)==minus){ // ���� minus��
			y=evalPop();   //pop�ؼ� �� ����
			z=evalPop();     //pop�ؼ� �� ����
			evalPush(z-y);  //�� ���� evalpush�� �̿��� push  ����pop�Ѱ� ������ �տ��;���
		}

		else if(getPriority(x)==times){  // ���� times��
			y=evalPop();    //pop�ؼ� �� ����
			z=evalPop();    //pop�ؼ� �� ����
			evalPush(z*y);  //�� ���� evalpush�� �̿��� push  ����pop�Ѱ� ������ �տ��;���
		}

		else if(getPriority(x)==divide){  // ���� divide��
			y=evalPop();    //pop�ؼ� �� ����
			z=evalPop();    //pop�ؼ� �� ����
			evalPush(z/y);  //�� ���� evalpush�� �̿��� push  ����pop�Ѱ� ������ �տ��;���
		}
		exp++;  //������ ����Ű���� ������Ŵ
	}

	evalResult=evalPop();  //�������� pop�ϸ� ������� ����
}
