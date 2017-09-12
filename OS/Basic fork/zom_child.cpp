#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>

using namespace std;

int main()
{	int pid1=fork();
	if(pid1==0)
	{	int pid=fork();
		if(pid==0)
		{	sleep(5);
			cout<<"\nOrphan\n";
		}
		else
			cout<"parent done\n";
	}
	else
	{	int pid=fork();
		if(pid==0)
			cout<<"child done\n";
		else
		{	wait(pid);
			cout<<"\nZombie\n";
		}
	}
}
		
