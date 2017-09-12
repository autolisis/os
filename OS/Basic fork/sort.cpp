#include<iostream>
#include<algorithm>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

using namespace std;

int main()
{
	int a[10] = {0};
	for(int i=0;i<10;i++)
		cin>>a[i];

	int pid=fork();
	if(pid==0)
	{	sort(a,a+10);
		cout<<"Ascending: \n";
		for(int i=0;i<10;i++)
			cout<<a[i]<<"\t";
		exit(0);
	}
	else
	{	sort(a,a+10,greater<int>());
		cout<<"\nDescending: \n";
		for(int i=0;i<10;i++)
			cout<<a[i]<<"\t";
	}

}
