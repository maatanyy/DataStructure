/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {        
	int key;             
	struct Node* link;    
} listNode;
//구조체 Node를 listNode로 정의 정수형 key랑 Node포인터 link변수로 가짐

typedef struct Head {     
	struct Node* first;    
}headNode;
//구조체 Head를 headNode로 정의, Node형 포인터 first를 가짐


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);
int insertFirst(headNode* h, int key);    //처음 원소 삽입하는 함수

int insertNode(headNode* h, int key);      //원소 하나 삽입하는 함수
int insertLast(headNode* h, int key);      //마지막 원소 삽입하는 함수

int deleteFirst(headNode* h);            //처음 원소 제거하는 함수
int deleteNode(headNode* h, int key);    //원소 하나 제거하는 함수
int deleteLast(headNode* h);            //마지막 원소 제거하는 함수
int invertList(headNode* h);             //리스트 뒤집는 함수

void printList(headNode* h);        //리스트 출력하는 함수

int main()
{
	char command;         //명령어 선언
	int key;           //key 선언
	headNode* headnode=NULL;     //headNode* headnode 초기화

	printf("******[노민성]*****[2018038076]*****\n");

	do{
		printf("----------------------------------------------------------------\n");      //어떤기능 수행할지 입력받음
		printf("                     Singly Linked List                         \n");
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
		case 'z': case 'Z':             //z클릭시 초기화
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':          //p클릭시 전체출력
			printList(headnode);
			break;
		case 'i': case 'I':         //i클릭시 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':          //d클릭시 제거
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':       //n클릭시 마지막에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':        //e클릭시 마지막 제거
			deleteLast(headnode);
			break;
		case 'f': case 'F':         //f클릭시 처음에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':      //t클릭시 처음 제거
			deleteFirst(headnode);
			break;
		case 'r': case 'R':      //r클릭시 뒤집음
			invertList(headnode);
			break;
		case 'q': case 'Q':   //q클릭시 메모리 해제
			freeList(headnode);
			break;
		default:        //그외의 경우 집중하라고 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');     //q클릭할때 까지 반복

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //빈 노드 하나 동적할당
	node->key = key;                       //노드의 키에 입력받은 key 추가

	node->link = h->first;     //node->link가 h->first와 같은 걸 가리키게한다
	h->first = node;           //node를 h->first가 가르키게 한다.

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */

int insertNode(headNode* h, int key) {

	listNode* p = h->first;   //p로 headNode포인터 대신해서 쓰겠다 선언

	listNode* node = (listNode*)malloc(sizeof(listNode));    //새로운 노드 동적할당
	node->key = key;         //노드의 키에 키값 대입
	node->link = NULL;      //노드의 링크는 null로 초기화


	if (h->first == NULL) {        //만약 비어있으면 (h->first가 가르키는 게 비어있으면)
		node->link = h->first;   //node를 h->first가 처음 가르키는 값으로 만듬
		h->first = node;       //node를 h->first가 가르키게 한다.
	}

	else if (h->first->key > node->key) {    // 만약 h->first가 가르키는 키가 노드의 키보다 크면
		node->key = key;                    // 노드가 h->first가 가르키는 값보다 먼저 오도록 바꿔줌
		node->link = h->first;             //node->link가 h->first와 같은 걸 가리키게한다
		h->first = node;
	}

	else if (h->first->key == node->key) {     //만약 h->first가 가르키는 키값이랑 노드키랑같으면
		node->key = key;                     //node가 h->first가 가리키는값이 되도록 바꿔줌
		node->link = h->first;               //node->link가 h->first와 같은 걸 가리키게한다
		h->first = node;                 //node를 h->first가 가르키게 한다.
	}


	else if (p) {                     //만약 p가 비어있지 않다면 즉 원래 리스트에 값이 있다면

		while (p->link != NULL) {             //p->link!=NULL즉 리스트의 마지막까지 반복

			if ((node->key > p->key) && (p->link->key < node->key)) {    //노드의 키가 p의키보다 크고 p 다음의 키가 node의 키보다 작은 경우 즉 기존<기존<새 노드의 경우
				p = p->link;                 //p를 다음으로 옮겨줌
			}

			else if ((node->key > p->key) && (p->link->key > node->key)) {     //노드의 키가 p의 키보다 크고 p 다음의 키보다 노드의키가 작은 경우   즉 기존<새노드<기존의 경우
				node->link = p->link;            //노드의 링크가 p의 링크를 가리키게함
				p->link = node;               //p링크가 노드를 가리키게함
				break;                         //반복문 빠져나옴
			}

			else if ((node->key > p->key) && (p->link->key == node->key)) {         //node->key가 p의 키보다크고 p다음의키랑 같은 경우 즉 A B B의경우
				node->link = p->link;         //노드의 링크가 p의 링크를 가리키게함
				p->link = node;             //p링크가 노드를 가리키게함
				break;                        //반복문 빠져나옴
			} 

			else if ((node->key < p->link->key) && (p->link->link == NULL)) {     //만약 node 키가 p가 가리키는 곳의 key 보다 작고 p다음의 링크가 비어있으면 즉 노드<마지막리스트
				node->link = p->link;              //노드의 링크가 p의 링크를 가리키게함
				p->link = node;                  //p링크가 노드를 가리키게함
			} 
		}

		//반복문 끝나고 나서 즉 마지막에
	if (p->key > node->key) {     //이 경우는 p가 하나일 경우에 p값이 노드 값보다 크면
		node->link = h->first;          //node->link가 h->first와 같은 걸 가리키게한다
		h->first = node;                //node를 h->first가 가르키게 한다.
	}

	else {    //그 외의 경우 즉 node가 리스트어떤값보다도 큰경우
		p->link = node;     //리스트의 맨뒤에 노드를 연결해준다
	}
}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {       //마지막에 노드 추가해주는 함수

	listNode* p = h->first;        //p로 headNode포인터 대신해서 쓰겠다 선언
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적 할당
	node->key = key;               //노드의 키에 키값 넣어줌
	node->link = NULL;         //노드링크 null로 초기화

	if (p) {        //만약 p가 비어있지 않다면
		while (p->link != NULL) {   //p링크가 널이 아니면 계속 다음 으로 p이동 즉,마지막으로 이동하는 과정
			p = p->link;
		}
		p->link = node;   //마지막 p의 링크에 노드를 이어줌
	}

	else {        //p가 비어있다면 즉 리스트에 값이 없는 경우
		node->link = h->first;    //node->link가 h->first와 같은 걸 가리키게한다
		h->first = node;          //node를 h->first가 가르키게 한다.
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {   //리스트의 처음 삭제하는 함수

	listNode* p = h->first;        //p로 headNode포인터 대신해서 쓰겠다 선언

	if (p) {            //만약 p가 비어있지 않다면
		h->first = p->link;    //h->first가 p->link를 가리키게 하고
		free(p);      //p를 메모리 해제 해주고
		p = p->link;     //p가 다음 p가 되게함
		
	}
	else {      //p가 비어있는 경우
		printf("There is nothing to delete\n");     //지울게 없다고 알려줌
	}
	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {    //노드 제거하는 함수

	listNode* trail;    //이전 노드를 가르킬 포인터 trail선언
	listNode* current;   //현재 노드를 가르킬 포인터 current 선언

	listNode* p = h->first;   //p로 headNode포인터 대신해서 쓰겠다 선언

	if (p) {       // p가 null이 아니면 
		trail = p;           //trial 이 p가됨
		current = p->link;    //curerrent는 p의 링크가 가르키는 게 됨

		if (trail->key == key) {   //만약 트레일값이랑 키값이랑 같으면
			h->first = trail->link;        //h->first가 trail->link를 가리키게하고
			free(trail);       //trail을 해제해줌
			p = p->link;      //p는 그다음게 됨
			return 0;
		}

		else if ((trail->key != key) && (current->key != key)) {      //트레일키도 키가아니고 current키도 키가 아니면
			trail = current;             //trail이 current가 되고
			current = current->link;        //current는 다음게 됨
		}

		else if ((trail->key != key) && (current->key == key)) {       //만약 트레일의키가 키가 아니고 큐렌트의 키카 키면
			trail->link = current->link;      //trail링크가 current링크가 가리키는걸 가리킴
			free(current);        //current메모리해제해줌
			return 0;
		}
		 
		printf("There is no such number.\n");     //그러한숫자가 없다고 알려줌 (만약 리스트에 입력된숫자랑 같은값이 없는경우)
	}

	else{  //리스트가비어있는경우
		printf("It is empty.\n");     //비어있다고 알려줌
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {   //마지막 삭제하는 함수

	listNode* trail;         //이전 노드를 가르킬 포인터 trail선언
	listNode* current;       //현재 노드를 가르킬 포인터 current 선언

	listNode* p = h->first;      //p로 headNode포인터 대신해서 쓰겠다 선언

	if (p) {  //만약 p가 비어있지 않다면

		if (p->link == NULL) {  //p가 마지막이라면
			h->first = p->link;  //p링크가 가리키는 값을 h->first가 가르키게하고
			free(p);    //p를 해제해줌
			p = p->link;   //p는 그다음이 됨
		}

		else {         //그외의 경우
			trail = p;    //trail이 p가 되고
			current = p ->link;   //current는 p다음 링크에 있는게 됨

			while (current->link!= NULL) { //current링크가 비어있지 않다면
				trail = current;      //trail이 current가 되고
				current = current->link;   //crrent는 그다음으로 감
			}
			free(current);  //current해제
			trail->link = NULL;  //trail의 링크를 널로초기화
		}
	}

	else {  //p가 비어있다면
		printf("There is nothing to delete.\n");  //지울게없다고 출력해줌
	}
	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {  //역순으로 재배치 하는 함수

	listNode* p = h->first;     //p로 headNode포인터 대신해서 쓰겠다 선언
	listNode* middle;          //listNode포인터 middle 선언
	listNode* trail;         //listNode포인터 trail 선언

	middle = NULL;   //middle을 널로 초기화

	while (p->link!=NULL) {  // p링크가 널이아니면 즉 마지막이 아니면 반복문 진행
		trail = middle;     // trail이 middle을 가리키게 함 (첫 반복엔 둘다 null)
		middle = p;         // middle이 p를 가리키게 함
		p = p->link;     // p가 그다음을 가르키게함
		middle->link = trail;       //역순이 되도록 가리킴
		h->first = middle;     //첫 노드를 middle에 이음
	}

	//마지막에 한번더 위의 과정을 진행해줘야함
	 trail = middle;
	 middle = p;
	 p = p->link;
	 middle->link = trail;
	 h->first = middle;

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

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

