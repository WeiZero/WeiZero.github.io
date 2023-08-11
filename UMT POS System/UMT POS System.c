#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning(disable : 4996)

#define DISCOUNT1 0.05
#define DISCOUNT2 0.10
#define DISCOUNT3 0.15

double const PRICE_BOOK[] = { 135.00,134.80,141.40,206.20,85.50,116.90,194.40,141.30,201.60 };
int quantityBook[10], totalQuantity[10], i, salesOrder, exitButton;
char nOrder, book[] = "ABCDEFGHI";

void logo();
void menu1();
void menu2();
void menu3();
void confirmOrder();
void summaryReport();
void endingMsg();


void main()
{
	menu1();
	
}

void logo()
{
	//display the logo
	printf("\n\t\t\t\t  %30s\n", "WELCOME TO");
	printf("\t\t      UUUUUUU     UUUUUUU  MMMMMMMM               MMMMMMMM  TTTTTTTTTTTTTTTTTTTTTT\n");
	printf("\t\t      U:::::U     U:::::U  M:::::::M             M:::::::M  T::::::::::::::::::::T\n");
	printf("\t\t      U:::::U     U:::::U  M::::::::M           M::::::::M  T::::::::::::::::::::T\n");
	printf("\t\t      U:::::U     U:::::U  M:::::::::M         M:::::::::M  T::::::::::::::::::::T\n");
	printf("\t\t      U:::::U     U:::::U  M::::::::::M       M::::::::::M  TTTTTTTT:::::TTTTTTTTT\n");
	printf("\t\t      U:::::U     U:::::U  M:::::::::::M     M:::::::::::M         T:::::T        \n");
	printf("\t\t      U:::::U     U:::::U  M:::::::M::::M   M::::M:::::::M         T:::::T        \n");
	printf("\t\t      U:::::U     U:::::U  M::::::M M::::M M::::M M::::::M         T:::::T        \n");
	printf("\t\t      U:::::U     U:::::U  M::::::M  M::::M::::M  M::::::M         T:::::T        \n");
	printf("\t\t      U:::::U     U:::::U  M::::::M   M:::::::M   M::::::M         T:::::T        \n");
	printf("\t\t      U:::::U     U:::::U  M::::::M    M:::::M    M::::::M         T:::::T        \n");
	printf("\t\t      U::::::UUUUU::::::U  M::::::M     MMMMM     M::::::M         T:::::T        \n");
	printf("\t\t      U:::::::::::::::::U  M::::::M               M::::::M         T:::::T        \n");
	printf("\t\t       UU:::::::::::::UU   M::::::M               M::::::M         T:::::T        \n");
	printf("\t\t         UU:::::::::UU     M::::::M               M::::::M         T:::::T        \n");
	printf("\t\t           UUUUUUUUU       MMMMMMMM               MMMMMMMM         TTTTTTT        \n");
	printf("\t\t\t\t%10s %15s\n", "", "        UMT POS System!");
}

void menu1()
{
	//Declaration
	int menuNum1;

	
	do {
		menuNum1 = 0; //Initialization
		logo();
		printf("\n\n\t\t\tSelect an option(1 = View Menu, 2 = Sales Order, 3 = Exit): "); //Display the main menu have users to navigate
		scanf(" %d", &menuNum1);
		rewind(stdin);
		

		switch (menuNum1)
		{
		case 1://It will redirect and start the function menu2()
			menu2();
			break;

		case 2://Clears the screen to reduce clutter, then redirect and start the function menu3()
			system("cls");
			menu3();
			break;

		case 3://Displays the ending message and ends the program
			endingMsg();
			break;

		default://Any number thats not 1-3 will display this message 
			system("cls");
			printf("\n\t\t\t\t\tInvalid Number! Please enter within 1-3\n");	
		}


	} while (menuNum1 != 3); //It will continuously loop until the user enters the number 3
}

void menu2()
{
	//declaration
	int menuNum2;

	do
	{	//Displays the different programming fields to have users to view and navigate
		printf("\n\t\t\t\t\t\tSelect a field to view:\n");
		printf("\t\t\t\t\t1 = Software Engineering Programming\n");
		printf("\t\t\t\t\t2 = Web Development Programming\n");
		printf("\t\t\t\t\t3 = Data Science Programming\n");
		printf("\t\t\t\t\t4 = Back to Main Menu\n");
		printf("\t\t\t\t\t\tInput : ");
		rewind(stdin);
		scanf("%d", &menuNum2);

		switch (menuNum2)
		{
		case 1://Clears the screen to reduce clutter, then displays the names and prices for book A to C
			system("cls");
			printf("\n\t\t\t\t%-50s\n", "Software Engineering Programming Books:");
			printf("\t\t\t%-50s  %2s %7.2f\n", "A = An Introduction to Software Engineering", "RM", PRICE_BOOK[0]);
			printf("\t\t\t%-50s  %2s %7.2f\n", "B = Fundamentals of Software Engineering", "RM", PRICE_BOOK[1]);
			printf("\t\t\t%-50s  %2s %7.2f\n\t\t\t", "C = Clean Code", "RM", PRICE_BOOK[2]);
			system("pause");
			break;

		case 2://Clears the screen to reduce clutter, then displays the names and prices for book D to F
			system("cls");
			printf("\n\t\t\t\t%-50s \n", "Web Development Programming Books:");
			printf("\t\t\t%-50s  %2s %7.2f\n", "D = JavaScript: The Definitive Guide", "RM", PRICE_BOOK[3]);
			printf("\t\t\t%-50s  %2s %7.2f\n", "E = Eloquent JavaScript", "RM", PRICE_BOOK[4]);
			printf("\t\t\t%-50s  %2s %7.2f\n\t\t\t", "F = Don’t Make Me Think, Revisited", "RM", PRICE_BOOK[5]);
			system("pause");
			break;

		case 3://Clears the screen to reduce clutter, then displays the names and prices for book G to I
			system("cls");
			printf("\n\t\t\t\t%-50s \n", "Data Science Programming Books:");
			printf("\t\t\t%-50s  %2s %7.2f\n", "G = Practical Statistics for Data Scientists", "RM", PRICE_BOOK[6]);
			printf("\t\t\t%-50s  %2s %7.2f\n", "H = Python Crash Course", "RM", PRICE_BOOK[7]);
			printf("\t\t\t%-50s  %2s %7.2f\n\t\t\t", "I = Python Data Science Handbook", "RM", PRICE_BOOK[8]);
			system("pause");
			break;

		case 4://Clears the screen and goes back to the function menu1()
			system("cls");
			break;

		default://Any number thats not 1-4 will display this message 
			system("cls");
			printf("\n\t\t\t\t\tPlease enter within 1 - 4:\n");
		}

	} while (menuNum2 != 4);//It will continuously loop until the user enters the number 4
}

void menu3() {

	//declaration
	int  range=0;
	char choiceOfBook, cOrder;


	//initialization
	i = 1;
	salesOrder = 1;
	exitButton = 1;
	totalQuantity[0] = 0, totalQuantity[1] = 0, totalQuantity[2] = 0, totalQuantity[3] = 0, totalQuantity[4] = 0, totalQuantity[5] = 0, totalQuantity[6] = 0, totalQuantity[7] = 0, totalQuantity[8] = 0;

	//menu for users to enter their purchase
	do {

		printf("\n\t\t\t\t\t\tSales Order No: %d\n", salesOrder);
		do {


			printf("\n\t\t\t\tBook A,B,C,D,E,F,G,H,I (X = Confirm order) : ");
			scanf("%c", &choiceOfBook);
			rewind(stdin);

			if (choiceOfBook == 'A' | choiceOfBook == 'a')
			{
				do 
				{
				printf("\t\t\t\t\t\t\t\t  Quantity : ");
				scanf("%d", &quantityBook[0]);
				rewind(stdin);
				
					if (quantityBook[0] <= range) //validation,if user enter a quantity lesser or equal to 0,will display this message
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");

				} while (quantityBook[0] <= range); //go in the loop if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'B' | choiceOfBook == 'b')
			{
				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[1]);
					rewind(stdin);

					if (quantityBook[1] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");

				} while (quantityBook[1] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'C' | choiceOfBook == 'c')
			{
				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[2]);
					rewind(stdin);

					if (quantityBook[2] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				} while (quantityBook[2] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'D' | choiceOfBook == 'd')
			{

				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[3]);
					rewind(stdin);

					if (quantityBook[3] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				} while (quantityBook[3] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'E' | choiceOfBook == 'e')
			{
				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[4]);
					rewind(stdin);

					if (quantityBook[4] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				} while (quantityBook[4] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'F' | choiceOfBook == 'f')
			{
				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[5]);
					rewind(stdin);

					if (quantityBook[5] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				} while (quantityBook[5] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'G' | choiceOfBook == 'g')
			{
				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[6]);
					rewind(stdin);

					if (quantityBook[6] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				} while (quantityBook[6] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'H' | choiceOfBook == 'h')
			{
				do
				{
					printf("\t\t\t\t\t\t\t\t  Quantity : ");
					scanf("%d", &quantityBook[7]);
					rewind(stdin);

					if (quantityBook[7] <= range) //validation
						printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				} while (quantityBook[7] <= range); //loop continue if quantity of book less or equal 0
			}

			else if (choiceOfBook == 'I' | choiceOfBook == 'i')
			{
			    do
			    {
				   printf("\t\t\t\t\t\t\t\t  Quantity : ");
				   scanf("%d", &quantityBook[8]);
				   rewind(stdin);

				   if (quantityBook[8] <= range) //validation
					  printf("\t\t\t      Enter a positive number for quantity!(Minimum = 1)\n");
				}while (quantityBook[8] <= range); //loop continue if quantity of book less or equal 0
			    
			}

			else if (choiceOfBook == 'X' | choiceOfBook == 'x')
			{
				if(quantityBook[0]==0 && quantityBook[1] == 0 && quantityBook[2] == 0 && quantityBook[3] == 0 && quantityBook[4] == 0 && quantityBook[5] == 0 && quantityBook[6] == 0 && quantityBook[7] == 0 && quantityBook[8] == 0) //validation,ask user to order at least 1 item
				{
					printf("\t\t\t\t\t   Please Enter your purchase!\n\t\t\t\t\t");
					system("pause");
				}

				else
					exitButton = 0; //store 0 to exitButton, loop end.
			}

			else//validation
				printf("\n\t\t\t\t\t\tEnter a valid choice\n");

		} while (exitButton == 1); //it will continue loop if exitButton=1


		//ask users if they confirm the order
		do 
		{
			printf("\t\t\t\t\t Confirm the order?(Y = Yes, N=No) : ");
			scanf("%c", &cOrder);
			rewind(stdin);

			//if no , users can reenter the other choice again
			if (cOrder == 'N' | cOrder == 'n')
			{
				quantityBook[0] =0 , quantityBook[1] = 0 , quantityBook[2] = 0 , quantityBook[3] = 0 ,quantityBook[4] = 0 , quantityBook[5] = 0 , quantityBook[6] = 0 , quantityBook[7] =0 ,quantityBook[8] = 0;
				exitButton = 1;
				--salesOrder;
				system("cls");
			}

			//if yes, generate a receipt
			else if (cOrder == 'Y' | cOrder == 'y')
			{
				system("cls");
				confirmOrder();		
			}

			else
				printf("\n\t\t\t\t\t\t Enter a valid choice\n");

		} while (cOrder != 'Y' && cOrder != 'y' && cOrder != 'N' && cOrder != 'n'); //validation 
		
		salesOrder++;

	} while (i == 1); //if i=1, loop will continue
}

void confirmOrder()/*receipt*/ 
{

	//declaration
	double totalToPay=0.00 , subTotal=0.00 , discount=0.00 ;
	int z;

	//printing a receipt for an order
	for (z = 0; z < 9; z++)
	{
		if (quantityBook[z] > 0) //check if quantity of book > 0, print and store the quantity
		{
			printf("\t\t\t%-4s %c %s %-5d %10s %6.2lf %-12s %-5s %2s %8.2lf\n", "Book", book[z], ":", quantityBook[z], "@ RM", PRICE_BOOK[z], "", "=", "RM", quantityBook[z] * PRICE_BOOK[z]);
			totalQuantity[z] += quantityBook[z];
		}
	}
	
	//calculating subtotal
	subTotal = (quantityBook[0] * PRICE_BOOK[0]) + (quantityBook[1] * PRICE_BOOK[1]) + (quantityBook[2] * PRICE_BOOK[2]) + (quantityBook[3] * PRICE_BOOK[3]) + (quantityBook[4] * PRICE_BOOK[4]) +
		(quantityBook[5] * PRICE_BOOK[5]) + (quantityBook[6] * PRICE_BOOK[6]) + (quantityBook[7] * PRICE_BOOK[7]) + (quantityBook[8] * PRICE_BOOK[8]);
	
	printf("\t\t\t%63s\n","==============");

	//calculating discount for an order
	if (subTotal > 200 && subTotal<300) //Purchase more than RM200
	{
		discount = subTotal * DISCOUNT1;
		totalToPay = subTotal - discount;
		printf("\t\t\t%-8s %38c %3s %-2s %8.2lf\n", "Subtotal",'=',"","RM", subTotal);
		printf("\t\t\t%-8s %35c %3s %-2s %8.2lf\n", "Discount 5%", '=', "", "RM", discount);
		printf("\t\t\t%63s\n","==============");
		printf("\t\t\t%-8s %34c %3s %-2s %8.2lf\n", "Total to pay", '=', "", "RM", totalToPay);
		printf("\t\t\t%63s\n", "==============");
	}

	else if (subTotal > 300 && subTotal<500)  //Purchase more than 300
	{
		discount = subTotal * DISCOUNT2;
		totalToPay = subTotal - discount;
		printf("\t\t\t%-8s %38c %3s %-2s %8.2lf\n", "Subtotal", '=', "", "RM", subTotal);
		printf("\t\t\t%-8s %34c %3s %-2s %8.2lf\n", "Discount 10%", '=', "", "RM", discount);
		printf("\t\t\t%63s\n", "==============");
		printf("\t\t\t%-8s %34c %3s %-2s %8.2lf\n", "Total to pay", '=', "", "RM", totalToPay);
		printf("\t\t\t%63s\n", "==============");
	}

	else if (subTotal > 500) //Purchase more than 500
	{
		discount = subTotal * DISCOUNT3;
		totalToPay = subTotal - discount;
		printf("\t\t\t%-8s %38c %3s %-2s %8.2lf\n", "Subtotal", '=', "", "RM", subTotal);
		printf("\t\t\t%-8s %34c %3s %-2s %8.2lf\n", "Discount 15%", '=', "", "RM", discount);
		printf("\t\t\t%63s\n", "==============");
		printf("\t\t\t%-8s %34c %3s %-2s %8.2lf\n", "Total to pay", '=', "", "RM", totalToPay);
		printf("\t\t\t%63s\n", "==============");
	}

	else //purchase less below 200
	{
		discount = 0; 
		totalToPay = subTotal - discount;
		printf("\t\t\t%-8s %38c %3s %-2s %8.2lf\n", "Subtotal", '=', "", "RM", subTotal);
		printf("\t\t\t%-8s %38c %3s %-2s %8.2lf\n", "Discount", '=', "", "RM", discount);
		printf("\t\t\t%63s\n", "==============");
		printf("\t\t\t%-8s %34c %3s %-2s %8.2lf\n", "Total to pay", '=', "", "RM", totalToPay);
		printf("\t\t\t%63s\n", "==============");
	}
	printf("\n\t\t\t\t\t  THANK YOU,HAVE A NICE DAY!\n\t\t\t\t\t ");
	system("pause");

	//ask user if they have a next order or not
	do
	{
		printf("\t\t\t\t\tNext order?( Y = yes, N= no) : ");
		scanf("%c", &nOrder);
		rewind(stdin);

		if (nOrder == 'Y' | nOrder == 'y') //i=1 ,continue loop for menu 3
		{
			i = 1;
			exitButton = 1;
			quantityBook[0] = 0, quantityBook[1] = 0, quantityBook[2] = 0, quantityBook[3] = 0, quantityBook[4] = 0,
				quantityBook[5] = 0, quantityBook[6] = 0, quantityBook[7] = 0, quantityBook[8] = 0;
			system("cls");
		}

		else if (nOrder == 'N' | nOrder == 'n') //jump out the loop of menu 3 and go for summary report
		{
			i = 0;  // i=0 , will exit loop of menu3
			system("cls");
			summaryReport();
		}

		else
			printf("\t\t\t\t\t  Enter a valid choice(Y / N)\n");
	} while (nOrder!='Y' && nOrder != 'y' && nOrder != 'N' && nOrder != 'n'); //validation
}

void summaryReport()
{
	//declaration and initializing
	float amount, totalAmount = 0.00;
	int amtQuantity = 0,a;


	printf("\t\t\t\t\tDAILY SALES ORDER SUMMARY REPORT\n");
	printf("\n\t\t\t\t\tTotal Number of Sales Orders = %d\n\n", salesOrder);

	printf("\t\t\t\t    %-6s %21s   %11s	\n", "Book ", "Quantity Sold Sales", "Amount");
	printf("\t\t\t\t    %-6s %21s   %11s	\n", "-----", "--------------------", "-----------");

	for (a = 0; a < 9; a++) //loop for generating total quantity and total amount of Book A to Book I for a day
	{
		amount = totalQuantity[a] * PRICE_BOOK[a]; 

		printf("\t\t\t\t    %3c %24d   RM%9.2f\n", book[a], totalQuantity[a], amount);

		amtQuantity += totalQuantity[a];
		totalAmount += amount; 
	}

	printf("\t\t\t\t    %-6s %21s   %11s	\n", "-----", "--------------------", "-----------");
	printf("\t\t\t\t    %-6s %21d   RM%9.2f	\n\n", "TOTAL", amtQuantity, totalAmount);
	endingMsg();
	system("pause");
	
}

void endingMsg()//display ending message
{
	printf("\n\n");
	printf("\t\t\t\t\t THANKS FOR SHOPPING WITH US!!\n");
	printf("\t\t\t\t\t       SEE YOU NEXT TIME!\n\n\n\t\t\t\t\t");
	exit(0);
}