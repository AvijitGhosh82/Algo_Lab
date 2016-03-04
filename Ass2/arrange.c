#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void tile(int **A, int size,int begx, int begy,int c)
{
    //c=c%4;
    int a[]={1,2,3,4,5,6,7,8,9};
    c=a[c%9];
    int i,j;
    if(size==2)
    {
        for(i=begx;i<begx+size;i++)
        {
            for(j=begy;j<begy+size;j++)
            {
                if(A[i][j]==-1)
                    A[i][j]=c;
            }
        }
        return;

    }
    else{
        int dx,dy;
        for(i=begx;i<begx+size;i++)
        {
            for(j=begy;j<begy+size;j++)
            {
                if(A[i][j]!=-1)
                {
                    dx=i;
                    dy=j;
                    break;
                }
            }
        }
        if(dx<(begx+size/2) && dy<(begy+size/2)) //top left, no 2 pos 
                {
            A[(begx+size/2)][(begy+size/2)]=c; //-1,-1 +1-1
            A[(begx+size/2)-1][(begy+size/2)]=c;// -1+1 +1+1
            A[(begx+size/2)][(begy+size/2)-1]=c;
        }
        else if(dx>=(begx+size/2) && dy<(begy+size/2)) //top right
        {
            A[(begx+size/2)][(begy+size/2)]=c;
            A[(begx+size/2)-1][(begy+size/2)]=c;
            A[(begx+size/2)-1][(begy+size/2)-1]=c;
        }
        else if(dx<(begx+size/2) && dy>=(begy+size/2)) //bottom left
        {
            A[(begx+size/2)-1][(begy+size/2)-1]=c;
            A[(begx+size/2)][(begy+size/2)-1]=c;
            A[(begx+size/2)][(begy+size/2)]=c;
        }
        else if(dx>=(begx+size/2) && dy>=(begy+size/2)) //bottom right
        {
            A[(begx+size/2)-1][(begy+size/2)-1]=c;
            A[(begx+size/2)][(begy+size/2)-1]=c;
            A[(begx+size/2)-1][(begy+size/2)]=c;
        }
        tile(A,size/2,begx,begy,c+1);
        tile(A,size/2,begx+size/2,begy,c+2);
        tile(A,size/2,begx,begy+size/2,c+3);
        tile(A,size/2,begx+size/2,begy+size/2,c+4);

    }
}


int main()
{
    int size,i,j;
    printf("Enter size of array. It should be a power of 2: \n");
    scanf("%d",&size);
    int **A;

      /* obtain values for rows & cols */

      /* allocate the array */
      A = malloc(size * sizeof(int *));
      for (i=0; i<size; i++)
      {
        A[i] = malloc(size * sizeof(int));
      }
      for (i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            A[i][j]=-1; 
        }
    }
    srand(time(NULL));
    int r1 = rand() % size ;
    int r2=rand()%size;
    A[r1][r2]=0;
    tile(A,size,0,0,0);
    for (i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("%d  ",A[i][j]);
        }
        printf("\n");
    }
    return 0;
}