#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fancyprint.h"

#define MAX 100
 
struct queue
{
    int queue_array[MAX];
    int front;
    int rear;
};
typedef struct queue queue;
queue Q;
 
// void enqueue(void);
// int  pop(void);
// void display(void);


void enqueue(int add_item)
{
    // int add_item;
    if (Q.rear == MAX - 1)
    // printf("Queue Overflow \n");
    	return;
    else
    {
        if (Q.front == - 1)
        /*If queue is initially empty */
        Q.front = 0;
        // printf("Inset the element in queue : ");
        // scanf("%d", &add_item);
    	int i;
    	for(i=Q.front;i<=Q.rear;i++)
    	{
    		if(Q.queue_array[i]==add_item)
    			return;
    	}
        Q.rear += 1;
        Q.queue_array[Q.rear] = add_item;
    }
} /*End of insert()*/
 
void dequeue()
{
    if (Q.front == - 1 || Q.front > Q.rear)
    {
        // printf("Queue Underflow \n");
        return ;
    }
    else
    {
        // printf("Element deleted from queue is : %d\n", Q.queue_array[Q.front]);
        Q.front = Q.front + 1;
    }
} /*End of delete() */
void display()
{
    int i;
    if (Q.front == - 1)
        // printf("Queue is empty \n");
        return;
    else
    {
        // printf("Queue is : \n");
        for (i = Q.front+1; i <= Q.rear; i++)
            printf("%d ", Q.queue_array[i]);
        printf("\n");
    }
}
void prune()
{
	int i;int sum;
	while(1)
	{
		sum=0;
		for(i=Q.front+1;i<=Q.rear;i++)
		{
			sum+=Q.queue_array[i];
		}
		if(sum<(sum+Q.queue_array[Q.front]))
			dequeue();
		else
			break;
	}
}

// typedef struct binTree
// {
// 	int data;
// 	struct binTree *lchild;
// 	struct binTree *rchild;
// 	struct binTree *parent;

// } binTree;

int max (int a, int b)
{
	if(a>=b)
		return a;
	else 
		return b;
	
}

int flag[201]={0};

void fill(binTree *bT, int count)//,int val)
{
	int val;
	int max=100, min=-100;
	while(1)
    {
    	val = (rand() % (max+1-min))+min;
    	if (flag[val+100]==0)
    	{
    		flag[val+100]=1;
    		break;
    	}

    }


	if (count==0)
	{	
		// printf("NULL\n");
		return;
	}

	bT->data=val;
	count--;

	// printf("%d\n", val);
	max=60; min=40;
	double weight= (rand() % (max+1-min))+min;
	weight/=100;
	// printf("Weight %lf\n", weight);
	// double weight=0.5;
	int lcount=weight*count;
	int rcount=count-lcount;

	// printf("lcount %d\n", lcount);
	// printf("rcount %d\n", rcount);

	if(lcount>0)
		{	
			bT->lchild=(binTree *)malloc(sizeof(binTree));
			bT->lchild->lchild=NULL;
			bT->lchild->parent=bT;
			bT->lchild->rchild=NULL;
		}
		else
			bT->lchild=NULL;

	if(rcount>0)
	{	
			bT->rchild=(binTree *)malloc(sizeof(binTree));
			bT->rchild->lchild=NULL;
			bT->rchild->parent=bT;
			bT->rchild->rchild=NULL;
	}
	else
		bT->lchild=NULL;


	// printf("Left of %d\n", val);
	fill(bT->lchild,lcount);//,val+1);
	// printf("Right of %d\n", val);
	fill(bT->rchild,rcount);//,val+2);

}

void preorder(binTree *bT)
{
	if (bT==NULL)
		return;
	else
	{	
		printf("%d ", bT->data);
		preorder(bT->lchild);
		preorder(bT->rchild);
	}

}

void inorder(binTree *bT)
{
	if (bT==NULL)
		return;
	else
	{	
		inorder(bT->lchild);
		printf("%d ", bT->data);
		inorder(bT->rchild);
	}

}


void postorder(binTree *bT)
{
	if (bT==NULL)
		return;
	else
	{	
		postorder(bT->lchild);
		postorder(bT->rchild);
		printf("%d ", bT->data);
	}

}

void max_root_leaf(binTree *bT, int sum, int *maxsum, binTree **maxLeaf)
{
	if(bT==NULL)
		return;
	sum+=bT->data;

    if (bT->lchild == NULL && bT->rchild == NULL)
    {
        if (sum > *maxsum)
        {
            *maxsum=sum;
            *maxLeaf=bT;
        }
    }


	max_root_leaf(bT->lchild,sum,maxsum,maxLeaf);
	max_root_leaf(bT->rchild,sum,maxsum,maxLeaf);

}

void max_path(binTree *node, int *maxsum)
{
	
}

int printPath (binTree *root, binTree *leaf)
{
    if (root == NULL)
        return 0;
 
    if (root == leaf || printPath(root->lchild, leaf) || printPath(root->rchild, leaf) )
    {
        printf("%d ", root->data);
        return 1;
    }
 
    return 0;
}

int findMax(binTree* root, int *res)
{
    //Base Case
    if (root == NULL)
        return 0;
 
    // l and r store maximum path sum going through left and
    // right child of root respectively
    int lsum = findMax(root->lchild,res);
    int rsum = findMax(root->rchild,res);
 
    // Max path for parent call of root. This path must
    // include at-most one child of root

    int max_child=max(lsum, rsum);


    int max_single = max( max_child + root->data, root->data);

    // Max Top represents the sum when the binTree under
    // consideration is the root of the maxsum path and no
    // ancestors of root are there in max sum path
    int max_top = max(max_single , lsum + rsum + root->data);
 
    *res = max(*res, max_top); // Store the Maximum Result.
    max_top=*res;

    if(max_top==(lsum + rsum + root->data))
    	{
    		// printf("A ");
    		if(root->lchild!=NULL)
    			{
    				// printf("%d ", root->lchild->data);
    				enqueue(root->lchild->data);
    				//prune();
    			}

    		if(root!=NULL)
    			{
    				// printf("%d ", root->data);
    				enqueue(root->data);
    				//prune();
    			}
    		if(root->rchild!=NULL)
    			{
    				// printf("%d ", root->rchild->data);
    				enqueue(root->rchild->data);
    				//prune();
    			}
    		prune();

    	}
    else if(max_top==root->data)
    	{
    		// printf("%d ", root->data );
    		enqueue(root->data);
    		prune();
    	}
    else if(max_top==(root->data+lsum))
    	{
    		if(root->lchild==NULL)
    			{
    				// printf(" B1 %d ", root->data );
    				enqueue(root->data);
    				prune();
    			}
    		else
    			{
    				// printf(" B2 %d %d", root->lchild->data, root->data );
    				enqueue(root->data);
    				enqueue(root->lchild->data);
    				prune();
    			}
    	}

    else if(max_top==(root->data+rsum))
    	{
    		if(root->rchild==NULL)
    			{
    				// printf(" C1 %d ", root->data );
    				enqueue(root->data);
    				prune();
    			}
    		else
    			{
    				// printf(" C2 %d %d", root->rchild->data, root->data );
    				enqueue(root->data);
    				enqueue(root->rchild->data);
    				prune();
    			}
    	}
 
    return max_single;
}
 


int main()
{
	srand(time(NULL));
	binTree *root;
	root=(binTree *)malloc(sizeof(binTree));
	root->parent=NULL;
	printf("Enter size of tree:\n" );
	int n;
	scanf("%d", &n);
	fill(root,n);//,0);
	printf("Binary Tree Diagram: \n");
	print_ascii_tree(root);
	printf("\n\nPREORDER\n");
	preorder(root);
	printf("\n\n");
	printf("INORDER\n");
	inorder(root);
	printf("\n\n");
	printf("POSTORDER\n");
	postorder(root);
	printf("\n\n");
	binTree *maxLeaf;
	int maxsum=root->data;
	max_root_leaf(root,0,&maxsum,&maxLeaf);
	printf("Max root to leaf sum is: %d\n", maxsum);
	// printf("From %d ", root->data);
	// printf("To %d \n", maxLeaf->data);
	printPath(root,maxLeaf);
	printf("\n\n");

	int res = -1000000;
    findMax(root, &res);
	printf("\n\nMax sum is: %d\n", res);
	display();
	printf("\n\n");

	// printf("\n\nRemeber to delete extra print statements!!\n\n");




	return 0;

}