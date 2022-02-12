#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 10


int main(int argc, char const *argv[]){

    struct Area* root = NULL;
    struct Area* retval ;
    int area, id;
    char* datasets[] = {"dataset1.txt", "dataset2.txt", "dataset3.txt","dataset4.txt"};
    char* infos[] = {"patientinfo1.txt", "patientinfo2.txt", "patientinfo3.txt","patientinfo4.txt"};


    int i;
    for(i=0;i<20;i++){
        insertNodeAVL(i+1,&root);

    }
    clock_t t;
    t = clock();

    FILE* f = fopen("dataset1.txt","r");
    if(!f)exit(0);

    while(fscanf(f,"%d %d\n",&area,&id)!=EOF){

        //Finding Best Hospital
        srand(time(NULL));
        int rum1 = rand()%4;
        retval = searchNodeAVL(area,&root);
        int host_id = add_patient(&retval->head);

        //Random discharge of patient.
        if(rum1 == 0)random_del(&retval->head);

        //Writing patient info to a log txt.
        FILE* f2 = fopen("patientinfo1.txt","a");
        if(!f2) exit(0);
        
        time_t rawtime;
        struct tm * timeinfo;

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        fprintf(f2,"%d %d %d %s",area,host_id,id,asctime(timeinfo));
        fclose(f2);

    }

    fclose(f);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    printf("The program took %f seconds to execute\n\n", time_taken);

    FILE* f3 = fopen("records.txt","a");
    if(!f)exit(0);

    fprintf(f3,"%d %f\n",1000,time_taken);

    fclose(f3); 

    for (i=0;i<20;i++){
        printf("Area:%d\n",i+1);
        retval = searchNodeAVL(i+1,&root);
        print_list(retval->head);
        printf("\n\n");
    }
    
    return 0;
}