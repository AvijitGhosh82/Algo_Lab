
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct complex{
  double real;
  double imag;
  } complex;

complex mult(complex a, complex b)
{
  complex m;
  m.imag=a.real*b.imag + a.imag*b.real;
  m.real=a.real*b.real - a.imag*b.imag;
  return m;
}

randomize(complex A[], int x, int n)
{
	int i;
	for(i=0;i<x;i++)
	{
		A[i].real=rand()%10;
		A[i].imag=0.0;
		printf("%.0lf",A[i].real);
	}
	printf("\n");

    for (i=x;i<n;i++)
	{
	    A[i].real=A[i].imag=0.0;
    }
	
}

complex add(complex a, complex b)
{
  complex sum;
  sum.real=a.real+b.real;
  sum.imag=a.imag+b.imag;
  return sum;
}

complex subt(complex a, complex b)
{
  complex sum;
  sum.real=a.real-b.real;
  sum.imag=a.imag-b.imag;
  return sum;
}

double absm(complex A)
{
  return sqrt((A.real*A.real)+(A.imag*A.imag));
}


complex conju(complex A[],int n)
{
  int i;
  double t;
  for(i=0;i<n;i++)
  {
    
    A[i].imag*=-1;
  }
  return;
}

norm(complex A[],int n)
{
  int i;
  double t;
  for(i=0;i<n;i++)
  {
    A[i].imag/=n;
    A[i].real/=n;
  }
  return;
}

complex fft(int n, complex A[] ,complex F[]) {
  int j,k; complex omegak,omega;
  if (n == 1) 
    {  F[0]= A[0];
      return;}
  int hf=n/2;
  complex E[hf], O[hf], EF[hf], OF[hf];
  for (j=k=0; k<=n; j++,k+=2) {
      E[j]=A[k]; O[j]=A[k+1];
  }
  fft(n/2, E, EF);
  fft(n/2, O, OF);



  omegak.real = omega.real = cos((2*3.14)/n);
  omegak.imag = omega.imag = sin((2*3.14)/n);

  for (k=0; k<n/2; k++,omegak=mult(omegak,omega)) {
    F[k] =add(EF[k],mult(omegak,OF[k]));
    F[k+hf] =subt(EF[k],mult(omegak,OF[k]));
  }
}


ifft(int n, complex F[],complex A1[])
{
  conju(F,n);
  fft(n,F,A1);
  conju(A1,n);
  norm(A1,n);
}

void main()
{
  //int n=4;
  srand(time(NULL));

  printf("Enter number of digits: \n");
  int x;
  scanf("%d",&x);
  int n = 1;
  while(n < x)
    n*=2;
	
  n=n*2;//for wrapping around check

  int i;

  complex  A[n];
  complex B[n];

  printf("The two randomly generated integers are: \n");

  randomize(A,x,n);
  randomize(B,x,n);

  complex FA[n], FB[n],test[n];
  fft(n,A,FA);
  fft(n,B,FB);


  complex C[n];

  for(i=0;i<n;i++)
  {
  	C[i]=mult(FA[i],FB[i]);
  }

  complex P[n];

   ifft(n,C,P);

   //Now i have the numbers in the product. I need to sum and carry them to get the final result base 10

   int dig=0.0;
   int carry=0.0;
   int val;
   int ANS[n];
   int c=0;
  
  for(i=n-2;i>=0;i--)
    {
      // printf("IF%d %.2lf + %.2lf I = %.0lf\n",i,P[i].real, P[i].imag, round(absm(P[i])));
      val=round(absm(P[i]))+carry;
      dig=val%10;
      carry=val/10;
      ANS[c]=dig;
      c++;
    }
    // printf("IF%d %.2lf + %.2lf I = %.0lf\n",n-1,P[n-1].real, P[n-1].imag, round(absm(P[n-1])));
    val=round(absm(P[n-1]))+carry;
    ANS[c]=val;
      // dig=val%10;
      // carry=val/10;
      // ANS[c]=dig;
      // ANS[c+1]=carry;

    printf("Their product is: ");

    for(i=n-1;i>(n-(2*x));i--)
    	printf("%d",ANS[i]);
    printf("\n");

  return;
}