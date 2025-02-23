#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 150

void maxPath(int* max, int sum, int curr, int ix ,int** trikotnik, int n){
    if(curr > n || ix > curr) return;

    if(curr == n){
        if(*max < sum) *max=sum;
        return;
    }

    //leva pot
    maxPath(max,sum+trikotnik[curr][ix], curr+1,ix, trikotnik,n);

    //desna pot
    maxPath(max,sum+trikotnik[curr][ix], curr+1, ix+1,trikotnik, n);
}

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
        
        /* for(int j=0;j<i;j++) printf("%d ", trikotnik[n][j]);
        printf("\n");*/
        n++;
    }

    //rekurzija
    int max=0;
    maxPath(&max, 0,0,0, trikotnik,n);
    printf("%d\n", max);

    //počistimo za sabo
    free(temp);
    for(int i=0;i<MAX;i++) free(trikotnik[i]);
    free(trikotnik); 
    
    return 0;
}
