#include <stdio.h>
#include <math.h>


typedef struct build{
	int l;
	int h;
	int r;
} build;

typedef struct skyline{
	int x;
	int ht;
} skyline;

int max(int a, int b)
{
	if (a>b)
		return a;
	else
		return b;
}

int append(skyline *arr, int n, skyline st)
    {
        // Check for redundant strip, a strip is
        // redundant if it has same height or left as previous
        if (n>0 && arr[n-1].ht == st.ht)
            return 0;
        if (n>0 && arr[n-1].x == st.x)
        {
            arr[n-1].ht = max(arr[n-1].ht, st.ht);
            return 0;
        }
 
        arr[n] = st;
        printf("Appended (%d %d)\n", st.x, st.ht);
        n++;
        return 1;
    }

skyline * merge(skyline *AL, skyline *AR, int size)
{
	int nsize=2*size;
	skyline res[nsize];
 
    int h1 = 0, h2 = 0;
 
    int i = 0, j = 0, k=0;
    while (i < size && j < size)
    {
        // Compare x coordinates of left sides of two
        // skylines and put the smaller one in result
        if (AL[i].x<AR[j].x)
        {
            int x1 = AL[i].x;
            h1 = AL[i].ht;
            // Choose height as max of two heights
            int maxh = max(h1, h2);
            skyline st;
            st.x=x1;
            st.ht=maxh;
            if(append(res,k,st)==1) k++;
 
            // res[k].x=x1;
            // res[k].ht=maxh;
            i++;//k++;
        }
        else
        {
            int x2 = AR[j].x;
            h2 = AR[j].ht;
            int maxh = max(h1, h2);
            skyline st;
            st.x=x2;
            st.ht=maxh;
            if(append(res,k,st)==1) k++;
            // res[k].x=x2;
            // res[k].ht=maxh;
            j++;//k++;
        }
    }
 
    // If there are strips left in this skyline or other
    // skyline
    while (i < size)
    {
        int x1 = AL[i].x;
            h1 = AL[i].ht;
            skyline st;
            st.x=x1;
            st.ht=h1;
            if(append(res,k,st)==1) k++;
        i++;//k++;
    }
    while (j < size)
    {
        int x2 = AR[j].x;
            h2 = AR[j].ht;
            skyline st;
            st.x=x2;
            st.ht=h2;
            if(append(res,k,st)==1) k++;
        j++;//k++;
    }
    return res;
}


skyline * getsky(build* B, int size)
{
	
	if(size==1)
	{
		skyline res[2];
		res[0].x=B[0].l;
		res[0].ht=B[0].h;
		res[1].x=B[0].r;
		res[1].ht=0;
		
		printf("Base Case (%d %d)\n", res[0].x, res[0].ht);
		printf("Base Case (%d %d)\n", res[1].x, res[1].ht);


		return res;
	}
		int mid=size/2;

		skyline *sl=getsky(B, mid); //left skyline

		int i;
		for(i=0;i<mid;i++)
			printf("Left sky (%d %d)\n",sl[i].x, sl[i].ht);

		skyline *sr=getsky(B+mid, size-mid); //right skyline

		for(i=0;i<mid;i++)
			printf("Right sky (%d %d)\n",sr[i].x, sr[i].ht);
		skyline *res =merge(sl,sr,size);
		return res;
	
}



int main()
{
    build arr[] = {{1, 11, 5}, {2, 6, 7}
    					, {3, 13, 9},
                      {12, 7, 16}};
         // {14, 3, 25}, {19, 18, 22},
         //              {23, 13, 29}, {24, 4, 28}};
    int n = 4;
    int i;
 
    // Find skyline for given buildings and print the skyline
    skyline *ptr = getsky(arr, n);
    printf(" Skyline for given buildings is \n");
    n*=2;
    for (i=0;i<n;i++)
    {
    	printf("(%d, %d)\n", ptr[i].x, ptr[i].ht);
    }
    return 0;
}