#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int count=0;
int izbor[70];

void toString(int len){
    //printf("+---To String---+\n");
    printf("%d ", izbor[0]);

    for(int i=1;i<len;i++){
        printf("+ %d ",izbor[i]);
    } printf("\n");
}

int primes(int n, int* primes){
    int ix=0;
    for(int i=n;i>1;i--){
        bool prime=true;
        for(int j=2;j<=sqrt(i);j++){
            if(!(i%j)) prime=false;
        }
        if(prime) primes[ix++]=i;
    }

    return ix;
}

void findPrimeSUM(int n, int* prime, int pl, int ix, int len){
    if(n<0 || ix>=pl) return;
    if(n==0){
        count++;
        toString(len);
        return;
    }

    izbor[len]=prime[ix];
    findPrimeSUM(n-prime[ix], prime, pl, ix,len+1); //vzamemo trenutnega
    izbor[len]=0;
    findPrimeSUM(n,prime,pl,ix+1,len); //ne vzamemo trenutnega in ga nikoli več ne bomo

}

int main(){
    //int n=30;
    

    /* for(int i=0;i<len;i++) printf("%d ", prime[i]);
    printf("\n"); */

    int winner=0;

    for(int i=0;i<72;i++){
        int* prime=calloc(i,sizeof(int));
        int len=primes(i, prime);

        count=0;
        findPrimeSUM(i,prime,len,0,0);
        printf("%d: %d\n", i, count);
        winner=i;

        if(count > 5000) break;
        free(prime);
    }
    printf("\n%d: %d\n", winner, count);

    return 0;
}