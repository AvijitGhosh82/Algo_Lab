#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
	if(a>b)
		return a;
	else return b;
}

int min(int a, int b)
{
	if(a<b)
		return a;
	else return b;
}

typedef struct List
{
	struct List *next;
	int val;

}List;

typedef struct Stack{
	int top;
	int N;
	int *arr;
}Stack;

typedef struct Node{
	int val;
	int visited;
	List *adj;
}Node;

int indexreturn(Node narr[], int n, int N)
{
	int i;
	for(i=0;i<N;i++)
	{
		if(narr[i].val==n)
			return i;
	}
}

void addedge(Node narr[], int n1, int n2, int N)
{
	int id=indexreturn(narr,n1,N);
	List **head=&(narr[id].adj);
	List* new_node = (List*)malloc(sizeof(List));
	new_node->val=n2;
	new_node->next=*head;

	*head=new_node;

}

void printadj(List *head)
{
	List *l=head;
	if(l==NULL)
		printf("NULL");
	while(l!=NULL)
		{
			printf("%d ",l->val);
			l=l->next;
		}
		printf("\n");
}


void push(Stack *S, int n)
{
	if((S->top)<(S->N))
		S->arr[++(S->top)]=n;
}

int pop(Stack *S)
{
	if((S->top)>=0)
		return S->arr[(S->top)--];
}

void printstack(Stack *S)
{
	int i;
	for(i=0;i<=(S->top);i++)
		printf("%d ", S->arr[i] );
	printf("\n");
}



void topoSortUtil(int v, Node narr[], int N, Stack *S)
{
    int id=indexreturn(narr,v,N);
    narr[id].visited=1;

    List *l=narr[id].adj;
	while(l!=NULL)
		{
			int id2=indexreturn(narr,l->val,N);
			if (narr[id2].visited==0)
            	topoSortUtil(narr[id2].val, narr, N, S);
			l=l->next;
		}

    push(S,v);
}

void topologicalSort(Node narr[], int N)
{
    Stack *S=NULL;

    S=(Stack *)malloc(sizeof(Stack));
	S->N=N;
	S->arr=(int *)malloc(N*sizeof(int));
	S->top=-1;

    int i;

    for (i = 0; i < N; i++)
      if (narr[i].visited == 0)
        topoSortUtil(narr[i].val, narr,N, S);
    printf("\nThe topological sort of the DAG is: \n");

    while (S->top != -1)
    {
        printf("%d ", pop(S));
    }
    printf("\n");
}

int main()
{
	printf("Enter number of inputs: \n");
	int num,i,j;
	scanf("%d", &num);
	int A[num];

	Node narr[num];

	for(i=0;i<num;i++)
	{
		scanf("%d", &A[i]);
		narr[i].val=A[i];
		narr[i].adj=NULL;
		narr[i].visited=0;

	}

	for(i=0;i<num;i++)
	{
		for(j=i+1;j<num;j++)
		{
			if(A[i]==A[j])
				{
					printf("Array not unique.\n");
					return;
				}
		}
	}

	printf("Array is unique. Creating DAG: \n");

	for(i=0;i<num;i++)
	{
		for(j=i+1;j<num;j++)
		{
			addedge(narr, max(A[i],A[j]), min(A[i],A[j]),num);
			printf("Edge %d --> %d\n",max(A[i],A[j]),min(A[i],A[j]) );
		}
	}

	printf("\n\n");

	for(i=0;i<num;i++)
	{
		printf("Nodes from %d \n", narr[i].val);
		printadj(narr[i].adj);
	}

	topologicalSort(narr,num);

}