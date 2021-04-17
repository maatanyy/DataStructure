/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */

int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {     //헤더노드 초기 설정하는 함수

	if (*h != NULL)           //이중포인터h라서 *h가 headnode의 주소가 되고 이게 NULL이 아니면 즉 다른게 있다면 free를 통해 해제해준다.
		freeList(*h);        //free함수 호출하고 *h를 보내준다

	headNode* temp = (headNode*)malloc(sizeof(headNode));   //만약 *h가 NULL이면 즉 헤드노드가 없다면 만들어줘야한다. 
	temp->first = NULL;   //해드노드가 가르키는 곳을 비워둔다
	*h = temp;         //*h의 값을로 temp의 주소를 넣어준다.

	return 1;
}


int freeList(headNode* h){   //동적할당한 메모리를 해제하는 함수

	listNode* p = h->first;    //리스트노드 포인터 p는 h->first

	listNode* prev = NULL;   	//새로운 포인터를 하나 초기화하고 선언한다.
	while (p!= NULL) { 	 	//p가 NULL이 아니면, 즉 마지막까지 반복문을 통해 이동한다
		prev = p;   	//prev를 통해 p를 가르키고
		p = p->rlink;   	//p는 p오른쪽 링크로 이동한다
		free(prev);   	//prev를 해제해준다
	}
	free(h); 	 //헤더노드를 마지막에 해제해준다.
	return 0;

}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p!=NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* p = h->first;               //p로 headNode포인터 대신해서 쓰겠다 선언
	listNode* node = (listNode*)malloc(sizeof(listNode));           //새로운 노드 동적 할당

	node->key = key;                         //노드의 키에 키값 넣어줌
	node->llink = NULL;             //노드의 llink비워줌
	node->rlink = NULL;             //노드의 rlink비워줌

	if (p){        //만약 p가 비어있지 않다면
		while (p->rlink != NULL) {   //p링크가 널이 아니면 계속 다음 으로 p이동 즉,마지막으로 이동하는 과정
			p = p->rlink;
		}
		p->rlink = node;   //마지막 p의 링크에 노드를 이어줌
	}

	else {        //p가 비어있다면 즉 리스트에 값이 없는 경우
		h->first = node;          //node를 h->first가 가르키게 한다.
	}

	return 0;
}




/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {   //앞에 노드를 추가하는 함수

	listNode* p = h->first;     //헤드포인터를 대신해서쓸 p선언
	listNode* newnode = (listNode*)malloc(sizeof(listNode));   //새로운노드를 동적할당해줌
	newnode->key = key;  //새로운노드의 키에 키를 대입해준다

	newnode->llink = NULL;	      //newnode의 llink는 NULL로해준다
	newnode->rlink = h->first;     //newnode->rlink가 h->first와 같은 걸 가리키게한다
	h->first = newnode;           //newnode를 h->first가 가르키게 한다.
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


