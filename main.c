#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "queue.c"


//Cấu trúc điểm
struct point{
    int row;
    int col;
    int node;
};

//Cấu trúc lưu điểm cha
struct back{
    int fa;
    int son;
};

//Hàm kiểm tra điểm bất kỳ có tọa độ nằm trong ma trận đã khai báo hay không.
bool kiemtraDiem(int x, int y);

//Hàm tìm các điểm xung quanh điểm bất kỳ có giá trị 1.
bool kiemtraDiemXungQuanh(int mtx[9][9], int row,int col);

//Hàm kiểm tra điểm có âm hay không
bool kiemTra(int x, int y);

//Hàm tìm quãng đường ngắn nhất đi qua các điểm cần thiết tới điểm đích.
void nganNhat(int count,int fa,struct back b[20],struct point p[100]);

int main()
{
    //Khai báo ma trận
    int matrix[9][9] = {
    {1, 0, 0, 0, 1, 0, 1, 1, 0},
    {1, 1, 0, 1, 1, 1, 0, 0, 1},
    {0, 1, 0, 1, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 0, 1, 0, 1, 1},
    {0, 0, 1, 0, 1, 0, 1, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 1, 1, 1, 1, 1, 0}
    };

    //Khai báo các biến cần thiết
    int x, y;
    bool check;
    struct point p[100];
    struct back b[20];

    //Gán các biến cấu trúc điểm bằng -1
    for(int i = 0;i < 100; i++){
        p[i].row = -1;
        p[i].col = -1;
    }

    //In ma trận ra màn hình
    printf("Ma tran:\n");
    for(int i = 0;i < 9; i++){
        for(int j = 0;j < 9; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }


    //Phần kiểm tra tọa độ điểm có nằm trong ma trận
    printf("--------------------------------------------\n");
    printf("Nhap toa do de kiem tra:\n");
    do{
       do{
          printf("Nhap toa do x lon hon 0 cua diem:");
          scanf("%d", &x);
         }
        while(x < 0);

       do{
         printf("Nhap toa do y lon hon 0 cua diem:");
         scanf("%d", &y);
       }
       while(y < 0);

        check = kiemtraDiem(x, y);
    }
    while(check == false);


    //Phần kiểm tra các điểm xung quanh có bằng 1
    printf("--------------------------------------------\n");
    printf("Cac diem xung quanh co gia tri bang 1 la:\n");
    if(kiemtraDiemXungQuanh(matrix, y + 1, x)){
        printf("Diem (%d, %d) co gia tri bang 1\n",x, (y + 1));
    }

    if(kiemtraDiemXungQuanh(matrix, y, x + 1)){
       printf("Diem (%d, %d) co gia tri bang 1\n", (x + 1), y);
    }

    if(kiemtraDiemXungQuanh(matrix, y - 1, x)){
        printf("Diem (%d, %d) co gia tri bang 1\n", x, (y - 1));
    }

    if(kiemtraDiemXungQuanh(matrix, y, x - 1)){
       printf("Diem (%d, %d) co gia tri bang 1\n", (x - 1), y);
    }


    //Xử lí thuật toán tìm đường
    printf("--------------------------------------------\n");
    if(matrix[x][y] == 0){
        printf("Khong the tim duong ngan nhat\n");
    }
    else
    {
    struct Queue* queue = createQueue(1000);
    int count = 0;
    p[count].row = 0;
    p[count].col = 0;
    p[count].node = count;
    enqueue(queue, p[count].node);

    while(isEmpty(queue) != 1){

        int u = front(queue);
        dequeue(queue);

        if(p[u].col == x && p[u].row == y){
                ++count;
            b[count].fa = u;
            b[count].son = count;
            p[count].row = x;
            p[count].col = y;
            p[count].node = count;
            enqueue(queue, p[count].node);
            break;
        }

        if(kiemtraDiemXungQuanh(matrix, p[u].row,(p[u].col + 1)) &&
           kiemTra(p[u].col + 1, p[u].row)){
               bool key = true;
               for(int i = 0;i < 100; i++){
                if(p[i].row == p[u].row && p[i].col == (p[u].col + 1)){
                    key = false;
                    break;
                }
               }
               if(key){
               ++count;
               b[count].fa = u;
               b[count].son = count;
               p[count].row = p[u].row;
               p[count].col = (p[u].col + 1);
               p[count].node = count;
               enqueue(queue, p[count].node);}
        }
        if(kiemtraDiemXungQuanh(matrix, (p[u].row + 1), p[u].col) &&
           kiemTra(p[u].col, p[u].row + 1)){
             bool key = true;
               for(int i = 0;i < 100; i++){
                if(p[i].row == (p[u].row + 1) && p[i].col == p[u].col){
                    key = false;
                    break;
                }
               }
            if(key){
            ++count;
            b[count].fa = u;
            b[count].son = count;
            p[count].row = (p[u].row + 1);
            p[count].col = p[u].col;
            p[count].node = count;
            enqueue(queue, p[count].node);}
        }
         if(kiemtraDiemXungQuanh(matrix, p[u].row, (p[u].col - 1)) &&
            kiemTra(p[u].col - 1, p[u].row)){
            bool key = true;
               for(int i = 0;i < 100; i++){
                if(p[i].row == p[u].row && p[i].col == (p[u].col - 1)){
                   key = false;
                    break;
                }
               }
               if(key){
               ++count;
               b[count].fa = u;
               b[count].son = count;
               p[count].row = p[u].row;
               p[count].col = (p[u].col - 1);
               p[count].node = count;
               enqueue(queue, p[count].node);}
        }
         if(kiemtraDiemXungQuanh(matrix, (p[u].row - 1), p[u].col) &&
            kiemTra(p[u].col, p[u].row - 1)){
             bool key = true;
               for(int i = 0;i < 100; i++){
                if(p[i].row == (p[u].row - 1) && p[i].col == p[u].col){
                    key = false;
                    break;
                }
               }
            if(key){
            ++count;
            b[count].fa = u;
            b[count].son = count;
            p[count].row = (p[u].row - 1);
            p[count].col = p[u].col;
            p[count].node = count;
            enqueue(queue, p[count].node);}
        }
    }

    //In kết quả các điểm để tới điểm đích
    printf("Cac diem can thiet de toi diem dich la:\n");
    for(int i = 0;i < count - 1; i++){
        printf("Diem %d:(%d, %d)\n", p[i].node, p[i].col, p[i].row);
    }


    //In ra quãng đường ngắn nhất
    printf("--------------------------------------------\n");
    printf("Duong di ngan nhat la:\n");
    nganNhat(b[count].son, b[count].fa, b, p);
}
    printf("\n");
    return 0;
}


//Hàm kiểm tra điểm bất kỳ có tọa độ nằm trong ma trận đã khai báo hay không.
bool kiemtraDiem(int x, int y){
    if(x > 8 || y > 8){
        printf("\n");
        printf("Diem ban nhap khong ton tai trong ma tran\n");
        printf("-----------------------------------------\n");
        return false;
    }
    else{
        printf("Diem ban nhap ton tai trong ma tran\n");
        return true;
    }
}


//Hàm tìm các điểm xung quanh điểm bất kỳ có giá trị 1.
bool kiemtraDiemXungQuanh(int mtx[9][9], int row,int col){
    if(mtx[row][col] == 1)
        return true;
    else
        return false;
}


//Hàm kiểm tra điểm có âm hay không
bool kiemTra(int x, int y){
    if(x < 0 || y < 0)
        return false;
    else
        return true;
}


//Hàm tìm quãng đường ngắn nhất đi qua các điểm cần thiết tới điểm đích.
void nganNhat(int son,int fa,struct back b[20],struct point p[100]){
    int fa1 = 0;
    int son1 = 0;
    if(fa == 0 && son == 0){
        return 0;
    }
    else{
        for(int i = 0;i < 20; i++){
            if(fa == b[i].son){
                fa1 = b[i].fa;
                son1 = b[i].son;
                break;
            }
        }
        printf("(%d, %d)", p[son1].col, p[son1].row);
        nganNhat(son1, fa1, b, p);
    }
}



