#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
	char item[30];
	float price;
	int qty;
};

struct orders{
	char costumer[30];
	char date[20];
	int numofitm;
	struct items itm[50];
};


void generate_header(char name[50],char date[20])
{
	    printf("\n\n");
        printf("\t    ADV. Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}

void generate_body(char item[30],int qty,float price)
{
	  printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty * price);
        printf("\n");
}

void generate_footer(float total)
{
	    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;//netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}





int main()
{
	int op,found=0,i;
	float total=0;
	struct orders ord;
	struct orders ord_copy;
	char save='y',choice='y';
	FILE *fp;
	char name[30];
	
while(choice =='y')
{

	printf("\t --------MY RESTAURANT--------\n\n");
	 printf("Please select your prefered:\t");
	printf("\n1.General Invoice\n2.show all invoice\n3.Search Invoice\n4.Exit\n");
	printf("\n\n");

	printf("Enter your choice:\t");
	scanf("%d",&op);

	switch(op)
	{
		case 1:
			system("clear");
			printf("Name of the costumer:\t");
			scanf("%s",ord.costumer);
			strcpy(ord.date,__DATE__);
			printf("\nENter the number of items:\t");
			scanf("%d",&ord.numofitm);
			getchar();

			for(i=0;i<ord.numofitm;i++)
			{
				printf("\n\nPlease enter the item %d:",i+1);
				scanf("%s",ord.itm[i].item);

				printf("\nPlease enter the quantity:\t");
				scanf("%d",&ord.itm[i].qty);

				printf("\nPlease enter price per unit:\t");
				scanf("%f",&ord.itm[i].price);
				total+=ord.itm[i].qty*ord.itm[i].price;
			}

			generate_header(ord.costumer,ord.date);
			for(i=0;i<ord.numofitm;i++)
			{
				generate_body(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
			}
			generate_footer(total);
			getchar();
			printf("\n Do you want to Save this Invoice:\t");
			scanf("%c",&save);

			if(save =='y')
			{
				fp=fopen("Restro.dat","a+");
				fwrite(&ord,sizeof(struct orders),1,fp);
				if(fwrite!=0)
				{
					printf("Saved Succesfully\n");
				}
				else
				{
					printf("Failed to save\n");
				}
				fclose(fp);
			}
			break;

		case 2:
			system("clear");
			fp=fopen("Restro.dat","r");
			printf("***************Previous Invoices****************\n\n");
			while(fread(&ord_copy,sizeof(struct orders),1,fp))
			{
				float tot=0;
				generate_header(ord_copy.costumer,ord_copy.date);

				for(i=0;i<ord_copy.numofitm;i++)
				{
					generate_body(ord_copy.itm[i].item,ord_copy.itm[i].qty,ord_copy.itm[i].price);
					tot+=ord_copy.itm[i].qty*ord_copy.itm[i].price;
				}
				generate_footer(tot);
			}
			fclose(fp);
			break;


		case 3:
			system("clear");
			printf("Enter the Name of the costumer:\t");
			scanf("%s",name);

			fp=fopen("Restro.dat","r");
			printf("\t**********Invoice of %s***************",name);

			while(fread(&ord_copy,sizeof(struct orders),1,fp))
			{
				float tot1;
				if(!strcmp(ord_copy.costumer,name))
				{
					generate_header(ord.costumer,ord_copy.date);

					for(i=0;i<ord_copy.numofitm;i++)
					{
						generate_body(ord_copy.itm[i].item,ord_copy.itm[i].qty,ord_copy.itm[i].price);
					    tot1+=ord_copy.itm[i].qty*ord_copy.itm[i].price;
					}
					generate_footer(tot1);
					found=1;
				}

			}
			if(found==0)
			{
				printf("Sorry the invoice for %s is doen't exits\n\n",name);
			}
			fclose(fp);
			break;

		case 4:
			printf("\t\t\t BYE BYE");
			exit(0);
			break;


		default:
			printf("Sorry Invalid input\n\n");
			break;
	}
    getchar();
	printf("Do you want ot Continue:\t\t");
	scanf("%c",&choice);
}
printf("\t\t\t BYE BYe");

	return 0;
}


