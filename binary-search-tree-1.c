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
	struct node* left;
	struct node* right;
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
	do {
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

		switch (command) {
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
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
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

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
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

	if (head->left == NULL) {  //만약 head->left가 NULL인 경우, 즉 tree에 아무 것도 없는 경우는
		head->left = newnode;   //newnode가 root node가 되도록, head->left를 newnode로 해준다.
		return 1;  //종료
	}

	while (temp != NULL) {  //만약 temp!=NULL, 즉 노드가 있는 경우
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


int deleteLeafNode(Node* head, int key)  //leafnode 삭제하는 함수
{
	Node* temp = searchIterative(head, key);  //temp에 searchIterative 함수 결과 저장

	Node* search = head->left;  //Node 포인터 search 는 head->left를 가르 킴(root)

	if (temp == NULL) {  //temp가 비어있으면 즉, 그 노드에 대한 주소가 null인 경우 즉 트리에 찾는 노드가 없을 경우
		printf("that node is not in tree.\n");   //tree에 노드가 없다고 출력
	}

	else {   //그 외에 트리에 찾는 노드가 있는 경우 
		if (search != NULL) {  //root노드가 널이 아니면

			if (search->key == key) {  //만약 루트노드의 키랑 찾는 키랑 같으면
				if ((search->left == NULL) && (search->right == NULL)) {  //루트노드가 리프노드이면
					head->left = NULL;     //head->left를 NULL로 바꿔준다
					free(search);   //search(root)를 free해준다
					return 1;   //종료
				}
				else {   //루트노드가 리프 노드가 아니면
					printf("Node with that key is not LeafNode\n");   //노드가 리프 노드가 아니라고 출력해준다
					return 1;  //종료
				}
			}

			else {  //루트노드가 아닌 다른 노드의 경우 

				while (search->key != key) {   //search->key==key이면 반복문 탈출
					temp = search;      //temp는 search를 가르킨다
					if (key < search->key)    //만약 key < search->key이면
						search = search->left;  //search는 search->left가 됨
					else if (key > search->key)        //만약 key > search->key이면
						search = search->right;  //search는 search->right가 됨
				}
				//반복문 탈출 후(
				if ((search->left == NULL) && (search->right == NULL)) {   //search 노드의 리프노드의 left가 null이고 right가 null인 경우
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
				else {  //그 외의 경우 즉 searchnode가 leafNode가 아닌 경우
					printf("Node with that key is not LeafNode\n");  //leafnode가 아니라고 출력해준다
					return 1;  //종료
				}

			}
		}


		else {  //트리에 노드가 없는 경우
			printf("Tree is empty.\n");   //트리가 비어있다고 출력해준다
			return 1;  //종료
		}
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

	while (search!=NULL) {   //search 가 NULL일떄까지 반복
		if (key < search->key)    //만약 key < search->key이면
			search = search->left;  //search는 search->left가 됨
		else if (key > search->key)           //만약 key > search->key이면
			search = search->right;  //search는 search->right가 됨
		else if (key == search->key)  //key랑 search->key랑 같으면
			return search;  //search를 리턴한다
	}
	return NULL;   //while문 탈출시 NULL를 return 
}


int freeBST(Node* head) //tree의 메모리를 해제 해주는 함수
{
	//첫 노드가 제일 마지막에 왼쪽/오른쪽 돌고 마지막에 해제하도록 후위순회를 이용
	if (head != NULL) {  //head가 null이 아니면
		freeBST(head->left);  //freeBST를 head->left를 이용해 다시 호출
		if (head->right == head) {  //head의 오른쪽이 head인 경우는 처음 노드에서 무한히 반복되므로 예외처리를 해줘야 한다
			free(head);   //이 경우에는 head를 free해준다
		}
		freeBST(head->right);  //head->right가 head가 아닌 경우에는 freeBST를 head->right로 호출해준다
		free(head);  //head를 해제해준다.
	}
	
	return 0;  //리턴
}





