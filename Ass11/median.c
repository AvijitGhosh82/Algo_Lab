#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int min(int a, int b)
{
    return (a<b)? a: b;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void fivesort(int arr[], int fst, int last)
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
   fivesort(arr,fst,j-1);
   fivesort(arr,j+1,last);
 }
}


int partition(int arr[], int l, int r, int x)
{
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);

    i = l;
    int j;
    for (j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}


int findMedian(int arr[], int n)
{
    fivesort(arr, 0, n-1);
    return arr[n/2];
}


int pivotmedianselect(int *A,int n,int m)
{
	int i,j,k,p,size;
	
	if(n<=5)	//base case
	{
		fivesort(A,0,n-1);
		return A[m-1];
	}

	size = (int)ceil((float)n/5.0);
	int B[1000],C[5];	

	for(i=0;i<size-1;i++)
	{
		for(j=5*i,k=0;j<5*i+5;j++,k++) 
				C[k] = A[j];

		fivesort(C,0,4);
		B[i] = C[2];
	}
	
	for(j=5*i,k=0;j<n;j++,k++) 
			C[k] = A[j];
	fivesort(C,0,k-1);
	B[i] = C[k/2];
	

	p = pivotmedianselect(B,size,(size+1)/2);
	i = partition(A,0,n-1,p);
	i++;

	if(m == i) 
		return p;
	else if(i>m) 
		return pivotmedianselect(A,i-1,m);
	else 
		return pivotmedianselect(A+i,n-i,m-i);
}


/*int pivotmedianselect(int arr[], int l, int r, int k)
{

    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1;

        int i, median[(n+4)/5];
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n)
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        int medOfMed;
        if (i == 1)
                medOfMed=median[0];
        else
                medOfMed=arr[pivotmedianselect(median, 0, i-1, i/2)];


        int pivot = partition(arr, l, r, medOfMed);

        if (pivot-l == k-1)
            return pivot;
        if (pivot-l > k-1)
            return pivotmedianselect(arr, l, pivot-1, k);

        return pivotmedianselect(arr, pivot+1, r, k-pivot+l-1);
    }

    return INT_MAX;
}*/

/*int kthSmallestTwo(int A[], int B[], int a1, int a2, int b1, int b2, int k1, int k2)
{

    int p1=pivotmedianselect(A,a1,a2,k1);
    int p2=pivotmedianselect(B,b1,b2,k2);


    if((a2-a1)==1 || (b2-b1)==1)
        return min(A[a2],B[b2]);

    if(p1>(sizeof(A)/sizeof(int)) || p2>(sizeof(B)/sizeof(int)))
    	return -1;

    if(A[p1]<B[p2])
    {
        return kthSmallestTwo(A, B, a1, p1-1, p2+1, b2, k1, k2-p2+1-b1);
    }
    else if (A[p1]>B[p2])
    {
        return kthSmallestTwo(A, B, p1+1 , a2, b1, p2-1, k1-p1+1-a1, k2);
    }
    // else
    //     return min(A[p1],B[p2]);
    return INT_MAX;

}*/

int kthSmallestTwo(int A[], int B[], int n ,int k)
{
	int prev,curr,flag=1,k1=1,ctr=1,i,k2=1,min,r;

	prev = pivotmedianselect(B,n,k2);
	
	while(ctr<=k)
	{
		if(flag) 
				curr = pivotmedianselect(A,n,k1);
		else 
				curr = pivotmedianselect(B,n,k2);

		ctr++;

		flag = (curr<prev)?(flag):(!flag);
		min = (curr>prev)?prev:curr;

		prev = (curr>prev)?curr:prev;

		if(flag==1) k1++;
		else k2++;

        if(ctr<=k)
		{
			if(k1 > n)
        		{ 	i=0;break;	}
        	if(k2 > n)
       			{	i=1;break;	}
        }
	
	}
	
	r = k-ctr;
	if(i==0)
    	min = pivotmedianselect(B,n,r+k2);
    if(i==1)
    	min = pivotmedianselect(A,n,r+k1);
    	
    return min;
    
    //printf("%dth element is = %d\n",k,min);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int k,n;
	if(argc==3)
	{
		k=atoi(argv[1]);
		n=atoi(argv[2]);


	int i,j;
	int A[n],B[n];

	for (i = 0; i < n; i++) {
    A[i] = rand()%1000;

    for (j = 0; j < i; j++) {
        if (A[i] == A[j]) {
            A[j] = rand()%1000;;
        	}
    	}
	}

	for (i = 0; i < n; i++) {
    B[i] = rand()%1000;

    for (j = 0; j < n; j++) {
        if (B[i] == A[j]) {
            B[j] = rand()%1000;;
        	}
    	}

    for (j = 0; j < i; j++) {
        if (B[i] == B[j]) {
            B[j] = rand()%1000;;
        	}
    	}
	}

    //int A[] = {12, 37, 58, 8, 4, 19};
    //int B[] = {30, 5,100,110, 200,26};
    //printf("%d\n", kthSmallestTwo(A, B, 0, n-1, 0, n-1, k, k));
    
    for (i = 0; i < n; i++) 
    	printf("%d ",A[i]);
    	
    printf("\n");
    	
    for (i = 0; i < n; i++) 
    	printf("%d ",B[i]);
    
    printf("\n");
    
    printf("%d\n", kthSmallestTwo(A, B, n, k));
	}

	else
	{
		k=atoi(argv[1]);
		n=atoi(argv[2]);
		int i,j;
		int A[n],B[n];

		for(i=3;i<3+n;i++)
		{
			A[i]=atoi(argv[i]);
		}
		for(i=3+n;i<3+n+n;i++)
		{
			B[i]=atoi(argv[i]);
		}
		
		for (i = 0; i < n; i++) 
    	printf("%d ",A[i]);
    	
		printf("\n");
			
		for (i = 0; i < n; i++) 
			printf("%d ",B[i]);
		
		printf("\n");

		printf("%d\n", kthSmallestTwo(A, B, n, k));


	}
    return 0;
}
