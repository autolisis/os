#include<iostream>

using namespace std;

class process
{	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int pt;
	
	public:
	void inpt(int npid,int nat,int nbt)
	{
			pid=npid;
			at=nat;
			bt=nbt;
	}

	void inpt_pt(int npid,int nat,int nbt,int npt)
	{
			pid=npid;
			at=nat;
			bt=nbt;
			pt=npt;
	}

	int get_pt()
	{
		return pt;
	}

	int get_at()
	{
		return at;
	}

	int get_bt()
	{
		return bt;
	}
	
	int get_pid()
	{	
		return pid;
	}
	
	void bt_done()
	{	bt=0;
	}

	void assign_rest(int nct)
	{	
		ct=nct;
		tat=ct-at;
		wt=tat-bt;
	}

	void bt_decrement()
	{	bt--;
	}
	
	void bt_decrement(int n)
	{	bt-=n;
	}
	
	void print_pid_rt()
	{	cout<<"\t"<<pid<<"\t\t"<<bt<<"\n";
	}

	void print_srt()
	{
		cout<<"\t"<<pid<<"\t"<<at<<"\t"<<bt<<"\t"<<ct<<endl;
	}

	void print_pt()
	{
		cout<<pid<<"\t"<<at<<"\t"<<bt<<"\t"<<ct<<"\t"<<tat<<"\t"<<wt<<"\t"<<pt<<endl;
	}

	void print_pt_pe()
	{
		cout<<"\t"<<pid<<"\t"<<at<<"\t"<<bt<<"\t"<<ct<<"\t"<<tat<<"\t"<<wt<<"\t"<<pt<<endl;
	}

	void print()
	{
		cout<<pid<<"\t"<<at<<"\t"<<bt<<"\t"<<ct<<"\t"<<tat<<"\t"<<wt<<endl;
	}
};
