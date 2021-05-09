/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


//void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [Noh Min Sung] [2018038076] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		/*case 'p': case 'P':
			printStack();
			break;*/

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{	
	for (;;) {
		for (; node; node = node->left)
			push(node);

		node = pop();

		if (!node)
			break;

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)  //레벨 순서 순회하는 함수
{

	if (!ptr)     //만약 ptr이 비었으면
		return;      //종료
	enQueue(ptr);   //비어있지 않으면 ptr을 euque해줌

	for (; ; ) {   //무한 루프
		ptr = deQueue();   //ptr은 deQueue한게 됨

		if (ptr) {  //만약 ptr이 존재한다면, 즉 큐에서 뭐가 나왔다면
			printf(" [%d] ", ptr->key);   //ptr의 key를 출력해준다

			if (ptr->left)  //만약 ptr->left가 존재한다면
				enQueue(ptr->left);   //ptr->left 를 enQueue해줌

			if (ptr->right)   //만약 ptr->right가 존재한다면
				enQueue(ptr->right);  //ptr->right를 enQueue해줌
		}

		else  //ptr이 존재하지 않는다면
			break;  //반복문 탈출
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top == -1) {
		//printf("stack is empty\n");
		return NULL;
	}
	return stack[top--];
}

void push(Node* aNode)
{	
	if (top >= MAX_STACK_SIZE - 1) {
		printf("stack is full\n");
	}

	else {
		stack[++top] = aNode;
	}
}



Node* deQueue()    //deQueue 함수 (queue에서 하나 빼는 함수)
{
	if (front == rear) {  //만약 front 랑 rear랑 같다면, 즉 초기조건이고 큐가 비어있는 상태
		//printf("Queue is empty.\n");
		return NULL;   //종료해줌, 
	}

	else { //front 랑 rear랑 다르면 즉 뺄게 있으면
		front = (front + 1) % MAX_QUEUE_SIZE;  //front를 하나 증가시키고 
			return queue[front];  //queue[front]를 리턴해줌
	}
}

void enQueue(Node* aNode)   //enQueue함수 (queue에 하나 넣는 함수)
{
	if ((front == (rear + 1) % MAX_QUEUE_SIZE)) {  //만약 front가 rear+1이랑 같다면 즉 큐가 가득찬 경우라면
		printf("Queue is full.\n");  //큐가 가득 찼다고 출력해줌
		return;  //종료
	}
	else {  //큐가 가득찬 경우가 아니라면
		rear = (rear + 1) % MAX_QUEUE_SIZE;  //rear를 하나 증가시켜주고
		queue[rear] = aNode;   //queue[rear]에 aNode를 넣어준다.
	}
}






