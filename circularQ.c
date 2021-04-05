/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>  

#define MAX_QUEUE_SIZE 4   // MAX_QUEUE_SIZE의 크기는 4로 정의 

typedef char element;    //char형을 elemtent로 씀

typedef struct {                      //구조체 QueueType를 선언한다.
	element queue[MAX_QUEUE_SIZE];
	int front, rear;               //큐에서 사용할 front,rear 선언
}QueueType;


QueueType* createQueue();        //각종 함수 선언
int freeQueue(QueueType* cQ);
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);
element getElement();

int main(void)
{
	QueueType* cQ = createQueue();  //QueueType 포인터 cQ를 createQueue 함수를 이용해서 생성한다
	element data;     //typedef char element 떄문에 char data와 같다.
	char command;   //어떤 함수를 수행할지 입력을 받기위해 command 선언
    printf("[----- [Noh Min Sung] [2018038076] -----]\n");

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //command 입력받음

		switch (command) {        //switch통해 입력받은 command에 따라 다른 함수 실행
		case 'i': case 'I':   // 사용자가 i,I 입력하면 
			data = getElement();  //getElement함수를 이용해 데이터를 입력받고
			enQueue(cQ, data);    //enQueue함수에 cQ와 data를 전달
			break;
		case 'd': case 'D':        // 사용자가 d, D 입력하면
			deQueue(cQ, &data);   //enQueue함수에 cQ와 data를 전달
			break;
		case 'p': case 'P':         // 사용자가 p,P 입력하면 
			printQ(cQ);             //printQ함수(Queue 정보출력하는 함수)에 cQ전달
			break;
		case 'b': case 'B':         // 사용자가 b,B 입력하면 
			debugQ(cQ);               //debugQ함ㅁ\수에 cQ전달
			break;
		case 'q': case 'Q':        // 사용자가 q,Q 입력하면 
			freeQueue(cQ);        //freeQueue(동적할당 해제하는 함수)에 cQ전달
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');  //q나 Q 입력 될때까지 반복

	return 1;
}

QueueType* createQueue()    // Queue를 만듬
{
	QueueType* cQ;         // 구조체 포인터 cQ선언
	cQ = (QueueType*)malloc(sizeof(QueueType));  //구조체 QueueType의 크기만큼 cQ 동적할당
	cQ->front = 0;  //cQ->front 를 0으로 초기화
	cQ->rear = 0;   //cQ->rear를 0으로 초기화
	return cQ;   //cQ즉 구조체 포인터의 주소를 return
}

int freeQueue(QueueType* cQ)  //동적할당한 cQ를 해제해줌
{
	if (cQ == NULL) return 1;  //cQ가 가르키는 주소가 비어있으면 즉 이미 할당해제되어있으면 return 1
	free(cQ);  //주소가 있으면 해제해줌
	return 1;   //해제가 되었으니 return 1해준다
}

element getElement()  //문자를 하나 입력 받는 함수
{
	element item; 
	printf("Input element = ");
	scanf(" %c", &item);  //입력받은 문자를 item에 저장
	return item;  //문자 반환
}


/* complete the function */
int isEmpty(QueueType* cQ)     // 큐가 비어있나 확인 하는 함수
{
	if (cQ->front == cQ->rear) {      //만약 구조체 포인터가 가르키는 구조체의 front 와 rear가 같으면 (큐가 비어있을 조건이다. 여기선0)
		printf("Queue가 비어있습니다.");  //큐가 비어있다고 출력해준다.
			return 1;  //리턴
	}
	return 0;   //큐가 비어있지 않으면 return 0 해준다
}

/* complete the function */
int isFull(QueueType* cQ)  //큐가 가득차있나 확인하는 함수
{
	if (cQ->front ==((cQ->rear+1)% MAX_QUEUE_SIZE)){  // 원형큐의 문제점이 가득차서 front랑 rear이랑 같을 때 isEmpty의 조건인 (front==rear)랑 같아져서 구분이 안된다는 것이다. 
		printf("Queue가 가득 차 있습니다.");          // 즉 이걸 해결하기 위해 최대원소의 수를 MAX_QUEUE_SIZE-1로함 즉 (rear+1)%MAX_QUEUE_SIZE랑 front랑 같으면 가득차있다는 뜻
		return 1;
	}
	return 0;  //가득차 있지 않으면 return 0
}


/* complete the function */
void enQueue(QueueType* cQ, element item)   //Queue에 item 추가하는 함수
{	
     if (isFull(cQ))         //만약 가득차있다면 (isFULL)함수 사용해서 판단
      return;               //아래과정 안하고 그냥 리턴한다

	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;   //가득차있지 않다면 rear를 하나 증가시키고 %MAX_QUEUE_SIZE (modulo연산) 값이 rear가 된다. rear++와 같음
	cQ->queue[cQ->rear] = item;       //이 증가한 cQ->queue[cQ->rear] 에 item을 넣어준다
	return;                       //리턴
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)   //Queue의 원소를 삭제
{
	if (isEmpty(cQ))   //만약 큐가 비어있다면(isEmpty)함수 사용해서 판단
		return;            //그냥 리턴한다

	cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;   //큐가 비어있지 않으면 front를 하나 증가시키고 %MAX_QUEUE_SIZE 
	cQ->queue[cQ->front] = '\0';   //그 증가한 front가 가르키는 곳의 값을 null로 초기화

	return;   //종료
}


void printQ(QueueType* cQ)   //Queue의 정보를 출력하는 함수
{
	int i, first, last;   

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;    //front를 하나 증가시킨 다음 %MAX_QUEUE_SIZE 즉 어디부터 들어있나 확인
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;      //(rear + 1)% MAX_QUEUE_SIZE가 last가 됨

	printf("Circular Queue : [");

	i = first;     //시작하는 곳이 i가됨
	while (i != last) {   //i가 마지막이 아니면
		printf("%3c", cQ->queue[i]);  //cQ->queue[i]값 출력
		i = (i + 1) % MAX_QUEUE_SIZE;  //i++;   

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)   //디버그하는 함수
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)        //i = 0; i < MAX_QUEUE_SIZE까지 반복문을 돌면서
	{
		if (i == cQ->front) {                //cQ->front가 있으면 어디에있는지 출력해주고
			printf("  [%d] = front\n", i);
			continue;                           //계속 진행
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);     // 그다음 계속 Queue[i]랑 그 안에 있는 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);     // front랑 rear값 출력해줌
}

