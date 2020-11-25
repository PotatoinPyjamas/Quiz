#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<fstream.h>
#include<iomanip.h>
#include<time.h>
#include<ctype.h>
class qb
{
int qno;
char qs[201];
char mcq[201];
char ans[2];
public:
qb()
{
strcpy (qs," ");
strcpy(mcq," ");
strcpy(ans," ");
}
void enterqs();
void displayqs();
int searchqno(int, char*);
int retqno()
{
return qno;
}
void setqno(int n)
{
qno=n;
}
char* retans()
{
return ans;
}
char* retqs()
{
return qs;
}
char* retmcq()
{
return mcq;
}
};
int qb::searchqno(int n, char* s1)
{ cout<<endl;
  int flag=0;
  ifstream fi;
  char buf[50];
  qb q;
  strcpy(buf,s1);
  fi.open(buf, ios::in | ios::out | ios::binary);
  if(!fi)
  {
  cout<<"File cannot be opened!";
  getch();
  }
  while(fi.read((char *) &q, sizeof(q)))
  {
     cout<<endl;
    if(q.retqno()==n)
    {
    flag++;
    break;
    }
  }
  fi.close();
  getch();
  return flag;
}

void qb::enterqs()
{
cout<<"Enter Question "<<endl;
gets(qs);
cout<<"Enter the options"<<endl;
gets(mcq);
cout<<"Enter the correct answer"<<endl;
gets(ans);
}
void qb::displayqs()
{
cout<<qs<<endl;
cout<<mcq;
cout<<ans;  //remove
cout<<endl;   //remove this line!!only for crosschecking
}

struct sinfo
{
char qs[200], mcq[200], ans[2], userans[5];
};
sinfo s[4];  //kept 4 as currently only 5 qs exist in the qb, change to 15 later

void dispresult()
  {
  for(int j=0,k=1;j<4;j++,k++)
  {
  cout<<"Question "<<j+1<<endl;
  cout<<s[j].qs<<endl;
  cout<<s[j].mcq<<endl;
  cout<<"Correct answer: "<<s[j].ans<<"\t\t";
  cout<<"Your answer: "<<strupr(s[j].userans)<<endl;
  cout<<endl;
  if(k%4==0)
  getch();
  }
}
class playgame
{
int gameno, total;
char playername[40],gdate[50];
public:
playgame()
{
gameno=0;
total=0;
strcpy(playername," ");
time_t rtime;
struct tm *timeinfo;
time(& rtime);
timeinfo=localtime(&rtime);
strftime(gdate,  50, "%d/%m/%Y",timeinfo);
}
void setusername(char* u)
{ strcpy(playername,u);
}
void setgamedate(char* gd)
{
strcpy(gdate, gd);
}
char* retgamedate()
{
return gdate;
}
void showall();
void quiz(int);
void pro(int);
void display();
void game(char* u) ;
void settotal(int n)
{
  total=n;
}
void leaderboard();
void setgameno(int n)
{
  gameno=n;
}
char* retplayername()
{
return playername;
}
int retgameno()
{
return gameno;
}
int rettotal()
{
  return total;
}
};
int A[10];
void randomqs()
{clrscr();
 randomize();
 int firsttime=1,x=0,e=0,r;
 while(x<4)
 {
   r=random(5);
   if(firsttime==1)
   {
    A[x]=r;
    firsttime=0;
   }
   else
   {
    for(int i=0; i<=x; i++)
    {
      if(r==A[i])
      {
       e=1;
       break;
      }
    }
    if(e==0)
    {
       x++;
       A[x]=r;

    }
    e=0;
   }
}
}
void playgame:: display()
{ cout<<gameno<<"\t\t";
  cout<<gdate<<"\t";
  cout<<playername<<"\t\t\t";
  cout<<total<<"\t\t"<<endl;
}
void playgame::quiz(int n)
{
clrscr();
int lastgameno;
playgame pg;
ifstream fi;
fi.open("quizdetails.dat",ios::in|ios::binary |ios::ate);
if(!fi)
{
  lastgameno=1;
}
  long p=fi.tellg();
  fi.seekg(p-1*sizeof(pg));
  fi.read((char*)&pg, sizeof(pg));
  lastgameno=pg.retgameno()+1;
  fi.close();
  char opt[5]="n";
  int skip=0,r=0,w=0;
  ifstream fq;
  qb q1;
  switch(n)
  {
  case 1:
    fq.open("qs.dat",ios::in|ios::binary);
    break;
  case 2:
    fq.open("qh.dat",ios::in|ios::binary);
    break;
  case 3:
    fq.open("qgk.dat",ios::in|ios::binary);
    break;
  }
  if(!fq)
  {
    cout<<"File not found"<<endl;
    return;
  }
  else
  {
    randomqs();
    for(int i=0;i<4;i++)
    {
      fq.seekg(sizeof(q1)*A[i],ios::beg);
      fq.read((char*)&q1,sizeof(q1)) ;
      cout<<"Question "<<i+1<<endl;
      q1.displayqs();
      strcpy(s[i].qs,q1.retqs());
      strcpy(s[i].mcq,q1.retmcq());
      strcpy(s[i].ans,q1.retans());
      char ch;
      cin>>ch;
      opt[0]=ch;
      ch=' ';
      strcpy(s[i].userans,opt);
      if(strcmpi(opt,"skip")==0)
	skip++;
      else if(strcmpi(opt,q1.retans() )==0)
       r++;
      else
       w++;

    }
    total=(4*r)-w;
    pg.setgameno(lastgameno);
    pg.setgamedate(gdate);
    pg.setusername(playername);
    pg.settotal(total);
    clrscr();
    cout<<"The total marks are"<<" "<<total<<endl;
    cout<<endl;
    char opt1[2];
    cout<<"Do you want to view the result?"<<endl;
    cin>>opt1;
    if(strcmpi(opt1,"y")==0)
    {
     dispresult();
    }
    fq.close();
    cout<<"SAVING GAME NO "<<lastgameno<<endl;
    ofstream fout;
    fout.open("quizdetails.dat", ios::out|ios::binary|ios::app);
    fout.write((char*)&pg,sizeof(pg));
    fout.close();
    ifstream fin;
    int flag=0;
    clrscr();
    fin.open("quizdetails.dat", ios::in|ios::binary);
    cout<<"GAME NO\t\tDATE\t\tPLAYER\t\tSCORE"<<endl;
    while(!fin.eof() && flag==0)
    {
      fin.read((char*)&pg,sizeof(pg));
      long pos=fin.tellg();
      if(pg.retgameno()==lastgameno)
      {
	fin.seekg(pos-1*sizeof(pg));
	pg.display();
	flag++;
	break;
      }
    }
    fin.close();
    cout<<"Your scores uptil now!!"<<endl;
    flag=0;
    fin.open("quizdetails.dat", ios::in|ios::binary);
    cout<<"GAME NO\t\tDATE \t\tPLAYER\t\tSCORE"<<endl;
    while(fin.read((char*)&pg,sizeof(pg)))
    {
      if(strcmpi(pg.retplayername(), playername)==0)
      {
	pg.display();
      }
    }
    fin.close();
  }
 char cho3, cho4;
 cout<<" Do you want to view the leaderboard?"<<endl;
 cin>>cho3 ;
 if(cho3=='y'||cho3=='Y');
 pg.leaderboard();
 cout<<" Do you want to view all the games played?"<<endl;
 cin>>cho4;
 if(cho4=='y'||cho4=='Y');
 pg.showall();
}
void playgame::pro(int n)
{
clrscr();
int timeout=0, miss=0;
int lastgameno;
playgame pg;
ifstream fi;
fi.open("quizdetails.dat",ios::in|ios::binary |ios::ate);
if(!fi)
{
  lastgameno=1;
}
  long p=fi.tellg();
  fi.seekg(p-1*sizeof(pg));
  fi.read((char*)&pg, sizeof(pg));
  lastgameno=pg.retgameno()+1;
  fi.close();
  char opt[5]="n";
  int skip=0,r=0,w=0;
  ifstream fq;
  qb q1;
  switch(n)
  {
  case 1:
    fq.open("qs.dat",ios::in|ios::binary);
    break;
  case 2:
    fq.open("qh.dat",ios::in|ios::binary);
    break;
  case 3:
    fq.open("qgk.dat",ios::in|ios::binary);
    break;
  }
  if(!fq)
  {
    cout<<"Qs file not found"<<endl;
    return;
  }
  else
  {
    randomqs();
    for(int i=0;i<4;i++)
    {

      fq.seekg(sizeof(q1)*A[i],ios::beg);
      fq.read((char*)&q1,sizeof(q1)) ;
      cout<<"Question "<<i+1<<endl;
      q1.displayqs();
     // cout<<endl;
      strcpy(s[i].qs,q1.retqs());
      strcpy(s[i].mcq,q1.retmcq());
      strcpy(s[i].ans,q1.retans());
      char ch;
      clock_t start=clock();
      cout<<"Timer :10 secs"<<endl;
      while(!kbhit())
      {
	if(((clock()-start)/CLOCKS_PER_SEC)>=10)
	{
	  cout<<"Time up!!!"<<endl;
	  start=clock();
	  timeout++;
	  miss++;
	  break;
	}
      }
      if(kbhit())
      {
	cin>>ch;
      }
      opt[0]=ch;
      ch=' ';
      strcpy(s[i].userans,opt);
      if(strcmpi(opt,"skip")==0)
	skip++;
      else if(strcmpi(opt,q1.retans() )==0)
       r++;
      else
      {
	if(timeout==0)
	{
	  w++;
	}
      }
      timeout=0;
   }
   getch();
   total=(5*r)-(2*w)-miss;
   pg.setgameno(lastgameno);
   pg.setgamedate(gdate);
   pg.setusername(playername);
   pg.settotal(total);
   clrscr();
   cout<<"The total marks are"<<" "<<total<<endl;
   cout<<endl;
   char opt1[2];
   cout<<"Do you want to view the result?"<<endl;
   cin>>opt1;
   if(strcmpi(opt1,"y")==0)
   {
     dispresult();
   }
   fq.close();
   cout<<"SAVING GAME NO "<<lastgameno<<endl;
   ofstream fout;
   fout.open("quizdetails.dat", ios::out|ios::binary|ios::app);
   fout.write((char*)&pg,sizeof(pg));
   fout.close();
   ifstream fin;
   int flag=0;
   clrscr();
   fin.open("quizdetails.dat", ios::in|ios::binary);
   cout<<"GAME NO\t\tDATE\t\tPLAYER\t\tSCORE"<<endl;
   while(!fin.eof() && flag==0)
   {
     fin.read((char*)&pg,sizeof(pg));
     long pos=fin.tellg();
     if(pg.retgameno()==lastgameno)
     {
      fin.seekg(pos-1*sizeof(pg));
      pg.display();
      flag++;
      break;
      }
    }
  fin.close();
  cout<<"Your scores uptil now!!"<<endl;
  flag=0;
  fin.open("quizdetails.dat", ios::in|ios::binary);
  cout<<"GAME NO\t\tDATE \t\tPLAYER\t\tSCORE"<<endl;
  while(fin.read((char*)&pg,sizeof(pg)))
  {
    if(strcmpi(pg.retplayername(), playername)==0)
    {
      pg.display();
    }
  }
  fin.close();
  }
char cho3, cho4;
cout<<" Do you want to view the leaderboard?"<<endl;
cin>>cho3 ;
if(cho3=='y'||cho3=='Y');
pg.leaderboard();
cout<<" Do you want to view all the games played?"<<endl;
cin>>cho4;
if(cho4=='y'||cho4=='Y');
pg.showall();
}
void playgame::leaderboard()
{
 int i=0;
 playgame p;
 ifstream f;
 struct game
 {
   char pname[40];
   int tot;
 }g[200], temp;

 f.open("quizdetails.dat", ios::in|ios::binary);
 cout<<"PLAYER\t\t\t\tSCORE"<<endl;
 while(f.read((char*)&p, sizeof(p))&& !f.eof())
 {
   g[i].tot=p.rettotal();
   strcpy(g[i].pname,p.retplayername());
   i++;
  }

 for(int j=0; j<i; j++)
 {
  for(int k=0; k<i-j-1; k++)
  {
   if(g[k].tot<g[k+1].tot)
   {
    temp =g[k];
    g[k]=g[k+1];
    g[k+1]= temp;
    }
  }
 }

 for(int m=0; m<5; m++)
 {
  cout<<setiosflags(ios::left)<<setw(30)<<g[m].pname<<"\t"<<setiosflags(ios::left)<<setw(8)<<g[m].tot<<endl;
 }
}

void playgame::showall()
{int i=0;
 playgame p;
 ifstream f;
 clrscr();
 f.open("quizdetails.dat", ios::in|ios::binary);
 cout<<"GAME NO\tGAMEDATE \tPLAYER\t\t\t   SCORE"<<endl;

 while(f.read((char*)&p, sizeof(p))&& !f.eof())
 { if(i%15==0 && i!=0)
   {
   getch();
   clrscr();
   }
   cout<<p.retgameno()<<"\t"<<p.retgamedate()<<"\t"<<setiosflags(ios::left)<<setw(30)<<p.retplayername()<<setiosflags(ios::left)<<setiosflags(ios::right)<<p.rettotal()<<endl;
   i++;
 }
}

class quiz
{ char user[40];
char pass[40];
public:
void doscreen();
void mainmenu(char*);
void adminmenu();
char* readuser();
void createuser();

char* retuser()
{return user;}

char* retpassword()
{ return pass;}


void setusername(char* u)
{
strcpy(user,u);
}
void setpass()
{ cout<< "\nEnter Password: ";
cin>> pass;
}
void setpass(char *p)
{
strcpy(pass,p);
}
void display()
{ cout<<user;}
};
char* quiz::readuser()
{
quiz q;
char password[40];
ifstream log;
char buf[40];
log.open("login.dat",ios::in|ios::binary);
clrscr();
cout<<"\t\t\t****LOGIN***";
cout<<"\nEnter userid: ";
gets(user);
int found=0;
while(log.read((char*)&q,sizeof(q)) && found==0 )
{
 if(strcmpi(q.retuser(),user)==0)
 {
   found++;
   strcpy(buf,q.retpassword());
   break;
  }
}
log.close();
cout<<"\nEnter password:";
int i=0;
int flag=0;
while(flag==0)
{
  char ch=getch();
  password[i]=ch;
  if(ch==char(13))
  {
    flag++;
  }
  else if(ch=='\b')
  {
    if(i>0)
    {
      cout<<'\b';
      cout<<' ';
      cout<<'\b';
      i--;
      continue;
    }
   }
   else
   {
     password[i]=ch;
     cout<<"*";
     i++;
   }
}
password[i++]='\0';
if (found==0)
{
  ofstream login;
  login.open("login.dat",ios::out|ios::binary|ios::app);
  q.setusername(user);
  q.setpass(password);
  login.write((char*)&q,sizeof(q));
  getch();
  login.close();
}
if(strcmpi(user,"admin")==0)
{
  if(strcmpi(buf,"adminshn")==0)
  {
    cout<<"\nUsername and password is correct.";
    adminmenu();
  }
  else
  {
    cout<<endl;
    cout<<"Wrong password"<<endl;
    cout<<"Forgot password ? ";
    char cho3;
    cin>>cho3;
    if(cho3=='y'||cho3=='Y')
    {
      cout<<" We have mailed you your password ";
      return " ";
    }

   }
}
return user;
}
/********************************************************************/
void quiz:: mainmenu(char* u)
{
playgame pg;
pg.setusername(u);
clrscr();
int num, opt;
cout<<"\t\t\t******MAIN MENU******"<<endl;
cout<<"\t******Quiz time: ENTER YOUR CATEGORY FOR QUESTIONS:******"<<endl;
cout<<"1.Science."<<endl;
cout<<"2.History."<<endl;
cout<<"3.General Knowledge."<<endl;
cout<<"4.Leaderboard."<<endl;
cout<<"5.All the games played."<<endl;
cout<<"6.Exit."<<endl;
cin>>opt;
if(opt==6)  //exit is selected
{
  return;
}
if(opt==4)
{
pg.leaderboard();
getch();
return;
}
if(opt==5)
{
pg.showall();
getch();
return;
}

cout<<"Enter 1 for Basic and 2 for Pro"<<endl;
cin>>num;
switch(num)
{
case 1:
pg.quiz(opt);
break;
case 2:
pg.pro(opt);
break;
case 3:
break;
case 6:
break;
default:
cout<<"Invalid entry";
}
return;
}
void quiz::adminmenu()
{

ofstream fout;
ifstream fin;
fstream finout;
int lastqno=0;
char ch='y';
int cho;
qb q1;
do
{
clrscr();
cout<<"Welcome Admin"<<endl;
cout<<"1. Enter new qs "<<endl;
cout<<"2. Modify qs "<<endl;
cout<<"3. Delete qs "<<endl;
cout<<"4. Display "<<endl;
cout<<"5. Exit "<<endl;
cout<<"Enter your choice "<<endl;
cin>>cho;
switch (cho)
{
case 1:
  int cho1;
  cout<<" 1. Enter new Science question."<<endl;
  cout<<" 2. Enter new History question."<<endl;
  cout<<" 3. Enter new GK question."<<endl;
  cout<<" 4. Exit."<<endl;
  cout<<" Enter your choice"<<endl;
  cin>>cho1 ;
  ch='y';
  switch(cho1)
  {
    case 1:
      while (ch=='y'||ch=='Y')
      {
	fin.open("qs.dat",ios::in | ios::binary | ios::ate);
	fout.open("qs.dat",ios::out|ios::binary|ios::app);
	if(!fin)
	{
	  lastqno=1;
	}
	else
	{
	 long p=fin.tellg();
	 fin.seekg(p-1*sizeof(q1));
	 fin.read((char*)&q1, sizeof(q1));
	 lastqno=q1.retqno()+1;
	}
	fin.close();
	q1.setqno(lastqno);
	q1.enterqs();
	fout.write((char*)&q1,sizeof(q1));
	fout.close();
	cout<<"Do you want to add another new question?"<<endl;
	cin>>ch;
      }
      break;
    case 2:
      while (ch=='y'||ch=='Y')
      {
	fin.open("qh.dat",ios::in | ios::binary | ios::ate);
	fout.open("qh.dat",ios::out|ios::binary|ios::app);
	if(!fin)
	{
	  lastqno=1;
	}
	else
	{
	 long p=fin.tellg();
	 fin.seekg(p-1*sizeof(q1));
	 fin.read((char*)&q1, sizeof(q1));
	 lastqno=q1.retqno()+1;
	}
	fin.close();
	q1.setqno(lastqno);
	q1.enterqs();
	fout.write((char*)&q1,sizeof(q1));
	fout.close();
	cout<<"Do you want to add another new question?"<<endl;
	cin>>ch;
      }
      break;
    case 3:
      while (ch=='y'||ch=='Y')
      {
	fin.open("qgk.dat",ios::in | ios::binary | ios::ate);
	fout.open("qgk.dat",ios::out|ios::binary|ios::app);
	if(!fin)
	{
	  lastqno=1;
	}
	else
	{
	 long p=fin.tellg();
	 fin.seekg(p-1*sizeof(q1));
	 fin.read((char*)&q1, sizeof(q1));
	 lastqno=q1.retqno()+1;
	}
	fin.close();
	q1.setqno(lastqno);
	q1.enterqs();
	fout.write((char*)&q1,sizeof(q1));
	fout.close();
	cout<<"Do you want to add another new question?"<<endl;
	cin>>ch;
      }
      break;
     case 4:
     break;
    }
    break;
/************************************************/
case 2:  //modifying the questions and answers
  int cho2;
  cout<<" 1. Modify Science question."<<endl;
  cout<<" 2. Modify History question."<<endl;
  cout<<" 3. Modify GK question."<<endl;
  cout<<" 4. Exit."<<endl;
  cout<<" Enter your choice"<<endl;
  cin>>cho2 ;
  int qnum, flag=0;
  long pos;
  ch='y';
  switch(cho2)
  {
    case 1:
      while (ch=='y'||ch=='Y')
      {
	cout<<"Enter question number to modify:"<<endl;
	cin>>qnum;
	if(q1.searchqno(qnum, "qs.dat")==0)
	{
	  flag=1;

	  break;
	}
	finout.open("qs.dat",ios::in | ios::out|ios::binary);
	while(!finout.eof() && flag==0)
	{
	  finout.read((char*) &q1, sizeof(q1));
	  pos=finout.tellg();
	  if(qnum==q1.retqno())
	  {
	    cout<<q1.retqno();
	    q1.displayqs();
	    cout<<"Modifying  : "<<endl;
	    q1.setqno(qnum);
	    q1.enterqs();
	    finout.seekg(pos-1*sizeof(q1));
	    finout.write((char*)&q1,sizeof(q1));
	    cout<<"Record updated!";
	    flag++;
	  }                   	}
	  finout.close();
	  if(flag==1)
	  {
	   cout<<"Record not found";
	  }
	  cout<<"Do you want to modify another new question?"<<endl;
	  cin>>ch;
	  flag=0;
	}
     break;
     case 2:
     while (ch=='y'||ch=='Y')
      {
	cout<<"Enter question number to modify:"<<endl;
	cin>>qnum;

	if(q1.searchqno(qnum, "qh.dat")==0)
	{
	  flag=1;

	  break;
	}
	finout.open("qh.dat",ios::in | ios::out|ios::binary);
	while(!finout.eof() && flag==0)
	{
	  finout.read((char*) &q1, sizeof(q1));
	  pos=finout.tellg();
	  if(qnum==q1.retqno())
	  {
	    cout<<q1.retqno();
	    q1.displayqs();
	    cout<<"Modifying  : "<<endl;
	    q1.setqno(qnum);
	    q1.enterqs();
	    finout.seekg(pos-1*sizeof(q1));
	    finout.write((char*)&q1,sizeof(q1));
	    cout<<"Record updated!";
	    flag++;
	  }                   	}
	  finout.close();
	  if(flag==1)
	  {
	   cout<<"Record not found";
	  }
	  cout<<"Do you want to modify another new question?"<<endl;
	  cin>>ch;
	  flag=0;
	}
     break;
      /*	while (ch=='y'||ch=='Y')
      {
	cout<<"Enter question number to modify:"<<endl;
	cin>>qnum;
	if(q1.searchqno(qnum, "qh.dat")==0)
	{
	  flag=1;
	  break;
	}
	finout.open("qh.dat",ios::in | ios::out|ios::binary);
	while(!finout.eof() && flag==0)
	{
	  finout.read((char*) &q1, sizeof(q1));
	  pos=finout.tellg();
	  if(qnum==q1.retqno())
	  {
	    cout<<q1.retqno();
	    q1.displayqs();
	    cout<<"Modifying  : "<<endl;
	    q1.setqno(qnum);
	    q1.enterqs();
	    finout.seekg(pos-1*sizeof(q1));
	    finout.write((char*)&q1,sizeof(q1));
	    cout<<"Record updated!";
	    flag++;
	  }                   	}
	  finout.close();
	  if(flag==0)
	  {
	   cout<<"Record not found";
	  }
	  cout<<"Do you want to modify another new question?"<<endl;
	  cin>>ch;
	  flag=0;
	}
	break;  */
     case 3:
	while (ch=='y'||ch=='Y')
	{
	  cout<<"Enter question number to modify:"<<endl;
	  cin>>qnum;
	  if(q1.searchqno(qnum, "qgk.dat")==0)
	  {
	    flag=1;
	    break;
	  }
	  finout.open("qgk.dat",ios::in | ios::out|ios::binary);
	  while(!finout.eof() && flag==0)
	  {
	    finout.read((char*) &q1, sizeof(q1));
	    pos=finout.tellg();
	    if(qnum==q1.retqno())
	    {
	      cout<<q1.retqno();
	      q1.displayqs();
	      cout<<"Modifying  : "<<endl;
	      q1.setqno(qnum);
	      q1.enterqs();
	      finout.seekg(pos-1*sizeof(q1));
	      finout.write((char*)&q1,sizeof(q1));
	      cout<<"Record updated!";
	      flag++;
	    }                   	}
	    finout.close();
	    if(flag==1)
	    {
	      cout<<"Record not found";
	    }
	    cout<<"Do you want to modify another new question?"<<endl;
	    cin>>ch;
	    flag=0;
	  }
	break;
     case 4:
	break;
    }
break;
case 3:   //deleting the questions
  int cho4;
  cout<<" 1. Delete Science question."<<endl;
  cout<<" 2. Delete History question."<<endl;
  cout<<" 3. Delete GK question."<<endl;
  cout<<" 4. Exit."<<endl;
  cout<<" Enter your choice"<<endl;
  cin>>cho4 ;
  getch();
  switch(cho4)
  {
    case 1:
      ch='y';
      while (ch=='y'||ch=='Y')
      {
	cout<<"Enter question number to delete:"<<endl;
	cin>>qnum;
	if(q1.searchqno(qnum, "qs.dat")==0)
	{
	  flag=1;
	  break;
	}
	fin.open("qs.dat",ios::in | ios::binary);
	finout.open("temps.dat", ios::out | ios::in |ios::binary);
	fin.seekg(0);
	while((!fin.eof()) && fin.read((char*) &q1, sizeof(q1)))
	{
	 if(q1.retqno()!=qnum)
	  {
	    finout.write((char*) &q1, sizeof(q1));
	  }
	}
	finout.close();
	fin.close();//stoppedm here
	char chD=' ';
	cout<<"Are you sure you want to delete??(Yy/Nn)"<<endl;
	cin>>chD;
	if(chD=='Y' ||chD=='y')
	{
	cout<<"Deleting...";
	cout<<q1.retqno();
	q1.displayqs();
	remove("qs.dat");
	rename("temps.dat", "qs.dat");
	}
	if(flag==1)
	  {
	   cout<<"Record not found"<<endl;
	  }
	cout<<"Do you want to delete another question?"<<endl;
	  cin>>ch;
	  flag=0;
      }
      break;
      case 2:
      ch='y';
      while (ch=='y'||ch=='Y')
      {
	cout<<"Enter question number to delete:"<<endl;
	cin>>qnum;
	if(q1.searchqno(qnum, "qh.dat")==0)
	{
	  flag=1;
	  break;
	}
	fin.open("qh.dat",ios::in | ios::binary);
	finout.open("temph.dat", ios::out | ios::in |ios::binary);
	fin.seekg(0);
	while((!fin.eof()) && fin.read((char*) &q1, sizeof(q1)))
	{
	 if(q1.retqno()!=qnum)
	  {
	    finout.write((char*) &q1, sizeof(q1));
	  }
	}
	finout.close();
	fin.close();//stopped here
	char chD=' ';
	cout<<"Are you sure you want to delete??(Yy/Nn)"<<endl;
	cin>>chD;
	if(chD=='Y' ||chD=='y')
	{
	  cout<<"Deleting...";
	  cout<<q1.retqno();
	  q1.displayqs();
	  remove("qh.dat");
	  rename("temph.dat", "qh.dat");
	}
      if(flag==1)
      {
      cout<<"Record not found";
      }
      cout<<"Do you want to delete another question?"<<endl;
      cin>>ch;
      flag=0;
      }
      break;
      case 3:
      ch='y';
      while (ch=='y'||ch=='Y')
      {
	cout<<"Enter question number to delete:"<<endl;
	cin>>qnum;
	if(q1.searchqno(qnum, "qgk.dat")==0)
	{
	  flag=1;
	  break;
	}
	fin.open("qgk.dat",ios::in | ios::binary);
	finout.open("tempgk.dat", ios::out | ios::in |ios::binary);
	fin.seekg(0);
	while((!fin.eof()) && fin.read((char*) &q1, sizeof(q1)))
	{
	 if(q1.retqno()!=qnum)
	  {
	    finout.write((char*) &q1, sizeof(q1));
	  }
	}
	finout.close();
	fin.close();//stoppedm here
	char chD=' ';
	cout<<"Are you sure you want to delete??(Yy/Nn)"<<endl;
	cin>>chD;
	if(chD=='Y' ||chD=='y')
	{
	cout<<"Deleting...";
	cout<<q1.retqno();
	q1.displayqs();
	remove("qgk.dat");
	rename("tempgk.dat", "qgk.dat");
	}
	if(flag==1)
	  {
	   cout<<"Record not found";
	  }
	  cout<<"Do you want to delete another question?"<<endl;
	  cin>>ch;
	  flag=0;
      }
      break;
      case 4:
      break;
     }
break;
case 4:
  int cho3;
  cout<<" 1. Display Science questions."<<endl;
  cout<<" 2. Display History questions."<<endl;
  cout<<" 3. Display GK questions."<<endl;
  cout<<" 4. Exit."<<endl;
  cout<<" Enter your choice"<<endl;
  cin>>cho3 ;
  switch(cho3)
  {
    case 1:
    fin.open("qs.dat", ios::in|ios::binary);
    if(!fin)
    {
      cout<<"File cannot be opened!"<<endl;
      getch();
      break;
    }
    else
    {
      while(fin.read((char*)&q1,sizeof(q1)))
      {
       cout<<q1.retqno();
       q1.displayqs();
      }
    }
    fin.close();
    getch();
    break;
    case 2:
    fin.open("qh.dat", ios::in|ios::binary);
    if(!fin)
    {
      cout<<"File cannot be opened!"<<endl;
      getch();
      break;
    }
    else
    {
      while(fin.read((char*)&q1,sizeof(q1)))
      {
       cout<<q1.retqno();
	q1.displayqs();
      }
    }
    fin.close();
    getch();
    break;
    case 3:
    fin.open("qgk.dat", ios::in|ios::binary);
    if(!fin)
    {
      cout<<"File cannot be opened!"<<endl;
      getch();
      break;
    }
    else
    {
      while(fin.read((char*)&q1,sizeof(q1)))
      {
	cout<<q1.retqno();
	q1.displayqs();
      }
    }
    fin.close();
    getch();
    break;
 }
break;
case 5:
break;
}
}while(cho<5);
return;
}
void quiz::doscreen()
{
int i;
int g=DETECT, d;
initgraph(&g, &d, "c:\\turboc3\\bgi");
cleardevice();
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 10);
setbkcolor(rand());
setcolor(3);
outtextxy(200,100,"QUIZ");
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
outtextxy(500,250, "By");
outtextxy(500,300,"Harman,");
outtextxy(500,325,"Nachiket");
outtextxy(500,350,"And");
outtextxy(500,375,"Shruti");
getch();
cleardevice();
setcolor(7);
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
outtextxy(30,150,"Welcome Player,");
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
outtextxy(30,200,"Read all instructions carefully.");
outtextxy(30,225,"Proceed only once you have fully understood.");
outtextxy(30,250,"You may contact the admins if any discrapancy arises");
getch();
cleardevice();
setcolor(7);
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
outtextxy(0,100,"This quiz consists of 20 questions.");
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
outtextxy(0,150,"Having 3 categories - Science, History and GK.");
outtextxy(0,175,"It also has 2 levels - Basic and Pro.");
getch();
cleardevice();
setcolor(7);
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
outtextxy(30,75,"Marking scheme for Basic level -");
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
outtextxy(30,125,"Correctly answered question -  +4");
outtextxy(30,150,"Incorrectly answered question -  -1");
outtextxy(30,175,"For a skipped or unattempted question - No negative marking");
outtextxy(30,200,"Not time based.");
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
outtextxy(30,250,"Marking scheme for Pro level -");
settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
outtextxy(30,300,"Correctly answered question -  +5");
outtextxy(30,325,"Incorrectly answered question -  -2");
outtextxy(30,350,"For a skipped or unattempted question -  -1");
outtextxy(30,375,"Time based - 10 sec per qs.");
getch();
closegraph();
}



void main()
{
char buf[40];
quiz q;
playgame pg;
clrscr();
strcpy(buf,q.readuser());
//q.doscreen();
q.mainmenu(buf);
cout<<"Hope you enjoyed your game!!Bye";
getch();
}