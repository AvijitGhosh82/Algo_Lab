#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct build{
	int left;
	float lheight;
	int right;
	float rheight;
} build;


/* Link list skyLine */
typedef struct skyLine
{
	int left;
	float height;
	struct skyLine* next;
} skyLine;

typedef struct point{
	float x;
	float y;
}point;

point inter(float  a1, float b1, float a2, float b2, float a3, float b3, float a4, float b4)
{
	float m1, c1, m2, c2;
    float x1, y1, x2, y2;
    float dx, dy;
    float intersection_X, intersection_Y;
 
    x1=a1;
    x2=a2;
    y1=b1;
    y2=b2;
 
    dx = x2 - x1;
    dy = y2 - y1;
 
    m1 = dy / dx;
    // y = mx + c
    // intercept c = y - mx
    c1 = y1 - m1 * x1; // which is same as y2 - slope * x2
 
    x1=a3;
    x2=a4;
    y1=b3;
    y2=b4;

 
    dx = x2 - x1;
    dy = y2 - y1;
 
    m2 = dy / dx;
    // y = mx + c
    // intercept c = y - mx
    c2 = y1 - m2 * x1; // which is same as y2 - slope * x2
         point p;

    
    if( (m1 - m2) == 0)
        // printf("No Intersection between the lines\n");
    {
    	p.x=-1;
    	p.y=-1;
    }
    else
    {
        p.x = (c2 - c1) / (m1 - m2);
        p.y = m1 * intersection_X + c1;
        // printf("Intersecting Point: = %.2f, %.2f\n", intersection_X, intersection_Y);

    }
    return p;
}

int max(float a, float b)
{
	if (a>b)
		return a;
	else
		return b;
}

void qsortx(build arr[], int fst, int last)
{
 int i,j,p;
 build tmp;
 if(fst<last)
 {
   p=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i].left<=arr[p].left && i<last)
        i++;
     while(arr[j].left>arr[p].left)
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
   qsortx(arr,fst,j-1);
   qsortx(arr,j+1,last);
 }
}

void printList(skyLine *sky)
{

	do
	{
		printf("(%d %.2f) ", sky->left,sky->height);
		sky = sky->next;
	}while(sky!=NULL);

	printf("\n\n");
}

void append(skyLine ** head_ref, float new_left, float new_ht)
{
	skyLine* new_skyLine =(skyLine*) malloc(sizeof(skyLine));
	if(new_skyLine==NULL)
		printf("Horror!\n");
	new_skyLine->next=NULL;


	/* put in the left */
	new_skyLine->left = new_left;
	new_skyLine->height = new_ht;

	if(*head_ref==NULL)
	{	
		*head_ref=new_skyLine;
		return;
	}

	// else if((*head_ref)->next==NULL)
	// {	
	// 	(*head_ref)->next=new_skyLine;
	// 	return;
	// }

	else{
	skyLine* ptr = *head_ref; 
	while(ptr->next !=NULL)
		ptr=ptr->next;

	 if (ptr->height == new_skyLine->height)
	            return;
	 if (ptr->left > new_skyLine->left)
	            return;
	        if (ptr->left == new_skyLine->left)
	        {
	            ptr->height = max(ptr->height, new_skyLine->height);

	            return;
	        }

	 
	 ptr->next=new_skyLine;
	 // new_skyLine->next=NULL;
	 return;
}



} 




skyLine *skymerge(skyLine *A, skyLine *B)
{
    // Create a resultant skyLine with capacity as sum of two
    // skyLines

    skyLine *res = (skyLine*) malloc(sizeof(skyLine));
    res->next=NULL;
 
    // To store current heights of two skyLines
    float h1 = 0, h2 = 0;
 
    while (A!=NULL && B!=NULL)
    {
        // Compare x coordinates of left sides of two
        // skyLines and put the smaller one in result
        if (A->left < B->left)
        {
            int x1 = A->left;
            h1 = A->height;
            int maxh = max(h1, h2); 
            append(&res, x1, maxh);
            A=A->next;
        }
        else
        {
			int x2 = B->left; 
			h2 = B->height;
            int maxh = max(h1, h2);
            append(&res, x2, maxh);
            B=B->next;
        }
    }
 
    // If there are strips left in this skyLine or other
    // skyLine
    while (A!=NULL)
    {
        append(&res, A->left, A->height);
        A=A->next;
    }
    while (B!=NULL)
    {
        append(&res,B->left, B->height);
        B=B->next;
    }
    return res;
}




skyLine *findskyLine(build arr[], int l, int r,int n)
{
    if (n==2)
    {
    	// if(l==n-1)
    	// {
    	// 	skyLine *res = (skyLine*) malloc(sizeof(skyLine));
     //    	res->next=NULL;
     //    	append(&res, arr[l].left, arr[l].lheight);
	    //     append(&res, arr[l].right, arr[l].rheight);
	    //     return res;
	    // }
    	// r=l+1;
        skyLine *res = (skyLine*) malloc(sizeof(skyLine));
        res->next=NULL;
        //case 1: Overlapping
        if(arr[l].right>arr[r].left)
        {
        	point p=inter(arr[l].left, arr[l].lheight, arr[l].right, arr[l].rheight, arr[r].left, arr[r].lheight, arr[r].right, arr[r].rheight);
        	if(p.y>0)
        	{
        		append(&res, arr[l].left, arr[l].lheight);
        		append(&res, p.x, p.y);
        		append(&res, arr[r].left, arr[r].lheight);
        		append(&res, arr[l].right, arr[l].rheight);
        		append(&res, arr[r].right, arr[r].rheight);
        		return res;

        	}

        }
        append(&res, arr[l].left, arr[l].lheight);
        append(&res, arr[r].left, arr[r].lheight);
        append(&res, arr[l].right, arr[l].rheight);
        append(&res, arr[r].right, arr[r].rheight);
        // printf("Base (%d %d)\n", arr[l].left, arr[l].lheight);
        // printf("Base (%d %d)\n", arr[l].right, arr[l].lheight);

        return res;
    }
 
    int mid = (l + r)/2;
 
    // Recur for left and right halves and merge the two results
    skyLine *sl = findskyLine(arr, l, mid,n/2)->next;
    // sl=sl->next;
    skyLine *sr = findskyLine(arr, mid+1, r,n/2)->next;
    // sr=sr->next;
    skyLine *res = skymerge(sl,sr);
    // res=res->next;

    printf("Leftlist\n");
    printList(sl);
    printf("Rightlist\n");
    printList(sr);
    printf("Merge\n");
    printList(res->next);
 
    // Return merged skyLine
    return res;
}


int main()
{
	srand(time(NULL));
	/* Start with the empty list */
	skyLine* res = NULL;
	// skyLine* a = NULL;
	// skyLine* b = NULL;
	// skyLine* c = NULL;

int i,n,l,r,h;

	printf("Enter leftmost x coordinate: ");
	scanf("%d",&l);
	printf("Enter rightmost x coordinate: ");
	scanf("%d",&r);
	printf("Enter maximum height: ");
	scanf("%d",&h);
	printf("Enter number of buildings in city: ");
	scanf("%d",&n);
	int range;
	build arr[n];
	for(i=0;i<n;i++)
	{
		range = 1 + r - l;
		arr[i].left=rand()%range +l;
		arr[i].lheight=rand()%h;
		arr[i].rheight=rand()%h;
		range = 1 + r - arr[i].left;
		arr[i].right=rand()%range +arr[i].left+1;
	}

	printf("Randomly generated buildings: \n");
	for(i=0;i<n;i++)
	{
		printf("(%d %.2f %d %.2f) ", arr[i].left, arr[i].lheight, arr[i].right, arr[i].rheight);
	}
	printf("\n\n");

	qsortx(arr,0,n-1);

	printf("Sorted according to x axis: \n");
	for(i=0;i<n;i++)
	{
		printf("(%d %.2f %d %.2f) ", arr[i].left, arr[i].lheight, arr[i].right, arr[i].rheight);
	}
	printf("\n\n");
	printf("Beginning skyline generation: \n\n");

	res=findskyLine(arr,0,n-1,n);

	printf("\nFinal Skyline: \n");
	printList(res->next);		 	 

	// getchar();
	return 0;
}