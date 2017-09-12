#include "process_sch.h"
#include <queue>

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

void rr(process p[])
{	order_at(p);

	queue<process> q;
	process temp;
	int start,end,max=5;
	int count=1;
	end=0;
	start=0;
	int tq=3;

	int sysclock = p[0].get_at();
	q.push(p[0]);

	while(!q.empty())
	{	for(int i=count;i<5;i++)
		{	if(p[i].get_at()<sysclock)
			{	q.push(p[i]);
				count++;
			}
		}
		
		if( q.front().get_bt() > tq ) 
		{	q.front().bt_decrement(tq);
			sysclock+=tq;
			cout<<sysclock;
			q.front().print_pid_rt();
		}
		else
		{	sysclock+=q.front().get_bt();
			q.front().bt_done();
			q.front().assign_rest(sysclock);
			cout<<sysclock;
			q.front().print_srt();
		}
		
		temp=q.front();
		q.pop();
		if(temp.get_bt()!=0)
			q.push(temp);
	}	
}			
