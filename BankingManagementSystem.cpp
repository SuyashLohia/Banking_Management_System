#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
void menu();
void admin();
void etransact();
void report();
void add();
void cdeposit();
void deposit();
fstream file;
int a =0;
class account
{
public:
int acno;
char name[100];
char mobile[15];
char landline[15];
char email[100];
char address[100];
char city[150];
char country[15];
char pcode[10];
float balance;
char ltrdate[100];
char ltrmonth[100];
char ltryear[100];
char ltrtype[100];
int trno;
public:
void update_bal(int m)
{balance+=m;}
void update_bal2(int n)
{balance-=n;}
void add_cust();
void disp_cust();
int ret_acno()
{ return acno;}
char* ret_name()
{return name;}
char* ret_mobile()
{return mobile;}
char* ret_landline()
{return landline;}
char* ret_email()
{return email;}
float ret_bal()
{return balance;}
char* ret_ltrd()
{return ltrdate;}
char* ret_ltrm()
{return ltrmonth;}
char* ret_ltry()
{return ltryear;}
int ret_trno()
{return trno;}
char* ret_trtype()
{return ltrtype;}
};

class transact : private account
{
public:
void withdraw(int wa);
void deposit(int ca);
};

void account:: add_cust()
{
acno=++::a;
clrscr();
cout<<"ENTER NAME OF ACCOUNT HOLDER:";
gets(name);
cout<<"ENTER MOBILE NUMBER:";
gets(mobile);
cout<<"ENTER LANDLINE NUMBER ELSE ENTER '-':";
gets(landline);
cout<<"ENTER EMAIL:";
gets(email);
cout<<"ENTER ADDRESS:";
gets(address);
cout<<"ENETR CITY:";
gets(city);
cout<<"ENETR COUNTRY:";
gets(country);
cout<<"ENTER POSTAL CODE:";
gets(pcode);
cout<<"ENTER INITIAL BALANCE:";
cin>>balance;
cout<<" For exciting deals go to www.indianbank.com/offers";
}

void account:: disp_cust()

{
cout<<"NAME OF THE ACCOUNT HOLDER IS--  "<<name<<'\n'<<"HIS ACCOUNT NUMBER IS--  "<<acno<<'\n'<<"MOBILE NUMBER IS--  "<<mobile<<endl;
cout<<"LANDLINE NUMBER IS--  "<<landline<<'\n'<<"ADDRESS AS PROVIDED IS \n "<<address<<'\n'<<city<<'-'<<pcode<<'\n'<<country<<endl;
cout<<"EMAIL IS--  "<<email<<"\nBALANCE IS--  "<<balance;
}

int acsearch()
{
clrscr();
int act;
cout<<"ENTER ACCOUNT NUMBER TO BE SEARCHED:";
cin>>act;
file.open("mybank.dat",ios::in|ios::binary);
int x=0;
account ob;
if(file!=NULL)
{
while(file.read((char*)&ob,sizeof(ob)))
{
if (ob.ret_acno()==act)
{
cout<<"ACCOUNT HOLDER FOUND:::\n\n";
ob.disp_cust();
x=1;
}
}
if(x==0)
cout<<"ERROR";

}
else
cout<<"ERROR";
file.close();
getch();
return x;
}

void nasearch()
{
clrscr();
file.open("mybank.dat",ios::in|ios::binary);
account ob;
char tmo[100];
if(file!=NULL)
{
cout<<"ENTER NAME TO BE SEARCHED:";
gets(tmo);
int x=0;
while(file.read((char*)&ob,sizeof(ob)))
{
if(strcmp(ob.ret_name(),tmo)==0)
{
cout<<"ACCOUNT HOLDER FOUND::\n\n";
ob.disp_cust();
x=1;
}
}
if(x==0)
cout<<"ERROR";
}
else
cout<<"ERROR";
getch();
file.close();
admin();
}


void search_cust()
{
clrscr();
char ch;
cout<<"BY WHAT METHOD DO YOU WANT TO SEARCH?";
cout<<"1.ACCOUNT NUMBER\t2.NAME\n\n ENTER CHOICE:";
ch=getche();
switch(ch)
{
case '1': acsearch();
	  break;
case '2': nasearch();
	  break;
}

}

void delete_cust()
{
clrscr();
fstream temp;
account ob;
int tac,found=0;
cout<<"ENTER ACCOUNT NUMBER TO BE DELETED:";
cin>>tac;
file.open("mybank.dat",ios::in|ios::binary);
temp.open("tmybank.dat",ios::out|ios::binary);
while(file.read((char*)&ob,sizeof(ob)))
{
if(ob.ret_acno()!=tac)
    temp.write((char*)&ob,sizeof(ob));
else
{
ob.disp_cust();
cout<<"\n\nRECORD DELETED";
found++;
}
}
file.close();
temp.close();
remove("mybank.dat");
rename("tmybank.dat","mybank.dat");
getch();
cout<<"PRESS ANY KEY FOR ADMIN MENU:";
admin();
}

void modify_cust()
{
clrscr();
fstream tfile;
account ob;
int tacc;
cout<<"ENTER ACCOUNT NUMBER TO BE UPDATED:";
cin>>tacc;
file.open("mybank.dat",ios::in|ios::binary);
while(file.read((char*)&ob,sizeof(ob)))
{
if(ob.ret_acno()==tacc)
{
cout<<"CURRENT DETAILS ARE:\n\n";
ob.disp_cust();
getch();
cout<<"\n\nINPUT NEW DETAILS:";
ob.add_cust();
file.seekp(file.tellp()-sizeof(ob), ios::beg);
file.write((char*)&ob,sizeof(ob));
break;

}

}
file.close();
}



void transact:: withdraw(int wa)
{   fstream tfile;
clrscr();
account ob;
float m;
file.open("mybank.dat",ios::in|ios::binary);
tfile.open("temp.dat",ios::app|ios::binary);
while(file.read((char*)&ob,sizeof(ob)))
{
  if(wa==ob.ret_acno())
    {
  cout<<"ENTER AMOUNT TO BE WITHDRAWN:";
  cin>>m;
  ob.update_bal2(m);
  tfile.write((char*)&ob,sizeof(ob));
  getch();
  }
  else
  tfile.write((char*)&ob,sizeof(ob));
}
tfile.close();
file.close();
remove("mybank.dat");
rename("temp.dat","mybank.dat");
}



void transact:: deposit(int ca)
{
  fstream tfile;
clrscr();
account ob;
float m;
file.open("mybank.dat",ios::in|ios::binary);
tfile.open("temp.dat",ios::app|ios::binary);
while(file.read((char*)&ob,sizeof(ob)))
{
  if(ca==ob.ret_acno())
    {
  cout<<"ENTER AMOUNT TO BE DEPOSITED:";
  cin>>m;
  ob.update_bal(m);
  tfile.write((char*)&ob,sizeof(ob));
  getch();
  }
  else
  tfile.write((char*)&ob,sizeof(ob));
}

tfile.close();
file.close();
remove("mybank.dat");
rename("temp.dat","mybank.dat");
}



void add()
{
	account ob;
	file.open("mybank.dat",ios::app|ios::binary);
	ob.add_cust();
	file.write((char*)&ob, sizeof(ob));
	file.close();
	cout<<"\n ANY KEY FOR ADMIN";
	admin();
}

void display()
{
    clrscr();
    int c=0;
    file.open("mybank.dat",ios::in|ios::binary);
    account ob;
    if(file!=NULL)
    {
       file.seekg(0);
       while(file.read((char*)&ob,sizeof(ob)))
       {
	 ++c;
       ob.disp_cust();
       cout<<"\n\n";
       }
}
 if(c==0)
 cout<<"ERROR";
 file.close();
 cout<<"\n\nPRESS ANY KEY TO RETURN TO ADMIN";
 getch();
 admin();

}

void cdeposit()
{  clrscr();

int y=0;   int t;   account tp;
cout<<"ENTER ACCOUNT NUMBER:";
cin>>t;
file.open("mybank.dat",ios::in|ios::binary);
while(file.read((char*)&tp,sizeof(tp)))
{
if (tp.ret_acno()==t)
{ y=-1;
break;
}
}
file.close();
if (y!=-1)
{
cout<<"INVALID ACCOUNT.";
getch();
etransact();
}
transact c;
c.deposit(t);
}


void cwithdraw()
{
  clrscr();

int o=0;   int b;   account tw;
cout<<"ENTER ACCOUNT NUMBER:";
cin>>b;
file.open("mybank.dat",ios::in|ios::binary);
while(file.read((char*)&tw,sizeof(tw)))
{
if (tw.ret_acno()==b)
{ o=-1;
break;
}
}
file.close();
if (o!=-1)
{
cout<<"INVALID ACCOUNT.";
getch();
etransact();
}
transact d;
d.withdraw(b);
}


void bank_stat()
{  account ob; int acc;
   cout<<"\n\nENTER ACCOUNT NUMBER FOR STATEMENT:";
   cin>>acc;
   file.open("mybank.dat",ios::in|ios::binary);
   while(file.read((char*)&ob,sizeof(ob)))
   {
   if(ob.ret_acno()==acc)
   {
   cout<<"\n\nLAST TRANSACTION WAS MADE ON:"<<ob.ret_ltrd()<<"/"<<ob.ret_ltrm()<<"/"<<ob.ret_ltry()<<"\n\n";
   cout<<"\n\nTYPE OF TRANSACTION WAS:"<<ob.ret_trtype();
   getch();
   }
}
file.close();
menu();
}

void admin()

{

char ch;

while(1)
{ clrscr();

cout<<"\t\tADMIN"<<'\n'<<'\n';
cout<<"\t\t1.ADD CUSTOMER"<<'\n'<<"\t\t2.DISPLAY CUSTOMER"<<endl;
cout<<"\t\t3.SEARCH CUSTOMER"<<'\n'<<"\t\t4.DELETE CUSTOMER"<<endl;
cout<<"\t\t5.MODIFY CUSTOMER"<<'\n'<<"\t\t0. MAIN MENU"<<'\n';
cout<<"ENTER CHOICE:";
ch=getch();

switch(ch)
{
case '1': add();
	  break;

case '2': display();
	  break;

case '3': search_cust();
	  break;

case '4': delete_cust();
	  break;

case '5': modify_cust();
	  break;

case '0': menu();

}

}

}

void etransact()
{
char ch;
while(1)
{   clrscr();
cout<<"TRANSACT"<<'\n'<<'\n';
cout<<"1.WITHDRAW"<<'\n'<<"2.DEPOSIT"<<endl<<"0.MAIN MENU"<<endl<<endl;
cout<<"ENTER YOUR CHOICE:";
ch=getch();
switch(ch)
{
 case '1': cwithdraw();
	   break;
 case '2': cdeposit();
	   break;
 case '0': menu();
}
}
}

void report()
{
	clrscr();
	char ch;
	while(1)
	{
	clrscr();
	cout<<" BANK REPORT \n\n Please Choose among the following \n";
	cout<<"1. Bank Statement\n0. Main Menu";
	ch=getche();
		switch(ch)
		{
		case '1': 	bank_stat();
				break;

		case '0': 	menu();
					break;
		}
	}
}


void menu()
{
	clrscr();
	char c; char ch[500];
	while(1)
	{
		clrscr();
		cout<<"WELCOME TO INDIAN BANK.\n\n\n";

		cout<<"\nPLEASE CHOOSE FROM AMONGST THE FOLLOWING OPTIONS:\n\n";

		cout<<"1.ADMIN MENU\n\n2.TRANSACTIONS\n\n3.REPORTS\n\n0.EXIT";
		cout<<"\n\nENTER YOUR CHOICE:";
		c=getche();
		switch(c)
		{
		case '1':       clrscr();
				admin();
				break;

		case '2':	etransact();
				break;

		case '3':	report();
				break;
		case '0':       exit(0);
		}
	}
}

void main()
{
	menu();
}