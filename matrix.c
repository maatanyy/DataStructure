#include <stdio.h>
#include <stdlib.h>  // malloc 쓰기위해 
#include <time.h>  // 랜덤함수 쓰기위해 선언

/*             HomeWork#4                 */
/*     소프트웨어학과 2학년 노민성        */
/*          학번: 2018038076              */


/* Method Declaration */
int** create_matrix(int row, int col);    // 동적 메모리 할당으로 행렬을 만드는 함수 선언
void print_matrix(int** matrix, int row, int col);  // 행렬을 출력하는 함수 선언
int free_matrix(int** matrix, int row, int col);    // 동적 할당을 해제 해주는 함수 선언
int fill_data(int** matrix, int row, int col);   // 행렬의 값을 채워주는 함수 선언
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  // 행렬의 각 성분을 더하는 함수 선언
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   // 행렬의 각 성분을 빼는 함수 선언
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);     // 전치행렬을 구하는 함수 선언
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);       // 행렬을 곱하는 함수 선언

int main()
{
    char command;
    printf("[----- [노민성]  [2018038076] -----]\n");

    int row, col;   //행과 열 선언
    srand(time(NULL));  //랜덤값 구하기 위해 씀

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);                   // 행과 열을 사용자로부터 입력 받음
    int** matrix_a = create_matrix(row, col);     // create_matrix를 사용해 matrix_a 동적 할당
    int** matrix_b = create_matrix(row, col);    // create_matrix를 사용해 matrix_b 동적 할당
    int** matrix_a_t = create_matrix(col, row);  // create_matrix를 사용해 matrix_a_t 동적 할당

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }     // matrix_a가 비어있거나 matrix_b가 비어있으면 -1반환

    do {          //반복
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");           //  z 누를시 Initialize Matrix하겠다, p누를시  Print Matrix하겠다.
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");          //  a 누를시 Add Matrix하겠다, s누를시 Subtract Matrix하겠다.
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");         //  t 누를시 Transpose matrix_a하겠다, m누를시 Multiply Matrix하겠다.
        printf(" Quit                = q \n");                                          //  q 누를시 Quit 하겠다.
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);    // 실행할 명령어 입력받음

        switch (command) {   // command에 따라서 아래 case로 나누어 실행
        case 'z': case 'Z':                            //z 나 Z이면
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);        // fill_data함수를 사용해 matrix_a에 값 넣어줌
            fill_data(matrix_b, row, col);        // fill_data함수를 사용해 matrix_b에 값 넣어줌
            break;                               // switch문 빠져나옴
        case 'p': case 'P':                       // p나 P이면
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);           // print_matrix 함수를 통해 matrix_a출력
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);          // print_matrix 함수를 통해 matrix_b출력
            break;                             // switch문 빠져나옴
        case 'a': case 'A':                          // a나 A면
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);    // addition_matrix함수를 통해 matrix_a + matrix_b
            break;                                   // switch문 빠져나옴
        case 's': case 'S':                        // s나 S면
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);  // subtraction_matrix함수를 통해  matrix_a - matrix_b
            break;                                  // switch문 빠져나옴
        case 't': case 'T':                                 // t나 T면
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  // transpose_matrix를 통해 a의 전치행렬을 만듬,matrix_a_t도 보내는 건 결과를 저장하기위해
            print_matrix(matrix_a_t, col, row);
            break;                                   //   switch문 빠져나옴
        case 'm': case 'M':               //   m이나 M이면
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);    //  transpose_matrix를 통해 a의 전치행렬을구함
            multiply_matrix(matrix_a, matrix_a_t, row, col);         // multiply_matrix를 통해 a와 a의전치행렬을 곱함
            break;                                   //  switch문 빠져나옴
        case 'q': case 'Q':                            // q나 Q이면
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);    //  matrix_a_t메모리해제
            free_matrix(matrix_a, row, col);    //  matrix_a 메모리 해제
            free_matrix(matrix_b, row, col);     //   matrix_b 메모리 해제
            break;                                //   switch문 빠져나옴
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //   없는 명령어시 집중하라고 출력
            break;                                     //   switch문 빠져나옴
        }

    } while (command != 'q' && command != 'Q');   //   q나 Q가 입력될때가지 while문 반복

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {      // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return NULL;
    }
    
    int** arr = (int**)malloc(sizeof(int*) * row);  //   arr동적할당

    for (int i = 0; i < row; i++)     // row의 수만큼돌며(행의수)
    {
        arr[i] = (int*)malloc(sizeof(int) * col);  //   arr[i]동적할당 크기는 int형*col(열의 수)
    }

    if (arr == NULL) {       //   arr이 비어있으면
        create_matrix(row, col);       //   다시 create_matrix 함수로 이동
    }

    return arr;  //   동적할당한 arr의 return
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)   //  행렬을 출력하는 함수
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
    }

    for (int i = 0; i < row; i++) {           //  행만큼반복
        for (int k = 0; k < col; k++) {        //  열만큼반복
            printf("%3d ", matrix[i][k]);     //  matrix[행][열] 값 출력
        }
        printf("\n");         //한 행이끝나면 한줄띄움
    }

    if (matrix == NULL) {    //문제가 있다면 다시 실행
        print_matrix(matrix, row, col);
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)        //  메모리해제하는 함수
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return -1;   //not okay
    }

    for (int i = 0; i < row; i++) {      //  행만큼 반복
        free(matrix[i]);             //  matrix[i] 해제 ,행만큼 반복하는 이유는 선언할 때 (int**)malloc(sizeof(int*) * row);를 통해 행의수만큼했음
   }
    free(matrix);   //  두번 동적할당했으니 한번더 matrix해제

    return 1; //잘 동작시 return 1
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)  //  행렬에 값을 채워준는 함수
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return -1;   //not okay
    }

    for (int i = 0; i < row; i++) {  //  행만큼반복
        for (int k = 0; k < col; k++) {  //  열만큼반복
            matrix[i][k] = rand() % 20;  // matrix[i][k]값은 0~19
        }
    }

    if (matrix == NULL) {    //문제가 있다면 다시 실행
       fill_data(matrix, row, col);
    }

    print_matrix(matrix, row, col);   //  print_matrix 함수를 통해 matrix출력
    printf("\n");
    return 1; //잘 동작시 return 1
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)  //  행렬의 각 성분 더하는 함수
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return -1;   //not okay
    }

    int** matrix_sum;             //  더블포인터 matrix_sum 선언
   matrix_sum=create_matrix(row,col);        //  matrix_sum를 create_matrix함수를 이용해 통해 받은 arr저장
    for (int i = 0; i < row; i++) {     //  행만큼 반복
        for (int k = 0; k < col; k++) {         //  열만큼 반복
         matrix_sum[i][k]= matrix_a[i][k] + matrix_b[i][k];   //  각 성분더해줌
        }
    }

    if (matrix_sum == NULL) {    //문제가 있다면 다시 실행
        addition_matrix(matrix_a,matrix_b, row, col);
    }

    print_matrix(matrix_sum, row, col);  //  matrix_sum출력
    free_matrix(matrix_sum, row, col);    //  matrix_sum해제 여기서 해제하는 이유는 메뉴에서 q를 눌렀을때 이건 없기 때문

    return 1; //잘 동작시 return 1
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)  //  행렬의 각 성분 빼는 함수
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return -1;   //not okay
    }

    int** matrix_sub;              //더블포인터 matrix_sub;선언
    matrix_sub = create_matrix(row, col);         //  create_matrix(row, col)함수를 사용해 matrix_sub에 값 넣어준다.
    for (int i = 0; i < row; i++) {            //  row만큼 반복
        for (int k = 0; k < col; k++) {             //  col만큼 반복
            matrix_sub[i][k] = matrix_a[i][k] - matrix_b[i][k];       //  matrix_sub[i][k]에 matrix_a[i][k] - matrix_b[i][k]한 값을 넣어준다.  
        }
    }

    if (matrix_sub == NULL) {    //문제가 있다면 다시 실행
        subtraction_matrix(matrix_a, matrix_b, row, col);
    }

    print_matrix(matrix_sub, row, col);    //  matrix_sub를 출력해준다
    free_matrix(matrix_sub, row, col);      //  matrix_sub의 메모리를 해제해준다. 
    return 1; //잘 동작시 return 1

}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)      //  메인함수에서 전달할때 col,row로 전달한다
{           
    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return -1;   //not okay
    }

    for (int i = 0; i < col; i++) {                         //  col만큼 반복
        for (int j = 0; j < row; j++) {                     //  row만큼 반복
            matrix_t[j][i] = matrix[i][j];                // matrix[i][j]의 값을 matrix_t[j][i] 에 넣어준다.
        }
    }

    return 1; //잘 동작시 return 1
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)     //  곱하는 함수
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // 입력된 행과열이 0이하이면 
        printf("Check the sizes of row and col!\n");   // 잘못입력했다고 알려줌
        return -1;   //not okay
    }

    if ((matrix_t == NULL)||(matrix_a==NULL)) {      //  만약 곱하는데 사용할 행렬 matrix_t나 행렬 matrix_a가 비어있다면
        /* proper actions for unexpected conditions */
        printf("Make a matrix first");             //  행렬을 먼저 만들라고 출력
    }
    
    int** matrix_axt;                               //  더블포인터 matrix_axt선언
    matrix_axt = create_matrix(row, row);            // 여기서 고민을 많이 했는데 row와 col이 다를경우 새로운 행렬을 row,col을 넣어서 만들면 나중에 쓰레기값이 나온다
                                                     // row 와 col이 다를경우 만들어지는 행렬은 (row *col)*(col*row)=(row,row) 즉 row와 row를 인자로 행렬을 만들면 row와 col이 다른경우에도 오류가 나지않는다
    for (int i = 0; i < row; i++) {                   // 3*2행렬과 2*3행렬을 그려서 인덱스의 곱을 생각해보며 이런식을 도출했다. 
        for (int k = 0; k < row; k++) {                            // 바깥의 두개의 반복문에는 row  제일 안쪽 반복문에는 col까지 반복한다 
            matrix_axt[i][k] = 0;                                       //  matrix_axt[i][k]를 일단 0을 넣어줌(초기화) create_matrix함수 사용시 값이 들어있음으로
            for (int j = 0; j < col; j++) {
                matrix_axt[i][k] += (matrix_a[i][j] * matrix_t[j][k]);  // matrix_axt[i][k]의 값을 반복문을 통해 구해준다
            }
        }
    }

    if ((matrix_a == NULL)|| (matrix_t == NULL)) {    //문제가 있다면 다시 실행
        multiply_matrix(matrix_a,matrix_t, row, col);
    }

    print_matrix(matrix_axt, row, row);    // matrix_axt 결과를 출력해준다
    free_matrix(matrix_axt, row, col);         // matrix_axt 메모리를 해제해준다.
    return 1; //잘 동작시 return 1
}

