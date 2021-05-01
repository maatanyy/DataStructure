/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
        printf("[----- [Noh Min Sung] [2018038076] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
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
	return 1;
}



void inorderTraversal(Node* ptr)  //중위 순회 함수
{
	if (ptr) {     //만약 Node* ptr이 존재한다면 if문 실행, 처음엔 root
		inorderTraversal(ptr->left);  //ptr->left로 inorderTraversal 호출, 만약 없으면 넘어감
		printf("[%d]   ", ptr->key);  //ptr의 키 출력 (위의 호출을 넘어간 케이스임)
		inorderTraversal(ptr->right);  //ptr->right로 inorderTraversal 호출, 만약 없으면 넘어감
	}
}

void preorderTraversal(Node* ptr)  //전위 순회 함수
{
	if (ptr) {      //만약 Node* ptr이 존재한다면 if문 실행, 처음엔 root
		printf("[%d]   ", ptr->key);    //ptr->key 출력
		preorderTraversal(ptr->left);   //ptr->left로 preorderTraversal 호출, 만약 없으면 넘어감
		preorderTraversal(ptr->right);  //ptr->right로 preorderTraversal 호출, 만약 없으면 넘어감
	}
}

void postorderTraversal(Node* ptr)   //후위 순회 함수
{
	if (ptr) {     //만약 Node* ptr이 존재한다면 if문 실행, 처음엔 root
		postorderTraversal(ptr->left);  //prt->left로 postorderTraversal 호출, 만약 없으면 넘어감
		postorderTraversal(ptr->right);  //prt->right로 postorderTraversal 호출, 만약 없으면 넘어감
		printf("[%d]   ", ptr->key);   //ptr->key 출력
	}
}


int insert(Node* head, int key)   //노드를 추가하는 함수
{
	Node* newnode = (Node*)malloc(sizeof(Node));   //삽입할 newnode 동적 할당
	newnode->key = key;      //newnode의 key에 입력받은 키 넣어줌
	newnode->left = NULL;   //newnode->left NULL로 초기화
	newnode->right = NULL;  //newnode->right NULL로 초기화

	Node* temp = head->left;  //temp 선언하고 head->left 즉 root를 가르키게함
	Node* temp2 = temp;    //temp2선언하고 temp를 가르키게함 처음엔 root

	if (head->left== NULL) {  //만약 head->left가 NULL인 경우, 즉 tree에 아무 것도 없는 경우는
		head->left = newnode;   //newnode가 root node가 되도록, head->left를 newnode로 해준다.
		return 1;  //종료
	}

	while (temp!=NULL){  //만약 temp!=NULL, 즉 노드가 있는 경우
		temp2 = temp;   //temp2가 temp를 가르키게하고 

		if (temp->key > key) {  //만약 temp->key가 key보다 크면
			temp = temp->left;  //temp는 temp->left가 된다. 
		}

		else if (temp->key < key) {  //만약 temp->key가 key보다 작으면
			temp = temp->right;  //temp는 temp->right가 된다. 
		}
	}
	
      //while문을 빠져 나온 상태, 즉 temp가 NULL인경우
      //위에서 while문 시작시 temp2는 temp를 하기 때문에 while문 탈출 시 temp2는 temp의 부모 위치에 있음
	if (temp2->key > key) {    //만약 temp2->key가 key보다 크면
		temp2->left = newnode;  //temp2->left 가 newnode를 가르키게 함
		return 1;  //종료
	}
	else if (temp2->key < key) {   //temp2->key가 key보다 작으면
		temp2->right = newnode;    //temp2->right가 newnode를 가르키게 함
		return 1;   //종료
	}
}


int deleteLeafNode(Node* head, int key)
{
	Node* temp = NULL;  

	Node* search = head->left;  //Node 포인터 search 는 head->left를 가르 킴(root)

	if (search != NULL) {

		if (search->key == key) {
			if ((search->left == NULL) && (search->right == NULL)) {
				free(search);
				return 1;
			}
			else {
				printf("Node with that key is not LeafNode\n");
				return 1;
			}
		}

		else {

			while ((search->key != key)&&(search != NULL)) {   //search->key!=key 이면 반복문 진행 즉 search->key==key 이면 탈출
				temp = search;
				if (key < search->key)    //만약 key < search->key이면
					search = search->left;  //search는 search->left가 됨
				else if(key > search->key)        //만약 key > search->key이면
					search = search->right;  //search는 search->right가 됨
			}

			if (search == NULL) {
				printf("Node with that key is not LeafNode\n");
				return 1;
				}

			else if ((search->left == NULL) && (search->right == NULL)) {
				if (temp->right == search) {
					free(search);
					temp->right = NULL;
					return 1;
				}
				else if (temp->left == search) {
					free(search);
					temp->left = NULL;
					return 1;
				}
			}

		}
	}

	else {
		printf("Tree is empty.\n");
		return 1;
	}

}

Node* searchRecursive(Node* ptr, int key)  // recursive방식으로 노드를 찾는 함수
{
	Node* search = ptr;  //Node 포인터 search는 ptr을 가르킴 (ptr은 head->left)

	if (!search)  //만약 search가 없다면, 즉 그런 노드가 없으면 NULL반환
		return NULL;
	else if (key == search->key)  //만약 찾는 key랑 search->key랑 같으면
		return search;				//search의 주소 리턴
	else if (key < search->key)   //만약 찾는 key < search->key면
		return searchRecursive(search->left, key);   //search->left와 key로 다시 searchRecursive 호출
	else if (key > search->key)   //만약 key > search->key면
		return searchRecursive(search->right, key);   //search->right와 key로 다시 searchRecursive 호출
}

Node* searchIterative(Node* head, int key)  // iterative 방식으로 노드를 찾는 함수
{
	Node* search = head->left;  //Node 포인터 search 는 head->left를 가르 킴(root)

	while (search->key!=key) {   //search->key!=key 이면 반복문 진행 즉 search->key==key 이면 탈출
		if (key < search->key)    //만약 key < search->key이면
			search = search->left;  //search는 search->left가 됨
		else            //만약 key > search->key이면
			search = search->right;  //search는 search->right가 됨
	}
	return search;   //while문 탈출시 search를 return 
}


int freeBST(Node* head)
{

}





