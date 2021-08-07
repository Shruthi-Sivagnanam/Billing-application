/*This a project for billing, addition of products and deletion of products
for departmental stores
Author name: Shruthi S
Concepts used: File handling
Type of file: Text file*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
struct date dt;


//structure memebers

struct bill{                      //for stock file
	int code;
	char iname[30];
	float price;
}s1,s2;

struct am{                        //for day to day purchase file
	float tamount;
	int date[3];
	char c[10];
}b1;

//Userdefined-function
void billing()
{
int code,n,i=1,e=0,m;
char ch[100];
float tamount=0,total=0,s,discount=0,gtotal;
FILE *fp,*ft;
ft=fopen("amount.txt","a+");
fp=fopen("stock.txt","r");
getdate(&dt);
do
{ printf("\n\nS.no: %d",i);
  printf("\nCode: ");
  scanf("%d",&code);
  while(fread(&s2,sizeof(s2),1,fp))
 {
   if(s2.code==code)
   { printf("Item: %s",s2.iname);
     printf("\t\tMRP: %f",s2.price);
     printf("\t\tNumber: ");
     scanf("%d",&n);
     tamount=n*s2.price;
     total+=tamount;
     printf("\n\t\t\t\t\t\t\tPrice: %f",tamount);
     printf("\n\t---------------------------------------------------------");
     e=1;
   }
 }
 if(e==0)
 printf("wrong code\n");
 fseek(fp,0,SEEK_SET);
 i++;

 }while(code!=-1);
 printf("\n\t------------------------------------------------------------");
 printf("\n\n\n\t\t\t   Total: %f",total);
 getch();
 clrscr();
 if(total>=500 && total<1000)
  discount=0.02;
 else if(total>=1000 && total>5000)
  discount=0.05;
 else if(total>=5000)
  discount=0.10;
 gtotal=total-total*discount;
 printf("\n\t\t\t\t   XYZ\n");
 printf("\t\t\t     Departmental stores");
 printf("\n\n\t\t\t  Total: %f",total);
 printf("\n\t\t\t  Discount: %f ",discount);
 printf("\n\t\t\t  Grand Total: %f",gtotal);
 printf("\n\t-------------------------------------------------");
 printf("\n\n\t\t\t\tMode of payment");
 printf("\n\t\t\t1.Credit card\n\t\t\t2.Cash");
 printf("\n\t\t Enter the mode : ");
 scanf("%d",&m);
 b1.tamount=gtotal;
 b1.date[0]=dt.da_day;
 b1.date[1]=dt.da_mon;
 b1.date[2]=dt.da_year;
 switch(m)
 { case 1:
       printf("\n\n\t\t\t  Thank you");
       strcpy(b1.c,"card");
       break;
   case 2:
	printf("\n\n\t\t\tAmount Given: ");
	scanf("%f",&s);
	printf("\n\t\t\tBalance: %f",s-total);
	strcpy(b1.c,"cash");
	break;
}
 fwrite(&b1,sizeof(b1),1,ft);
 fclose(ft);
 fclose(fp);
}
void addition()
{int a;
 FILE *fp;
 fp=fopen("stock.txt","a+");
 do{
 clrscr();
 printf("\n\t\t\t\t   XYZ\n");
 printf("\t\t\t     Departmental stores");
 printf("\n\n\t\t\t    Addition of products");
 printf("\n\n\n\t\t\t\t***********");
 printf("\n\n\t\t\tEnter the code: ");
 scanf("%d",&s1.code);
 printf("\n\t\t\tEnter the name: ");
 scanf("%s",s1.iname);
 printf("\n\t\t\tEnter the price: ");
 scanf("%f",&s1.price);
 printf("\n\t\t\t\t************");
 fwrite(&s1,sizeof(s1),1,fp);
 printf("\n\n\t\t  Do you want to add more items?<0/1>: ");
 scanf("%d",&a);
 }while(a==1);
 printf("\n\n\t\t\tThank you");
 fclose(fp);
}
void deletion()
{int a,code;
 do{
 int e=0;
 FILE *fp,*fr;
 fp=fopen("stock.txt","r");
 fr=fopen("temp.txt","a+");
 clrscr();
 printf("\n\t\t\t\t   XYZ\n");
 printf("\t\t\t     Departmental stores");
 printf("\n\n\t\t\t    Deletion of products");
 printf("\n\n\n\t\t\t\t***********");
 printf("\n\n\t\t\tEnter the code: ");
 scanf("%d",&code);
 while(fread(&s2,sizeof(s2),1,fp))
 {
 if(code==s2.code)
    e=1;
 else
   fwrite(&s2,sizeof(s2),1,fr);
 }
 if(e==0)
  printf("\n\t\t  The code is not in the file!");
 else
  printf("\n\t\t  The item is deleted succesfully");
 fclose(fr);
 fclose(fp);
 remove("stock.txt");
 rename("temp.txt","stock.txt");
 printf("\n\n\t\t  Do you want to delete more items?<0/1>: ");
 scanf("%d",&a);
 }while(a==1);
}
void stock_detail()
{ int g=0;
  FILE *fp;
  fp=fopen("stock.txt","r");
  printf("\n\t\t\t\tStock Details\n");
  printf("\tS.no  Item name\tprice\n\n");
  while(fread(&s2,sizeof(s2),1,fp))
  {g++;
  if(g%11==0)
  {
  getch();
  clrscr();
  printf("\n\n\t\t\t\tStock Details\n");
  printf("\tS.no  Item name\tprice\n\n");
  }
  printf("\t%d\t%s\t%f",s2.code,s2.iname,s2.price);
  printf("\n");
  }
  fclose(fp);
}

void billing_detail()
{ int f=0;
  FILE *fp;
  fp=fopen("amount.txt","r");
  printf("\t\t\t\tBilling Details\n\n");
  printf("\tDate\t\tAmount\t\tMode\n");
  while(fread(&b1,sizeof(b1),1,fp))
  {f++;
  if(f%11==0)
  {getch();
  clrscr();
  printf("\n\t\t\t\tBilling Details\n\n");
  printf("\tDate\t\tAmount\t\tMode\n");
  }
  printf("\t%d-%d-%d\t%f\t%s",b1.date[0],b1.date[1],b1.date[2],b1.tamount,b1.c);
  printf("\n");
  }
}


void main()
{
 int choice;
 int b,d;
 clrscr();
 printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t    XYZ\n");
 printf("\t\t\t     Departmental stores");
 getch();
 do{
 clrscr();
 printf("\t\t\t\t   XYZ\n");
 printf("\t\t\t     Departmental stores");
 printf("\n\n\n\n\n\n\t\t\t\t****Menu****");
 printf("\n\t\t\t  1.Billing");
 printf("\n\t\t\t  2.Addition of products");
 printf("\n\t\t\t  3.Deletion of products");
 printf("\n\t\t\t  4.Stock Detail");
 printf("\n\t\t\t  5.Bill Detail");
 printf("\n\t\t\t\t************");
 printf("\n\t\t\tEnter your choice(1,2,3,4,5): ");
 scanf("%d",&choice);
 clrscr();

 printf("\n");
 getdate(&dt);

 switch(choice)
 {
	case 1:
		do{
		clrscr();
		printf("\n\t\t\t\t   XYZ\n");
		printf("\t\t\t     Departmental stores");
		printf("\n\t\t\t\t  Billing");
		printf("\n\nDate: %d-%d-%d",dt.da_day,dt.da_mon,dt.da_year);
		billing();
		printf("\n\t\tDo want to continue billing?<0/1>: ");
		scanf("%d",&d) ;
		}while(d==1);
		break;
	case 2:
		addition();
		break;
	case 3:
		deletion();
		break;
	case 4:
	       stock_detail();
	       break;
	case 5:
		billing_detail();
		break;
	default:
		printf("\n\n\t\t\t\tWrong choice!!");
		printf("\n\n\t\t\t\tThank You :)");
		break;
 }
 getch();
 clrscr();
 printf("\n\n\n\t\t\tWant to go to application?<0/1>\n\t\t\t\t\t");
 scanf("%d",&b);
 }while(b==1);
 clrscr();
 printf("\n\n\n\n\n\n\n\t\t\t\tThank you :)");
 getch();
}

