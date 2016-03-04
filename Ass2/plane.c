#include <stdio.h>
#include <math.h>
#include <float.h>

typedef struct point{
  double x;
  double y;
}point;

double min(double a, double b)
{
  if(a<b) return a;
  else return b;
}

double dist(point A, point B)
{
  return sqrt( powf( ( A.x-B.x ) , 2) + powf( (A.y-B.y) , 2 ) );
}


void qsortx(point arr[], int fst, int last)
{
 int i,j,p;
 point tmp;
 if(fst<last)
 {
   p=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i].x<=arr[p].x && i<last)
        i++;
     while(arr[j].x>arr[p].x)
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

void qsorty(point arr[], int fst, int last)
{
 int i,j,p;
 point tmp;
 if(fst<last)
 {
   p=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i].y<=arr[p].y && i<last)
        i++;
     while(arr[j].y>arr[p].y)
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
   qsorty(arr,fst,j-1);
   qsorty(arr,j+1,last);
 }
}

float zonemin(point zone[], int size, double d)
{
    double minim = d; 
    int i, j;
    printf("ZONE of size: %d\n",size);
    for(i=0;i<size;i++)
      {
    printf("(%.2lf, %.2lf)\n",zone[i].x, zone[i].y);
      }
    printf("\n");
 
    qsorty(zone,0,size-1);

    for (i = 0; i < size; i++)
      for (j = i+1; j < size && (zone[j].y - zone[i].y) < minim; j++)//this loop runs only 7 times at max
            if (dist(zone[i],zone[j]) < minim)
          {    minim = dist(zone[i], zone[j]);
           printf("Zone points (%.2lf, %.2lf) (%.2lf, %.2lf)=  %.3lf\n",zone[i].x, zone[i].y, zone[j].x,zone[j].y,minim);
          }
 
    return minim;
}


double closestpt(point P[], int n)
{
  int i,j;
  //base case
  if(n<=3){
    // double minim = dist(P[0],P[n-1]);
    double minim =DBL_MAX;
    for (i = 0; i < n; ++i)
      for (j = i+1; j < n; ++j)
    if (dist(P[i], P[j]) < minim)
      { minim = dist(P[i], P[j]);
        printf("NON ZONE POINT (%.2lf, %.2lf) (%.2lf, %.2lf)=  %.3lf\n",P[i].x, P[i].y, P[j].x,P[j].y,minim);
      }
    return minim;
  }
    
    int mid = n/2;
    point midPoint = P[mid];
 
    // Vertical line passing through the middle point

    double dl = closestpt(P, mid);
    double dr = closestpt(P + mid, n-mid);
    printf("DL = %.2lf\n",dl);
    printf("DR = %.2lf\n",dr);
    
    
    double d = min(dl, dr);
    printf("D = %.2lf\n",d);
 
    point zonearr[n]; //zone lying at distance d on both sides
    j = 0;
    for (i = 0; i < n; i++)
      {    if (abs(P[i].x - midPoint.x) < d)
            { zonearr[j] = P[i];
              j++;
            }
      }

    return min(d, zonemin(zonearr, j, d) );
}

int main()
{

    printf("Enter the number of points to be inserted: \n");
    int n,i;
    scanf("%d", &n);
    point P[n];
    printf("Enter points 1 by 1 in the format x <space> y:\n");
    for(i=0;i<n;i++)
    {
        scanf("%lf %lf", &P[i].x, &P[i].y);
    }
    qsortx(P,0,n-1);
    printf("Inserted points arranged by x axis:\n");
    for (i=0;i<n;i++)
      printf("(%.2lf %.2lf)\n", P[i].x,P[i].y);
    printf("The smallest distance is %f \n", closestpt(P, n));
    return 0;
}