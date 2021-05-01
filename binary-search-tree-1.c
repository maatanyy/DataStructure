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



void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf("[%d]   ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf("[%d]   ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d]   ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;

	Node* temp = head->left;
	Node* temp2 = temp;

	if (head->left== NULL) {
		head->left = newnode;
		return 1;
	}

	while (temp!=NULL){
		temp2 = temp;

		if (temp->key > key) {
			temp = temp->left;
		}

		else if (temp->key < key) {
			temp = temp->right;
		}
	}
	
	if (temp2->key > key) {
		temp2->left = newnode;
		return 1;
	}
	else if (temp2->key < key) {
		temp2->right = newnode;
		return 1;
	}
}


int deleteLeafNode(Node* head, int key)
{

}


Node* searchRecursive(Node* ptr, int key)
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

Node* searchIterative(Node* head, int key)
{
	Node* search = head->left;

	while (search->key!=key) {
		if (key < search->key)
			search = search->left;
		else
			search = search->right;
	}
	return search;
}


int freeBST(Node* head)
{

}





