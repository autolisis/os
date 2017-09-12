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

void assign_all(process p[])
{	int ct = p[0].get_at();
	for(int i=0;i<5;i++)
	{	ct += p[i].get_bt();
		p[i].assign_rest(ct);
	}
}

void fifo(process p[])
{	order_at(p);
	assign_all(p);
}

