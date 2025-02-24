#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX 305
#define strMAX 40

int isGreater(char* d1, char* d2){
    //dobimo dva string datuma in ju moramo evalvirati
    //datum oblike dd.mm.yyyy
    int* datum1 = calloc(3, sizeof(int));
    int* datum2 = calloc(3, sizeof(int));

    char* cd1 = calloc(strlen(d1), sizeof(char));
    char* cd2 = calloc(strlen(d2), sizeof(char));
    strcpy(cd1,d1); 
    strcpy(cd2,d2);

    char* a = strtok(cd1, ".");
    for (int i = 0; i < 3 && a != NULL; i++) {
        datum1[i] = atoi(a);
        a = strtok(NULL, ".");
    } free(cd1);

    char* b = strtok(cd2, ".");
    for (int i = 0; i < 3 && b != NULL; i++) {
        datum2[i] = atoi(b);
        b = strtok(NULL, ".");
    } free(cd2);
    

    //for(int i=0;i<3;i++) printf("%d: d1:%d in d2:%d\n", i, datum1[i], datum2[i]);
    if(datum1[2]!=datum2[2]) return datum1[2]-datum2[2]; //leta
    else if (datum1[1]!=datum2[1]) return datum1[1]-datum2[1]; //meseci
    else if(datum1[0]!=datum2[0]) return datum1[0]-datum2[0]; //dnevi
    else return 0; //sicer enaka
}

int main(){
    FILE* in = fopen("podatki3.csv", "rt");

    char*** podatki=calloc(MAX, sizeof(char**));
    for(int i=0;i<MAX; i++) podatki[i]=calloc(MAX, sizeof(char*));
    
    char* line = calloc(MAX, sizeof(char));

    int n=0; //stevilo vrstic
    int el=0; //stevilo elementov v eni vrstici

    while(fgets(line, MAX, in)!=NULL){
        //printf("%s", line);

        el=0;
        char* a = strtok(line, ",\n");
        //printf("%s\n", a);

        while(a!=NULL){
            //printf("%d\n", el);
            podatki[n][el]=calloc(strlen(a), sizeof(char));
            strcpy(podatki[n][el],a);
            a = strtok(NULL, ",\n");
            el++;
        } 
        n++;
    }

    /* for(int i=0;i<n;i++){
        for(int j=0;j<el;j++){
            printf("%s ", podatki[i][j]);
        } printf("\n");
    } */

    //zdaj moramo izvesti še poizvedbo,
    //iz vsake države potrebujemo najmlajšega, če sta dva tistega z leksikografsko najmanjšim imenom
    int ix_date=-1;
    int ix_country=-1;
    int ix_name=-1;
    
    for(int i=0;i<el;i++){
        if(!strcmp("name", podatki[0][i])) ix_name=i;
        else if (!strcmp("date", podatki[0][i])) ix_date = i;
        else if (!strcmp("country", podatki[0][i])) ix_country = i;
    } 

    //printf("%s\n", podatki[1][ix_date]);


    //printf("coutnry: %d name: %d date: %d\n", ix_country, ix_name, ix_date);
       
    //naredimo tabelo n velikosti, ker lahko se zgodi, da so vsi iz iste države isto starti le imena različna
    char** drzave=calloc(n, sizeof(char*));
    for(int i=0;i<n;i++) drzave[i]=calloc(strMAX,sizeof(char));

    //poiščemo katere države imamo in koliko jih je:
    int nDrzav=0;

    for(int i=1;i<n;i++){
        bool nimamo=1;
        for(int j=0;j<nDrzav;j++){
            if(!strcmp(drzave[j], podatki[i][ix_country])) nimamo = 0;
        }
        if(nimamo){
            strcpy(drzave[nDrzav],podatki[i][ix_country]);
            
            nDrzav++;
        }
    }
    
    
    //test print
    //for(int i=0;i<nDrzav;i++) printf("%d: %s\n",i, drzave[i]);

    //spet potrebujemo precej veliko tabelo, ki bo vsebovala vse najmlajše:
    
    int* najmlajsi= calloc(nDrzav, sizeof(int));

    for(int i=1;i<n;i++){
        //nas primerek je podatki[i][karkoli že želimo]
        int iz_drzave=0;

        for(int j=0;j<nDrzav;j++){
            if(!strcmp(drzave[j], podatki[i][ix_country])) iz_drzave=j;
        }

        if(najmlajsi[iz_drzave]==0){
            //indeks 0 ni veljaven, torej ga lahko takoj zapišemo kot najmlajšega:
            najmlajsi[iz_drzave]=i;
        } else {
            //je že bil nekoč nastavljen: A-mlajši B-leksikografsko manjše ime:
            int comp=isGreater(podatki[najmlajsi[iz_drzave]][ix_date], podatki[i][ix_date]);
            //printf("%d\n", comp);
            if(comp<0){
                najmlajsi[iz_drzave]=i;
            } else if(comp==0){
                //datuma enaka
                int name_comp=strcmp(podatki[najmlajsi[iz_drzave]][ix_name], podatki[i][ix_name]);
                if(name_comp>0){
                    najmlajsi[iz_drzave]=i;
                }
            }
        }
    }

    //zadnji PRINT
    for(int i=0;i<nDrzav;i++){
        printf("%s %s %s\n", podatki[najmlajsi[i]][ix_name], podatki[najmlajsi[i]][ix_country],podatki[najmlajsi[i]][ix_date]);
    }


    //počistimo za sabo
    free(najmlajsi);
    
    for(int i=0;i<n;i++) free(drzave[i]);
    free(drzave);

    //podatki
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX; j++) free(podatki[i][j]);
        free(podatki[i]);
    }
    free(podatki);
    free(line);
    fclose(in);
    return 0;
}
