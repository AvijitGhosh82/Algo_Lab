#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct range{
	int start;
	int end;
}range;

typedef struct RangeList{
	range r;
	struct RangeList *next;

}RangeList;

typedef struct LinkedList{
	int data;
	struct LinkedList *next;

}LinkedList;

typedef struct IntervalTree{
	int l;
	int u;
	LinkedList *list;
	struct IntervalTree *lchild;
	struct IntervalTree *rchild;
} IntervalTree;

int max(int a, int b)
{
	if(a>b) 
		return a;
	else
		return b;
}

void printList(LinkedList *head)
{
	if(head==NULL)
	{
		printf("...........\n");
		return;
	}
    LinkedList *temp = head;
    while(temp != NULL)
    {
        printf("%d,  ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void printRList(RangeList *head)
{
	if(head==NULL)
	{
		printf("...........\n");
		return;
	}
    RangeList *temp = head;
    while(temp != NULL)
    {
        printf("[%d, %d] ", temp->r.start, temp->r.end);
        temp = temp->next;
    }
    printf("\n");
}

int height(IntervalTree *t) {
    if (t == NULL)
        return 0;
    else
        return max(height(t->lchild), height(t->rchild)) + 1;
}

void PRETTY_PRINT(IntervalTree* root)
{
    if (root == NULL)
        return;
    PRETTY_PRINT(root->lchild);
    int h=height(root);
    int i;
    for(i=1;i<h;i++)
    	printf("\t");
    printf("[%d, %d] ", root->l, root->u);
    if(root->list)
    	printList(root->list);
    else 
    	printf("\n");
    PRETTY_PRINT(root->rchild);
}


void sortedInsert(LinkedList** head_ref, int val)
{
    LinkedList *current;
    LinkedList *new_node=(LinkedList *)malloc(sizeof(LinkedList));
    new_node->data=val;
    new_node->next=NULL;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void sortedRange(RangeList** head_ref, range v)
{
    RangeList *current;
    RangeList *new_node=(RangeList *)malloc(sizeof(RangeList));
    new_node->r=v;
    new_node->next=NULL;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->r.start >= new_node->r.start)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->r.start < new_node->r.start)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

IntervalTree* allot(int L[], int U[], int fl, int ul)
{
	if(fl>ul)
	{	
		return NULL;
	}
	else
	{
		int mid=(fl+ul)/2;
		int s=(ul-fl)+1;
		if(s%2==0)
			mid=mid+1;
		IntervalTree *root;
  		root=(IntervalTree *)malloc(sizeof(IntervalTree));
  		root->l=L[mid];
  		root->u=U[mid];
  		root->list=NULL;
  		// root->list=(LinkedList *)malloc(sizeof(LinkedList));
  		// root->list->next=NULL;
  		root->lchild=NULL;
  		root->rchild=NULL;
  		root->lchild=allot(L,U,fl,mid-1);
  		root->rchild=allot(L,U,mid+1,ul);

  		return root;

  	}


}

// IntervalTree*
IntervalTree* CREATE_INTERVAL_TREE(int l,int u,int n)
{
	int size=u-l+1;
	// printf("Size %d\n",size);
	int total_length = u - l + 1;
	int subrange_length = total_length/n;
	// printf("Length %d\n", subrange_length);
	int lasth;

  	int low[n], high[n];

	int current_start = l;
	int c=0;
	int i;
	for (i = 1; i < n; ++i) {
		lasth=current_start + subrange_length-1;
		if(lasth>u)
  		{
  			lasth=current_start;
  			break;
  		}

 		// printf("[%d, %d]\n", current_start , lasth);
 		low[c]=current_start;
 		high[c]=lasth;
 		c++;
  		current_start += (subrange_length);
  	}

	if(lasth<u)
	{
		// printf("[%d, %d]\n", current_start, u);
		low[c]=current_start;
		high[c]=u;
	}
	IntervalTree *root=allot(low,high,0,n-1);
	return root;

}



void INSERT(IntervalTree *iT, int val)
{
	if(iT==NULL)
	{
	// {	printf("Out of range\n");
		return;
	}
	if(iT->l<=val && iT->u>=val)
	{
		sortedInsert(&(iT->list),val);
		return;
	}
	else if(val<iT->l)
		INSERT(iT->lchild, val);
	else if(val>iT->u)
		INSERT(iT->rchild, val);

}

void getnums(LinkedList *head, LinkedList **N)
{
	// printf("In getnums\n");
	if(head==NULL)
	{
		
		return;
	}
    LinkedList *temp = head;
    while(temp != NULL)
    {
        sortedInsert(N,temp->data);
        temp = temp->next;
    }
}

void traverse(IntervalTree* root, LinkedList **N, RangeList **R)
{
		// printf("In traverse\n");

    if (root == NULL)
        return;
    traverse(root->lchild,N,R);
    // printf("[%d, %d] ", root->l, root->u);
    range r;
    r.start=root->l;
    r.end=root->u;
    sortedRange(R,r);
    // printf("[%d, %d] ", r.start, r.end);

    getnums(root->list,N);
    traverse(root->rchild,N,R);
}
void MERGE(IntervalTree **roo, int l, int u)
{
	//OVERLAP
	IntervalTree *root=*roo;
	if(root==NULL)
		return;
	if((root->lchild==NULL || root->rchild==NULL) && (root->l > l && root->u <u))
		return;
	if((root->lchild->l <= l && root->rchild->u>=u)||(root->l <= l && root->u >=u))
	{
		LinkedList *N=NULL;
		RangeList *R=NULL;
		traverse(root,&N,&R);
		// printf("\n");

		// printList(N);
		// printRList(R);
		range nr;
		nr.start=l;
		nr.end=u;
		sortedRange(&R,nr);

		// printRList(R);


		RangeList *res=(RangeList *)malloc(sizeof(RangeList));
		res->next=NULL;
		res->r=R->r;

		RangeList *ptr=R,*ptr1=ptr->next;
		range cur=R->r,pre;
		while(ptr1!=NULL)
		{
			cur=ptr1->r;
			pre=ptr->r;
			
			if (cur.start <= pre.end)
                {
                	res->r.end = max(pre.end, cur.end);
                }
            else
            	{
            		RangeList *np=(RangeList *)malloc(sizeof(RangeList));
            		np->r=cur;
            		np->next=NULL;
                	res->next=np;
                }
			ptr=ptr->next;
			ptr1=ptr->next;
		}

		// printRList(res);

		//Now I have a merged range. Time to recreate tree.
		// IntervalTree **Noderef=&root;

		int size=sizeof(res)/sizeof(RangeList);
		// printf("Size: %d\n", size);
		int newL[size];
		int newU[size];
		int c=0;

		while(res!=NULL)
		{
			newL[c]=res->r.start;
			newU[c]=res->r.end;
			c++;
			res=res->next;
		}

		IntervalTree *mergedroot=allot(newL,newU,0,size-1);

		while(N!=NULL)
		{
			INSERT(mergedroot,N->data);
			// printf("%d\n", N->data);
			N=N->next;
		}

		*roo=mergedroot;

		return;
	}
	else if(l>root->u)
		MERGE(&(root->rchild),l,u);
	else if (u<root->l)
		MERGE(&(root->lchild),l,u);

}

int main()
{
	srand(time(NULL));
	printf("Enter l:\n");
	int l,u,n,i;
	scanf("%d",&l);
	printf("Enter u:\n");
	scanf("%d",&u);
	printf("Enter n:\n");
	scanf("%d",&n);
	IntervalTree *Tree=CREATE_INTERVAL_TREE(l,u,n);
	//blank tree
	PRETTY_PRINT(Tree);
	printf("\n\n");

	int range=u-l+1;
	int flag[range];
	for(i=0;i<range;i++)
		flag[i]=0;
	printf("Enter number of insertions\n");
	int ins,j,val;
	scanf("%d",&ins);
	for(j=0;j<ins;j++)
	{
		while(1)
	    {
	    	val = (rand() % (u+1-l))+l;
	    	if (flag[val-l]==0)
	    	{
	    		flag[val-l]=1;
	    		break;
	    	}

	    }
	    INSERT(Tree,val);
	}
	//after insertions
	PRETTY_PRINT(Tree);
	printf("\n\n");

	printf("Enter new U and L\n");	
	int t,L,U;
	L=U=0;
	scanf("%d", &t);
	for(i=0;i<t;i++)
	{
		L=(rand() % (u+1-l))+l;
		while(L>U)
			U=(rand() % (u+1-l))+l;

		MERGE(&Tree,L,U);
		PRETTY_PRINT(Tree);
		printf("\n\n");


	}
	
	// LinkedList *Li=NULL,*Ui=NULL,*N=NULL;
	// 	traverse(Tree,&N,&Li,&Ui);
	// 	printf("\n");
	// 	printList(Li);
	// 	printList(Ui);
	// 	printList(N);


}