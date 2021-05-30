/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
        printf("[---------------- [Noh Min Sung] [2018038076] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)   //메모리해제
{
	if(a != NULL)   //a가 NULL이 아니면
		free(a);        //a의 메모리를 해제해준다.
	return 0;
}

void printArray(int *a)      //정보 출력해주는 함수
{
	if (a == NULL) {             //a가 NULL이면
		printf("nothing to print.\n");    //출력할 게 없다고 출력해줌
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)     //i=0부터 MAX_ARRAY_SIZE까지 반복하면서
		printf("a[%02d] ", i);            // 인덱스 번호 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //i=0부터 MAX_ARRAY_SIZE까지 반복하면서
		printf("%5d ", a[i]);             // 인덱스 값 출력
	printf("\n");
}

    // 주어진 리스트중 최소값을 찾고 맨 앞 값과 바꾸고 처음 값을 제외 한 나머지를 계속 반복한다.
int selectionSort(int *a)        //선택 정렬
{
	int min;       //최소 값 저장하는데 사용
	int minindex;  //최소 값 인덱스 번호 저장하는데 사용
	int i, j; 

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬전 정보를 출력해줌

	for (i = 0; i < MAX_ARRAY_SIZE; i++)   //i=0부터 MAX_ARRAY_SIZE까지 반복하면서
	{
		minindex = i;   //minindex = i가 되고
		min = a[i];     //a[i]가 min이 된다
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)  //j는 i+1부터 MAX_ARRAY_SIZE까지 반복하면서
		{
			if (min > a[j])         //만약 min 이 a[j]보다 크면
			{        
				min = a[j];         //a[j]가 min이 되고
				minindex = j;        //minindex는 j가 된다
			}
		}
		a[minindex] = a[i];         //a[minindex]를 a[i]로 해주고
		a[i] = min;               //a[i]를 min의 값으로 함   (첫 인덱스를 최소로)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);   //a 출력, 정렬된 정보가 출력됨
	return 0;
}

 // 정렬되지 않은 부분집합의 원소를 하나씩 꺼내서 이미 정렬되어 있는 부분집합의 맨 뒤부터 비교하면서 삽입
int insertionSort(int *a)
{
	int i, j, t;   // i,j,t 선언

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬되기 전 정보 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)    // i=1부터 MAX_ARRAY_SIZE까지 반복하면서
	{
		t = a[i];  //t는 a[i]가 되고, 임시로 저장
		j = i;     //j는 i로 
		while (a[j-1] > t && j > 0)   //정렬 된 부분 집합의 뒤부터 비교하면서
		{
			a[j] = a[j-1];   //하나씩 줄여감
			j--;
		}
		a[j] = t;   // t를 a[j]에 넣음
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 된 후 정보 출력

	return 0;
}

 //인접한 요소를 비교 교환하며 최대 값을 뒤로 보내는 걸 반복함
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 되기 전 정보 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)  //i=0부터 최대크기까지 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  //j=0부터 최대크기까지 반복
		{
			if (a[j-1] > a[j])  //반약 이전 칸 값이 다음값 보다 크면
			{
				t = a[j-1];         //값을 서로 바꿔줌 (t에 임시저장)
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 된 후 정보 출력

	return 0;
}

 //비교 횟수 h를 정하고 점점 줄여가며 정렬 처음엔 4라하면 그다음은 2 이런식으로 그 차이만큼 인덱스 비교하며 정렬
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);    //정렬 되기 전 정보 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)  //처음 h는 전체 크기/2로 잡고 반복하면서 /2배씩 계속 줄여나감
    	{
		for (i = 0; i < h; i++)  // i=0부터 <h이면 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  //j는 i+h 부터 전체 크기보다 작으면 반복하는데 j+h=j가 됨
			{
				v = a[j];   //v는 a[j]값이 되고
				k = j;    //k는 j로 설정
				while (k > h-1 && a[k-h] > v)   //반복문을 통해 값 비교
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;  //반복문 탈출했을 경우 a[k]를 v로 함
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);   //정렬 되고난 후 정보 출력

	return 0;
}

 //피봇을 기준으로 피봇보다 작은 값을 왼쪽 큰 값을 오른쪽으로 정렬 후 반복
int quickSort(int *a, int n)
{
	int v, t; 
	int i, j;

	if (n > 1)   //만약 n이 1보다 크면
	{
		v = a[n-1];   //v는 a[n-1]이 되고
		i = -1;   //i는 -1부터 커짐 
		j = n - 1;   //j는 n-1 (맨 끝부터 작아짐)

		while(1)  //무한루프
		{
			while(a[++i] < v);   //앞 인덱스 하나씩 증가시키며 피봇값과 비교
			while(a[--j] > v);   //뒤 인덱스 하나씩 감소시키며 피봇값과 비교

			if (i >= j) break;  //만약 i>=j면 반복문 탈출
			t = a[i];   //a[i]를 t로
			a[i] = a[j];   //a[j]를 a[i]로
			a[j] = t;       //t를 a[j]로
		}  //반복문 탈출시 (i>=j)인 경우
		t = a[i];    //a[i]를 t로
		a[i] = a[n-1];   //a[n-1]를 a[i]로
		a[n-1] = t;       //t를 a[n-1]로

		quickSort(a, i);  //피봇 기준 왼쪽, 오른쪽 나눠서 퀵솔트 다시함
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



