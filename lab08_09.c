#include<stdio.h>

int main(){


        int sparse_mat[3][3] = 
        {
            (1 , 0 , 0),
            (0 , 0 , 2),
            (3 , 0 , 0)
        };

        int s =0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(sparse_mat[i][j] != 0){
                    s++;
                }
            }
            int matrix[3][s];
            int k = 0;
            for(int i =0;i<3;i++){
                  for(int j = 0;j<3;j++){
                    if(sparse_mat[i][j]!=0){
                        matrix[0][k] = i;
                        matrix[1][k] = j;
                        matrix[2][k] = sparse_mat[i][j];
                        k++;
                    }
                  }
            }
        for(int i =0;i<3;i++){
            for(int j = 0;j<3;j++){
                printf("%d ",matrix[i][j]);
                printf("\t");
            }
            printf("\n");


        }

        }   
    return 0;
}