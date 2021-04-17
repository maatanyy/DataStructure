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

	printf("*************[노민성][2018038076]********\n");

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

	listNode* p = h->first;               //p로 headNode포인터 대신 해서 쓸거라 선언
	listNode* node = (listNode*)malloc(sizeof(listNode));           //새로운 노드 동적 할당

	node->key = key;                 //노드의 키에 키값 넣어줌
	node->llink = NULL;             //노드의 llink비워줌
	node->rlink = NULL;             //노드의 rlink비워줌

	if (p){        //만약 p가 비어있지 않다면
		while (p->rlink != NULL) {   //p링크가 널이 아니면 계속 다음 으로 p이동 즉,마지막으로 이동하는 과정
			p = p->rlink;
		}
		p->rlink = node;   //마지막 p의 링크에 노드를 이어줌
		node->llink = p; //새노드의 llink에 p->rlink 이어줌
	}

	else {        //p가 비어있다면 즉 리스트에 값이 없는 경우
		h->first = node;          //node를 h->first가 가르키게 한다.
	}

	return 0;
}




/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {   //list 마지막 노드를 삭제하는 함수

	listNode* p=h->first;   //p는 h->first를 가르킴

	listNode* trail;   //listNode포인터 trail 선언
	listNode* current;	//listNode포인터 current 선언

	if(p){	    //만약 p가 비어있지 않다면, 즉 리스트에 값이 있다면

		if(p->rlink==NULL){   //만약 p->rlink가 비어있다면 즉 p가 마지막이면
		h->first = p->rlink;     //마지막을 가르키고(NULL)
		free(p);            //p를 초기화시킴
		}

		else{   //만약 2개이상의 인덱스가 리스트에 남아있다면
			trail=p;    //trail이 p를 가르키고
			current = p->rlink;   //current는 p->rlink가 됨, 즉 한칸 이동
  
			while(current->rlink!=NULL){  //만약 current의 rlink가 눌이 아니라면 즉 마지막이 아니라면
				trail=current;   //trail이 current가 됨
				current=current->rlink;   //current는 current의 rlink가됨.한칸 이동
			}
								//반복문 빠져나왔을때 마지막에 current가 있고 trail을 그 한칸전에 있음
				free(current);   //current를 메모리 해제해줌 (마지막)
				trail->rlink=NULL;  //trail의 오른쪽 링크를 null로 바꿔줌
		} 
	}

	else{  										// 만약 p가 비어있다면 , 즉 delete할게 없다면
		printf("There is nothing to delete\n");  	// 지울게 없다고 출력해줌
	}

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
int deleteFirst(headNode* h) {     //처음을 지우는 함수

	listNode* p = h->first;     //listNode포인터 p를 헤드포인터 대신해서 씀

	if(p){      //만약 p가 비어있지 않다면
		h->first = p->rlink;     //h->first가 가르키는 곳을 p의 오른쪽 링크로 이동
		free(p);  //p는 해제해준다
		p=p->rlink;    //p->rlink가 p가 된다

	}
	 
	else{          //만약 p가 비어있다면
		printf("There is nothing to delete\n");   //지울게 없다고 출력해준다
	}

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
	
	listNode* p = h->first;							// listNode포인터 p를 헤드포인터 대신해서 씀
	listNode* node = (listNode*)malloc(sizeof(listNode));           //새로운 노드 동적 할당

	node->key = key;       //node->key에 key를 넣어준다
	node->llink = NULL;     //node->link는 NULL로 초기화
	node->rlink = NULL;     //node->rink는 NULL로 초기화

	if (p) {   //만약 리스트가 비어있지 않다면

		while (p->rlink != NULL) {  //p->rlink!=NULL이면 계속 반복
			
			if ((node->key > p->key) && (node->key < p->rlink->key)) {  // 만약 p->key < 새노드 < p->rlink->key의 구조라면
				node->llink = p;          //node의 llink가 p를 가르키게하고
				node->rlink = p->rlink;    //node의 rlink가 p의 rlink가 가르키는걸 가르키게하고
				p->rlink->llink = node;     //p->rlink->llink가ㅏ node를 가르키게하고
				p->rlink = node;      //p->rlink는 node를 가르킨다
				break;   //반복문 탈출
			}

			else if ((node->key == p->key)) {    //만약 node->key == p->key라면
				node->llink = p;             //p다음에 node연결해줬음
				node->rlink = p->rlink;       //node->rlink가 p->rlink가 가르키는걸 가리킴
				p->rlink->llink = node;      //p->rlink!=NULL일때 반복문이 돌아가니 p->rlink->llink가 문제없이 돌아감
				p->rlink = node;        //p->rlink에 node 이어줌
				break;    //반복문 탈출
			}
		
			else if ((node->key < p->key)) {
				node->rlink = p;     //newnode->rlink가 h->first와 같은 걸 가리키게한다
				p->llink = node;			// p->llink가 node를 가르킴
				h->first = node;           //newnode를 h->first가 가르키게 한다.

				break;    //반복문 탈출
			}
			p = p->rlink;   //위 조건에 해당안될시 , 즉 기존노드 < 기존노드 < 새노드의 경우 p를 옆으로 이동

		}

		//위 반복문을 나왔을 경우인데 두가지의 경우가 있다 첫번째 케이스는 리스트의 원소가 하나일 경우고 두번째는 리스트의 원소가 여러개인데 새노드의 값이 제일 큰 경우이다

		if (p->key < node->key) {   //만약 새노드의 값이 제일 크면 맨 뒤에 이어준다 이건 두가지 경우 똑같이 작용한다.
			p->rlink = node;     //p->rlink에 node를 이어줌
			node->llink = p;     //node->llink는 p를 가르킨다
			return 0;       //리턴
		}

		else if ((p->key > node->key)&&(p->llink!=NULL)) {     //리스트의 원소가 하나인경우 새 노드값이 p->key보다 작은경우
			node->llink = p->llink;    //node의 llink가 p의 llink가 가르키는걸 가르키게하고
			node->rlink = p;   //node의 rlink가 p를 가르키게한다
			return 0;   //리턴
		}

		else if ((p->key > node->key) && (p->llink == NULL)) {  //리스트의 원소가 여러개인 경우 새 노드값이 p->key보다 작은경우
		node->rlink = h->first;     //newnode->rlink가 h->first와 같은 걸 가리키게한다
		h->first = node;           //newnode를 h->first가 가르키게 한다.
		return 0;        //리턴
		}

		else if (p->key == node->key) {  //만약 p key와 node key가 같은 경우
			p->rlink = node;           //p->rlink가 노드를 가르키게 한다
			node->llink = p;            //node->llink는 p를 가르키게 한다
			return 0;      //리턴
		}
	}

	else {    //만약 p가 비어져있는경우라면
		insertFirst(h, key);  //insertFirst함수 호출한다
	}
			return 0;	
}
/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	
	listNode* p = h->first;     //listNode포인터 p를 헤드포인터 대신해서 씀

	listNode* trail;   //listNode포인터 trail 선언
	listNode* current;	//listNode포인터 current 선언

	if (p) {	    //만약 p가 비어있지 않다면, 즉 리스트에 값이 있다면

		if (p->rlink == NULL) {   //만약 p->rlink가 비어있다면 즉 p가 마지막이면
			if (p->key != key) {    //만약 p->key가 입력받은 key랑 다르면
				printf("There is no that key in list.\n");   //그런 키가 없다고 출력해줌
			}

			else {    //만약 p->key가 입력받은 key랑 같으면
				h->first = p->rlink;     //마지막을 가르키고(NULL)
				free(p);            //p를 초기화시킴
			}
		}

		else {   //만약 2개이상의 인덱스가 리스트에 남아있다면

			while (p->rlink!=NULL) {
				
				trail = p;    //trail이 p를 가르키고
				current = p->rlink;   //current는 p->rlink가 됨, 즉 한칸 이동

				if (trail->key == key) {   //만약 trail의 key랑 key랑 같다면
					h->first = trail->rlink;       //h->first가 trail의 rlink를 가르키게하고
					free(trail);         //trail의 메모리를 해제해준다
					p = p->rlink;       //p가 그다음으로 이동하고
					return 0;         //종료시킨다
				}

				else if (current->key == key) {    //만약 current의 키가 키이면,즉 trail 다음 리스트의 키값이 키이면

					if (current->rlink != NULL) {   //만약 current->rlink가 null이 아닌 경우 즉 list원소의 수가 3개 이상인경우,이렇게 나눈 이유는 아래에서 쓰는 current->rlink->llink때문에 2개일때는 오류가뜸
						trail->rlink = current->rlink;   //current->rlink를 trail의 rlink가 가르키게 해주고
						current->rlink->llink = current->llink;   //current의 rlink의 llink 즉 다음노드의 왼쪽링크가 current의 llink 즉 trail을 가르키게 해준다
						free(current);  //current를 해제해준다
						return 0;
					}

					else {   //만약 current->rlink가 null인 경우 즉 리스트의 원소의 수가 2개인 경우
						trail->rlink = current->rlink;   //trail->rlink가 current->rlink를 가르키도록 (여기선 null이됨)
						free(current);  //current 메모리 해제해준다
						return 0;
					}
				}

				else if ((trail->key != key) && (current->key != key)) {       //만약 trail key도 key가 아니고 current key도 key가 아니면
					p = p->rlink;   //p를 한칸 이동한다
				}
			}
				printf("There is no that key in list.\n");   //그런 키가 없다고 출력해줌
		}

	}

	else {          //만약 p가 비어있다면
		printf("There is no element in list, first please add any node.\n");   //지울게 없다고 출력해준다
	}

	return 1;
}

