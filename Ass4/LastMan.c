#include <stdio.h>
#include <math.h>


int eliminate(int n, int m)
{
	//int k=2; //Elimination of 2nd person
	int x = 2*m;
	//printf("\nFuncstart x= %d\n", x);
	while (x > n) {//Happens when it is odd
		//x = floor(( k*(x-n) - 1 )/ (k-1) );
		x = 2*(x-n)-1;
		//printf("\nInloop x= %d\n", x);
	}
	return x;
}

/*
Why this works:
Consider there are n people initially. To remove one person alternatively we just multiply the
round number m by 2, UNTIL it exceeds the total number n. The next elimination is now found by 
shifting the place in a loop, that is, n+1 becomes 1 , n+2 becomes 2 , and so on. This is done by 
subtracting n from 2*m. Now we remember that all 2*k type (even) numbers are already eliminated.
So we now subtract 1 to adjust for the shifted numbers, and thus we get the next number to be 
eliminated this way. Doubling and subtracting 1 is done repeatedly so that the number is less than
or equal to n. 

Example, if n=10, the numbers 2, 4, 6, 8, and 10 are removed in passes 1,2,3,4 and 5
Now, m=6. 2*m=12, which is greater than n. We now subtract it from 10 to get 2, double it as before 
and obtain 4. Now 1 is subtracted to get 3. 
When m=7, 2*m=14. Difference =4. 2*4 -1 = 7, our next number. 

Similarly for m=8 , 2*m=16, diff=6, 2*6-1 =11. This, again is greater than 10 so we repeat this 
adjustment again. Diff=1, 2*1 -1 =1 which is our next number.

*/

int formula(int n)
{
	//V(2m+l) = 2l+ 1

	int x=1;
	while(1)
	{
		if((2*x) > n)
		{	
			break;
		}	
		x=2*x;
	}
	int l=n-x;
	return (2*l) +1;

}


void main()
{
	printf("Enter n\n");
	int n;
	scanf("%d", &n);
	int i;
	printf("Elimination order: \n");
	for(i=1;i<n;i++)
		printf("%d ", eliminate(n,i));
	printf("\nSurvivor is: %d\n", eliminate(n,n));
	printf("Value given by formula is: %d\n", formula(n));
}