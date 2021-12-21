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

Node* searchIterative(Node* head, int key);  /*IterativeSearch Function*/
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
void iterativeInorder(Node* node)  //iterative방식 Inorder 함수 
{	
	for (;;) {   //무한루프
		for (; node; node = node->left)  //만약 node가 존재한다면 node->left하며 반복
			push(node);  //node를 push한다
        //위의 for문 탈출시 
		node = pop();  //node를 pop한다

		if (!node)  //만약 node가 없다면
			break;  //반복문 탈출

		printf(" [%d] ", node->key);  //node->key값을 출력한다
		node = node->right;  //node는 node->right가 된다
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)  //레벨 순서 순회하는 함수
{
    front = rear = -1;  //front와 rear 는 -1로함, 큐 처음 상태
	if (!ptr)     //만약 ptr이 비었으면
    {
        printf("tree is empty.\n");  //비어있다고 알려주고 종료C
        return;      //종료
    }
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


int deleteNode(Node* head, int key)   //노드 제거하는 함수
{
	Node* temp = searchIterative(head, key);  //temp에 searchIterative 함수 결과 저장

	Node* search = head->left;  //Node 포인터 search 는 head->left를 가르 킴(root)

	if (temp == NULL) {  //temp가 비어있으면 즉, 그 노드에 대한 주소가 null인 경우 즉 트리에 찾는 노드가 없을 경우
		printf("that node is not in tree.\n");   //tree에 노드가 없다고 출력
	}

	else {   //그 외에 트리에 찾는 노드가 있는 경우 

		if (search != NULL) {     //root노드가 널이 아니면

			if (search->key == key) {       //만약 루트노드의 키랑 찾는 키랑 같으면

				//*********루트노드가 리프노드이면
				if ((search->left == NULL) && (search->right == NULL)) {
					head->left = NULL;          //head->left를 NULL로 바꿔준다
					free(search);           //search(root)를 free해준다
					return 1;          //종료
				}

				//********루트노드가 하나의 자식을 가진 비리프 노드라면
				else if ((search->left == NULL) && (search->right != NULL)) {   //만약 오른쪽 자식이 있으면
					head->left = search->right;  //head->left를 search->right로 바꾼다
					free(search);  //search를 free해준다
					return 1;   //종료
				}

				//**********루트노드가 하나의 자식을 가진 비리프 노드라면(2)
				else if ((search->left != NULL) && (search->right == NULL)) {  //만약 왼쪽 자식이 있으면
					head->left = search->left;   //head->left를 search->left로 바꾼다
					free(search);    //search를 free해준다
					return 1;   //종료
				}

				//*********루트노드가 양쪽 다 자식이 있으면
				else if ((search->left != NULL) && (search->right != NULL)) {
					Node* find = NULL;    //Node* find 선언
					find = search->right;   //find는 search->right를 가리킨다

					if (find->left != NULL) {   //만약  find->left가 NULL이 아닌 경우
						Node* findparent = NULL;   //Node* findparent 선언

						while (find->left != NULL) {  //find->left가 null이 아닌 경우
							findparent = find;  //findparent는 find가되고
							find = find->left;  //find 는 find->left로 이동한다
						}
						// 반복문탈출시에 find->left는 NULL이고 가장 왼쪽노드에있다
						search->key = find->key;  //search->key를 find->key로 바꾸고
						findparent->left = NULL;  //findparent->left를 NULL로 하고
						free(find);   //find는 해제해준다
					}

					else if ((find->right != NULL) && (find->left == NULL)) {  //만약 find->right가 NULL이 아니고 find->left는 NULL인 경우
						search->key = find->key;  //search->key는 find->key로 바꾸고
						search->right = find->right;   //search->right는 find->right가 된다
						free(find);  //find는 해제해준다
					}

					else if ((find->left == NULL) && (find->right == NULL)) {  //만약 find->left가 NULL 이고 find->right도 NULL인 경우
						search->key = find->key;    //search->key는 find->key로 바꾸고
						free(find);         //find는 해제해준다
						search->right = NULL;   //search->right는 NULL로 해준다
					}

				}
			}


			else {    //루트 노드의 키랑 같지 않으면

				while (search->key != key) {   //search->key==key이면 반복문 탈출
					temp = search;             //temp는 search를 가르킨다
					if (key < search->key)     //만약 key < search->key이면
						search = search->left;   //search는 search->left가 됨
					else if (key > search->key)  //만약 key > search->key이면
						search = search->right;  //search는 search->right가 됨
				}

				//*********search 노드가 리프노드인 경우
				if ((search->left == NULL) && (search->right == NULL)) {

					if (temp->right == search) { //만약 temp->right가 search이면
						free(search);    //search를 free하고
						temp->right = NULL;   //temp->right를 null로 한다
						return 1;  //종료
					}
					else if (temp->left == search) {  //만약 temp->left가 search이면
						free(search);  //search를 free하고
						temp->left = NULL;  //temp->left를 null로 한다
						return 1;  //종료
					}
				}

				//*******search->left가 NULL이 아닌 경우(하나의 자식을 가진경우)
				else if ((search->left != NULL) && (search->right == NULL)) {
					if (temp->right == search) { //만약 temp->right가 search이면
						temp->right = search->left;   //temp->right를 search->left
						free(search);    //search를 free한다
						return 1;  //종료
					}
					else if (temp->left == search) {  //만약 temp->left가 search이면
						temp->left = search->left;  //temp->left를 search->left로 한다
						free(search);  //search를 free한다
						return 1;  //종료
					}
				}


				//*******search->right가 NULL이 아닌 경우(하나의 자식을 가진경우2)
				else if ((search->left == NULL) && (search->right != NULL)) {
					if (temp->right == search) { //만약 temp->right가 search이면
						temp->right = search->right;   //temp->right를 search->right로 한다
						free(search);    //search를 free한다
						return 1;  //종료
					}
					else if (temp->left == search) {  //만약 temp->left가 search이면
						temp->left = search->right;  //temp->left를 search->right로 한다
						free(search);  //search를 free한다
						return 1;  //종료
					}
				}

				//********search가 양쪽 다 자식을 가진 경우
				else if ((search->left != NULL) && (search->right != NULL)) {  
					Node* find = NULL;    //Node* find 선언
					find = search->right;   //find는 search->right를 가리킨다

					if (find->left != NULL) {   //만약  find->left가 NULL이 아닌 경우
						Node* findparent = NULL;   //Node* findparent 선언

						while (find->left != NULL) {  //find->left가 null이 아닌 경우
							findparent = find;  //findparent는 find가되고
							find = find->left;  //find 는 find->left로 이동한다
						}
						// 반복문탈출시에 find->left는 NULL이고 가장 왼쪽노드에있다
						search->key = find->key;  //search->key를 find->key로 바꾸고
						findparent->left = NULL;  //findparent->left를 NULL로 하고
						free(find);   //find는 해제해준다
					}

					else if ((find->right != NULL) && (find->left == NULL)) {  //만약 find->right가 NULL이 아니고 find->left는 NULL인 경우
						search->key = find->key;  //search->key는 find->key로 바꾸고
						search->right = find->right;   //search->right는 find->right가 된다
						free(find);  //find는 해제해준다
					}

					else if ((find->left == NULL) && (find->right == NULL)) {  //만약 find->left가 NULL 이고 find->right도 NULL인 경우
						search->key = find->key;    //search->key는 find->key로 바꾸고
						free(find);         //find는 해제해준다
						search->right = NULL;   //search->right는 NULL로 해준다
					}

				}

				else {  //트리에 노드가 없는 경우
					printf("Tree is empty.\n");   //트리가 비어있다고 출력해준다
					return 1;  //종료
				}

			}
		}
	}
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



Node* pop()  //pop하는 함수
{
	if (top == -1) {  //top 이 -1인경우 스택이 비어있으니 pop할게 없다
		//printf("stack is empty\n");
		return NULL;  //return NULL
	}
	return stack[top--];  //비어있지 않으면 stack[top--]을 return 해준다
}

void push(Node* aNode)  //push하는 함수
{	
	if (top >= MAX_STACK_SIZE - 1) {  //top >= MAX_STACK_SIZE - 1 ,즉 스택의 크기보다 크면(다 차있으면)
		printf("stack is full\n");  //가득차있다고 알려줌
	}

	else {  //아닐 경우
		stack[++top] = aNode;  //stack[++top]에 노드를 넣어준다
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

Node* searchIterative(Node * head, int key)  //Iterative 방식으로 위치 찾는 함수
{
	Node* search = head->left;  //Node 포인터 search 는 head->left를 가르 킴(root)

	while (search != NULL) {   //search 가 NULL일떄까지 반복
		if (key < search->key)    //만약 key < search->key이면
			search = search->left;  //search는 search->left가 됨
		else if (key > search->key)           //만약 key > search->key이면
			search = search->right;  //search는 search->right가 됨
		else if (key == search->key)  //key랑 search->key랑 같으면
			return search;  //search를 리턴한다
		}

	return NULL;   //while문 탈출시 NULL를 return 
}






