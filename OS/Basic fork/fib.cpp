#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{	int n,temp;
	cin>>n;
	int a,b;
	a=0;
	b=1;

	int pid=fork();
	if(pid ==0 )
		while(b<n)
			{	
				cout<<b<<"\t";
				temp=a;
				a=b;
				b+=temp;
			}
	
}
