#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 150

int main(){
    FILE* in = fopen("test03.txt", "rt");
    int n=0;
    //beremo vhod, in
    char* temp=calloc(MAX*3, sizeof(char));

    int** trikotnik = calloc(MAX,sizeof(int*));
    for(int i=0;i<MAX;i++) trikotnik[i]=calloc(MAX, sizeof(int));

    while(fgets(temp, MAX*3, in) !=NULL){
        int i=0;
        char* a=strtok(temp, " \n");
        while(a != NULL){
            trikotnik[n][i]=atoi(a);
            i++;
            a=strtok(NULL, " \n");
        }

        n++;
    }

    //Dinamično programiranje: od spodaj navzgor
    for(int i=n-2; i>=0;i--){ //n-2, ker je n-1 so že vsote vseh poti
        for(int j=0;j<=i;j++){
            trikotnik[i][j] += (trikotnik[i+1][j] > trikotnik[i+1][j+1]) ? trikotnik[i+1][j] : trikotnik[i+1][j+1];
        }
    }

    printf("%d\n", trikotnik[0][0]);

    //počistimo za sabo
    free(temp);
    for(int i=0;i<MAX;i++) free(trikotnik[i]);
    free(trikotnik); 
    return 0;
}
