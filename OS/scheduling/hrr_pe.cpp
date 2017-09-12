#include "process_sch.h"

void order_at(process p[])
{	
	for(int i=0;i<5;i++)
		for(int j=0;j<4-i;j++)
			if( p[j].get_at() > p[j+1].get_at() )
				{
					process temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;					
				}				
}

process find_hrr(process p[],int n,int sysclock)
{	process temp;
	float chrr,hrr;
	int posn=0;

	hrr = (float)(sysclock-p[0].get_at()-p[0].get_bt()) / (float)p[0].get_bt();

	for(int i=1;i<n;i++)
	{	chrr = (float)(sysclock-p[i].get_at()+p[i].get_bt()) / (float)p[i].get_bt();
		if (chrr < hrr)
		{	hrr=chrr;
			posn = i;
		}	
	}	
	
	return p[posn];
}

void hrr(process p[])
{
	order_at(p);
	int k=5;
	int sysclock = 1;

	for(int x=0;x<5;)
	{	int n=0;
		for(int i=0;i<k;i++)
			if( sysclock > p[i].get_at() )
				n++;
		if(n==0)
		{	sysclock++;
			x--;
			continue;	
		}

		process np=find_hrr(p,n,sysclock);
			
		int i;
		for(i=0;i<k;i++)
			if( np.get_pid() == p[i].get_pid() )
				break;

		p[i].bt_decrement();


		if(p[i].get_bt() == 0)
		{	p[i].assign_rest(sysclock);
			cout<<sysclock<<"\t";
			p[i].print_srt();
			for(int j=i;j<k-1;j++)
				p[j] = p[j+1];
			k--;	
			x++;			
		}
		else
		{	cout<<sysclock<<"\t";
			p[i].print_pid_rt();
		}

		sysclock++;

	}

}

