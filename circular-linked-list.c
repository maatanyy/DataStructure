/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

    printf("[----- [Noh Min Sung] [Student ID] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {       //메모리 해제하는 함수

	listNode* p= NULL;      //새로운 포인터 p 선언하고 NULL로 초기화
	listNode* prev = NULL;    //새로운 포인터 prev 선언하고 NULL로 초기화
	p = h->rlink;         //p는 h->rlink가 가르키는 곳을 가르킨다 

	if (p != h) {        //만약 p가 h랑 다르면 즉 h의 노드의 수가 1개가 아니면
		while (p->rlink != h) {     //p->rlink가 h가 아니면 계속 반복한다
			prev = p;              //prev가 p를 가르키고
			p = p->rlink;   	    //p는 p오른쪽 링크로 이동한다
			free(prev);             //prev를 메모리 해제해준다
		}
		free(p);          //반복문 탈출하면 p랑 h가 남아있으니 먼저 p를 메모리 해제해준다
		free(h);        //마지막으로 h를 메모리 해제해준다
	}

	else        //만약 h의 노드의 수가 1개이면
		free(h);     //바로 h를 메모리해제해준다.

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {  //마지막에 노드를 추가하는 함수

	listNode* newnode = (listNode*)malloc(sizeof(listNode));   //새로운 노드를 동적 할당해줌
	newnode->key = key;  //새로운 노드의 키에 키를 대입해준다


	if (h->rlink == h) {     // 만약 h->rlink가 h인 경우 즉 headnode만 존재하는 경우는 새로운 노드의 경우만 신경쓰면된다
		h->rlink = newnode;        //h->rlink가 newnode를 가르키게한다
		h->llink = newnode;		    //h->ㅣlink가 newnode를 가르키게한다
		newnode->rlink = h;         //newnode->rlink가 h를 가르키게한다
		newnode->llink = h;         //newnode->llink가 h를 가르키게한다
		return 1;                  //리턴
	}

	else {       //headnode외에 다른 노드도 존재하는 경우는 기존노드와의 관계도 신경써야 한다
		newnode->llink = h->llink;      //newnode의 llink가 headnode의 llink가 가르키는 걸 가르키게 한다
		h->llink->rlink = newnode;        //headnode의 llink의 rlink가 newnode를 가르키게 한다
		newnode->rlink = h;             //newnode의 rlink가 headnode를 가르키게 한다
		h->llink = newnode;            //h의 llink가 newnode를 가르키게 한다
		return 1;                     //리턴
	}
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {  //마지막 노드를 삭제하는 함수

	listNode* p = NULL;      //listNode 포인터 p를 선언하고 NULL로 초기화

	if (h->rlink == h) {     //만약 headnode의 rlink가 headnode 즉 리스트에 노드가 없으면
		printf("There is only HeadNode, Nothing to delete.\n");   //지울게 없다고 출력해줌
		return 1;        //리턴
	}

	else {     //만약 headnode의 rlink가 headnode가 아니면 즉, 리스트에 노드가 있으면
		p = h->llink;      //h->llink가 가르키는걸 p가 가르킴
		h->llink->llink->rlink = h;   //h->llink->llink->rlink는 h를 가르킴
		h->llink = h->llink->llink;    //h->llink는 h->llink->llink가 가르키는 걸 가르킴
		free(p);   //p를 해제해준다 (h->llink)
		return 1;  //리턴
	}
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* newnode = (listNode*)malloc(sizeof(listNode));   //새로운 노드를 동적 할당해줌
	newnode->key = key;  //새로운 노드의 키에 키를 대입해준다
	

	if (h->rlink == h) {     // 만약 h->rlink가 h인 경우 즉 headnode만 존재하는 경우는 새로운 노드의 경우만 신경쓰면된다
		h->rlink = newnode;        //h->rlink가 newnode를 가르키게한다
		h->llink = newnode;		    //h->ㅣlink가 newnode를 가르키게한다
		newnode->rlink = h;         //newnode->rlink가 h를 가르키게한다
		newnode->llink = h;         //newnode->llink가 h를 가르키게한다
		return 1;                  //리턴
	}

	else {       //headnode외에 다른 노드도 존재하는 경우는 기존노드와의 관계도 신경써야 한다
		newnode->rlink = h->rlink;      //새로운 노드의 rlink가 headnode의 rlink가 가르키던 걸 가르키게 한다
		h->rlink->llink = newnode;      //새로운 노드의 llink는 headnode를 가르키게 한다
		newnode->llink = h;             //headnode의 llink는 새로운 노드를 가르킨다
		h->rlink = newnode;             //headnode의 rlink는 새로운 노드를 가르킨다
		return 1;                       //리턴
	}
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {   //첫 노드를 삭제하는 함수

	listNode* p = NULL;      //listNode 포인터 p를 선언하고 NULL로 초기화

	if (h->rlink == h) {     //만약 headnode의 rlink가 headnode 즉 리스트에 노드가 없으면
		printf("There is only HeadNode, Nothing to delete.\n");   //지울게 없다고 출력해줌
		return 1;        //리턴
	}

	else {     //만약 headnode의 rlink가 headnode가 아니면 즉, 리스트에 노드가 있으면
		p = h->rlink;      //h->rlink가 가르키는걸 p가 가르킴
		h->rlink->rlink->llink = h;   //h->rlink->rlink->llink는 h를 가르킴
		h->rlink = h->rlink->rlink;    //h->rlink는 h->rlink->rlink가 가르키는 걸 가르킴
		free(p);   //p를 해제해준다 (h->rlink)
		return 1;  //리턴
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* p = h->rlink;  
	listNode* middle;    
	listNode* trail;   

	middle = NULL;
	while (p->rlink != h) {  
		trail = middle;     
		middle = p;         
		p = p->rlink;     
		middle->rlink = middle->llink;     
		middle->llink = p;   
		h->rlink = middle;
	}

	trail = middle;    
	middle = p;			 
	p = p->rlink;
	middle->rlink = middle->llink;    
	middle->llink = p;      
    h->rlink= middle;
	
	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
						
	listNode* p = h->rlink;     //listNode를 선언하고 h->rlink를 가르키게 한다
	listNode* node = (listNode*)malloc(sizeof(listNode));  //새로운 노드 동적 할당
	node->key = key;       //node->key에 key를 넣어준다

	if (h->rlink != h) {   //h->rlink!=h 즉 리스트가 비어있지 않다면

		while (p->rlink != h)	{  //p->rlink!=h 즉 리스트의 마지막까지 반복한다

			if ((node->key > p->key) && (node->key < p->rlink->key)) {    // 만약 p->key < 새노드 < p->rlink->key의 구조라면
				node->rlink = p->rlink;          //node->rlink 는 p->rlink를 가르키고
				node->llink = p;       //node->llink는 p를 가르킨다
				p->rlink->llink = node;     //p->rlink->llink가 node를 가르킨다
				p->rlink = node;      //p->rlink는 node를 가르킨다
				return 0;            //종료한다
			}

			else if ((node->key == p->key)) {    //만약 node->key == p->key라면
				node->llink = p;             //node->llink가 p를 가르키고
				node->rlink = p->rlink;       //node->rlink가 p->rlink가 가르키는걸 가리킨다
				p->rlink->llink = node;      //p->rlink->llink는 node를 가르킨다
				p->rlink = node;        //p->rlink는 node를 가르킨다
				return 0;				 //종료한다
			}

			else if ((node->key < p->key)) {  //만약 node 키가 p키보다 작다면
				node->rlink = p;     //node->rlink가 p를 가르키고
				node->llink = p->llink;		//node->llink는 p->llink를 가르키게한다
				p->llink->rlink = node;           //p->llink->rlink는 node를 가르키게 한다
				p->llink = node;        //p->llink는 node를 가르킨다
				return 0;		 //종료한다
			}
			p = p->rlink;   //위 조건에 해당안될시 , 즉 기존노드 < 기존노드 < 새노드의 경우 p를 옆으로 이동

		}

		//위 반복문을 나왔을 경우인데 두가지의 경우가 있다 첫번째 케이스는 리스트의 원소가 하나일 경우고 두번째는 리스트의 원소가 여러개인데 새노드의 값이 제일 큰 경우이다

		if (p->key < node->key) {   //만약 새노드의 값이 제일 크면 맨 뒤에 이어준다 이건 두가지 경우 똑같이 작용한다.
			node->llink = h->llink;  //node->llink가 h->llink를 가르킨다
			node->rlink = h;    //node->rlink가 h를 가르킨다
			h->llink = node;   //h->link는 node를 가르킨다
			p->rlink = node;   //p->rlink는 node를 가르킨다
			return 0;       //리턴
		}

		else if ((p->key < node->key) && (p->rlink != h)) {     //리스트의 원소가 여러개인 경우 새 노드값이 p->key보다 큰 경우
			node->rlink = h->rlink;   //node->rlink는 h->rlink를 가르킨다
			node->llink = p->llink;  //node->llink는 p->llink를 가르킨다
			h->rlink = node;   //h->rlink는 node를 가르킨다
			p->llink = node;   //p->llink는 node를 가르킨다
			return 0;   //리턴
		}

		else if ((p->key < node->key) && (p->rlink == h)) {  //리스트의 원소가 하나인 경우 새 노드값이 p->key보다 큰 경우
			node->llink = p->llink;    //node->llink는 p->llink를 가르킨다
			node->rlink = p;    //node->rlink는 p를 가르킨다
			p->llink->rlink = node;   //p->llink->rlink는 node를 가르킨다
			p->llink = node;   //p->llink는 node를 가르킨다
			return 0;        //리턴
		}

		else if (p->key == node->key) {  //만약 p key와 node key가 같은 경우
			node->llink = h->llink;   //node->llink는 h->llink를 가르킨다
			node->rlink=h;    //node->rlink는 h를 가르킨다
			h->llink = node;   //h->llink는 node를 가르킨다
			p->rlink = node;    //p->rlink는 node를 가르킨다
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
int deleteNode(listNode* h, int key) {
	listNode* p = h->rlink;     //listNode포인터 p를 헤드포인터 대신해서 씀

	listNode* trail;   //listNode포인터 trail 선언
	listNode* current;	//listNode포인터 current 선언

	if (h->rlink != h) {	   //리스트에 노드가 있다면

		if (p->rlink == h) {   //만약 p->rlink==h즉 노드가 한개라면
			if (p->key != key) {    //만약 p->key가 입력받은 key랑 다르면
				printf("There is no that key in list.\n");   //그런 키가 없다고 출력해줌
				return 1;  //리턴
			}

			else {    //만약 p->key가 입력받은 key랑 같으면
				h->llink = h;   //h->llink가 h를 가르킴
				h->rlink = h;   //h->rlink가 h를 가르킴
				free(p);            //p를 초기화시킴
				return 1;     //리턴
			}
		}

		else {   //만약 2개이상의 인덱스가 리스트에 남아있다면

			while (p->rlink != h) { // 끝까지 반복한다(p->rlink가 h 나올떄까지)

				trail = p;    //trail이 p를 가르키고
				current = p->rlink;   //current는 p->rlink가 됨, 즉 한칸 이동

				if (trail->key == key) {   //만약 trail의 key랑 key랑 같다면
					trail->llink->rlink = trail->rlink;   //trail->llink->rlink가 trail->rlink를 가르킴
					trail->rlink->llink = trail->llink;   //trail->rlink->llink가 trail->llink를 가르킴
					free(trail);         //trail의 메모리를 해제해준다
					return 0;         //종료시킨다
				}

				else if (current->key == key) {    //만약 current의 키가 키이면,즉 trail 다음 리스트의 키값이 키이면

					if (current->rlink != h) {   //만약 current->rlink가 h가 아닌경우
						trail->rlink = current->rlink;   //trail->rlink가 current->rlink를 가르킴
						current->rlink->llink = trail;   //current의 rlink의 llink가 trail을 가르킴
						return 0;  //종료
					}

					else {   //만약 current->rlink가 h인 경우
						trail->rlink = h;   //trail->rlink가 h를 가르킴
						h->llink = trail;  //h->llink가 trail을 가르킴
						free(current);  //current 메모리 해제해준다
						return 0;  //종료
					}
				}

				else if ((trail->key != key) && (current->key != key)) {       //만약 trail key도 key가 아니고 current key도 key가 아니면
					p = p->rlink;   //p를 한칸 이동한다
				}
			}
			printf("There is no that key in list.\n");   //그런 키가 없다고 출력해줌
			return 1;  //리턴
		}

	}

	else {          //만약 p가 비어있다면
		printf("There is no element in list, first please add any node.\n");   //지울게 없다고 출력해준다
		return 1;  //리턴
	}
}


