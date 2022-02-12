#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_



//struct Hospital

struct Host{
    int host_id;
    int num_patient;
    struct Host*  next;
};

//struct Area


struct Area{

    int id;
    struct Host* head;
    struct Area* r;
    struct Area* l;
    int height;
};



//functions for area.
int getMax(int a,int b);
int getHeight( struct Area* root);
int getBalance( struct Area* root);
void ReBalanceInsertion(int id, struct Area** root);
void ReBalanceDeletion( struct Area** root);
void r_rotate( struct Area** root);
void l_rotate( struct Area** root);
int findMin( struct Area* root);
void insertNodeAVL(int area_id,struct Area** root);
void deleteNodeAVL(int host_id,  struct Area** root);
struct Area* searchNodeAVL(int host_id,  struct Area** root);
void PreOrder(struct Area* root );

//Functions for hospitals.

void insert_node(int host_id, int num_patients,struct Host** head);

void sort(struct Host** root);
struct Host* merge(struct Host* head1, struct Host* head2);
void split(struct Host* head,struct Host** part1, struct Host** part2);

int add_patient(struct Host** head);
int is_full(struct Host* head);
void print_list(struct Host* head);

void random_del(struct Host** head);











#endif