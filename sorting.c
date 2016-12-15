#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"
//long *Load_File(char *Filename, int *Size);
int* mypq(int,int*);
double my_pow(double, double);

long *Load_File(char *Filename, int *Size)
{
  FILE * fp = fopen(Filename,"r");
  long* arr=NULL;
  fscanf(fp,"%d",Size);
  arr = malloc(sizeof(long)* (*Size));
  int i = 0;
  if(fp!=NULL)
    {
      while(i < *Size){      
	fscanf(fp,"%ld",&arr[i++]);
      }	    
      fclose(fp);
      return arr;
    }
  else
    {
      fprintf(stderr,"file did not open correctly");
      return NULL;
    }
}

double my_pow(double x, double y)
{
  //x to the power of y;
  int sum = x;
  if(y==0)
    return 1;
  else if(y==1)
    return x;
  else
    while(y>1)
      {
	sum=sum*x;
	y--;
      }
  return sum;
}


int* mypq(int N,int * x)
{
  //N is len of array to be sorted
  //x is the len of return array 
  int* arr=malloc(sizeof(int)*10000);//remember to free in sort function
  double p = 0;
  double q = 0;
  int sum = 0;
  int i=0;
  int j=0;
  int k;

  while(my_pow(2,sum) < N)//O(log2(N))
    {      
      for(p=sum;p>=0;p--)
	{
	  q=sum-p;
	  arr[i] = (int) ((my_pow(2,p)) * (my_pow(3,q)));
	  //printf("%f   sum =%d i=%d  p=%f  q=%f \n",arr[i],sum,i,p,q);
	  i++;
	}
      sum++;  
    }
  i--;   
  for(j=1;j<(i);j++)
    {
      k=j;
      while((k>0) & (arr[k-1] > arr[k]))
	{ 
	  p=arr[k-1];
	  arr[k-1]=arr[k];
	  arr[k]=p;
	  k--;
	} 
    }

  while(arr[i]>N)
    {    
      i--;
    }
  i++;
  *x=i;  //x is the size to be returned

  return arr;
    
}


int Save_File(char *Filename, long *Array, int Size)
{
  int i=0;  
  int count=0;
  //char buffer[20];
  FILE* ptr;
  ptr = fopen(Filename,"w");
 
  if(!ptr)
    return -1;
  if(!fprintf(ptr,"%d",Size))
    {
      fclose(ptr);
      return -1;  
    } 
  //count++;
  for(i=0;i<Size;i++)
    {
      if(!fprintf(ptr,"%ld",Array[i]))
	return(count);
      count++;
    }
  fclose(ptr);
  return count;

}


void Shell_Insertion_Sort (long *Array, int Size, double *x, double *y)
{
  //get strides
  int stdlen;
  int* strides = mypq(Size,&stdlen);// must be freed
  int i = stdlen-1;//
  int base,max,left,right,tmp;
  int j=0;
  //printf(" Size = %d,    i= %d \n", Size, i);
  while(j<Size)
    {
      //printf("Array[%d] = %ld\n",j, Array[j]);
      j++;
    }
  double NComp = 0;
  double NMove = 0;
  while(i>-1)//i will access array of strides
    {
      NComp++;
      max = (Size)- strides[i];
      for(base = 0;base<=max; base++)
	{
	  NComp++;
	  left = base;
	  right = left + strides[i];
	  tmp = Array[right];
	  while((left >=0) && (Array[left] > tmp))
	    {	      
	      NComp+=2;	   	    
	      Array[right] = Array[left];
	      NMove++;
	      right = left;;
      	      left -= strides[i];	      
 	    }
	  Array[right]=tmp;
	  NComp++;
	  if(left>=0){
	    NComp++;
	  }
	}
      NComp++;
      i--;
    }
  NComp++;
  *x= NComp;
  *y= NMove;
  free(strides);

}



void Improved_Bubble_Sort (long *Array, int Size, double *x, double *y)
{
    //get strides
  int i = (Size)/1.3;
  int max,j,k;
  double tmp;
  double NComp = 0;
  double NMove = 0;
  while(i)//i will access array of strides
    {
      NComp++;
      max=Size-2*i;
      for(j=max;j>=0;j-=i)
	{
	  NComp++;
	  for(k=0;k<=j;k+=i)
	    {
	      NComp++;
	      if(Array[k]>Array[k+i])
		{     
		  tmp = Array[k];
		  Array[k]=Array[k+i];
		  Array[k+i]=tmp;
		  NMove++;
		}
	      NComp++;
	    }
	  NComp++;
	}
      NComp++;
      i = i/1.3;
    }
  NComp++;
  *x=NComp;
  *y=NMove;
}


void Save_Seq1 (char *Filename, int N)
{
  int x=0;
  int i;
  int * arr;
  FILE * fptr = fopen(Filename,"w");
  if(fptr)
    {
      arr=  mypq(N,&x);
      for(i=0;i<x;i++)
	{
	  fprintf(fptr,"%d",arr[i]);
	  
	}
      fclose(fptr);
      free(arr);
    }
}

void Save_Seq2 (char *Filename, int N)
{
  int i;
  FILE* fptr = fopen(Filename,"w");
  i=N/1.3;
  if(fptr)
    {
      while(i)
	{
	  fprintf(fptr,"%d",i);
	  i=i/1.3;
	}
      fclose(fptr);
    }
}


/* int main() */
/* { */
/*   long* Array;  */
/*   int Size, i ; */
/*   double NComp,NMove; */
/*   Array = Load_File("1000.txt",&Size); */
/*   Improved_Bubble_Sort (Array,Size,&NComp,&NMove); */
/*   for(i=0;i<Size;i++){ */
/*     printf("Array of [%d] =  %ld\n", i,Array[i]); */
/*   } */
/*   printf("The number of moves is %f.\nThe number of comparisons is %f\n",NMove,NComp); */
/*   free(Array);  */
/*   return 0; */
/* } */

