/***********************************************************************************************

		-------------------------------------------
		   -------------------------------------
		     SHOP MANAGEMENT PROGRAM USING C++
		   -------------------------------------
		-------------------------------------------

					  || Developed By : ARJUN ALOSHIOUS ||


/************************************************************************************************

::::::::::::::::::::::::::::The Header Files Used::::::::::::::::::::::::::::::::::::::::::::::::

************************************************************************************************/


#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<iomanip.h>

/*_______________________________________________________________________________________________

:::::::::::::::::::::::::::Global Declarations:::::::::::::::::::::::::::::::::::::::::::::::::::
_______________________________________________________________________________________________*/

fstream P;
int ino[20],q[20],tot[20],no;

/*_______________________________________________________________________________________________

::::::::::::::::::::::::::::1st Class Definition:::::::::::::::::::::::::::::::::::::::::::::::::
_______________________________________________________________________________________________*/

class Administrator
{
  private:
    int Item_no,qty;
    char Name[30];
    float price;

  public:
    void Input();
    void Display();
    void Add_Products(int);
    void Display_Products();
    void Dis();
    void Search();
    void Modify();
    void Delete();
    void BillModify();
    int retno()
    {
      return Item_no;
    }
    char* retname()
    {
      return Name;
    }
    int retqty()
    {
      return qty;
    }
    int retprice()
    {
      return price;
    }

}Obj1;


void  Administrator :: Input()
{
  cout<<"\n\nEnter the Product's Item Number : ";
  cin>>Item_no;
  cout<<"Enter the Product's Name        : ";
  gets(Name);
  cout<<"Enter the Product's Price       : ";
  cin>>price;
  cout<<"Enter the Product's Quantity    : ";
  cin>>qty;
}


void  Administrator :: Display()
{
  cout<<"\n\nThe Product's Details are as follows : ";
  cout<<"\nItem Number  : "<<Item_no;
  cout<<"\nItem Name    : "<<Name;
  cout<<"\nItem Price   : "<<price;
  cout<<"\nQuantity     : "<<qty;
  getch();
}


void  Administrator :: Add_Products(int n)
{
  P.open("MarvFiles.dat",ios::app|ios::binary);
  P.seekg(0);
  for(int i=0;i<n;i++)
  {
    Input();
    P.write((char*)&Obj1,sizeof(Obj1));
  }
  P.close();
}


void  Administrator :: Display_Products()
{
  P.open("MarvFiles.dat",ios::in|ios::binary);
  P.seekg(0);
  while(P.read((char*)&Obj1,sizeof(Obj1)))
  {
    Display();
  }
  P.close();
}


void  Administrator :: Dis()
{
  int t=1;
  fstream P;
  P.open("MarvFiles.dat",ios::in|ios::binary);
  P.seekg(0);
  while(P.read((char*)&Obj1,sizeof(Obj1)))
  {
     cout<<"\n |   "<<t<<"       "<<Obj1.retno()<<"       "<<Obj1.retname();
     cout<<"\t\t\t     "<<Obj1.retprice()<<"\t        "<<Obj1.retqty();
     t++;
  }
  P.close();
}


void Administrator :: Search()
{
  int k,op,flag=0;
  char Name2[30];
  P.open("MarvFiles.dat",ios::in|ios::binary);
  P.seekg(0);
  cout<<"\n\n\nSearch by : \n\n   1) Name ?\t\tOR  by\t\t2) Item Number ? ";
  cout<<"\n\n\nEnter your option [1/2] : ";
  cin>>op;
  switch(op)
  {
    case 1 : cout<<"\n\nEnter the Name of the Product to be Searched for : ";
	     gets(Name2);
	     while(P.read((char*)&Obj1,sizeof(Obj1)))
	     {
	       if(strcmpi(Obj1.retname(),Name2)==0)
	       {
		 cout<<"\n\nThe Searched Product's Details are as follows: ";
		 Obj1.Display();
		 flag=1;
	       }
	     }
	     if(flag==0)
	       cout<<"\n\n\t\t\t     ITEM NOT FOUND ";
	     P.close();
	     break;

    case 2 : cout<<"\n\nEnter the Item Number of the Product to be Searched for : ";
	     cin>>k;
	     while(P.read((char*)&Obj1,sizeof(Obj1)))
	     {
	       if(Obj1.retno()==k)
	       {
		 cout<<"\n\nThe Searched Product's Details are as follows: ";
		 Obj1.Display();
		 flag=1;
	       }
	     }
	     if(flag==0)
	       cout<<"\n\n\t\t\t     ITEM NOT FOUND ";
	     P.close();
	     break;

   default : cout<<"\n\nInvalid option chosen!";
	     break;
  }
}


void Administrator :: Modify()
{
  int r,flag=0;
  P.open("MarvFiles.dat",ios::in|ios::out|ios::binary);
  P.seekg(0);
  cout<<"\n\nEnter the Item Number of the Product to be Modified : ";
  cin>>r;

  while(P.read((char*)&Obj1,sizeof(Obj1)))
  {
    if(Obj1.retno()==r)
    {
      Obj1.Display();
      Obj1.Input();
      int pos=(-1)*sizeof(Obj1);
      P.seekp(pos,ios::cur);
      P.write((char*)&Obj1,sizeof(Obj1));
      cout<<"\n\n\t\t\t     ITEM MODIFIED ";
      flag=1;
      break;
    }
  }
  P.close();
  if(flag==0)
     cout<<"\n\n\t\t\t     ITEM NOT FOUND ";
  getch();
}


void Administrator :: Delete()
{
  fstream Q;
  int t,check=0;
  P.open("MarvFiles.dat",ios::in|ios::binary);
  Q.open("Temporary.dat",ios::out|ios::binary);
  P.seekg(0);
  cout<<"\nEnter the Item Number of the Product to be Deleted : ";
  cin>>t;
  P.seekg(0);

  while(P.read((char*)&Obj1,sizeof(Obj1)))
  {
    if(Obj1.retno()!=t)
    {
      Q.write((char*)&Obj1,sizeof(Obj1));
    }
    else
      check++;
  }
  P.close();
  Q.close();
  remove("MarvFiles.dat");
  rename("Temporary.dat","MarvFiles.dat");
  if(check==0)
     cout<<"\n\n\t\t\t     ITEM NOT FOUND ";
  else
     cout<<"\n\n\t\t\t     ITEM DELETED ";
}


void Administrator :: BillModify()
{
  int r,flag=0;
  P.open("MarvFiles.dat",ios::in|ios::out|ios::binary);
  P.seekg(0);

  for(int i=0;i<no;i++)
  {
    P.seekg(0);
    while(P.read((char*)&Obj1,sizeof(Obj1)))
    {
      if(Obj1.retno()==ino[i])
      {
	qty=qty-q[i];
	tot[i]=price;
	int pos=(-1)*sizeof(Obj1);
	P.seekp(pos,ios::cur);
	P.write((char*)&Obj1,sizeof(Obj1));
	flag=1;
	break;
      }
    }
  }
  if(flag==0)
  {
    cout<<"\n\n\t\t\t     ITEM NOT FOUND ";
    getch();
  }
  P.close();
}

/*_______________________________________________________________________________________________

:::::::::::::::::::::::::::::2nd Class Definition::::::::::::::::::::::::::::::::::::::::::::::::
_______________________________________________________________________________________________*/

class Customer
{
  private:
    char Cname[20],ph[15];

  public:
    void CustInput();
    void CustDisplay();
    void Display_Customer();
    void CustSearch();
    void CustModify();
    void CustDelete();
    char* retname()
    {
      return Cname;
    }
    char* retphone()
    {
      return ph;
    }

}Obj2;


void  Customer :: CustInput()
{
  P.open("CustomerFile.dat",ios::app|ios::binary);
  cout<<"\n\nEnter the Customer Name   : ";
  gets(Cname);
  cout<<"Enter the Phone Number    : ";
  gets(ph);
  P.write((char*)&Obj2,sizeof(Obj2));
  P.close();
}


void  Customer :: CustDisplay()
{
  cout<<"\n\nThe Customer's Details are as follows : ";
  cout<<"\nCustomer Name : "<<Cname;
  cout<<"\nPhone Number  : "<<ph;
  getch();
}


void  Customer :: Display_Customer()
{
  P.open("CustomerFile.dat",ios::in|ios::binary);
  P.seekg(0);
  while(P.read((char*)&Obj2,sizeof(Obj2)))
  {
    Obj2.CustDisplay();
  }
  P.close();
}


void  Customer :: CustSearch()
{
  int op,flag=0;
  char Name2[20],k[15];
  P.open("CustomerFile.dat",ios::in|ios::app|ios::binary);
  P.seekg(0);
  cout<<"\n\n\nSearch by : \n\n   1) Name ?\t\tOR  by\t\t2) Phone Number ? ";
  cout<<"\n\n\nEnter your option [1/2] : ";
  cin>>op;
  switch(op)
  {
    case 1 : cout<<"\n\nEnter The Name Of The Customer To Be Searched For : ";
	     gets(Name2);
	     while(P.read((char*)&Obj2,sizeof(Obj2)))
	     {
	       if(strcmpi(Obj2.retname(),Name2)==0)
	       {
		 cout<<"\n\nThe Searched Customer's Details are as follows : ";
		 Obj2.CustDisplay();
		 flag=1;
	       }
	     }
	     if(flag==0)
	       cout<<"\n\n\t\t\t   CUSTOMER NOT FOUND ";
	     P.close();
	     break;

    case 2 : cout<<"\n\nEnter The Phone Number Of The Customer To Be Searched For : ";
	     gets(k);
	     while(P.read((char*)&Obj2,sizeof(Obj2)))
	     {
	       if(strcmpi(Obj2.retphone(),k)==0)
	       {
		 cout<<"\n\nThe Searched Customer's Details are as follows: ";
		 Obj2.CustDisplay();
		 flag=1;
	       }
	     }
	     if(flag==0)
	       cout<<"\n\n\t\t\t   CUSTOMER NOT FOUND ";
	     P.close();
	     break;

   default : cout<<"\n\nInvalid option chosen!";
	     break;
  }
}


void Customer :: CustModify()
{
  int flag=0;
  char cp[15];
  P.open("CustomerFile.dat",ios::in|ios::out|ios::binary);
  cout<<"\n\nEnter the Phone Number of the Customer to be Modified : ";
  gets(cp);
  while(P.read((char*)&Obj2,sizeof(Obj2)))
  {
   if(strcmpi(Obj2.retphone(),cp)==0)
    {
      Obj2.CustDisplay();
      cout<<"\n\nEnter the Customer Name   : ";
      gets(Cname);
      cout<<"Enter the Phone Number    : ";
      gets(ph);
      int pos=(-1)*sizeof(Obj2);
      P.seekp(pos,ios::cur);
      P.write((char*)&Obj2,sizeof(Obj2));
      cout<<"\n\n\t\t\t   CUSTOMER MODIFIED ";
      flag=1;
      break;
    }
  }
  P.close();
  if(flag==0)
     cout<<"\n\n\t\t\t   CUSTOMER NOT FOUND ";
}


void Customer :: CustDelete()
{
  fstream Q;
  int flag=0;
  char cp[15];
  P.open("CustomerFile.dat",ios::in|ios::binary);
  Q.open("Temporary.dat",ios::out|ios::binary);
  P.seekg(0);
  cout<<"\nEnter the Phone Number of the Customer to be Deleted : ";
  gets(cp);
  P.seekg(0);

  while(P.read((char*)&Obj2,sizeof(Obj2)))
  {
    if(strcmpi(Obj2.retphone(),cp)!=0)
    {
      Q.write((char*)&Obj2,sizeof(Obj2));
    }
    else
      flag=1;
  }
  P.close();
  Q.close();
  if(flag==0)
    cout<<"\n\n\t\t\t   CUSTOMER NOT FOUND ";
  else
    cout<<"\n\n\t\t\t   CUSTOMER DELETED ";
  remove("CustomerFile.dat");
  rename("Temporary.dat","CustomerFile.dat");
}


void  CustWelcome()
{
  int opt2;
  do
  {
    clrscr();
    cout<<"\n\n\t\t\t\t CUSTOMER MENU";
    cout<<"\n\n\n\n0.Exit"
	<<"\n1.Add New Customers"
	<<"\n2.Display Details Of Customers"
	<<"\n3.Search For A Customer"
	<<"\n4.Modify A Customer's Details"
	<<"\n5.Delete A Customer's Details"
	<<"\n6.Return To Home Screen";
    cout<<"\n\nEnter Your Option [0/1/2/3/4/5/6] : ";
    cin>>opt2;
    switch(opt2)
    {
       case 0: cout<<"\n\n\n\n\t\t\t\tTHANK YOU :) ";
	       getch();
	       exit(0);

       case 1: Obj2.CustInput();
	       break;

       case 2: Obj2.Display_Customer();
	       break;

       case 3: Obj2.CustSearch();
	       break;

       case 4: Obj2.CustModify();
	       break;

       case 5: Obj2.CustDelete();
	       break;

       case 6: return;

       default: cout<<"\n\nInvalid Option ";
    }
    getch();
  }while(1);
}

/*_______________________________________________________________________________________________

::::::::::::::::::::::::::::3rd Class Definition:::::::::::::::::::::::::::::::::::::::::::::::::
_______________________________________________________________________________________________*/

class Bill
{
  private:
    char pho[15];
    int  itemno[20],iqty[20],dd,mm,yy;
    float amt[20];

  public:
    void Billcalc();
    void printbill();

}Obj3;


void Bill :: Billcalc()
{
  clrscr();
  char ch[5],ch2[5];
  no=0;
  cout<<"\n ________________________MARV SHOPS Ltd. PRODUCTS RANGE_______________________"
      <<"\n |       |         |                            |             |              | "
      <<"\n | Sl.No.| Item No.|       Product Name         | Price Range |   Quantity   | "
      <<"\n |_______|_________|____________________________|_____________|______________|"
      <<"\n |       |         |                            |             |              |";
  Obj1.Dis();
  cout<<"\n  ___________________________________________________________________________";
  cout<<"\n\n  Enter The Item Number And Quantity Of Products You Wish To Buy : ";
  do
  {
    cout<<"\n  Item Number   : ";
    cin>>ino[no];
    cout<<"  Quantity      : ";
    cin>>q[no];
    no++;
    cout<<"\n  Want more items ? ";
    gets(ch);
  }while(strcmpi(ch,"Yes")==0 || strcmpi(ch,"y")==0);

  cout<<"\n  Proceed To Billing ? ";
  cin>>ch2;
  if(strcmpi(ch2,"Yes")==0 || strcmpi(ch2,"y")==0)
    printbill();
  else
  {
    cout<<"\n\n  Billing not processed .... ";
    getch();
  }
}


void Bill :: printbill()
{
  fstream Q;
  char cnm[20];
  cout<<"\n\n  Enter Your Phone          : ";
  gets(pho);
  cout<<"  Enter The Date [DD/MM/YY] : ";
  cin>>dd>>mm>>yy;

  Q.open("CustomerFile.dat",ios::in|ios::binary);
  Q.seekg(0);
  while(Q.read((char*)&Obj2,sizeof(Obj2)))
  {
    if(strcmpi(Obj2.retphone(),pho)==0)
    {
      strcpy(cnm,Obj2.retname());
      break;
    }
  }
  Q.close();

		      //\\UPDATING ITEM FILE//\\

  Obj1.BillModify();
  fstream B;
  B.open("Bill.dat",ios::binary|ios::app);
  P.open("MarvFiles.dat",ios::binary|ios::in);

		      //\\DISPLAYING THE BILL//\\

  float gtot=0;
  clrscr();
  cout<<"\n Name of Customer : "<<cnm;
  cout<<setw(46)<<"Date : "<<dd<<"/"<<mm<<"/"<<yy;
  cout<<"\n Contact Number : "<<pho;
  cout<<"\n\n ________________________MARV SHOPS Ltd. PRODUCTS BILL_________________________"
      <<"\n |       |         |                    |             |         |             |"
      <<"\n | Sl.No.| Item No.|   Product Name     | Price Range |  Qty.   | Total Price |"
      <<"\n |_______|_________|____________________|_____________|_________|_____________|"
      <<"\n |       |         |                    |             |         |             |";
  for(int i=0;i<no;i++)
  {
    P.seekg(0);
    while(P.read((char*)&Obj1,sizeof(Obj1)))
    {
      if(Obj1.retno()==ino[i])
      {
	cout<<"\n     "<<i+1<<"       "<<ino[i]<<"       "<<Obj1.retname();
	cout<<"\t\t  "<<Obj1.retprice()<<"\t        "<<q[i]<<"          "<<tot[i]*q[i];
	gtot+=(tot[i]*q[i]);
	itemno[i]=ino[i];
	iqty[i]=q[i];
	amt[i]=tot[i]*q[i];
	break;
      }
    }
  }
  cout<<"\n ______________________________________________________________________________\n";
  cout<<setw(71)<<"    Total Price :  "<<gtot;
  cout<<"\n ______________________________________________________________________________\n";
  B.write((char*)&Obj3,sizeof(Obj3));
  B.close();
  P.close();
  getch();
}


void End()
{
  clrscr();
  int r;
  cout<<"\n\n\n\n\t  How Did You Like Your Shopping Experience Here At MARV SHOPS ?"
      <<"\n\n\t\t\t Please Do Give Us A Rating :)"
      <<"\n\n\n\t1) It Was A Very Good Experience !"
      <<"\n\t2) It Was An Average Experience !"
      <<"\n\t3) It Was A Terrible Experience !   ";
  cin>>r;
  switch(r)
   {
     case 1:
     case 2: cout<<"\n\n\n\t\t     Thank You Very Much For The Rating !";
	     getch();
	     break;

     case 3: cout<<"\n\tOh! We Are So Sorry To Hear That !";
	     cout<<"\n\tPlease Do Feel Free To Contact Our Manager, And Help Us Help You.";
	     getch();
	     break;

     default:  cout<<"\n\tOkay, Thank You :)";
	       getch();
   }
   cout<<"\n\n\n\t\t  And Thank You For Shopping At MARV SHOPS !";
   cout<<"\n\n\t\t    We Wish You A MARVELOUS DAY Ahead !";
   cout<<"\n\n\t\t\t  Please Do Visit Again :)";
   getch();
   exit(0);
}


void Startup()
{
  clrscr();
  int opt;
  char wish[20];
  cout<<"\n\n\n\t\t\t\tHELLO ALL !\n\n\t\t\t\t   AND\n\n\t\t\t"
      <<" WELCOME TO MARV SHOPS Ltd.\n\n\n\t\t\t       "
      <<" WHICH PROVIDES AN IMMERSIVE SHOPPING EXPERIENCE!";
  cout<<"\n\n\n\n\n\t\t\t\t\t\t   CREATED BY : ARJUN ALOSHIOUS\n\t\t\t\t\t\t  "
      <<"   OF CLASS : XII A\n\t\t\t\t\t          ROLL NUMBER : 8";
  cout<<"\n\n\n\n     Shall We Start ?  ";
  gets(wish);
  if(strcmpi(wish,"Yes")==0 || strcmpi(wish,"y")==0)
  {
    clrscr();
  }
  else if(strcmpi(wish,"No")==0 || strcmpi(wish,"n")==0)
  {
    clrscr();
    cout<<"\n\n\n\n\n\n\n\n\n\t\t\t    Ok Then, See You Later !"
	<<"\n\n\t\t\t     Please Visit Again :)";
    getch();
    exit(0);
  }
}


void main()
{
  clrscr();
  int n,opt1,opt2;
  Startup();
  HomeScreen:
  {
    clrscr();
    cout<<"\n\n\n\t\t\t\tHOME SCREEN"
	<<"\n\n\n\nDo You Want To Visit : "
	<<"\n1) ADMINISTRATOR SECTION ?   2) CUSTOMER SECTION ?   OR   3) BILLING SECTION ?"
	<<"\n\nEnter Option [1/2/3] : ";
    cin>>opt1;
    switch(opt1)
    {

      case 1 :
	       while(1)
	       {
		 clrscr();
		 cout<<"\n\n\t\t\t\t MAIN MENU";
		 cout<<"\n\n\n\n0.Exit"
		     <<"\n1.Add New Products"
		     <<"\n2.Display Details of Products"
		     <<"\n3.Search For A Product"
		     <<"\n4.Modify A Product's Details"
		     <<"\n5.Delete A Product"
		     <<"\n6.Return To Home Screen";
		 cout<<"\n\nEnter Your Option [0/1/2/3/4/5/6] : ";
		 cin>>opt2;
		 switch(opt2)
		 {
		   case 0 : cout<<"\n\n\n\n\t\t\t\tTHANK YOU :) ";
			    getch();
			    exit(0);

		   case 1 : cout<<"\n\nEnter the number of products to be added : ";
			    cin>>n;
			    Obj1.Add_Products(n);
			    break;

		   case 2 : Obj1.Display_Products();
			    break;

		   case 3 : Obj1.Search();
			    break;

		   case 4 : Obj1.Modify();
			    break;

		   case 5 : Obj1.Delete();
			    break;

		   case 6 : clrscr();
			    goto HomeScreen;

		   default : cout<<"\n\nInvalid Option Chosen!";
			     getch();
			     break;
		 }
		 getch();
	       }

      case 2 : CustWelcome();
	       getch();
	       break;

      case 3 : Obj3.Billcalc();
	       End();
	       break;

     default : cout<<"\n\nInvalid Option Chosen!";
    }
    goto HomeScreen;
  }
}
/*____________________________________________________________________________________

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
____________________________________________________________________________________*/