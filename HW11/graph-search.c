#include <stdio.h>
#include <stdlib.h>

/*
 * Graph-search.c
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

//그래프의 정점에 대한 노드
typedef struct Node {  //Node 구조체 정의
	int key;             //int 형 key 선언
	struct Node* link;     
} Node;

#define MAX_VERTEX_SIZE 10  //Vertex는 최대 10개 (문제 조건)
#define TRUE 30  //벌텍스 방문한 곳에 사용
#define FALSE 50   //방문안한 벌텍스에 사용

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);

short int visited[MAX_VERTEX_SIZE];  //방문한 벌텍스 표시하는데 사용

int initializeGraph(Node* Nodelist);  //그래프 초기화하는 함수
int insertVertex(Node* Nodelist, int key);  //Vertex 추가하는 함수
int insertEdge(Node* Nodelist, int edge1, int edge2);  //Edge 추가하는 함수
void printGraph(Node* Nodelist);  //Graph 출력하는 함수
void freeGraph(Node* Nodelist);  //종료시 Graphfree하는데 쓰는 함수
void freeGraph2(Node* Nodelist);  //종료시 Graphfree하는데 쓰는 함수
void depthFirstSearch(Node* Nodelist, int v);   //깊이 우선 탐색 함수
void breathFirstSearch(Node* Nodelist, int v);   //너비 우선 탐색 함수


int main()
{
	char command;  //명령어 받을 변수
	int key;  //키
	int edge1, edge2;  //edge1, edge2 선언
	int front = rear = -1;
	
	Node Nodelist[10] = { {100, NULL} };   //벌텍스를 둘 Nodelist 선언

	for (int i = 0; i < MAX_VERTEX_SIZE; i++) {  //벌텍스의 수만큼 돌며 방문 FALSE로 초기화
		visited[i] = FALSE;
	}

	printf("[----- [Noh Min Sung] [2018038076] -----]\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v           Insert Edge            = e  \n");
		printf(" Depth First Search   = d           Breath First Search    = b  \n");
		printf(" Print Graph          = p           Quit                   = q  \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {

		case 'z': case 'Z':       //z 입력시
			initializeGraph(&Nodelist);      //그래프초기화함수 실행
			break;

		case 'q': case 'Q':       //q 입력시
			freeGraph(&Nodelist);   //그래프프리함수실행
			break;

		case 'v': case 'V':       //v 입력시 
			printf("Write Your Vertex = ");    //벌텍스입력 받음
			scanf("%d", &key);
			insertVertex(&Nodelist, key);  //insertVertex함수 실행
			break;

		case 'd': case 'D':    //d 입력시
			for (int i = 0; i < MAX_VERTEX_SIZE; i++) {   //visited[i]를 반복문 돌며 모두 방문안함으로 초기화하고
				visited[i] = FALSE;
			}
			printf("Write Your Vertex to Depth First Search = ");   //DFS할 vertex입력 받고
			scanf("%d", &key);
			depthFirstSearch(&Nodelist,key);    //DFS함수실행

			break;

		case 'b': case 'B':    //b 입력시
			for (int i = 0; i < MAX_VERTEX_SIZE; i++) {   //visited[i]를 반복문 돌며 모두 방문안함으로 초기화하고
				visited[i] = FALSE;
			}
			printf("Write Your Vertex to Breath First Search = ");   //BFS할 vertex입력 받고
			scanf("%d", &key);
			breathFirstSearch(&Nodelist, key);    //BFS함수실행
			break;


		case 'e': case 'E':         //E 입력시 
			printf("Write Your Edge (ex: 1 3)= ");        //엣지 입력받고
			scanf("%d %d", &edge1,&edge2);
			insertEdge(&Nodelist,edge1,edge2);   //insertEdge 함수 실행
			break;

		case 'p': case 'P':   //p입력시
			printGraph(&Nodelist);  //printGraph 함수 실행
			break;

		default:        //다른거 입력시 집중하라고 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');   //q 입력때 까지 반복

	return 1;
}

int initializeGraph(Node* Nodelist) {   //그래프 초기화하는 함수

	for (int i = 0; i < MAX_VERTEX_SIZE; i++) {  //최대 벌텍스 크기만큼 반복하며
		if (Nodelist[i].key == i) {   //노드리스트의 키가 i인 경우 즉 벌텍스가 존재하는 경우
			Nodelist[i].key = 100;   //초기화 시켜주고
			freeGraph2(Nodelist[i].link);  //링크도 초기화 시켜줌
			Nodelist[i].link = NULL;  //모두 NULL로 함
		}
	}

	front = rear = -1;

	for (int i = 0; i < MAX_VERTEX_SIZE; i++) {  //최대 벌텍스 크기만큼 반복하며
		visited[i] = FALSE;                    //노드 방문을 FALSE로 설정
	} 

}

int insertVertex(Node* Nodelist, int key)   //Vertex 추가하는 함수
{

	if ((key < 0) || (key > MAX_VERTEX_SIZE-1)) {  //만약 범위에 벗어난 키를 입력하면
		printf("Vertex Number can be 0 to 9.\n");   //범위에 맞는 값을 입력하라고 함.
		return 1;                                  //종료
	}

	if (Nodelist[key].key == key) {       //만약 이미 있는 벌텍스라면
		printf("That Vertex is already exsist.\n");        //있다고 출력
		return 1;                                  //종료
	}

	else {            //위의 예외 경우가 아닌 경우
		Nodelist[key].key = key;           //입력받은 키의 Nodelist[key]를 key로 바꿔줌
		Nodelist[key].link = NULL;        //해당 키의 Nodelist.link는 NULL로 해줌
		printf("Vertex[%d] is inserted.\n", key);   //해당 vertex가 생겼다고 알려줌
		return 1;             //종료
	}
	return 1;
}


int insertEdge(Node* Nodelist, int edge1, int edge2)       //Edge 추가하는 함수
{
	Node* current = NULL;    // 나중에 사용할 current 선언 
	Node* previous = NULL;  // 나중에 사용할 previous 선언 (current 이전을 가르킴)
	Node* current2 = NULL;    // 나중에 사용할 current2 선언
	Node* previous2 = NULL;  // 나중에 사용할 previous2 선언 (current2 이전을 가르킴)

	if ((edge1 < 0) || (edge1 > MAX_VERTEX_SIZE - 1) || (edge2 < 0) || (edge2 > MAX_VERTEX_SIZE - 1)) {   //만약 edge가 범위를 벗어난 값이면
		printf("Edge Number can be 0 to 9.\n");               //올바른 범위알려줌
		return 1;         //종료
	}

	else if ((Nodelist[edge1].key != edge1) || (Nodelist[edge2].key != edge2)) {     //만약 해당 Vertex가 존재하지 않는 경우
		printf("That Vertexs not exsist.\n");                                      //vertex가 없다고 출력
		return 1;                                                             //종료
	}

	else if (edge1 == edge2) {              //같은 edge를 입력했을 경우
		printf("Please write different edge.\n");        //다른 edge입력하라고 출력
		return 1;                                                             //종료              
	}

	else {                      //위의 예외 케이스가 아닌 경우, 즉 edge로 작업을 하는 경우
		
			Node* newEdge = (Node*)malloc(sizeof(Node));   //새로운 노드를 하나 할당해주고
			Node* newEdge2 = (Node*)malloc(sizeof(Node));  //새로운 노드를 하나 할당해주고
			newEdge->key = edge1;      //노드의 키에 edge1를 넣음
			newEdge->link = NULL;        //노드의 링크는 널로 설정
			newEdge2->key = edge2;      //노드의 키에 edge2를 넣음
			newEdge2->link = NULL;        //노드의 링크는 널로 설정

			while (1) {   //Nodelist[edge1].link 부분을 처리하기 위한 반복문
				if (Nodelist[edge1].link == NULL) {    // 만약 Nodelelist[edge1]의 링크가 널이면,,,즉 vertex만 존재하는 경우
					Nodelist[edge1].link = newEdge2;        //바로 링크뒤에 new Edge2를 연결해준다. 
					break;  //반복문 탈출
				}

				else if (Nodelist[edge1].link->key > edge2) {  //만약 엣지가 하나였는데 그 값보다 새로운 엣지가 작은 경우
					newEdge2->link = Nodelist[edge1].link;      //지금 엣지를 새로운 엣지가 가르키게 한다.
					Nodelist[edge1].link = newEdge2;          //새로운 엣지를 제일 앞에 newEdge2를 연결시켜준다
					break;  //반복문 탈출
				}

				else {             //vertex만 존재하는게 아닌경우, 즉 다른 edge가 있는 경우
					current = Nodelist[edge1].link;      //current는 Nodelist[edg1]의 링크를 가리키고
					while (current != NULL) {        //current가 NULL이 아니면 계속 반복한다
						if (current->key == edge2) {    //만약 입력받은 키에 대한 edge2가 이미 존재한다면
							printf("That edge is already exsist.\n");   //존재한다고 출력
							free(newEdge);   //할당받은 노드해제
							free(newEdge2);   //할당받은 노드해제
							return 1;       //종료
						}
						else if (((current->key) < edge2) && (current->link != NULL) && ((current->link->key) > edge2)) {  //새로운 엣지를 B라고하면 A<B<C 구조(기존 엣지에서)
							newEdge2->link = current->link;    //current 링크를 새로운 newEdge2의링크가 가르키게한다
							current->link = newEdge2;        //current 링크는 newEdge2를 가르킨다
							break;            //반복문 탈출
						}
						previous = current;        //previous는 current를 가르키고
						current = current->link;         //current는 current->link가 된다
					}
					//반복문 탈출했을 때,즉 기존에 입력받은 키에 대한 edge가 존재하지 않는다면
					if(current==NULL){
						previous->link = newEdge2;     //previous의 링크에 newEdge2를 이어준다
						break;  //반복문 탈출
					}
					else {
						break;  //반복문 탈출 (while문이 2개임)
					}
				}
			}

			while (1) {   //Nodelist[edge2].link 부분을 처리하기 위한 반복문
				if (Nodelist[edge2].link == NULL) {    // 만약 Nodelelist[edge2]의 링크가 널이면,,,즉 vertex만 존재하는 경우
					Nodelist[edge2].link = newEdge;        //바로 링크뒤에 새로 할당한 노드를 이어준다
					break;  //반복문 탈출
				}

				else if (Nodelist[edge2].link->key > edge1) {  //만약 엣지가 하나였는데 그 값보다 edge1가 작은 경우
					newEdge->link = Nodelist[edge2].link;      //지금 엣지를 새로운 엣지가 가르키게 한다.
					Nodelist[edge2].link = newEdge;          //새로운 엣지를 제일 앞에 연결시켜준다
					break;  //반복문 탈출
				}

				else {             //vertex만 존재하는게 아닌경우, 즉 다른 edge가 있는 경우
					current2 = Nodelist[edge2].link;      //current2는 Nodelist[edge2]의 링크를 가리키고
					while (current2 != NULL) {        //current2가 NULL이 아니면 계속 반복한다
						if (current2->key == edge1) {    //만약 입력받은 키에 대한 edge가 이미 존재한다면
							printf("That edge is already exsist.\n");   //존재한다고 출력
							free(newEdge);   //할당받은 노드해제
							free(newEdge2);   //할당받은 노드해제
							return 1;       //종료
						}
						else if (((current2->key) < edge1) && (current2->link != NULL) && ((current2->link->key) > edge1)) {  //새로운 엣지를 B라고하면 A<B<C 구조(기존 엣지에서)
							newEdge->link = current2->link;    //current2 링크를 newEdge의링크가 가르키게한다
							current2->link = newEdge;        //current2 링크는 newEdge를 가르킨다
							break;            //탈출
						}
						previous2 = current2;        //previous2는 current2를 가르키고
						current2 = current2->link;         //current2는 current2->link가 된다
					}
					//반복문 탈출했을 때,즉 기존에 입력받은 키에 대한 edge가 존재하지 않는다면
					if(current2==NULL) {    //만약 current2가 NULL이면 즉 위의 while문을 마지막까지 가서 탈출했다면
						previous2->link = newEdge;     //previous2의 링크에 새로운 노드를 이어준다
						break;  //탈출
					}
					else {  //반복문 중간에 특정 조건으로 탈출했다면 그냥 한번더 탈출한다 (특별한 조건 없이, 반복문이 2개 이므로)
						break;  //탈출
					}
				}
				               //종료
			}
			return 1;  //종료

          }	
}


void printGraph(Node* Nodelist) {  //그래프 정보 출력하는 함수
	int count = 0;   //그래프가 비었나 확인하기 위해 사용

	for (int j = 0; j < MAX_VERTEX_SIZE; j++) {  //그래프의 최대 벌텍스 수까지 돌면서
		if (Nodelist[j].key == j) {   //만약 벌텍스가 있다면
			count++;          //count 하나 증가시킴
		}		
	}
	         //반복문 탈출 후, 즉 검사후
	if (count == 0) {        //만약 count가 0이라면 즉 그래프가 비어있다면
		printf("The Graph is empty.\n");     //그래프가 비어있다고 출력
		return 1;      //종료
	}

	for (int i = 0; i < MAX_VERTEX_SIZE; i++)   //모든 벌텍스를 검사하며
	{
		if (Nodelist[i].key == i) {     //만약 Nodelist[i].key가 i인 경우,즉 벌텍스가 존재하는 경우
			printf("Vertex : [%d]\n", i);       //벌텍스를 출력

			if ((Nodelist[i].key == i) && (Nodelist[i].link == NULL)) {  //만약 벌텍스는 존재하는데 엣지는 없는 경우
				printf("There is no Edge.\n");   //엣지없다고 출력
			}

			else {			 //엣지가 존재하는 경우	
				Node* current = Nodelist[i].link;   //current는 Nodelist[i]의 링크를 가리키고
				printf("Edge : [%d] ", current->key);   //currnet->key값 출력
				while (current->link != NULL) {   //current->link가 NULL일떄까지 반복
					current = current->link;      //current는 current->link가 되고 
					printf("[%d] ", current->key);   //current->key값 출력
				}
			}
			printf("\n");		 //줄바꿈
		}
	}
}


void depthFirstSearch(Node* Nodelist, int v) {  //깊이 우선 탐색 함수

	if (Nodelist[v].key!=v) {     //만약에 vertex가 없는데 키를주고 탐색을 요구한 경우
		printf("Check Please.\n");   //체크해달라고 요청
		return 1;           //종료
	}

	Node* nodepointer;   //Node포인터 nodepointer 선언

	visited[v] = TRUE;   //벌텍스를 방문으로 바꿈
	printf(" %d ", v);   //v출력
	for (nodepointer = &Nodelist[v]; nodepointer;nodepointer=nodepointer->link)  //지금노드리스트의 주소를 노드포인터가 가르키며 노드포인터가 존재하면(NULL)이 아니면 계속 링크 옮기며 반복문 실행
		if (visited[nodepointer->key] == FALSE)   //만약 방문하지 않은곳이있다면
			depthFirstSearch(Nodelist, nodepointer->key);   //방문하지 않은곳의 key로 다시 DFS함수 호출

}

void breathFirstSearch(Node* Nodelist, int v) {  //너비 우선 탐색 함수

	front = rear = -1;  //front ,real는 -1로 초기화

	if (Nodelist[v].key != v) {     //만약에 vertex가 없는데 키를주고 탐색을 요구한 경우
		printf("Check Please.\n");   //체크해달라고 요청
		return 1;           //종료
	}

	Node* nodepointer;   //Node포인터 nodepointer 선언
	visited[v] = TRUE;   //벌텍스를 방문으로 바꿈
	printf(" %d ", v);   //v출력
	enQueue(&Nodelist[v]);  //입력받은 v에 해당하는 Nodelist주소를 큐에 넣어줌

	while (front != rear) {  //front랑 rear랑 같을때 까지 즉 큐가 빌때까지
		nodepointer = deQueue();   //nodepointer 는 deQueue 한것을가르킴
		for (nodepointer; nodepointer; nodepointer = nodepointer->link) {  //nodepointer라 존재하면 NULL일떄까지 링크로 이동
			if (visited[nodepointer->key] == FALSE) {   //만약 방문안한곳이면
				printf(" %d ", nodepointer->key);   //key를 출력해줌
				enQueue(&Nodelist[nodepointer->key]);  //방문한키의 Nodelist 주소를 enQueue해줌
				visited[nodepointer->key] = TRUE;   //visited를 True로 바꿔줌
			}
		}
	}
}

void freeGraph(Node* Nodelist) {  //그래프 메모리해제하는 함수
	for (int i = 0; i < MAX_VERTEX_SIZE; i++) {  //MAX_VERTEX_SIZE 만큼 돌며
		freeGraph2(Nodelist[i].link);   //Nodelist[i].link로 freeGraph2함수 호출
	}
}

void freeGraph2(Node* Nodelist) {  //그래프의 링크 하나씩 해제하는 함수
	if (Nodelist) {    //Nodelist가 존재하면
		freeGraph2(Nodelist->link);   //링크로 다시 freeGraph2 호출
		free(Nodelist);   //메모리해제해줌
	}
}


// Breath First Search에 이용!!!

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
