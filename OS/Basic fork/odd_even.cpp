#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;

int main()
{
	int l;
	cin>>l;

	int pid=fork();
	if(pid == 0)
	{	for(int i=0;i<=l;i+=2)
			cout<<i<<"\t";
		cout<<endl;
	}
	else
	{	for(int j=1;j<=l;j+=2)
			cout<<j<<"\t";
		cout<<endl;
	}
}


