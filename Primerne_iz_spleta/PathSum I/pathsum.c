#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

#define MAX 500
#define int64 long long

int main(){
    FILE* in = fopen("test02.txt", "rt");
    int n=0;
    char* temp=calloc(MAX, sizeof(char));
    int64** mat = calloc(MAX, sizeof(int64*));
    for(int i=0;i<MAX;i++) mat[i] = calloc(MAX, sizeof(int64));

    while(fgets(temp,MAX, in)!=NULL){
        int i=0;
        char* a=strtok(temp, ",\n");
        while(a != NULL){
            mat[n][i]=atoll(a);
            i++;
            a=strtok(NULL,",\n");
        }
        /* for(int j=0;j<i;j++) printf("%d ", mat[n][j]);
        printf("\n"); */

        n++;
    }

    //botom up;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==0 && j!=0) mat[i][j]+=mat[i][j-1]; //prvi vrstici imamo samo premik desno
            else if(j==0 && i!=0) mat[i][j]+=mat[i-1][j]; //prvi stolpec imamo samo premik navzdol
            
            else if (j!=0 && i!=0){
                mat[i][j]+= (mat[i-1][j] < mat[i][j-1]) ? mat[i-1][j] : mat[i][j-1];
            }

        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%lld ", mat[i][j]);            
        } printf("\n"); 
    } 

    printf("%lld\n", mat[n-1][n-1]);

    //počistimo
    free(temp);
    for(int i=0;i<MAX;i++) free(mat[i]);
    free(mat);
    fclose(in);
    return 0;
}