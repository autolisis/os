#include <iostream>

#include <fstream>
#include <stdlib.h>

//#include "fifo.cpp"
//#include "sjf.cpp"
//#include "srt.cpp"
//include "priority_npe.cpp"
//#include "priority_pe.cpp"
#include "hrr_pe.cpp"
//#include "hrr.cpp"
//#include "rr.cpp"

int main(void)
{
	process p[5];
	int pid,at,bt,pt;
	
// fcfs,sjf,srt,round-robin,hrr

// input
	for(int i=0;i<5;i++)
	{
		cin>>pid>>at>>bt;
		p[i].inpt(pid,at,bt);
	}
/*
// files
	int pid[5],bt[5],at[5],a;

	//pid
	for(int i=0;i<5;i++)
		pid[i] = i;

	fstream f;
	string s;
	
	//bt

 	a=system("wc -w p2.txt > f1.txt");
	f.open("f1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	bt[1]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

 	a=system("wc -w p3.txt > f1.txt");
	f.open("f1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	bt[2]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

 	a=system("wc -w p4.txt > f1.txt");
	f.open("f1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	bt[3]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');


 	a=system("wc -w p1.txt > f1.txt");
	f.open("f1.txt",ios::in);
	getline(f,s,' ');
	f.close();
//	bt[0]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');
	bt[0] = 36;

	a=system("wc -w p1.txt > f1.txt");
	f.open("f1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	bt[0]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

 	a=system("wc -w p5.txt > f1.txt");
	f.open("f1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	bt[4]=28;

	// at
	a=system("expr `date +%s` - `stat -c %Y p1.txt` > a1.txt");
	f.open("a1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	at[0]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

	a=system("expr `date +%s` - `stat -c %Y p2.txt` > a1.txt");
	f.open("a1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	at[1]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

	a=system("expr `date +%s` - `stat -c %Y p3.txt` > a1.txt");
	f.open("a1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	at[2]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

	a=system("expr `date +%s` - `stat -c %Y p4.txt` > a1.txt");
	f.open("a1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	at[3]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

	a=system("expr `date +%s` - `stat -c %Y p5.txt` > a1.txt");
	f.open("a1.txt",ios::in);
	getline(f,s,' ');
	f.close();
	at[4]=(int)(s[0]-'0')*10 + (int)(s[1]-'0');

	cout<<"input:\npid\tat\tbt\n";
	for(int i=0;i<5;i++)
	{	p[i].inpt(pid[i],at[i],bt[i]);
		cout<<pid[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<endl;
	}	
*/

// ficfs,sjf output
//	cout<<"pid\tat\tbt\tct\ttat\twt\n";
//	fifo(p);
//	for(int i=0;i<5;i++)
//		p[i].print();
//	sjf(p);	

//	hrr(p);

//	srt,hrr
	cout<<"clock\tpid\tat\trt\tct\n";
	hrr(p);
//	srt(p);


//	round-robin
//	cout<<"\nclock\tpid\tat\trt\tct\n";
//	rr(p);


// Priority
/*	for(int i=0;i<5;i++)
	{
		cin>>pid>>at>>bt>>pt;
		p[i].inpt_pt(pid,at,bt,pt);
	}

	cout<<"pid\tat\tbt\tct\ttat\twt\tpt\n";
	priority_npe(p);	
	

	cout<<"sysclock\tpid\tat\trt\tct\ttat\twt\tpt\n";
	priority_pe(p);
*/
	

	return 0;

	}

