#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int konj_x[]={2,2,-2,-2,1,1,-1,-1};
int konj_y[]={1,-1,1,-1,2,-2,2,-2};

void printB(bool** sah, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(sah[i][j]) printf("X");
            else printf("O");
        }
        printf("\n");
    } printf("\n");
}

int obleganje(bool** sah, int n, int x,int y,int curr){
    //printf("x:%d y:%d curr:%d\n", x,y,curr);
    if(x>n-1){
        y++;
        x=0;
    }
    if(y>n-1) return curr;

    //naredimo kopijo spomina za backtracking:
    bool** temp = malloc(n*sizeof(bool*));
    for(int i=0;i<n;i++){
        temp[i]=malloc(n*sizeof(bool));
        memcpy(temp[i], sah[i], sizeof(bool*));
    }

    int brez = obleganje(sah, n, x+1,y,curr);
    int konj=-1;

    if(!sah[x][y]){
        sah[x][y]=true;
        for(int i=0;i<8;i++){ //konjevi premiki, da slučajno ne napade svojega
            if(x+konj_x[i] < n && x+konj_x[i]>=0 && y+konj_y[i]<n && y+konj_y[i]>=0){
                sah[x+konj_x[i]][y+konj_y[i]]=true;
            }
        }
        konj = obleganje(sah, n, x+1,y,curr+1);        
    }
    //printB(sah,n);

    //backtracking
    for(int i=0;i<n;i++) memcpy(sah[i],temp[i],sizeof(bool*));
    for(int i=0;i<n;i++) free(temp[i]);
    free(temp); 

    return (konj > brez) ? konj : brez;
}

int main(){
    int n, p;
    scanf("%d %d", &n ,&p);

    //printf("%d %d %d\n", n, p, y[p-1]);
    bool** sah = calloc(n,sizeof(bool*));
    for(int i=0;i<n;i++) sah[i]=calloc(n, sizeof(bool));

    for(int i=0;i<p;i++){ 
        int x=0, y=0;
        scanf("%d %d", &x, &y);
        
        for(int j=0;j<n;j++){
            sah[x][j]=true;
            sah[j][y]=true;
        }
    }

    //printB(sah, n);

    int res = obleganje(sah, n, 0,0,0);
    printf("%d\n", res);
    
    for(int i=0;i<n;i++) free(sah[i]);
    free(sah);
    return 0;
}