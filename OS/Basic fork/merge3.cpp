#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
#include<ctype.h>
#include<stdlib.h>

using namespace std;

void merge2(int a[],int l,int m,int r)
{	int i,j,k;
	int n1=m-l+1;
	int n2=r-m;

	int L[n1],R[n2];

	for (i=0;i<n1;i++)
		L[i]=a[l+i];
	for (j=0;j<n2;j++)
		R[j]=a[m+1+j];

	// merge
	i=0; 				// Initial index- subarray 1
	j=0; 				// Initial index- subarray 2
	k=l; 				// Initial index- merged
	while(i<n1 && j<n2)
		if (L[i]<=R[j])
				a[k++]=L[i++];
		else
				a[k++]=R[j++];

//left overs
	while(i<n1)
		a[k++]=L[i++];
	while(j<n2)
		a[k++]=R[j++];
}
 
void sort2(int a[],int l,int r)		//two way partition
{
   	if (l < r)
	{  	int m1=l+(r-l+1)/3;
		int m2=l+2*(r-l+1)/3;
		pid_t pid=vfork();
		if(pid==0)
		{	sort2(a,l,m1);			// sort right half
			sort2(a,m1+1,m2);		// sort left half
			sort2(a,m2+1,r);
			exit(0);
		}
		else
		{	wait(0);
			merge2(a,l,m1,m2);
			merge2(a,m1,m2,r);
		}	
	}
}

int main(void)
{	int i,j;
	
	//test driver
	int c[10]={1,1,2,4,5,3,6,9,7,8};
	sort2(c,0,9);
	for(i=0;i<10;i++)
		cout<<c[i]<<" ";	
}
