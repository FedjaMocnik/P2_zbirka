#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
/* int vz=0;
int izb[11]; */

void kovanci(int* count, int ix, int sum, int* vals, int n){
    if(sum==0){
       *count+=1; //nov seštevek
       //for(int i=0;i<11;i++) if(izb[i]!=0)printf("%d +", izb[i]); printf("\n");
       return;
    } 
    if(sum < 0 || ix >= n) return;

    if(sum>=vals[ix]){
        //izb[vz++]=vals[ix];
        kovanci(count, ix, sum-vals[ix], vals, n);
        //vz--; izb[vz]=0;
    }     
    
    if(sum>=vals[ix]){
        kovanci(count, ix+1, sum, vals, n);
    }
}

int main(){
    int count=0;
    int val=0; int n=0;
    printf("vnesi znesek: "); scanf("%d", &val);
    printf("vnesi st. bankovcev: "); scanf("%d", &n);
    int* vals = calloc(n, sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &vals[i]);
    
    kovanci(&count,0,val,vals,n);
    printf("%d\n", count);
    free(vals);
    return 0;
}

