#include <stdio.h>
#include <stdlib.h>  // malloc �������� 
#include <time.h>  // �����Լ� �������� ����

/*             HomeWork#4                 */
/*     ����Ʈ�����а� 2�г� ��μ�        */
/*          �й�: 2018038076              */


/* Method Declaration */
int** create_matrix(int row, int col);    // ���� �޸� �Ҵ����� ����� ����� �Լ� ����
void print_matrix(int** matrix, int row, int col);  // ����� ����ϴ� �Լ� ����
int free_matrix(int** matrix, int row, int col);    // ���� �Ҵ��� ���� ���ִ� �Լ� ����
int fill_data(int** matrix, int row, int col);   // ����� ���� ä���ִ� �Լ� ����
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  // ����� �� ������ ���ϴ� �Լ� ����
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   // ����� �� ������ ���� �Լ� ����
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);     // ��ġ����� ���ϴ� �Լ� ����
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);       // ����� ���ϴ� �Լ� ����

int main()
{
    char command;
    printf("[----- [��μ�]  [2018038076] -----]\n");

    int row, col;   //��� �� ����
    srand(time(NULL));  //������ ���ϱ� ���� ��

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);                   // ��� ���� ����ڷκ��� �Է� ����
    int** matrix_a = create_matrix(row, col);     // create_matrix�� ����� matrix_a ���� �Ҵ�
    int** matrix_b = create_matrix(row, col);    // create_matrix�� ����� matrix_b ���� �Ҵ�
    int** matrix_a_t = create_matrix(col, row);  // create_matrix�� ����� matrix_a_t ���� �Ҵ�

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }     // matrix_a�� ����ְų� matrix_b�� ��������� -1��ȯ

    do {          //�ݺ�
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");           //  z ������ Initialize Matrix�ϰڴ�, p������  Print Matrix�ϰڴ�.
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");          //  a ������ Add Matrix�ϰڴ�, s������ Subtract Matrix�ϰڴ�.
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");         //  t ������ Transpose matrix_a�ϰڴ�, m������ Multiply Matrix�ϰڴ�.
        printf(" Quit                = q \n");                                          //  q ������ Quit �ϰڴ�.
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);    // ������ ��ɾ� �Է¹���

        switch (command) {   // command�� ���� �Ʒ� case�� ������ ����
        case 'z': case 'Z':                            //z �� Z�̸�
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);        // fill_data�Լ��� ����� matrix_a�� �� �־���
            fill_data(matrix_b, row, col);        // fill_data�Լ��� ����� matrix_b�� �� �־���
            break;                               // switch�� ��������
        case 'p': case 'P':                       // p�� P�̸�
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);           // print_matrix �Լ��� ���� matrix_a���
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);          // print_matrix �Լ��� ���� matrix_b���
            break;                             // switch�� ��������
        case 'a': case 'A':                          // a�� A��
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);    // addition_matrix�Լ��� ���� matrix_a + matrix_b
            break;                                   // switch�� ��������
        case 's': case 'S':                        // s�� S��
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);  // subtraction_matrix�Լ��� ����  matrix_a - matrix_b
            break;                                  // switch�� ��������
        case 't': case 'T':                                 // t�� T��
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  // transpose_matrix�� ���� a�� ��ġ����� ����,matrix_a_t�� ������ �� ����� �����ϱ�����
            print_matrix(matrix_a_t, col, row);
            break;                                   //   switch�� ��������
        case 'm': case 'M':               //   m�̳� M�̸�
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);    //  transpose_matrix�� ���� a�� ��ġ���������
            multiply_matrix(matrix_a, matrix_a_t, row, col);         // multiply_matrix�� ���� a�� a����ġ����� ����
            break;                                   //  switch�� ��������
        case 'q': case 'Q':                            // q�� Q�̸�
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);    //  matrix_a_t�޸�����
            free_matrix(matrix_a, row, col);    //  matrix_a �޸� ����
            free_matrix(matrix_b, row, col);     //   matrix_b �޸� ����
            break;                                //   switch�� ��������
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //   ���� ��ɾ�� �����϶�� ���
            break;                                     //   switch�� ��������
        }

    } while (command != 'q' && command != 'Q');   //   q�� Q�� �Էµɶ����� while�� �ݺ�

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {      // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return NULL;
    }
    
    int** arr = (int**)malloc(sizeof(int*) * row);  //   arr�����Ҵ�

    for (int i = 0; i < row; i++)     // row�� ����ŭ����(���Ǽ�)
    {
        arr[i] = (int*)malloc(sizeof(int) * col);  //   arr[i]�����Ҵ� ũ��� int��*col(���� ��)
    }

    if (arr == NULL) {       //   arr�� ���������
        create_matrix(row, col);       //   �ٽ� create_matrix �Լ��� �̵�
    }

    return arr;  //   �����Ҵ��� arr�� return
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)   //  ����� ����ϴ� �Լ�
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
    }

    for (int i = 0; i < row; i++) {           //  �ุŭ�ݺ�
        for (int k = 0; k < col; k++) {        //  ����ŭ�ݺ�
            printf("%3d ", matrix[i][k]);     //  matrix[��][��] �� ���
        }
        printf("\n");         //�� ���̳����� ���ٶ��
    }

    if (matrix == NULL) {    //������ �ִٸ� �ٽ� ����
        print_matrix(matrix, row, col);
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)        //  �޸������ϴ� �Լ�
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return -1;   //not okay
    }

    for (int i = 0; i < row; i++) {      //  �ุŭ �ݺ�
        free(matrix[i]);             //  matrix[i] ���� ,�ุŭ �ݺ��ϴ� ������ ������ �� (int**)malloc(sizeof(int*) * row);�� ���� ���Ǽ���ŭ����
   }
    free(matrix);   //  �ι� �����Ҵ������� �ѹ��� matrix����

    return 1; //�� ���۽� return 1
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)  //  ��Ŀ� ���� ä���ش� �Լ�
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return -1;   //not okay
    }

    for (int i = 0; i < row; i++) {  //  �ุŭ�ݺ�
        for (int k = 0; k < col; k++) {  //  ����ŭ�ݺ�
            matrix[i][k] = rand() % 20;  // matrix[i][k]���� 0~19
        }
    }

    if (matrix == NULL) {    //������ �ִٸ� �ٽ� ����
       fill_data(matrix, row, col);
    }

    print_matrix(matrix, row, col);   //  print_matrix �Լ��� ���� matrix���
    printf("\n");
    return 1; //�� ���۽� return 1
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)  //  ����� �� ���� ���ϴ� �Լ�
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return -1;   //not okay
    }

    int** matrix_sum;             //  ���������� matrix_sum ����
   matrix_sum=create_matrix(row,col);        //  matrix_sum�� create_matrix�Լ��� �̿��� ���� ���� arr����
    for (int i = 0; i < row; i++) {     //  �ุŭ �ݺ�
        for (int k = 0; k < col; k++) {         //  ����ŭ �ݺ�
         matrix_sum[i][k]= matrix_a[i][k] + matrix_b[i][k];   //  �� ���д�����
        }
    }

    if (matrix_sum == NULL) {    //������ �ִٸ� �ٽ� ����
        addition_matrix(matrix_a,matrix_b, row, col);
    }

    print_matrix(matrix_sum, row, col);  //  matrix_sum���
    free_matrix(matrix_sum, row, col);    //  matrix_sum���� ���⼭ �����ϴ� ������ �޴����� q�� �������� �̰� ���� ����

    return 1; //�� ���۽� return 1
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)  //  ����� �� ���� ���� �Լ�
{

    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return -1;   //not okay
    }

    int** matrix_sub;              //���������� matrix_sub;����
    matrix_sub = create_matrix(row, col);         //  create_matrix(row, col)�Լ��� ����� matrix_sub�� �� �־��ش�.
    for (int i = 0; i < row; i++) {            //  row��ŭ �ݺ�
        for (int k = 0; k < col; k++) {             //  col��ŭ �ݺ�
            matrix_sub[i][k] = matrix_a[i][k] - matrix_b[i][k];       //  matrix_sub[i][k]�� matrix_a[i][k] - matrix_b[i][k]�� ���� �־��ش�.  
        }
    }

    if (matrix_sub == NULL) {    //������ �ִٸ� �ٽ� ����
        subtraction_matrix(matrix_a, matrix_b, row, col);
    }

    print_matrix(matrix_sub, row, col);    //  matrix_sub�� ������ش�
    free_matrix(matrix_sub, row, col);      //  matrix_sub�� �޸𸮸� �������ش�. 
    return 1; //�� ���۽� return 1

}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)      //  �����Լ����� �����Ҷ� col,row�� �����Ѵ�
{           
    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return -1;   //not okay
    }

    for (int i = 0; i < col; i++) {                         //  col��ŭ �ݺ�
        for (int j = 0; j < row; j++) {                     //  row��ŭ �ݺ�
            matrix_t[j][i] = matrix[i][j];                // matrix[i][j]�� ���� matrix_t[j][i] �� �־��ش�.
        }
    }

    return 1; //�� ���۽� return 1
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)     //  ���ϴ� �Լ�
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {              // �Էµ� ������� 0�����̸� 
        printf("Check the sizes of row and col!\n");   // �߸��Է��ߴٰ� �˷���
        return -1;   //not okay
    }

    if ((matrix_t == NULL)||(matrix_a==NULL)) {      //  ���� ���ϴµ� ����� ��� matrix_t�� ��� matrix_a�� ����ִٸ�
        /* proper actions for unexpected conditions */
        printf("Make a matrix first");             //  ����� ���� ������ ���
    }
    
    int** matrix_axt;                               //  ���������� matrix_axt����
    matrix_axt = create_matrix(row, row);            // ���⼭ ����� ���� �ߴµ� row�� col�� �ٸ���� ���ο� ����� row,col�� �־ ����� ���߿� �����Ⱚ�� ���´�
                                                     // row �� col�� �ٸ���� ��������� ����� (row *col)*(col*row)=(row,row) �� row�� row�� ���ڷ� ����� ����� row�� col�� �ٸ���쿡�� ������ �����ʴ´�
    for (int i = 0; i < row; i++) {                   // 3*2��İ� 2*3����� �׷��� �ε����� ���� �����غ��� �̷����� �����ߴ�. 
        for (int k = 0; k < row; k++) {                            // �ٱ��� �ΰ��� �ݺ������� row  ���� ���� �ݺ������� col���� �ݺ��Ѵ� 
            matrix_axt[i][k] = 0;                                       //  matrix_axt[i][k]�� �ϴ� 0�� �־���(�ʱ�ȭ) create_matrix�Լ� ���� ���� �����������
            for (int j = 0; j < col; j++) {
                matrix_axt[i][k] += (matrix_a[i][j] * matrix_t[j][k]);  // matrix_axt[i][k]�� ���� �ݺ����� ���� �����ش�
            }
        }
    }

    if ((matrix_a == NULL)|| (matrix_t == NULL)) {    //������ �ִٸ� �ٽ� ����
        multiply_matrix(matrix_a,matrix_t, row, col);
    }

    print_matrix(matrix_axt, row, row);    // matrix_axt ����� ������ش�
    free_matrix(matrix_axt, row, col);         // matrix_axt �޸𸮸� �������ش�.
    return 1; //�� ���۽� return 1
}

