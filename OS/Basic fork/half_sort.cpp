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

	cout<<"Input:\n";
	for(int i=0;i<10;i++)
		cout<<a[i]<<"\t";

	cout<<endl;

	int pid=vfork();
	if(pid==0)
	{	sort(a,a+5);
		exit(0);
	}
	else
	{	sort(a+4,a+10,greater<int>());
		cout<<"Sorted:\n";
		for(int i=0;i<10;i++)
			cout<<a[i]<<"\t";
	}

}
