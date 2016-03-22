#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

typedef struct fheap_node {
    struct fheap_node *parent;
    struct fheap_node *left, *right;
    struct fheap_node *child;
    int rank;
    int marked;
    long key;
    int id;
} fheap_node;


typedef struct fheap {
    fheap_node **trees;
    fheap_node **nodes;
    int max_nodes, max_trees, n, order;
    long key_comps;
    // fheap_node *minele;
} fheap;

typedef struct block {
    int *arr;
}block;

int n;

int min(int a, int b)
{
    if(a<b)
        return a;
    else
        return b;
}


fheap *makeHeap(int max_nodes);
void freeHeap(fheap *h);
void insertHeap(fheap *h, int id, long k);
long int extractMinHeap(fheap *h);
void decreaseKeyHeap(fheap *h, int id, long newval);
void printNodes(fheap_node *ptr, int level);
void meldHeap(fheap *h, fheap_node *tree_list);
void unionHeap_list(fheap *res, fheap *h);
fheap* unionHeap(fheap *one, fheap *two);


fheap *makeHeap(int max_nodes)
{
    fheap *h;
    h = malloc(sizeof(fheap));
 
    h->max_trees = 1.0 + 1.44 * log(max_nodes)/log(2.0);
    h->max_nodes = max_nodes;
    h->trees = calloc(h->max_trees, sizeof(fheap_node *));
    h->nodes = calloc(max_nodes, sizeof(fheap_node *));
    h->n = 0;

    h->order = 0;
    h->key_comps = 0;

    return h; 
}

void freeHeap(fheap *h)
{
    int i;

    for(i = 0; i < h->max_nodes; i++) {
        free(h->nodes[i]);
    }

    free(h->nodes);
    free(h->trees);
    free(h);
}

void insertHeap(fheap *h, int id, long k)
{
    fheap_node *new;

    new = malloc(sizeof(fheap_node));
    new->child = NULL;
    new->left = new->right = new;
    new->rank = 0;
    new->id = id;
    new->key = k;

    h->nodes[id] = new;

    meldHeap(h, new);

    h->n++;
}


long int extractMinHeap(fheap *h)
{
    fheap_node *min_node, *child, *next;
    long k, k2;
    int r, d, id;

    d = h->order;
    r = -1;
    while(d) {
        d = d/2;
        r++;
    };

    min_node = h->trees[r];
    k = min_node->key;
    while(r > 0) {
        r--;
        next = h->trees[r];
        if(next) {
            if((k2 = next->key) < k) {
                k = k2;
                min_node = next;
            }
            h->key_comps++;
        }
    }

    r = min_node->rank;
    h->trees[r] = NULL;
    h->order -= (1 * powf(2,r));

    child = min_node->child;
    if(child) 
        meldHeap(h, child);

    id = min_node->id;

    h->nodes[id] = NULL;
    free(min_node);
    h->n--;

    return k;
}


void decreaseKeyHeap(fheap *h, int id, long newval)
{
    fheap_node *cut_node, *parent, *new_roots, *r, *l;
    int prev_rank;

    cut_node = h->nodes[id];

    if(cut_node==NULL)
        return;
    parent = cut_node->parent;
    cut_node->key = newval;

    if(!parent) {
        return;
    }

    l = cut_node->left;
    r = cut_node->right;
    l->right = r;
    r->left = l;
    cut_node->left = cut_node->right = cut_node;

    new_roots = cut_node;

    while(parent && parent->marked) {


        parent->rank--;
        if(parent->rank) {
            if(parent->child == cut_node) parent->child = r;
        }
        else {
            parent->child = NULL;
        }

        cut_node = parent;
        parent = cut_node->parent;


        l = cut_node->left;
        r = cut_node->right;
        l->right = r;
        r->left = l;

        l = new_roots->left;
        new_roots->left = l->right = cut_node;
        cut_node->left = l;
        cut_node->right = new_roots;
        new_roots = cut_node;
    }

    if(!parent) {
        prev_rank = cut_node->rank + 1;
        h->trees[prev_rank] = NULL;
        h->order -= (pow(2,prev_rank));
    }
    else {

        parent->rank--;
        if(parent->rank) {
            if(parent->child == cut_node) parent->child = r;
        }
        else {
            parent->child = NULL;
        }

        parent->marked = 1;
    }

    meldHeap(h, new_roots);
}


void meldNodes(fheap *res, fheap_node *ptr, int level)
{
     fheap_node *child_ptr, *partner;
     int i, ch_count;

     for(i = 0; i < level; i++) printf("   ");

     printf("%ld\n", ptr->key);
 	 insertHeap(res, ptr->id, ptr->key);

     
     if((child_ptr = ptr->child)) {
     child_ptr = ptr->child->right;
     
         ch_count = 0;

         do {
             meldNodes(res, child_ptr, level+1);
             child_ptr = child_ptr->right;
         ch_count++;
         } while(child_ptr != ptr->child->right);
     }


}



void unionHeap_list(fheap *res, fheap *h)
{
    int i;
    fheap_node *ptr;

    for(i=0; i<h->max_trees; i++) {
        if((ptr = h->trees[i])) {
            meldNodes(res,ptr,0);
        }
    }
}


fheap* unionHeap(fheap *one, fheap *two) {

        if (one == NULL && two == NULL) { 
            return NULL;
        }
        else if (one != NULL && two == NULL) { 
            return one;
        }
        else if (one == NULL && two != NULL) {
            return two;
        }
        else { 

            fheap *res=makeHeap(one->max_nodes+two->max_nodes);
            unionHeap_list(res,one);
            unionHeap_list(res,two);
            res->n=one->n+two->n;
            return res;
            
        }
    }


void meldHeap(fheap *h, fheap_node *tree_list)
{
    fheap_node *first, *next, *node_ptr, *new_root, *temp, *temp2, *lc, *rc;
    int r;

    node_ptr = first = tree_list;

    do {

        next = node_ptr->right;
        node_ptr->right = node_ptr->left = node_ptr;
        node_ptr->parent = NULL;


        new_root = node_ptr;
        r = node_ptr->rank;

        do {


            if((temp = h->trees[r])) {


                h->trees[r] = NULL;
                h->order -= (pow(2,r));

            if(temp->key < new_root->key) {
                    temp2 = new_root;
                    new_root = temp;
                    temp = temp2;
                }
                h->key_comps++;

            if(r++ > 0) {
                    rc = new_root->child;
                    lc = rc->left;
                    temp->left = lc;
                    temp->right = rc;
                    lc->right = rc->left = temp;
                }
                new_root->child = temp;
                new_root->rank = r;
                temp->parent = new_root;
                temp->marked = 0;
            }

            else {

                h->trees[r] = new_root;
                h->order += (pow(2,r));
                new_root->marked = 1;
        }

        } while(temp);

        node_ptr = next;

    } while(node_ptr != first);
}


void printNodes(fheap_node *ptr, int level)
{
     fheap_node *child_ptr, *partner;
     int i, ch_count;

     for(i = 0; i < level; i++) printf("   ");

     // printf("%d(%ld)[%d]\n", ptr->id, ptr->key, ptr->rank);
     printf("%ld\n", ptr->key);

     
     if((child_ptr = ptr->child)) {
     child_ptr = ptr->child->right;
     
         ch_count = 0;

         do {
             printNodes(child_ptr, level+1);
             child_ptr = child_ptr->right;
         ch_count++;
         } while(child_ptr != ptr->child->right);
     }


}


void printHeap(fheap *h)
{
    int i;
    fheap_node *ptr;

    printf("\n");
    printf("Number of elements:  %d\n", h->n);
    printf("Trees present in linked list: ");
    for(i=0; i<h->max_trees; i++) {
        // printf(" %d", h->trees[i] ? 1 : 0 );
        if(h->trees[i])
            printf("B%d ",i );
    }
    printf("\n\n");
    for(i=0; i<h->max_trees; i++) {
        if((ptr = h->trees[i])) {
            printf("Tree Order %d\n\n", i);
            printNodes(ptr, 0);
        printf("\n");
        }
    }
}


void quicksort(int arr[], int fst, int last)
{
 int i,j,p;
 int tmp;
 if(fst<last)
 {
   p=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i]<=arr[p] && i<last)
        i++;
     while(arr[j]>arr[p])
        j--;
     if(i<j)
     {
        tmp=arr[i];
        arr[i]=arr[j];
        arr[j]=tmp; 
     }
   }
   tmp=arr[p];
   arr[p]=arr[j];
   arr[j]=tmp;
   quicksort(arr,fst,j-1);
   quicksort(arr,j+1,last);
 }
}


void datacreate(block dat[][n], int k, int m, int n)
{
    srand(time(NULL));
    int hash[10000]={0};
    int i,j,l,d,s,t;
    s=k*m;
    int temp[s];

    for(i=0;i<k;i++)
    {
        
        for(t=0;t<s;t++)
        {
            while(1)
                {
                    d=rand()%10000;
                    if(hash[d]==0)
                     {   
                        hash[d]=1;
                        temp[t]=d;
                        break;
                    }
                }
        }

        quicksort(temp,0,s-1);

        t=0;

        for(j=0;j<n;j++)
        {
            dat[i][j].arr=(int*)malloc(m*sizeof(int));
            for(l=0;l<m;l++)
            {   
                dat[i][j].arr[l]=temp[t];
                t++;
            }
        }
    }

    //SORT



    FILE *f=fopen("data.txt", "w");

    for(i=0;i<k;i++)
    {
        for(j=0;j<n;j++)
        {
            for(l=0;l<m;l++)
            {   
                fprintf(f, "%4d ", dat[i][j].arr[l] );
                        
            }
            fprintf(f, "  |  ");
                
        }
        fprintf(f, "\n");
    }

    fclose(f);

}

void ascendingprint(fheap *H, int m)
{
    int c=H->n;
    int i;

    FILE *f=fopen("out.txt", "w");

    int x=0;


    for(i=0;i<c;i++)
    {
        if(x==m)
            {
                fprintf(f,"  |  ");
                x=0;
            }


        fprintf(f,"%ld ", extractMinHeap(H));
        x++;

    }
    
    fprintf(f, "\n");
    fclose(f);

}


int main()
{

    // fheap *H=makeHeap(1000);
    // insertHeap(H,100,100);
    // insertHeap(H,55,55);
    // insertHeap(H,98,98);
    // insertHeap(H,9,9);
    // insertHeap(H,30,30);

    // printHeap(H);

    // fheap *X=makeHeap(1000);
    // insertHeap(X,10,10);
    // insertHeap(X,5,5);
    // insertHeap(X,8,8);
    // insertHeap(X,90,90);
    // insertHeap(X,32,32);

    // printHeap(X);

    // fheap *R=unionHeap(H,X);
    // R->n=H->n+X->n;

    // printHeap(R);

    // printf("\n");

    // int c=R->n;
    // int i;

    // for(i=0;i<c;i++)
    // {
    //     printf("%ld ", extractMinHeap(R));
    // }
    
    // printf("\n");

    int k,m;

    printf("Enter k, the number of lists:\n");
    scanf("%d", &k);

    printf("Enter n, the number of blocks per list:\n");
    scanf("%d", &n);

    printf("Enter m, the number of integers per block:\n");
    scanf("%d", &m);

    block dat[k][n];


    datacreate(dat,k,m,n);
    int i,j,l,d;

    int min=100001, max=-1;

    fheap *H=NULL; //parent heap

    int counter=0;

    printf("Initial Cost 0\n");

    for(i=0;i<k;i++)
    {
        for(j=0;j<n;j++)
        {
            
            fheap *C=makeHeap(10000);
            if(min>dat[i][j].arr[0])
                min=dat[i][j].arr[0];
            max=dat[i][j].arr[m-1];


            for(l=0;l<m;l++)
            {   
                d=dat[i][j].arr[l]; 
                insertHeap(C,d,d);
                long com;
            }

            H=unionHeap(H,C);
            printf("Cost after %d inserts: %ld\n", m,H->key_comps);
            decreaseKeyHeap(H,max,min-1);
            printf("Cost after decreaseKeyHeap: %ld\n", H->key_comps);

            min=min-1;
                
        }
    }

    printHeap(H);

    ascendingprint(H, m);




    return 0;
}