





	  //		  PROJECT   RAILWAY TICKET  RESERVATION


	  # include <iostream.h>
	  # include <fstream.h>
	  # include <string.h>
	  # include <stdlib.h>
	  # include <stdio.h>
	  # include <ctype.h>
	  # include <dos.h>
	  # include <conio.h>
	  # include <process.h>


	  class TICKET
	  {

		private:
			  void ADD_RECORD(char[10],char[15],char[15],int,int);

		public:
			  void ADDITION(void);
			  void ENQUIRY(void);
			  char *TRAINNO(int);

		protected:

			  char TRNno[10],from[15],to[15];
			  int ecofair,exefair;

	  };

	  //THIS CLASS CONTROLS ALL THE FUNCTIONS RELATED TO PASSENGERS

	  class PASSENGER
	  {
		public:
			  void ADD_RECORD(int,int,char[26],char[36],int,char,char);
			  void DELETE_TICKET(int);
			  int DELETE_TRAIN(int);
			  void LIST(void);
			  int LAST_TICKETNO(void);
			  int SEATS(int);
			  int FOUND(int);
			  char *NAME(int);
			  void PASS_INFO();
			  void MODIFY();
		protected:
			  char Class,name[26],address[36],sex;
			  int slno,age,ticketno;
	  };

	  //THIS IS THE DERIVED CLASS WHICH CONTROLS ALL THE FUNCTIONS
	  //RELATED TO RESERVATION,CANCELLATION,ETC.

	  class RESERVE : public TICKET,public PASSENGER
	  {
		public:
			  void RESERVATION(void);
			  void CANCELLATION(void);
			  void DISPLAY_TICKET(void);
			  void DELETE_ALL(void);
	  };

	  //FUNCTION TO ADD GIVEN DATA IN THE TICKET FILE(TICKET.DAT)

	  void TICKET :: ADD_RECORD(char t_TRNno[10],char t_from[15],char t_to[15],int t_ecofair,int t_exefair)
	  {
		fstream file;
		file.open("TICKET.DAT",ios::app);
		strcpy(TRNno,t_TRNno);
		strcpy(from,t_from);
		strcpy(to,t_to);
		ecofair = t_ecofair;
		exefair = t_exefair;
		file.write((char*)this,sizeof(TICKET));
		file.close();
	  }

	  //FUNCTION TO RETURN TRAIN NO. FOR THE GIVEN S.NO

	  char *TICKET :: TRAINNO(int sno)
	  {
		fstream file;
		file.open("TICKET.DAT",ios::in);
		int count = 1;
		while(file.read((char*) this,sizeof(TICKET)))
		{
		     if (sno == count)
			break;

		     count++;
		}
		file.close();
		return TRNno;
	  }

	  //FUNCTION TO GIVE DATA TO ADD RECORDS IN THE TICKET FILE

	  void TICKET :: ADDITION(void)
	  {
	       fstream file;
	       file.open("TICKET.DAT",ios::in);
	       if (!file.fail() )
		  return;
	       file.close();
		   ADD_RECORD("SHATABDI","DELHI","MUMBAI",700,1200);
		   ADD_RECORD("RAJDHANI","MUMBAI","DELHI",700,1200);
		   ADD_RECORD("HIMALYAN","DELHI","CALCUTTA",800,1100);
		   ADD_RECORD("KARNATKA","CALCUTTA","DELHI",800,1100);
		   ADD_RECORD("PASHCHIM","DELHI","MADRAS",1100,1800);
		   ADD_RECORD("CHENNAI ","MADRAS","DELHI",1100,1800);
		   ADD_RECORD("MUMBAI  ","MUMBAI","CALCUTTA",1000,1600);
		   ADD_RECORD("CENTRAL ","CALCUTTA","MUMBAI",1000,1600);
		   ADD_RECORD("SOUTHERN","MUMBAI","MADRAS",800,1100);
		   ADD_RECORD("SOUTHERN","MADRAS","MUMBAI",800,1100);
		   ADD_RECORD("EASTERN ","CALCUTTA","MADRAS",900,1300);
		   ADD_RECORD("EASTERN ","MADRAS","CALCUTTA",900,1300);
	  }

	  //FUNCTION TO DISPLAY LIST OF TRAINS

	  void TICKET :: ENQUIRY(void)
	  {
	       clrscr();
	       fstream file;
	       file.open("TICKET.DAT",ios::in);
	       gotoxy(30,3);
	       cout<<"LIST OF THE TRAINS";
	       gotoxy(30,4);
	       cout<<"******************";
	       gotoxy(12,7);
	       cout<<"Sno.   TRAIN NAME      FROM         TO      1ST CLASS  AC CLASS";
	       int row = 9,sno = 1;
	       while(file.read((char*)this, sizeof(TICKET)))
	       {
		     gotoxy(12,row);
		     cout<<sno;
		     gotoxy(20,row);
		     cout<<TRNno;
		     gotoxy(35,row);
			 cout<<from;
		     gotoxy(47,row);
		     cout<<to;
		     gotoxy(58,row);
		     cout<<ecofair;
		     gotoxy(68,row);
		     cout<<exefair;
		     row++;
		     sno++;
	       }
	       file.close();
	  }

	  //FUNCTION TO RESERVE TICKET FOR THE PASSENGERS

	  void RESERVE :: RESERVATION(void)
	  {
	       clrscr();
	       ENQUIRY();
	       char t1[15],pclass,pname[26],paddress[36],psex,pTRNno[10];
	       int t2,valid,page,tno,sno;
	       PASSENGER p;
	       tno = p.LAST_TICKETNO() + 1;
	       do
	       {
		    valid = 1;
		    gotoxy(3,45);
		    clreol();
		    cout<<"PRESS <ENTER> TO EXIT";
		    gotoxy(3,22);
		    clreol();
		    cout<<"ENTER THE SNO. OF THE TRAIN : ";
		    gets(t1);
		    t2 = atoi(t1);
		    sno = t2;
		    if(strlen(t1) == 0)
		      return;
		    if(sno < 1 || sno > 12)
		    {
		      valid = 0;
			  gotoxy(3,23);
		      clreol();
		      cout<<"ENTER CORRECTLY";
		      getch();
		    }
	       }    while(!valid);

	       int i=1;

	       fstream file;
	       file.open("TICKET.DAT",ios::in);

	       while(file.read((char*)this, sizeof(TICKET)))
	       {
		    if(sno == i)
		      break;
		    i++;
	       }
	       file.close();
	       strcpy(pTRNno,TRNno);
		   if(p.SEATS(sno)>=250)
	       {
		 gotoxy(5,21);
		 cout<<"\7Sorry! SEATS ARE NOT AVAILABLE";
		 getch();
		 return;
	       }
	       gotoxy(3,23);
	       clreol();
	       do
	       {
		    gotoxy(3,21);
		    clreol();
		    gotoxy(3,25);
		    cout<<"BY WHICH CLASS YOU WOULD LIKE TO TRAVEL : ";
		    gotoxy(3,27);
		    cout<<"E=ECONOMIC,X=EXECUTIVE : ";
			    pclass = getche();
		    pclass = toupper(pclass);
		    if(pclass == 13)
		       return;
	       }     while(pclass !='E' && pclass !='X');

	       clrscr();
	       gotoxy(72,3);
	       cout<<"<0>-EXIT";
	       gotoxy(34,2);
	       cout<<"RESERVATION";
	       gotoxy(5,5);
	       cout<<"NAME     : ";
	       gotoxy(5,6);
	       cout<<"ADDRESS  : ";
	       gotoxy(5,7);
	       cout<<"SEX M/F  : ";
	       gotoxy(5,8);
	       cout<<"AGE      : ";

	       do
	       {
		    valid = 1;
		    gotoxy(5,25);
		    clreol();
			cout<<"ENTER THE NAME OF THE PASSENGER";
		    gotoxy(15,5);
		    clreol();
		    gets(pname);
		    if(pname[0] == '0')
		      return;
		    if(strlen(pname) < 1 || strlen(pname) > 25)
		    {
		      valid = 0;
		      gotoxy(5,25);
		      clreol();
		      cout<<"\7ENTER CORRECTLY {RANGE : 1 TO 25}";
		      getch();
		    }
	       }    while(!valid);

	       do
	       {
		    valid = 1;
		    gotoxy(5,25);
			clreol();
		    cout<<"ENTER THE ADDRESS OF THE PASSENGER";
		    gotoxy(15,6);
		    clreol();
		    gets(paddress);
		    if(paddress[0] == '0')
		      return;
		    if(strlen(paddress) < 1 || strlen(paddress) > 35)
		    {
		      valid = 0;
		      gotoxy(5,25);
		      clreol();
		      cout<<"\7ENTER CORRECTLY {RANGE : 1 TO 35}";
		      getch();
		    }
	       }    while(!valid);

	       do
	       {
		    gotoxy(5,25);
			clreol();
		    cout<<"ENTER THE SEX OF THE PASSENGER";
		    gotoxy(15,7);
		    clreol();
		    psex = getche();
		    psex = toupper(psex);
		    if(psex == '0')
		      return;
	       }    while(psex !='M' && psex !='F' );

	       do
	       {
		    valid = 1;
		    gotoxy(5,25);
		    clreol();
		    cout<<"ENTER THE AGE OF THE PASSENGER";
		    gotoxy(15,8);
		    clreol();
		    gets(t1);
		    t2 = atoi(t1);
			page = t2;
		    if(t1[0] == '0')
		      return;
		    if(page < 1 || page > 100)
		    {
		      valid = 0;
		      gotoxy(5,25);
		      clreol();
		      cout<<"\7ENTER CORRECTLY ";
		      getch();
		    }
	       }    while(!valid);



	       clrscr();
	       gotoxy(11,4);
	       cout<<"****************************************************";
	       gotoxy(11,21);
	       cout<<"****************************************************";
	       gotoxy(33,6);
	       cout<<"TICKET NO. : "<<tno;
		   gotoxy(17,9);
	       cout<<from<<" TO "<<to;
	       gotoxy(45,9);
	       cout<<"TRAIN NAME : "<<pTRNno;
	       gotoxy(20,11);
	       cout<<"PASSENGER NAME : "<<pname;
	       gotoxy(20,13);
	       cout<<"ADDRESS : "<<paddress;
	       gotoxy(20,15);
	       cout<<"SEX : "<<psex;
	       gotoxy(20,17);
	       cout<<"AGE : "<<page;
	       gotoxy(45,19);
	       if(pclass == 'E')
		 cout<<"TOTAL FAIR : "<<ecofair;
	       else
		 cout<<"TOTAL FAIR : "<<exefair;

	       p.ADD_RECORD(tno,sno,pname,paddress,page,psex,pclass);
	       getch();
	  }

	  // FUNCTION TO ADD THE GIVEN DATA IN THE PASSENGER'S FILE

	  void PASSENGER :: ADD_RECORD (int tno,int sno,char pname[26],char paddress[36],int page,char psex,char pclass)
	  {
	       fstream file;
	       file.open("PASS.DAT",ios::app);
	       ticketno = tno;
	       slno = sno;
	       strcpy(name,pname);
	       strcpy(address,paddress);
	       age = page;
	       sex = psex;
	       Class = pclass;
	       file.write((char*)this,sizeof(PASSENGER));
	       file.close();
	  }
	  void PASSENGER :: MODIFY()
	    {
		int tcno;
		char t1[15],pclass,pname[26],paddress[36],psex,pTRNno[10];
	       int t2,valid,page,tno,sno;


		PASS_INFO();
		cout<<"\nENTER THE TICKET NUMBER OF THE PASSENGER";
		cin>>tcno;
		fstream file;
		file.open("PASS.DAT",ios::in|ios::out);
		int m=0;
		int l;
		file.read((char*)this,sizeof(PASSENGER));
		while(!file.eof())
		  {    m++;
		       if(tcno==ticketno)
			 {
			  l=(m-1)*sizeof(PASSENGER);
			  cout<<l;
			  getch();
			  clrscr();
			  gotoxy(72,3);
			  cout<<"<0>-EXIT";
			  gotoxy(34,2);
			  cout<<"RESERVATION";
			  gotoxy(5,5);
			  cout<<"NAME     : ";
			  gotoxy(5,6);
			  cout<<"ADDRESS  : ";
			  gotoxy(5,7);
			  cout<<"SEX M/F  : ";
			  gotoxy(5,8);
			  cout<<"AGE      : ";

		    gotoxy(5,25);
		    clreol();
		    cout<<"ENTER THE NAME OF THE PASSENGER";
		    gotoxy(15,5);
		    clreol();
		    gets(pname);
			gotoxy(5,25);
		    clreol();
		    cout<<"ENTER THE ADDRESS OF THE PASSENGER";
		    gotoxy(15,6);
		    clreol();
		    gets(paddress);
		    gotoxy(5,25);
		    clreol();
		    cout<<"ENTER THE SEX OF THE PASSENGER";
		    gotoxy(15,7);
		    clreol();
		    psex = getche();
		    psex = toupper(psex);

		    gotoxy(5,25);
		    clreol();
		    cout<<"ENTER THE AGE OF THE PASSENGER";
		    gotoxy(15,8);
		    clreol();
		    gets(t1);
			t2 = atoi(t1);
		    page = t2;
		    cout<<"CLASS:E(ECONOMIC) OR X(EXECUTIVE)";
		 pclass=getche();
		 if(strlen(paddress)!=0)
		strcpy(address,paddress);
		if(strlen(pname)!=0)
		strcpy(name,pname);
		if(strlen(t1)!=0)
		age=page;
		if(psex!=13)
		sex=psex;
		if(pclass!=13)
		Class=pclass;
		file.seekp(l);
		file.write((char*)this,sizeof(PASSENGER));
		file.close();
		return;
	      }
	      else
		  file.read((char*)this,sizeof(PASSENGER));

	   }



     }




	  void PASSENGER :: PASS_INFO()
	    {
	       fstream file;
	       file.open("PASS.DAT",ios::in);

	       cout<<"                         PASSENGERS INFORMATION\n";
	       cout<<"                       **************************\n";
	       gotoxy(2,4);
	       cout<<"T.NO.";
		   gotoxy(11,4);
	       cout<<"TRN NO.";
	       gotoxy(25,4);
	       cout<<"NAME";
	       gotoxy(48,4);
	       cout<<"ADDRESS";
	       gotoxy(66,4);
	       cout<<"AGE";
	       gotoxy(70,4);
	       cout<<"SEX";
	       gotoxy(74,4);
	       cout<<"CLASS";
	       gotoxy(1,5);
	       cout<<"*******************************************************************************";
	       int tno,sno,page;
	       char pname[26],paddress[36],psex,pclass,pTRNno[10];
	       int i=6;
	       while(file.read((char*)this,sizeof(PASSENGER)))
	       {
		tno=ticketno;
		sno=slno;
	       strcpy(pname,name);
	       strcpy(paddress,address);
	       page = age;
	       psex = sex;
	       pclass = Class;
	       gotoxy(2,i);
	       cout<<tno;
	       gotoxy(11,i);
	       cout<<sno;
	       gotoxy(20,i);
	       cout<<pname;
	       gotoxy(45,i);
	       cout<<paddress;
	       gotoxy(67,i);
	       cout<<page;
	       gotoxy(71,i);
	       cout<<psex;
	       gotoxy(77,i);
	       cout<<pclass;

	       i++;
	       }
	       file.close();
	  }
	  //THIS FUNCTION RETURNS THE LAST TICKET NO. IN THE PASSENGER FILE

	  int PASSENGER ::LAST_TICKETNO(void)
	  {
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       int count = 0;
	       while(file.read((char*)this,sizeof(PASSENGER)))
		    count = ticketno;
	       file.close();
	       return count;
	  }

	  //THIS FUNCTION RETURNS TOTAL NO. OF SEATS IN THE PASSENGER FILE

	  int PASSENGER :: SEATS(int sno)
	  {
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       int count = 0;
	       while(file.read((char*)this,sizeof(PASSENGER)))
	       {
		    if(sno == slno)
		    count++;
	       }
	       file.close();
	       return count;
	  }

	  //THIS FUNCTION RETURNS 0 IF THE TICKET NO. IS NOT FOUND IN THE
	  //PASSENGER FILE

	  int PASSENGER :: FOUND(int tno)
	  {
	       fstream file;
		   file.open("PASS.DAT",ios::in);
	       int found = 0;

	       while(file.read((char*)this,sizeof(PASSENGER)))
	       {
		    if(tno == ticketno)
		    {
		      found = 1;
		      break;
		    }
	       }
	       file.close();
	       return found;
	  }

	  //THIS FUNCTION RETURNS PASSENGER'S NAME FOR THE GIVEN TICKETNO.

	  char *PASSENGER :: NAME(int tno)
	  {
	       fstream file;
		   file.open("PASS.DAT",ios::in);
	       while(file.read((char*)this,sizeof(PASSENGER)))
	       {
		    if(tno == ticketno)
		      break;
	       }
	       file.close();
	       return name;
	  }

	  //THIS FUNCTION DISPLAYS THE LIST OF THE PASSENGERS

	  void PASSENGER :: LIST (void)
	  {
	       clrscr();
	       char t1[10];
	       int t2,sno,valid;
	       TICKET ticket;
	       ticket.ENQUIRY();
	       do
		   {
		    valid = 1;
		    gotoxy(3,23);
		    clreol();
		    cout<<"PRESS <ENTER> TO EXIT";
		    gotoxy(3,20);
		    clreol();
		    cout<<"ENTER SNO.OF THE TRAIN WHOSE DETAILS YOU WANT";
		    gets(t1);
		    t2 = atoi(t1);
		    sno = t2;
		    if(strlen(t1) == 0)
		      return;
		    if(sno < 1 || sno > 12)
		    {
		      valid = 0;
		      gotoxy(3,23);
		      clreol();
		      cout<<"\7ENTER CORRECTLY";
		      getch();
			}
	       }    while(!valid);

	       clrscr();
	       int row = 8,found = 0,flag = 0;
	       char ch;
	       gotoxy(3,4);
	       cout<<"TRAIN NO.----> "<<ticket.TRAINNO(sno);
	       gotoxy(28,2);
	       cout<<"**LIST OF PASSENGERS**";
	       gotoxy(5,6);
	       cout<<"TICKET NO.  NAME                            CLASS ";
	       gotoxy(4,7);
	       cout<<"*******************************************************";
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       file.seekg(0,ios::beg);
	       while(file.read((char*)this,sizeof(PASSENGER)))
	       {
		    if(sno == slno)
			{
		      flag = 0;
		      delay(20);
		      found = 1;
		      gotoxy(5,row);
		      cout<<ticketno;
		      gotoxy(17,row);
		      cout<<name;
		      gotoxy(49,row);
		      if(Class == 'X')
			cout<<"EXECUTIVE";
		      else
			cout<<"ECONOMIC";
		      if(row == 21)
		      {
			flag = 1;
			row = 7;
			gotoxy(5,23);
			cout<<"PRESS ANY KEY TO CONTINUE OR PRESS <ESC>";
			ch = getch();
			if(ch == 27)
			  break;
			clrscr();
			gotoxy(32,3);
			cout<<"LIST OF PASSENGERS";
			gotoxy(2,5);
			cout<<"TICKET NO.  NAME                CLASS ";
		      }
		      else
			row++;
		    }
	       }
	       if(!found)
	       {
		 gotoxy(5,10);
		 cout<<"\7RECORDS NOT FOUND";
	       }
	       if(!flag)
	       {
		 gotoxy(5,23);
		 cout<<"PRESS ANY KEY TO CONTINUE....";
		 getch();
	       }
	       file.close();
	  }

	  //THIS FUNCTION DELETES PASSENGER RECORDS FOR THE GIVEN TICKET NO.

	  void PASSENGER :: DELETE_TICKET(int tno)
	  {
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       fstream temp;
	       temp.open("temp.dat",ios::out);
	       file.seekg(0,ios::beg);
	       while(!file.eof() )
	       {
		    file.read((char*)this,sizeof(PASSENGER));
		    if(file.eof() )
		      break;
			if(tno != ticketno)
		      temp.write((char*)this,sizeof(PASSENGER));
	       }
	       file.close();
	       temp.close();
	       file.open("PASS.DAT",ios::out);
	       temp.open("temp.dat",ios::in);
	       temp.seekg(0,ios::beg);
	       while(!temp.eof() )
	       {
		    temp.read((char*)this,sizeof(PASSENGER));
		    if(temp.eof() )
		      break;
		    file.write((char*)this,sizeof(PASSENGER));
	       }
	       file.close();
	       temp.close();
	  }

	  //THIS FUNCTION DELETES PASSENGER RECORDS FOR THE GIVEN TRAINNO.

	  int PASSENGER :: DELETE_TRAIN(int sno)
	  {
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       fstream temp;
	       temp.open("temp.dat",ios::out);
	       file.seekg(0,ios::beg);
	       int found = 0;
	       while(!file.eof() )
	       {
		    file.read((char*)this,sizeof(PASSENGER));
		    if(file.eof() )
		      break;
		    if(sno !=slno)
		      temp.write((char*)this,sizeof(PASSENGER));
		    else
		      found = 1;
	       }
	       file.close();
		   temp.close();
	       file.open("PASS.DAT",ios::out);
	       temp.open("temp.dat",ios::in);
	       temp.seekg(0,ios::beg);
	       while(!temp.eof() )
	       {
		    temp.read((char*)this,sizeof(PASSENGER));
		    if(temp.eof() )
		      break;
		    file.write((char*)this,sizeof(PASSENGER));
	       }
	       file.close();
	       temp.close();
	       return found;
	  }

	  //THIS FUNCTION CANCELS PASSENGER'S TICKET

	  void RESERVE ::CANCELLATION(void)
	  {
		   clrscr();
	       char t1[10],ch;
	       int t2,tno,valid;
	       do
	       {
		    valid = 1;
		    gotoxy(3,23);
		    clreol();
		    cout<<"PRESS <ENTER> TO SEE LIST OR 0 TO EXIT ";
		    gotoxy(3,20);
		    clreol();
		    cout<<"ENTER TICKETNO. OF PASSENGER TO CANCEL THE TICKET";
		    gets(t1);
		    t2 = atoi(t1);
		    tno = t2;
		    if(t1[0] == '0')
		      return;
		    if(strlen(t1) == 0)
		    {
		      valid = 0;
			  LIST();
		      clrscr();
		    }
		    if(!FOUND(tno) && valid)
		    {
		      valid = 0;
		      gotoxy(3,23);
		      clreol();
		      cout<<"\7RECORD NOT FOUND";
		      getch();
		    }
	       }    while(!valid);


	       //PAGE 11

	       clrscr();
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       while(file.read((char*)this,sizeof(PASSENGER)))
			if(ticketno == tno)
		      break;
	       file.close();
	       int i = 1;
	       file.open("TICKET.DAT",ios::in);
	       while(file.read((char*)this,sizeof(TICKET)))
	       {
		    if(slno == i)
		      break;
		    i++;
	       }
	       file.close();
	       PASSENGER p;
	       gotoxy(11,4);
	       cout<<"****************************************************";
	       gotoxy(11,21);
	       cout<<"****************************************************";
	       gotoxy(33,6);
	       cout<<"TICKET NO. : "<<tno;
	       gotoxy(17,9);
		   cout<<from<<" TO "<<to;
	       gotoxy(45,9);
	       cout<<"TRAIN NO. : "<<TRNno;
	       gotoxy(20,11);
	       cout<<"PASSENGER NAME : "<<p.NAME(tno);
	       gotoxy(20,13);
	       cout<<"ADDRESS : "<<address;
	       gotoxy(20,15);
	       cout<<"SEX : "<<sex;
	       gotoxy(20,17);
	       cout<<"AGE : "<<age;
	       gotoxy(45,19);
	       if(Class == 'E')
		 cout<<"TOTAL FAIR : "<<ecofair;
	       else
		 cout<<"TOTAL FAIR : "<<exefair;
	       do
	       {
		    gotoxy(10,23);
		    clreol();
			cout<<"CANCEL THIS TICKET (Y/N) : ";
		    ch = getch();
		    ch = toupper(ch);
	       }    while(ch != 'Y' && ch != 'N');

	       if(ch == 'N')
		 return;
	       DELETE_TICKET(tno);
	       gotoxy(10,25);
	       cout<<"\7TICKET CANCELLED";
	       getch();
	  }

	  //THIS FUNCTION DISPLAYS THE PASSENGER'S INFORMATION

	  void RESERVE :: DISPLAY_TICKET(void)
	  {

				//     PAGE 12

		   clrscr();
	       char t1[10],ch;
	       int t2,tno,valid;
	       do
	       {
		    valid = 1;
		    gotoxy(3,23);
		    clreol();
		    cout<<"PRESS <ENTER> TO SEE LIST OR 0 TO EXIT";
		    gotoxy(3,20);
		    clreol();
		    cout<<"ENTER THE TICKETNO. OF THE PASSENGER : ";
		    gets(t1);
		    t2 = atoi(t1);
		    tno = t2;
		    if(t1[0] == '0')
		      return;
		    if(strlen(t1) == 0)
		    {
		      valid = 0;
			  LIST();
		      clrscr();
		    }
		    if(FOUND(tno) && valid)
		    {
		      valid = 0;
		      gotoxy(3,23);
		      clreol();
		      cout<<"\7RECORD NOT FOUND";
		      getch();
		    }
	       }    while(!valid);

	       clrscr();
	       fstream file;
	       file.open("PASS.DAT",ios::in);
	       while(file.read((char*)this,sizeof(PASSENGER)))
		    if(ticketno == tno)
		      break;
	       file.close();
		   int i = 1;
	       file.open("TICKET.DAT",ios::in);
	       while(file.read((char*)this,sizeof(TICKET)))
	       {
		    if(slno == i)
		      break;
		    i++;
	       }
	       file.close();
	       PASSENGER p;
	       gotoxy(11,4);
	       cout<<"****************************************************";
	       gotoxy(11,21);
	       cout<<"****************************************************";
	       gotoxy(33,6);
	       cout<<"TICKET NO. : "<<tno;
	       gotoxy(17,9);
	       cout<<from<<" TO "<<to;
	       gotoxy(45,9);
	       cout<<"TRAIN NO. : "<<TRNno;
		   gotoxy(20,11);
	       cout<<"PASSENGER NAME : "<<p.NAME(tno);
	       gotoxy(20,13);
	       cout<<"ADDRESS : "<<address;


		     //     PAGE 13

	       gotoxy(20,15);
	       cout<<"SEX : "<<sex;
	       gotoxy(20,17);
	       cout<<"AGE : "<<age;
	       gotoxy(45,19);
	       if(Class == 'E')
		 cout<<"TOTAL FAIR : "<<ecofair;
	       else
		 cout<<"TOTAL FAIR : "<<exefair;
	       gotoxy(10,25);
	       cout<<"PRESS ANY KEY TO CONTINUE....";
	       getch();
	  }

	  //THIS FUNCTION GIVES TRAIN NO. TO DELETE ALL PASSENGER RECORDS

	  void RESERVE :: DELETE_ALL(void)
	  {
	       clrscr();
	       ENQUIRY();
	       char t1[5];
	       int t2,valid,sno;
	       do
	       {
		    valid = 1;
		    gotoxy(3,23);
		    clreol();
		    cout<<"PRESS <ENTER> TO EXIT";
		    gotoxy(3,20);
		    cout<<"ENTER SNO. OF THE TRAIN TO DELETE RELATED RECORDS";
		    gets(t1);
		    t2 = atoi(t1);
			sno = t2;
		    if(strlen(t1) == 0)
		      return;
		    if(sno < 1 || sno > 12)
		    {
		      valid = 0;
		      gotoxy(3,23);
		      clreol();
		      cout<<"\7ENTER CORRECTLY";
		      getch();
		    }
	       }    while(!valid);

	       gotoxy(3,23);
	       if(!DELETE_TRAIN(sno) )
		 cout<<"\7RECORDS NOT FOUND.PRESS ANY KEY TO CONTINUE....";
	       else
		 cout<<"\7RECORDS DELETED.PRESS ANY KEY TO CONTINUE....";
	       getch();
	  }

	  //THIS IS THE MAIN FUNCTION WHICH DISPLAYS MENU AND CALLS FUNCTIONS

	  void main(void)
	  {

			      // PAGE 14

	       PASSENGER p;
	       TICKET ticket;
	       RESERVE r;
	       ticket.ADDITION();
	       int ch,ch1;
	       while(1)
	       {
		    clrscr();
		    gotoxy(29,9);
		    cout<<"RAILWAY   TICKET   RESERVATION";
		    gotoxy(29,10);
		    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			gotoxy(30,11);
		    cout<<"1 : RESERVATION";
		    gotoxy(30,12);
		    cout<<"2 : CANCELLATION";
		    gotoxy(30,13);
		    cout<<"3 : PASSENGER RECORDS ->";
		    gotoxy(30,14);
		    cout<<"4 : ENQUIRY";
		    gotoxy(30,15);
		    cout<<"5 : LIST OF PASSENGERS";
		    gotoxy(30,16);
		    cout<<"6 : QUIT";
		    gotoxy(30,18);
		    cout<<"ENTER YOUR CHOICE : ";
		    cin>>ch;
		    switch(ch)
		    {
			case 1:
			       r.RESERVATION();
			       break;

			case 2:
			       r.CANCELLATION();
			       break;

			case 3:
			       clrscr();
			       gotoxy(29,10);
			       cout<<" PASSENGER RECORDS ";
			       gotoxy(29,11);
			       cout<<"~~~~~~~~~~~~~~~~~~~~~~~";
			       gotoxy(33,12);
			       cout<<"1 : PASSENGER INFORMATION";
			       gotoxy(33,13);
			       cout<<"2 : MODIFY";
			       gotoxy(33,14);
			       cout<<"0 : EXIT";
			       gotoxy(33,16);
			       cout<<"ENTER YOUR CHOICE--->";
			       cin>>ch1;
				   if(ch1==1)
				 {clrscr();
				 p.PASS_INFO();
				 getch(); }
			       else
				 if(ch1==2)
				   {clrscr();
				   p.MODIFY();}
				 else
				   break;
			       break;

			case 4:
			       ticket.ENQUIRY();
			       gotoxy(2,23);
			       cout<<"PRESS ANY KEY TO CONTINUE....";
			       getch();
			       break;

			case 5:
				   p.LIST();
			       break;

			case 6:
			       exit(0);

			default:
				cout<<"ENTER THE CORRECT CHOICE";
		    }
	       }
	  }