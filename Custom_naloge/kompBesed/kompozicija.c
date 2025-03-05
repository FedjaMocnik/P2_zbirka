#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 30
char nova[MAX];
long long num=0;

void razcleni(char* w, int min, int max, int n, int w_ix, int nova_ix, bool prev){
    if(w_ix == strlen(w)){
        if(n >= min && n <= max){
            //printamo po do ix, saj so lahko ostali kakšni chari od prej.
            //alternativa je, da sproti brišeš
            for(int i=0;i<nova_ix;i++) printf("%c", nova[i]);
            printf("\n");
            num++;
        }
        return;
    }
    
    //ne izberemo |
    nova[nova_ix]= w[w_ix];
    razcleni(w, min,max,n,w_ix+1,nova_ix+1,false);

    //izberemo |, če lahko
    if(!prev){
        nova[nova_ix] = '|';
        razcleni(w, min,max, n+1,w_ix,nova_ix+1,true);
    }
    
    return;
}

int main(){
    char* beseda = calloc(MAX,sizeof(char));
    int a=0,b=0;
    //izpiši število kompozicije beseda na min a in max b delov
    //izpiši tudi vse kompozicije aba 1 2 -> 3 aba, a|ba, ab|a
    scanf("%s %d %d", beseda, &a, &b);

    num=0;
    razcleni(beseda,a-1,b-1,0,0,0,true);
    printf("%lld\n", num);

    free(beseda);
    return 0;
}