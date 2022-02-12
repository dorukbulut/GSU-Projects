#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_SIZE 20
//AVL func.

int getMax(int a,int b){

    if(a >= b) return a;

    return b;

}
int getHeight( struct Area* root){
    
    if(root == NULL) return  0;
    if(root->l == NULL && root->r== NULL) return 1;

    return 1 + getMax(getHeight(root->r),getHeight(root->l));
}

int getBalance( struct Area* root){

    return getHeight(root->l) - getHeight(root->r);
}

void ReBalanceInsertion(int id, struct Area** root){

    int balance = getBalance(*root);

    if(balance > 1 && id < (*root)->l->id) {

        r_rotate(root);
        return;
    }

    if(balance < -1 && id > (*root)->r->id) {

        l_rotate(root);
        return;
    }

     if(balance > 1 && id > (*root)->l->id) {

        l_rotate(&(*root)->l);
        r_rotate(root);
        return;
    }


     if(balance < -1 && id < (*root)->r->id) {

        r_rotate(&(*root)->r);
        l_rotate(root);
        return;
    }

    return;
}

void ReBalanceDeletion( struct Area** root){
    int balance = getBalance(*root);

    if(balance > 1 && getBalance((*root)->l)>=0) {

        r_rotate(root);
        return;
    }

    if(balance < -1 && getBalance((*root)->r) <=0){

        l_rotate(root);
        return;
    }

     if(balance > 1 && getBalance((*root)->l ) < 0){

        l_rotate(&(*root)->l);
        r_rotate(root);
        return;
    }


     if(balance < -1 && getBalance((*root)->r ) > 0){

        r_rotate(&(*root)->r);
        l_rotate(root);
        return;
    }

    return;
}

void r_rotate( struct Area** root){

     struct Area*  tmp =  (*root)->l;
     struct Area*  sub_t = tmp->r;

    tmp->r = *root;
    (*root)->l = sub_t;

    (*root)->height = getHeight(*root);
    tmp->height = getHeight(tmp);

    *root = tmp;
}

void l_rotate( struct Area** root){

     struct Area* tmp = (*root)->r;
     struct Area* sub_t = tmp->l;

    tmp->l = *root;
    (*root)->r = sub_t;

    (*root)->height = getHeight(*root);
    tmp->height = getHeight(tmp);

    *root = tmp;
}

int findMin( struct Area* root){

    if(root->l == NULL) return root->id;

    

    
    return findMin(root->l);
}


void insertNodeAVL(int area_id,struct Area** root){

     struct Area* newArea = malloc(sizeof( struct Area));

    if(newArea == NULL) exit(0);
    newArea->head = NULL;
    newArea->id = area_id;
    for(int i=0;i<10;i++){
        insert_node(i+1,0,&newArea->head);
    } 
    
    newArea->height = 1;
    newArea->l = NULL;
    newArea->r = NULL;

    
    

    if(*root == NULL){
        
        *root = newArea;
        return;
    }

    if(area_id<(*root)->id)insertNodeAVL(area_id,&(*root)->l);

    else if(area_id>(*root)->id)insertNodeAVL(area_id,&(*root)->r);

    


    

    (*root)->height = 1 + getHeight(*root);

    ReBalanceInsertion(area_id,root);

    return;
}

void deleteNodeAVL(int aread_id,  struct Area** root){
    
    if(*root==NULL)return;

    else if((*root)->id> aread_id) deleteNodeAVL(aread_id,&(*root)->l);

    else if((*root)->id < aread_id) deleteNodeAVL(aread_id,&(*root)->r);

    else {
        
        if((*root)->l== NULL && (*root)->r==NULL){

            free(*root);
            *root = NULL;

            return;

        }

        if((*root)->l == NULL){
            
             struct Area* tmp = (*root);
            *root = (*root)->r;
            free(tmp);
            tmp = NULL;
            return;
        }

        if((*root)->r == NULL){

             struct Area* tmp = (*root);
            *root = (*root)->l;
            free(tmp);

            tmp = NULL;
            
            return;
        }


        else{
             struct Area* min = searchNodeAVL(findMin((*root)->r),root);

            (*root)->id = min->id;

            
            deleteNodeAVL(min->id,&(*root)->r);

            return;
        }
    }
    
    


     

    
    ReBalanceDeletion(root);

    return;
}

 struct Area* searchNodeAVL(int area_id,  struct Area** root){
    if ((*root)->id == area_id) return *root;
    
    

    if(area_id < (*root)->id){
        
            
        return searchNodeAVL(area_id,&(*root)->l);

    }

    if(area_id > (*root)->id){
        
            
        return searchNodeAVL(area_id,&(*root)->r);

    }
}

void PreOrder(struct Area* root ){
    if(root == NULL) return;

    printf("%d " ,root->id);
    PreOrder(root->l);
    PreOrder(root->r);
}


//Host funcs.

void insert_node(int host_id, int num_patients,struct Host** head){
    
    struct Host* newNode = malloc(sizeof(struct Host));
    if(!newNode) exit(0);

    newNode->host_id = host_id;
    newNode->num_patient = num_patients;
    
    newNode->next = *head;
    *head = newNode;

}

void sort(struct Host** root){
    struct Host* head = *root;
    struct Host* a;
    struct Host* b;
 
    
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    
    split(head, &a, &b);
 
    
    sort(&a);
    sort(&b);
 
    
    *root = merge(a, b);
}

struct Host* merge(struct Host* head1, struct Host* head2){
    struct Host* result = NULL;
 
    
    if (head1 == NULL)
        return (head2);
    else if (head2 == NULL)
        return (head1);
 
    
    if (head1->num_patient <= head2->num_patient) {
        result = head1;
        result->next = merge(head1->next, head2);
    }
    else {
        result = head2;
        result->next = merge(head1, head2->next);
    }
    return (result);
}

void split(struct Host* head,struct Host** part1, struct Host** part2){
    struct Host* tmp = head->next;
    struct Host* before = head;
    
 
    
    while (tmp != NULL) {
        tmp = tmp->next;
        if (tmp != NULL) {
            before = before->next;
            tmp = tmp->next;
        }
    }
 
    
    *part1 = head;
    *part2 = before->next;
    before->next = NULL;
}



int add_patient(struct Host** head){
    struct Host* tmp = *head;
    
    tmp->num_patient += 1;
    
    sort(head);

    return tmp->host_id; 

    
}

int is_full(struct Host* head){
    
    if(head->num_patient > MAX_SIZE)return 1;
    else return 0;
 }


void print_list(struct Host* head){
    while(head!=NULL){
        printf("Hospital:%d, Patients:%d\n",head->host_id,head->num_patient);
        head = head->next;
    }
}

void random_del(struct Host** head){
    srand(time(NULL));
    
    int rum1 = rand()%11;
    struct Host* tmp = *head;
    int i;
    for(i=0;i<rum1;i++){
        tmp = tmp->next;
    }

    tmp->num_patient--;
    sort(head);
}