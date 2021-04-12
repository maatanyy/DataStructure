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

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
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
		case 'z': case 'Z':
			headnode = initialize(headnode);
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

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* p = h->first;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;


	if (h->first == NULL) {
		node->link = h->first;
		h->first = node;
	}

	if (h->first->key > node->key) {
		node->key = key;
		node->link = h->first;
		h->first = node;
	}


	else if (p) {

		while (p->link != NULL) {

			if ((node->key > p->key) && (p->link->key < node->key)) {
				p = p->link;
			}

			else if ((node->key > p->key) && (p->link->key > node->key)) {
				node->link = p->link;
				p->link = node;
				break;
			}

			else if ((node->key > p->key) && (p->link->key == node->key)) {
				node->link = p->link;
				p->link = node;
				break;
			}

			else if ((node->key < p->link->key) && (p->link->link == NULL)) {
				node->link = p->link;
				p->link = node;
			}
		}

	if (p->key > node->key) {
		node->link = h->first;
		h->first = node;
	}

	else {
		p->link = node;
	}
}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* p = h->first;      
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (p) {
		while (p->link != NULL) {
			p = p->link;
		}
		p->link = node;
	}

	else {
		node->link = h->first;
		h->first = node;
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* p = h->first;

	if (p) {
		h->first = p->link;
		free(p);
		p = p->link;
		
	}
	else {
		printf("There is nothing to delete\n");
	}
	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* trail;
	listNode* current;

	listNode* p = h->first;

	if (p) {     // p가 null이 아니면 
		trail = p;
		current = p->link;    //

		if (trail->key == key) {
			h->first = trail->link;
			free(trail);
			p = p->link;
			return 0;
		}

		else if ((trail->key != key) && (current->key != key)) {
			trail = current;
			current = current->link;
		}

		else if ((trail->key != key) && (current->key == key)) {
			trail->link = current->link;
			free(current);
			return 0;
		}

		printf("There is no such number.\n");
	}

	else{
		printf("There is no way to delete.\n");
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* trail;
	listNode* current;

	listNode* p = h->first;

	if (p) {

		if (p->link == NULL) {
			h->first = p->link;
			free(p);
			p = p->link;
		}

		else {
			trail = p;
			current = p ->link;

			while (current->link!= NULL) {
				trail = current;
				current = current->link;
			}
			free(current);
			trail->link = NULL;
		}
	}

	else {
		printf("There is nothing to delete.\n");
	}
	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

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

