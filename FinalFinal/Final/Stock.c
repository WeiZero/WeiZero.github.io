#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#pragma warning (disable:4996)
#define PRODUCT_FILE "product.dat"
#define BACKUP_FILE "productBackup.dat"
#define MAX_PRODUCTS 20

//Structure for Stock Module
struct Date {
	int day, month, year;
};

typedef struct {
	char itemCode[6], itemName[40];
	double costPrice, sellPrice;
	char supplierName[40];
	int quantityInStock, totalQuantitySold, minimumLevel, reorderQuantity;
	struct Date itemRestockDate;
	char itemStatus[22];
}Warehouse;

//Main
void displayProducts(Warehouse items[], int itemCount); //done + valid
int addProducts(Warehouse items[], int itemCount); //done + valid
void viewProduct(Warehouse items[], int itemCount);//done + valid
void modifyProducts(Warehouse items[], int itemCount); //done + valid
void deleteProducts(Warehouse items[], int itemCount);//done + valid
void searchProduct(Warehouse items[], int itemCount); //done + valid
void stockMenu(Warehouse items[], int itemCount); //done + valid
int backup(Warehouse items[], int itemCount); //done + valid

//Add Item Sub Functions
char productID(Warehouse items[], int itemCount, int* continueInput, int duplicateCode);
char productName(Warehouse items[], int itemCount, int* continueInput, int duplicateCode);
double productCostPrice(Warehouse items[], int itemCount, int* continueInput);
double productSellPrice(Warehouse items[], int itemCount, int* continueInput);
char productSupplierName(Warehouse items[], int itemCount, int* continueInput);
int productQuantity(Warehouse items[], int itemCount, int* continueInput);
int productQuantitySold(Warehouse items[], int itemCount, int* continueInput);
int productMinimumLevel(Warehouse items[], int itemCount, int* continueInput);
int productReorderQuantity(Warehouse items[], int itemCount, int* continueInput);
int productDate(Warehouse items[], int itemCount, int* continueInput);

//Misc. 
void displaySearchHeader();
void productDetails(Warehouse items[], int i);
void productStatistics(Warehouse items[], int i);

//Add Products Sub Functions
char productID(Warehouse items[], int itemCount, int* continueInput, int duplicateCode) {
	printf("Main Menu\\Add Products\n");
	do
	{
		duplicateCode = 1;
		printf("(Must be only 5 characters Ex: A1234) (Enter # to go back to Main Menu)\n");
		printf("Enter Product Code : ");
		rewind(stdin);
		gets(items[itemCount].itemCode);

		if (strcmp(items[itemCount].itemCode, "#") == 0) {
			(*continueInput)--;// 1 - 1 =0
			break;
		}

		else if (islower(items[itemCount].itemCode[0]) != 0) //if the letter is a small capital, will run this
		{
			items[itemCount].itemCode[0] = items[itemCount].itemCode[0] - 32; // Converts the first letter to capital
		}

		else if (strlen(items[itemCount].itemCode) != 5 || isalpha(items[itemCount].itemCode[0]) == 0)
		{
			printf("Invalid Product Code Length/First Letter must be an alphabet! Please Try Again\n\n");
		}

		for (int i = 1; i < 5; i++)
		{
			if (isdigit(items[itemCount].itemCode[i]) == 0) {
				printf("Formatting Error!\n\n");
				break;
			}
		}

		for (int j = 0; j < itemCount; j++)
		{
			if (strcmp(items[itemCount].itemCode, items[j].itemCode) == 0) {
				printf("Item Code Already Exists!\n");
				duplicateCode--;
				break;
			}
		}
	} while (strlen(items[itemCount].itemCode) != 5 || isalpha(items[itemCount].itemCode[0]) == 0
		|| isdigit(items[itemCount].itemCode[1]) == 0 || isdigit(items[itemCount].itemCode[2]) == 0
		|| isdigit(items[itemCount].itemCode[3]) == 0 || isdigit(items[itemCount].itemCode[4]) == 0
		|| duplicateCode == 0);

}

char productName(Warehouse items[], int itemCount, int* continueInput, int duplicateCode) {
	do
	{
		duplicateCode = 1;
		printf("(Maximum length is 30 (Including spaces)) (Enter # to go back to Main Menu)\n");
		printf("Enter Product Name : ");
		rewind(stdin);
		scanf("%[^\n]", &items[itemCount].itemName);

		if (strcmp(items[itemCount].itemName, "#") == 0) {
			(*continueInput)--;
			break;
		}

		else if (strlen(items[itemCount].itemName) <= 0 || strlen(items[itemCount].itemName) > 30)
		{
			printf("Product Name length must be within 30! Please Try Again\n\n");
		}

		for (int j = 0; j < itemCount; j++)
		{
			if (strcmp(items[itemCount].itemName, items[j].itemName) == 0) {
				printf("Item Name Already Exists!\n");
				duplicateCode--;
				break;
			}
		}
	} while (strlen(items[itemCount].itemName) <= 0 || strlen(items[itemCount].itemName) > 30 || duplicateCode == 0);
}

double productCostPrice(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Product Cost Price : ");
		rewind(stdin);
		scanf("%lf", &items[itemCount].costPrice);

		if (items[itemCount].costPrice == -1) {
			(*continueInput)--;
			break;
		}

		else if (items[itemCount].costPrice < 1 || items[itemCount].costPrice > 9998)
		{
			printf("Please only within RM(1-9998) for price\n\n");
		}
	} while (items[itemCount].costPrice < 1 || items[itemCount].costPrice > 9998);
}

double productSellPrice(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Product Selling Price : ");
		rewind(stdin);
		scanf("%lf", &items[itemCount].sellPrice);

		if (items[itemCount].sellPrice == -1) {
			(*continueInput)--;
			break;
		}

		else if (items[itemCount].costPrice > items[itemCount].sellPrice || items[itemCount].sellPrice < 0 || items[itemCount].sellPrice > 9999)
		{
			printf("The product selling price must be higher than the cost price (Cost Price you entered is RM%.2lf)\n", items[itemCount].costPrice);
		}
	} while (items[itemCount].costPrice > items[itemCount].sellPrice || items[itemCount].sellPrice < 0 || items[itemCount].sellPrice > 9999);
}

char productSupplierName(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Maximum length is 30 (Including spaces)) (Enter # to go back to Main Menu)\n");
		printf("Enter Supplier Name : ");
		rewind(stdin);
		scanf("%[^\n]", &items[itemCount].supplierName);

		if (strcmp(items[itemCount].supplierName, "#") == 0) {
			(*continueInput)--;
			break;
		}

		else if (strlen(items[itemCount].supplierName) <= 0 || strlen(items[itemCount].supplierName) > 30)
		{
			printf("Supplier Name length must be within 30! Please Try Again\n\n");
		}

	} while (strlen(items[itemCount].supplierName) <= 0 || strlen(items[itemCount].supplierName) > 30);
}

int productQuantity(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Product Quantity In Stock : ");
		rewind(stdin);
		scanf("%d", &items[itemCount].quantityInStock);

		if (items[itemCount].quantityInStock == -1) {
			*(continueInput)--;
			break;
		}

		else if (items[itemCount].quantityInStock < 0 || items[itemCount].quantityInStock > 9999)
		{
			printf("Quantity in stock number range must be between 0-9999!\n\n");
		}
	} while (items[itemCount].quantityInStock < 0 || items[itemCount].quantityInStock > 9999);
}

int productQuantitySold(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Product Quantity Sold : ");
		rewind(stdin);
		scanf("%d", &items[itemCount].totalQuantitySold);

		if (items[itemCount].totalQuantitySold == -1) {
			*(continueInput)--;
			break;
		}

		else if (items[itemCount].totalQuantitySold < 0 || items[itemCount].totalQuantitySold > 9999)
		{
			printf("Quantity in stock number range must be between 0-9999!\n\n");
		}
	} while (items[itemCount].totalQuantitySold < 0 || items[itemCount].totalQuantitySold > 9999);
}

int productMinimumLevel(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Product Minimum Level : ");
		rewind(stdin);
		scanf("%d", &items[itemCount].minimumLevel);

		if (items[itemCount].minimumLevel == -1) {
			(*continueInput)--;
			break;
		}

		else if (items[itemCount].minimumLevel < 1 || items[itemCount].minimumLevel > 9999)
		{
			printf("Minimum Level number range must be between 1-9999\n\n");
		}
	} while (items[itemCount].minimumLevel < 1 || items[itemCount].minimumLevel > 9999);
}

int productReorderQuantity(Warehouse items[], int itemCount, int* continueInput) {
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Product Reorder Quantity : ");
		rewind(stdin);
		scanf("%d", &items[itemCount].reorderQuantity);

		if (items[itemCount].reorderQuantity == -1) {
			(*continueInput)--;
			break;
		}

		else if (items[itemCount].reorderQuantity < 1 || items[itemCount].reorderQuantity > 9999)
		{
			printf("Reorder Quantity number range must be between 1-9999\n\n");
		}
	} while (items[itemCount].reorderQuantity < 1 || items[itemCount].reorderQuantity > 9999);
}

int productDate(Warehouse items[], int itemCount, int* continueInput) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	do
	{
		printf("(Enter -1 to go back to Main Menu)\n");
		printf("Enter Item Restock Date (Year) (%0004d till %0004d) : ", t.wYear - 3, t.wYear);
		rewind(stdin);
		scanf("%0004d", &items[itemCount].itemRestockDate.year);

		if (items[itemCount].itemRestockDate.year == -1) {
			(*continueInput)--;
			break;
		}

		else if (items[itemCount].itemRestockDate.year >= t.wYear - 3 && items[itemCount].itemRestockDate.year <= t.wYear)
		{
			do
			{
				printf("(Enter -1 to go back to Main Menu)\n");
				printf("Enter Item Restock Date (Month) : ");
				rewind(stdin);
				scanf("%02d", &items[itemCount].itemRestockDate.month);

				if (items[itemCount].itemRestockDate.month == -1) {
					(*continueInput)--;
					break;
				}

				else if (items[itemCount].itemRestockDate.month == 1 || items[itemCount].itemRestockDate.month == 3 || items[itemCount].itemRestockDate.month == 5 || items[itemCount].itemRestockDate.month == 7 || items[itemCount].itemRestockDate.month == 8 || items[itemCount].itemRestockDate.month == 10 || items[itemCount].itemRestockDate.month == 12)
				{
					do//Entering 200 will ignore the third num and give 20 as day
					{
						printf("(Enter -1 to go back to Main Menu)\n");
						printf("Enter Item Restock Date (Day) : ");
						rewind(stdin);
						scanf("%02d", &items[itemCount].itemRestockDate.day);

						if (items[itemCount].itemRestockDate.day == -1) {
							(*continueInput)--;
							break;
						}

						else if (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 31)
						{
							printf("Wrong day input!\n\n");
						}
					} while (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 31);

					if (!continueInput) {
						system("cls");
						break;
					}
				}

				else if (items[itemCount].itemRestockDate.month == 4 || items[itemCount].itemRestockDate.month == 6 || items[itemCount].itemRestockDate.month == 9 || items[itemCount].itemRestockDate.month == 11)
				{
					do
					{
						printf("(Enter -1 to go back to Main Menu)\n");
						printf("Enter Item Restock Date (Day) : ");
						rewind(stdin);
						scanf("%02d", &items[itemCount].itemRestockDate.day);

						if (items[itemCount].itemRestockDate.day == -1) {
							(*continueInput)--;
							break;
						}

						else if (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 30)
						{
							printf("Wrong day input!\n\n");
						}
					} while (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 30);

					if (!continueInput) {
						system("cls");
						break;
					}
				}

				else if (items[itemCount].itemRestockDate.month == 2 && (items[itemCount].itemRestockDate.year % 4 != 0 && items[itemCount].itemRestockDate.year % 100 != 0))
				{
					do
					{
						printf("(Enter -1 to go back to Main Menu)\n");
						printf("Enter Item Restock Date (Day) : ");
						rewind(stdin);
						scanf("%02d", &items[itemCount].itemRestockDate.day);

						if (items[itemCount].itemRestockDate.day == -1) {
							(*continueInput)--;
							break;
						}

						else if (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 28)
						{
							printf("Wrong day input!\n\n");
						}
					} while (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 28);

					if (!continueInput) {
						system("cls");
						break;
					}
				}

				else if (items[itemCount].itemRestockDate.month == 2 && (items[itemCount].itemRestockDate.year % 4 == 0 || items[itemCount].itemRestockDate.year % 100 != 0))
				{
					do
					{
						printf("(Enter -1 to go back to Main Menu)\n");
						printf("Enter Item Restock Date (Day) : ");
						rewind(stdin);
						scanf("%02d", &items[itemCount].itemRestockDate.day);

						if (items[itemCount].itemRestockDate.day == -1) {
							(*continueInput)--;
							break;
						}

						else if (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 29)
						{
							printf("Wrong day input!\n\n");
						}
					} while (items[itemCount].itemRestockDate.day < 1 || items[itemCount].itemRestockDate.day > 29);

					if (!continueInput) {
						system("cls");
						break;
					}
				}

				else
				{
					printf("Wrong month input!\n\n");
				}
			} while (items[itemCount].itemRestockDate.month < 1 || items[itemCount].itemRestockDate.month > 12);

			if (!continueInput) {
				system("cls");
				break;
			}
		}

		else
		{
			printf("Must be within the last 3 years!\n\n");
		}
	} while (items[itemCount].itemRestockDate.year < t.wYear - 3 || items[itemCount].itemRestockDate.year > t.wYear);
}

//Misc.
void displaySearchHeader() {
	SYSTEMTIME t;
	GetLocalTime(&t);

	printf("\nProduct Details - as at %02d/%02d/%0004d %02d:%02d\n\n",
		t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
	printf("%-10s %-31s %-11s %-14s %-18s %-22s\n", "Item Code", "Item Name", "Cost Price", "Selling Price", "Quantity In Stock", "Item Status");
	printf("%-10s %-31s %-11s %-14s %-18s %-22s\n", "=========", "==============================", "==========", "=============", "=================", "=====================");
}

void productDetails(Warehouse items[], int i) {
	printf("=========================================================\n");
	printf("---General Information---\n", i + 1);
	printf("Item Code                : %s\n", items[i].itemCode);
	printf("Item Name                : %s\n", items[i].itemName);
	printf("Item Cost Price          : RM%.2lf\n", items[i].costPrice);
	printf("Item Sell Price          : RM%.2lf\n", items[i].sellPrice);
	printf("Supplier Name            : %s\n\n", items[i].supplierName);

	printf("---Stock and Sales Information---\n");
	printf("Quantity In Stock        : %d units\n", items[i].quantityInStock);
	printf("Total Quantity Sold      : %d units\n", items[i].totalQuantitySold);
	printf("Minimum Level            : %d units\n", items[i].minimumLevel);
	printf("Reorder Quantity         : %d units\n", items[i].reorderQuantity);
	printf("Last Restock Date        : %02d/%02d/%0004d\n", items[i].itemRestockDate.day, items[i].itemRestockDate.month, items[i].itemRestockDate.year);
	printf("Item Status              : %s\n", items[i].itemStatus);
	printf("=========================================================\n\n");
}

void productStatistics(Warehouse items[], int i) {
	printf("%d. %s\n", i + 1, items[i].itemName);
	printf("Sell Price                                                      RM%8.2lf\n", items[i].sellPrice);
	printf("Total Quantity Sold (Units)                                       %8d\n", items[i].totalQuantitySold);
	printf("                                                                ----------\n");
	printf("Total Sales Revenue (Sell Price * Total Quantity Sold)          RM%8.2lf\n", items[i].sellPrice * items[i].totalQuantitySold);
	printf("Cost Price                                                      RM%8.2lf\n", items[i].costPrice);
	printf("Total Cost of Goods Sold (Cost Price * Total Quantity Sold)     RM%8.2lf\n", items[i].costPrice * items[i].totalQuantitySold);
	printf("                                                                ----------\n");
	printf("Gross Profit                                                    RM%8.2lf\n", (items[i].sellPrice * items[i].totalQuantitySold) - (items[i].costPrice * items[i].totalQuantitySold));
	printf("                                                                ==========\n\n");
}

//Main Functions
void displayProducts(Warehouse items[], int itemCount) {
	FILE* ptr = fopen(PRODUCT_FILE, "rb");

	if (ptr == NULL) {
		printf("\n\nFail to open file!\n\n");
		return;
	}
	system("cls");
	printf("Main Menu\\Display Products");
	displaySearchHeader();
	while (fread(&items[itemCount], sizeof(items[itemCount]), 1, ptr)) {
		printf("%-10s %-31s RM%-9.2lf RM%-12.2lf %-18d %-22s\n", items[itemCount].itemCode, items[itemCount].itemName,
			items[itemCount].costPrice, items[itemCount].sellPrice, items[itemCount].quantityInStock, items[itemCount].itemStatus);
	}
	printf("\n\n");

	fclose(ptr);
}

int addProducts(Warehouse items[], int itemCount) {
	if (itemCount >= MAX_PRODUCTS)
	{
		printf("Storage Full!\n");
	}

	else if (itemCount < MAX_PRODUCTS)
	{
		char confirmAdd, addItem;
		do
		{
			if (itemCount >= MAX_PRODUCTS) {
				printf("Storage Full!\n");
				break;
			}

			FILE* addPtr = fopen(PRODUCT_FILE, "ab");

			int continueInput = 1, duplicateCode = 1;
			system("cls");
			productID(items, itemCount, &continueInput, duplicateCode);

			if (!continueInput) {
				system("cls");
				break;
			}

			productName(items, itemCount, &continueInput, duplicateCode);

			if (!continueInput) {
				system("cls");
				break;
			}

			productCostPrice(items, itemCount, &continueInput);


			if (!continueInput) {
				system("cls");
				break;
			}

			productSellPrice(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			productSupplierName(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			productQuantity(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			productQuantitySold(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			productMinimumLevel(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			productReorderQuantity(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			productDate(items, itemCount, &continueInput);

			if (!continueInput) {
				system("cls");
				break;
			}

			else if (items[itemCount].quantityInStock < items[itemCount].minimumLevel && items[itemCount].quantityInStock > 0)
			{
				strcpy(items[itemCount].itemStatus, "Active (Low on Stock)");
			}

			else if (items[itemCount].quantityInStock == 0)
			{
				strcpy(items[itemCount].itemStatus, "Active (Out of Stock)");
			}

			else if (items[itemCount].quantityInStock > 0)
			{
				strcpy(items[itemCount].itemStatus, "Active");
			}
			system("cls");
			do
			{
				printf("New Product Details\n");
				productDetails(items, itemCount);
				printf("(Y = Yes + Save, N = No + Discard Recently Added)\n");
				printf("Confirm Add? : ");
				rewind(stdin);
				confirmAdd = tolower(getchar());
				if (confirmAdd == 'y')
				{
					system("cls");
					printf("Saved Successfully!\n\n");
					fwrite(&items[itemCount], sizeof(items[itemCount]), 1, addPtr);
					itemCount++;
					break;
				}

				else if (confirmAdd == 'n')
				{
					break;
				}

				else
				{
					system("cls");
					printf("Enter only Y or N!\n\n");
				}

			} while (confirmAdd != 'y' && confirmAdd != 'n');

			fclose(addPtr);
			printf("(Y = yes)\n");
			printf("Add another product ? ");
			rewind(stdin);
			scanf("%c", &addItem);
			system("cls");
		} while (tolower(addItem) == 'y');
	}
	return itemCount;
}

void searchProduct(Warehouse items[], int itemCount) {
	SYSTEMTIME t;
	GetLocalTime(&t);

	char itemCode[99];
	int searchChoice, searchCount = 0;
	double startRange, endRange;
	printf("\n");
	do
	{
		printf("Main Menu\\Search Products\n"
			"Search by?\n"
			"1. Item Code\n"
			"2. Item Name\n"
			"3. Cost Price\n"
			"4. Sell Price\n"
			"5. Supplier Name\n"
			"6. Quantity\n"
			"7. Quantity Sold\n"
			"8. Go Back\n"
			"Choice : ");
		rewind(stdin);
		scanf("%d", &searchChoice);
		switch (searchChoice)
		{
		case 1:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Item Code\n");
				printf("\n(Enter # to go back)\n");
				printf("Search Item Code : ");
				rewind(stdin);
				gets(itemCode);

				if (strlen(itemCode) == 5)
				{
					if (islower(itemCode[0]) != 0) //if the letter is a small capital, will run this to uppercase it
					{
						itemCode[0] = itemCode[0] - 32; // Converts the first letter to capital
					}

					for (int i = 0; i < itemCount; i++) {
						if (strcmp(items[i].itemCode, itemCode) == 0) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}

				else if (itemCode[0] == '#') {
					system("cls");
					break;
				}

				else
				{
					printf("Invalid Length, Please Try Again!\n\n");
				}
			} while (tolower(itemCode[0]) != '#');
			break;

		case 2:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Item Name\n");
				printf("(Enter # to go back)\n");
				printf("Search Item Name : ");
				rewind(stdin);
				gets(itemCode);

				if (strlen(itemCode) <= 30 && itemCode[0] != '#')
				{
					for (int i = 0; i < itemCount; i++) {
						if (strcmp(items[i].itemName, itemCode) == 0) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}

				else if (itemCode[0] == '#') {
					system("cls");
					break;
				}

				else
				{
					printf("Invalid Length, Please Try Again!\n\n");
				}
			} while (tolower(itemCode[0]) != '#');
			break;

		case 3:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Cost Price\n");
				printf("(Enter -1 to go back)\n");
				printf("Search Cost Price Starting Range : RM ");
				rewind(stdin);
				scanf("%lf", &startRange);

				if (startRange == -1) {
					system("cls");
					break;
				}

				printf("                                       |\n"
					"                                       v\n");
				printf("                              To : RM ");
				rewind(stdin);
				scanf("%lf", &endRange);

				if (endRange == -1) {
					system("cls");
					break;
				}

				else if ((endRange < 0 || endRange > 9999) || (startRange < 0 || startRange > 9999))
				{
					printf("Invalid Input, Please Try Again!\n\n");
				}
				else if ((endRange >= 0 && endRange <= 9999) && (startRange >= 0 && startRange <= 9999)) {
					for (int i = 0; i < itemCount; i++) {
						if (items[i].costPrice >= startRange && items[i].costPrice <= endRange) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}
			} while (startRange != -1 || endRange != -1);
			break;

		case 4:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Sell Price\n");
				printf("(Enter -1 to go back)\n");
				printf("Search Sell Price Starting Range : RM ");
				rewind(stdin);
				scanf("%lf", &startRange);

				if (startRange == -1) {
					system("cls");
					break;
				}

				printf("                                       |\n"
					"                                       v\n");
				printf("                              To : RM ");
				rewind(stdin);
				scanf("%lf", &endRange);

				if (endRange == -1) {
					system("cls");
					break;
				}

				else if ((endRange < 0 || endRange > 9999) || (startRange < 0 || startRange > 9999))
				{
					printf("Invalid Input, Please Try Again!\n\n");
				}
				else if ((endRange >= 0 && endRange <= 9999) && (startRange >= 0 && startRange <= 9999)) {
					for (int i = 0; i < itemCount; i++) {
						if (items[i].sellPrice >= startRange && items[i].sellPrice <= endRange) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}
			} while (startRange != -1 || endRange != -1);
			break;

		case 5:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Supplier Name\n");
				printf("(Enter # to go back)\n");
				printf("Search Supplier Name : ");
				rewind(stdin);
				gets(itemCode);

				if (strlen(itemCode) <= 30 && itemCode[0] != '#')
				{
					for (int i = 0; i < itemCount; i++) {
						if (strcmp(items[i].supplierName, itemCode) == 0) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}

				else if (itemCode[0] == '#') {
					system("cls");
				}

				else
				{
					printf("Invalid Length, Please Try Again!\n\n");
				}
			} while (tolower(itemCode[0]) != '#');
			break;

		case 6:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Quantity In Stock\n");
				printf("(Enter -1 to go back)\n");
				printf("Search Quantity Starting Range (Units) : ");
				rewind(stdin);
				scanf("%lf", &startRange);

				if (startRange == -1) {
					system("cls");
					break;
				}

				printf("                                          |\n"
					"                                          v\n");
				printf("                                    To :  ");
				rewind(stdin);
				scanf("%lf", &endRange);

				if (endRange == -1) {
					system("cls");
					break;
				}

				else if ((endRange < 0 || endRange > 9999) || (startRange < 0 || startRange > 9999))
				{
					printf("Invalid Input, Please Try Again!\n\n");
				}
				else if ((endRange >= 0 && endRange <= 9999) && (startRange >= 0 && startRange <= 9999)) {
					for (int i = 0; i < itemCount; i++) {
						if (items[i].quantityInStock >= startRange && items[i].quantityInStock <= endRange) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}
			} while (startRange != -1 || endRange != -1);
			break;

		case 7:
			system("cls");
			do
			{
				printf("Main Menu\\Search Products\\Search by Quantity Sold\n");
				printf("(Enter -1 to go back)\n");
				printf("Search Quantity Sold Starting Range (Units) : ");
				rewind(stdin);
				scanf("%lf", &startRange);

				if (startRange == -1) {
					system("cls");
					break;
				}

				printf("                                               |\n"
					"                                               v\n");
				printf("                                         To : ");
				rewind(stdin);
				scanf("%lf", &endRange);

				if (endRange == -1) {
					system("cls");
					break;
				}

				else if ((endRange < 0 || endRange > 9999) || (startRange < 0 || startRange > 9999))
				{
					printf("Invalid Input, Please Try Again!\n\n");
				}
				else if ((endRange >= 0 && endRange <= 9999) && (startRange >= 0 && startRange <= 9999)) {

					for (int i = 0; i < itemCount; i++) {
						if (items[i].totalQuantitySold >= startRange && items[i].totalQuantitySold <= endRange) {
							printf("%d.\n", searchCount + 1);
							productDetails(items, i);
							searchCount++;
						}
					}
					printf("%d Matches Found\n", searchCount);
					searchCount = 0;
				}
			} while (startRange != -1 || endRange != -1);
			break;

		case 8:
			system("cls");
			break;

		default:
			system("cls");
			printf("Enter within 1-8!\n\n");
			break;
		}
	} while (searchChoice != 8);
}

void modifyProducts(Warehouse items[], int itemCount) {
	Warehouse renew;
	char modifyID[99], modifyChoice;
	int editChoice;
	SYSTEMTIME t;
	GetLocalTime(&t);
	system("cls");
	do
	{
		printf("Main Menu\\Modify Products\n");
		printf("Enter Item Code you want to edit (Enter # to go back to Main Menu) : ");
		rewind(stdin);
		gets(modifyID);

		if (strlen(modifyID) == 5)
		{
			if (islower(modifyID[0]) != 0) //if the letter is a small capital, will run this to uppercase it
			{
				modifyID[0] = modifyID[0] - 32; // Converts the first letter to capital
			}
			for (int i = 0; i < itemCount; i++) {
				if (strcmp(items[i].itemCode, modifyID) == 0) {
					productDetails(items, i);

					do
					{
						int continueModify = 1;
						printf("\nWhat part of the item do you want to modify?\n"
							"1. Item Code\n"
							"2. Item Name\n"
							"3. Item Cost Price\n"
							"4. Item Sell Price\n"
							"5. Supplier Name\n"
							"6. Quantity In Stock\n"
							"7. Quantity Sold\n"
							"8. Minimum Level\n"
							"9. Reorder Quantity\n"
							"10. Restock Date\n"
							"11. Update File and Go Back\n"
							"Choice : ");
						rewind(stdin);
						scanf("%d", &editChoice);
						switch (editChoice)
						{
						case 1:
							system("cls");
							do
							{
								printf("(Maximum length is 30 (Including spaces)) (Enter # to go back to Main Menu)\n");
								printf("Old Product Code : %s\n", items[i].itemCode);
								printf("New Product Code : ");
								rewind(stdin);
								scanf("%[^\n]", &renew.itemCode);

								if (strcmp(renew.itemCode, "#") == 0) {
									continueModify = 0;
									break;
								}

								else if (strlen(renew.itemCode) <= 0 || strlen(renew.itemCode) > 30)
								{
									printf("Product Name length must be within 30! Please Try Again\n\n");
								}
							} while (strlen(renew.itemCode) <= 0 || strlen(renew.itemCode) > 30);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									strcpy(items[i].itemCode, renew.itemCode);
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 2:
							system("cls");
							do
							{
								printf("(Maximum length is 30 (Including spaces)) (Enter # to go back to Main Menu)\n");
								printf("Old Product Name : %s\n", items[i].itemName);
								printf("New Product Name : ");
								rewind(stdin);
								scanf("%[^\n]", &renew.itemName);

								if (strcmp(renew.itemName, "#") == 0) {
									continueModify = 0;
									break;
								}

								else if (strlen(renew.itemName) <= 0 || strlen(renew.itemName) > 30)
								{
									printf("Product Name length must be within 30! Please Try Again\n\n");
								}
							} while (strlen(renew.itemName) <= 0 || strlen(renew.itemName) > 30);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									strcpy(items[i].itemName, renew.itemName);
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 3:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Old Product Cost Price : RM%.2lf\n", items[i].costPrice);
								printf("New Product Cost Price : RM");
								rewind(stdin);
								scanf("%lf", &renew.costPrice);

								if (renew.costPrice == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.costPrice > items[i].sellPrice || renew.costPrice < 0 || renew.costPrice > 9998)
								{
									printf("The product cost price must be lower than the selling price (Item Selling Price is RM%.2lf)\n", items[i].sellPrice);
								}
							} while (renew.costPrice < 0 || renew.costPrice > 9999 || renew.costPrice > items[i].sellPrice);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].costPrice = renew.costPrice;
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 4:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Old Product Selling Price : RM%.2lf\n", items[i].sellPrice);
								printf("New Product Selling Price : RM");
								rewind(stdin);
								scanf("%lf", &renew.sellPrice);

								if (renew.sellPrice == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.sellPrice < items[i].costPrice || renew.sellPrice < 0 || renew.sellPrice > 9999)
								{
									printf("The product selling price must be higher than the cost price (Cost Price you entered is RM%.2lf)\n", items[i].costPrice);
								}
							} while (renew.sellPrice < items[i].costPrice || renew.sellPrice < 0 || renew.sellPrice > 9999);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].sellPrice = renew.sellPrice;
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 5:
							system("cls");
							do
							{
								printf("(Maximum length is 30 (Including spaces)) (Enter # to go back to Main Menu)\n");
								printf("Old Supplier Name : %s\n", items[i].supplierName);
								printf("New Supplier Name : ");
								rewind(stdin);
								scanf("%[^\n]", &renew.supplierName);

								if (strcmp(renew.supplierName, "#") == 0) {
									continueModify = 0;
									break;
								}

								else if (strlen(renew.supplierName) <= 0 || strlen(renew.supplierName) > 30)
								{
									printf("Product Name length must be within 30! Please Try Again\n\n");
								}
							} while (strlen(renew.supplierName) <= 0 || strlen(renew.supplierName) > 30);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									strcpy(items[i].supplierName, renew.supplierName);
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 6:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Old Product Quantity In Stock : %d\n", items[i].quantityInStock);
								printf("New Product Quantity In Stock : ");
								rewind(stdin);
								scanf("%d", &renew.quantityInStock);

								if (renew.quantityInStock == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.quantityInStock < 0 || renew.quantityInStock > 9999)
								{
									printf("Quantity in stock number range must be between 0-9999!\n\n");
								}
							} while (renew.quantityInStock < 0 || renew.quantityInStock > 9999);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].quantityInStock = renew.quantityInStock;
									if (items[i].quantityInStock < items[i].minimumLevel && items[i].quantityInStock > 0 && strcmp(items[i].itemStatus, "Discontinued") != 0)
									{
										strcpy(items[i].itemStatus, "Active (Low on Stock)");
									}

									else if (items[i].quantityInStock == 0 && strcmp(items[i].itemStatus, "Discontinued") != 0)
									{
										strcpy(items[i].itemStatus, "Active (Out of Stock)");
									}

									else if (items[i].quantityInStock > 0 && strcmp(items[i].itemStatus, "Discontinued") != 0)
									{
										strcpy(items[i].itemStatus, "Active");
									}

									else if (strcmp(items[i].itemStatus, "Discontinued") != 0)
									{
										break;
									}
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 7:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Old Product Quantity Sold : %d\n", items[i].totalQuantitySold);
								printf("New Product Quantity Sold : ");
								rewind(stdin);
								scanf("%d", &renew.totalQuantitySold);

								if (renew.totalQuantitySold == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.totalQuantitySold < 0 || renew.totalQuantitySold > 9999)
								{
									printf("Quantity in stock number range must be between 0-9999!\n\n");
								}
							} while (renew.totalQuantitySold < 0 || renew.totalQuantitySold > 9999);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].totalQuantitySold = renew.totalQuantitySold;
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 8:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Old Product Minimum Level : %d\n", items[i].reorderQuantity);
								printf("New Product Minimum Level : ");
								rewind(stdin);
								scanf("%d", &renew.minimumLevel);

								if (renew.minimumLevel == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.minimumLevel < 1 || renew.minimumLevel > 9999)
								{
									printf("Minimum Level number range must be between 1-9999\n\n");
								}
							} while (renew.minimumLevel < 1 || renew.minimumLevel > 9999);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].minimumLevel = renew.minimumLevel;
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 9:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Old Product Reorder Quantity : %d\n", items[i].reorderQuantity);
								printf("New Product Reorder Quantity : ");
								rewind(stdin);
								scanf("%d", &renew.reorderQuantity);

								if (renew.reorderQuantity == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.reorderQuantity < 1 || renew.reorderQuantity > 9999)
								{
									printf("Reorder Quantity number range must be between 1-9999\n\n");
								}
							} while (renew.reorderQuantity < 1 || renew.reorderQuantity > 9999);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].reorderQuantity = renew.reorderQuantity;
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 10:
							system("cls");
							do
							{
								printf("(Enter -1 to go back to Main Menu)\n");
								printf("Enter Item Restock Date (Year) (%0004d till %0004d) : ", t.wYear - 3, t.wYear);
								rewind(stdin);
								scanf("%0004d", &renew.itemRestockDate.year);

								if (renew.itemRestockDate.year == -1) {
									continueModify = 0;
									break;
								}

								else if (renew.itemRestockDate.year >= t.wYear - 3 && renew.itemRestockDate.year <= t.wYear)
								{
									do
									{
										printf("(Enter -1 to go back to Main Menu)\n");
										printf("Enter Item Restock Date (Month) : ");
										rewind(stdin);
										scanf("%02d", &renew.itemRestockDate.month);

										if (renew.itemRestockDate.month == -1) {
											continueModify = 0;
											break;
										}

										if (renew.itemRestockDate.month == 1 || renew.itemRestockDate.month == 3 || renew.itemRestockDate.month == 5 || renew.itemRestockDate.month == 7 || renew.itemRestockDate.month == 8 || renew.itemRestockDate.month == 10 || renew.itemRestockDate.month == 12)
										{
											do//Entering 200 will ignore the third num and give 20 as day
											{
												printf("(Enter -1 to go back to Main Menu)\n");
												printf("Enter Item Restock Date (Day) : ");
												rewind(stdin);
												scanf("%02d", &renew.itemRestockDate.day);

												if (renew.itemRestockDate.day == -1) {
													continueModify = 0;
													break;
												}

												if (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 31)
												{
													printf("Wrong day input (1-31)!\n\n");
												}
											} while (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 31);

											if (!continueModify) {
												system("cls");
												break;
											}
										}

										else if (renew.itemRestockDate.month == 4 || renew.itemRestockDate.month == 6 || renew.itemRestockDate.month == 9 || renew.itemRestockDate.month == 11)
										{
											do
											{
												printf("(Enter -1 to go back to Main Menu)\n");
												printf("Enter Item Restock Date (Day) : ");
												rewind(stdin);
												scanf("%02d", &renew.itemRestockDate.day);

												if (renew.itemRestockDate.day == -1) {
													continueModify = 0;
													break;
												}

												if (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 30)
												{
													printf("Wrong day input (1-30)!\n\n");
												}
											} while (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 30);

											if (!continueModify) {
												system("cls");
												break;
											}
										}

										else if (renew.itemRestockDate.month == 2 && (renew.itemRestockDate.year % 4 != 0 && renew.itemRestockDate.year % 100 != 0))
										{
											do
											{
												printf("(Enter -1 to go back to Main Menu)\n");
												printf("Enter Item Restock Date (Day) : ");
												rewind(stdin);
												scanf("%02d", &renew.itemRestockDate.day);

												if (renew.itemRestockDate.day == -1) {
													continueModify = 0;
													break;
												}

												if (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 28)
												{
													printf("Wrong day input (1-28)!\n\n");
												}
											} while (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 28);

											if (!continueModify) {
												system("cls");
												break;
											}
										}

										else if (renew.itemRestockDate.month == 2 && (renew.itemRestockDate.year % 4 == 0 || renew.itemRestockDate.year % 100 != 0))
										{
											do
											{
												printf("(Enter -1 to go back to Main Menu)\n");
												printf("Enter Item Restock Date (Day) : ");
												rewind(stdin);
												scanf("%02d", &renew.itemRestockDate.day);

												if (renew.itemRestockDate.day == -1) {
													continueModify = 0;
													break;
												}

												if (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 29)
												{
													printf("Wrong day input (1-29)!\n\n");
												}
											} while (renew.itemRestockDate.day < 1 || renew.itemRestockDate.day > 29);

											if (!continueModify) {
												system("cls");
												break;
											}
										}

										else
										{
											printf("Wrong month input (1-12)!\n\n");
										}
									} while (renew.itemRestockDate.month < 1 || renew.itemRestockDate.month > 12);

									if (!continueModify) {
										system("cls");
										break;
									}
								}
								else
								{
									printf("Must be within the last 3 years!\n\n");
								}
							} while (renew.itemRestockDate.year < t.wYear - 3 || renew.itemRestockDate.year > t.wYear);

							if (!continueModify) {
								system("cls");
								break;
							}

							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Modify? : ");
								rewind(stdin);
								modifyChoice = tolower(getchar());
								if (modifyChoice == 'y')
								{
									system("cls");
									printf("Saved Successfully!\n\n");
									items[i].itemRestockDate.day = renew.itemRestockDate.day;
									items[i].itemRestockDate.month = renew.itemRestockDate.month;
									items[i].itemRestockDate.year = renew.itemRestockDate.year;
									break;
								}

								else if (modifyChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (modifyChoice != 'y' && modifyChoice != 'n');
							break;
						case 11:
							system("cls");
							printf("Updated Changes!\n");
							FILE* wPtr = fopen(PRODUCT_FILE, "wb");
							// fwrite
							for (int i = 0; i < itemCount; i++) {
								fwrite(&items[i], sizeof(items[i]), 1, wPtr);
							}
							fclose(wPtr);
							break;
						default:
							printf("Enter between 1-11!");
							break;
						}
					} while (editChoice != 11);
				}
			}
		}

		else if (modifyID[0] == '#') {
			system("cls");
		}

		else
		{
			printf("Invalid Length, Please Try Again!\n\n");
		}
	} while (tolower(modifyID[0]) != '#');

}

void viewProduct(Warehouse items[], int itemCount) {
	SYSTEMTIME t;
	GetLocalTime(&t);

	char viewID[99], hotItem[99], notHotItem[99];
	int viewChoice, viewMenu, totalUnitsSold = 0, hotUnits = 0, notHotUnits = 9999;
	double totalGrossProfit = 0;
	system("cls");
	do
	{
		printf("Main Menu\\View Product\n"
			"What do you want to do?\n"
			"1. View a specific product\n"
			"2. Generate Report\n"
			"3. Save changes\n"
			"4. Go Back\n"
			"Choice : ");
		rewind(stdin);
		scanf("%d", &viewMenu);

		switch (viewMenu)
		{
		case 1:
			system("cls");
			do
			{
				printf("Main Menu\\View Product\\View a specific product\n");
				printf("(Enter # to go back to Main Menu)\n");
				printf("Enter Item Code you want to view : ");
				rewind(stdin);
				gets(viewID);
				if (strlen(viewID) == 5)
				{
					if (islower(viewID[0]) != 0) //if the letter is a small capital, will run this to uppercase it
					{
						viewID[0] = viewID[0] - 32; // Converts the first letter to capital
					}
					for (int i = 0; i < itemCount; i++) {
						if (strcmp(items[i].itemCode, viewID) == 0) {
							productDetails(items, i);
							if (items[i].minimumLevel > items[i].quantityInStock && items[i].quantityInStock != 0)
							{
								printf("Warning : This product is low on stock!\n");
							}

							else if (items[i].quantityInStock == 0)
							{
								printf("Warning : This product has NO stock left, MUST restock immediately!\n");
							}
							do
							{
								printf("\nWhat do you want to do/check about the product\n"
									"1. Check Sales Statistics\n"
									"2. Restock Item\n"
									"3. Go Back\n"
									"Choice : ");
								rewind(stdin);
								scanf("%d", &viewChoice);

								switch (viewChoice)
								{
								case 1:
									system("cls");
									printf("Main Menu\\View Product\\View a specific product\\Check Sales Statistics\n");
									productStatistics(items, i);
									if (items[i].totalQuantitySold == 0)
									{
										printf("Gross Profit Margin                                                   0%%\n");
									}

									else if (items[i].totalQuantitySold > 0)
									{
										printf("Gross Profit Margin                                             %.0lf%%\n",
											(((items[i].sellPrice * items[i].totalQuantitySold) - (items[i].costPrice * items[i].totalQuantitySold)) / (items[i].sellPrice * items[i].totalQuantitySold)) * 100);
									}

									break;
								case 2:
									system("cls");
									printf("Main Menu\\View Product\\View a specific product\\Restock Item\n");
									printf("\n%d units of %s has been successfully ordered from %s!\n", items[i].reorderQuantity, items[i].itemName, items[i].supplierName);
									printf("Number of stocks has been successfully updated from %d units to %d units!\n", items[i].quantityInStock, items[i].quantityInStock + items[i].reorderQuantity);
									printf("Date of last restock date has been renewed to %02d/%02d/%0004d\n", t.wDay, t.wMonth, t.wYear);

									items[i].quantityInStock += items[i].reorderQuantity;
									items[i].itemRestockDate.day = t.wDay;
									items[i].itemRestockDate.month = t.wMonth;
									items[i].itemRestockDate.year = t.wYear;
									strcpy(items[i].itemStatus, "Active");
									break;
								case 3:
									system("cls");
									break;
								default:
									system("cls");
									printf("Enter within 1-3!\n");
									break;
								}
							} while (viewChoice != 3);
						}
					}
				}

				else if (viewID[0] == '#') {
					system("cls");
				}

				else
				{
					printf("Invalid Length, Please Try Again!\n\n");
				}

			} while (tolower(viewID[0]) != '#');
			break;

		case 2:
			printf("\n\nSales Report for All Products\n");
			for (int i = 0; i < itemCount; i++)
			{
				productStatistics(items, i);
				totalGrossProfit += ((items[i].sellPrice * items[i].totalQuantitySold) - (items[i].costPrice * items[i].totalQuantitySold));
				totalUnitsSold += items[i].totalQuantitySold;
				if (items[i].totalQuantitySold > hotUnits)
				{
					strcpy(hotItem, items[i].itemName);
					hotUnits = items[i].totalQuantitySold;
				}

				else if (items[i].totalQuantitySold < notHotUnits)
				{
					strcpy(notHotItem, items[i].itemName);
					notHotUnits = items[i].totalQuantitySold;
				}
			}
			printf("                                                                ==========\n");
			printf("Total Gross Profit for all products                             RM%8.2lf\n", totalGrossProfit);
			printf("Total Units Sold for all products (Units)                         %8d\n", totalUnitsSold);
			printf("Average Price Sold Per Product                                  RM%8.2lf\n", totalGrossProfit / totalUnitsSold);
			printf("                                                                ==========\n\n");

			printf("Most popular product is %s with %d units sold\n", hotItem, hotUnits);
			printf("Least popular product is %s with %d units sold\n\n", notHotItem, notHotUnits);
			break;

		case 3:
			system("cls");
			printf("Saved Changes!\n");
			FILE* viewPtr = fopen(PRODUCT_FILE, "wb");
			for (int i = 0; i < itemCount; i++) {
				fwrite(&items[i], sizeof(items[i]), 1, viewPtr);
			}
			fclose(viewPtr);
			break;

		case 4:
			system("cls");
			break;
		default:
			system("cls");
			printf("Enter within 1-3!\n");
			break;
		}
	} while (viewMenu != 4);
}

void deleteProducts(Warehouse items[], int itemCount) {
	char deleteID[99], deleteChoice;
	int dltMenuChoice;
	system("cls");
	do
	{
		printf("Main Menu\\Discontinue or Reactivate Products\n");
		printf("1. Discontinue a Product\n");
		printf("2. Reactivate a Product\n");
		printf("3. Update File and go Back\n");
		printf("Choice : ");
		rewind(stdin);
		scanf("%d", &dltMenuChoice);

		switch (dltMenuChoice)
		{
		case 1: // Discontinue
			system("cls");
			do
			{
				printf("Main Menu\\Delete Products\\Discontinue a Product\n");
				printf("(Enter # to go back to Main Menu)\n");
				printf("Enter Item Code you want to delete : ");
				rewind(stdin);
				gets(deleteID);
				if (strlen(deleteID) == 5)
				{
					if (islower(deleteID[0]) != 0) //if the letter is a small capital, will run this to uppercase it
					{
						deleteID[0] = deleteID[0] - 32; // Converts the first letter to capital
					}
					for (int i = 0; i < itemCount; i++) {
						if (strcmp(items[i].itemCode, deleteID) == 0) {
							if (strcmp(items[i].itemStatus, "Discontinued") == 0)
							{
								printf("Product Already Deleted!\n\n");
								break;
							}
							productDetails(items, i);
							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Delete? : ");
								rewind(stdin);
								deleteChoice = tolower(getchar());
								if (deleteChoice == 'y')
								{
									system("cls");
									printf("Changed Successfully!\n\n");
									strcpy(items[i].itemStatus, "Discontinued");
									break;
								}

								else if (deleteChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (deleteChoice != 'y' && deleteChoice != 'n');
						}
					}
				}

				else if (deleteID[0] == '#') {
					system("cls");
				}

				else
				{
					system("cls");
					printf("Invalid Length, Please Try Again!\n\n");
				}
			} while (tolower(deleteID[0]) != '#');
			break;

		case 2: // Reactivate
			system("cls");
			do
			{
				printf("Main Menu\\Delete Products\\Reactivate a Product\n");
				printf("(Enter # to go back to Main Menu)\n");
				printf("Enter Item Code you want to reactivate : ");
				rewind(stdin);
				gets(deleteID);
				if (strlen(deleteID) == 5)
				{
					if (islower(deleteID[0]) != 0) //if the letter is a small capital, will run this to uppercase it
					{
						deleteID[0] = deleteID[0] - 32; // Converts the first letter to capital
					}
					for (int i = 0; i < itemCount; i++) {
						if (strcmp(items[i].itemCode, deleteID) == 0) {
							if ((strcmp(items[i].itemStatus, "Active") == 0) || (strcmp(items[i].itemStatus, "Active (Out of Stock)") == 0) || (strcmp(items[i].itemStatus, "Active (Low on Stock)") == 0))
							{
								printf("Product is Already Active!\n\n");
								break;
							}
							productDetails(items, i);
							do
							{
								printf("(Y = Yes, N = No)\n");
								printf("Confirm Reactivation? : ");
								rewind(stdin);
								deleteChoice = tolower(getchar());
								if (deleteChoice == 'y')
								{
									system("cls");
									printf("Changed Successfully!\n\n");
									if (items[i].quantityInStock < items[i].minimumLevel && items[i].quantityInStock > 0)
									{
										strcpy(items[i].itemStatus, "Active (Low on Stock)");
									}

									else if (items[i].quantityInStock == 0)
									{
										strcpy(items[i].itemStatus, "Active (Out of Stock)");
									}

									else if (items[i].quantityInStock > 0)
									{
										strcpy(items[i].itemStatus, "Active");
									}
									break;
								}

								else if (deleteChoice == 'n')
								{
									break;
								}

								else
								{
									system("cls");
									printf("Enter only Y or N!\n\n");
								}

							} while (deleteChoice != 'y' && deleteChoice != 'n');
						}
					}
				}

				else if (deleteID[0] == '#') {
					system("cls");
				}

				else
				{
					system("cls");
					printf("Invalid Length, Please Try Again!\n\n");
				}
			} while (tolower(deleteID[0]) != '#');
			break;

		case 3: // Save
			system("cls");
			printf("Updated Changes!\n");
			FILE* deletePtr = fopen(PRODUCT_FILE, "wb");
			for (int i = 0; i < itemCount; i++) {
				fwrite(&items[i], sizeof(items[i]), 1, deletePtr);
			}
			fclose(deletePtr);
			break;
		default:
			break;
		}

	} while (dltMenuChoice != 3);
}

int backup(Warehouse items[], int itemCount) {
	int backupChoice;
	system("cls");
	do
	{
		printf("Main Menu/Backup\n"
			"1. Save Backup\n"
			"2. Load Backup\n"
			"3. Go Back\n"
			"Choice : ");
		rewind(stdin);
		scanf("%d", &backupChoice);


		if (backupChoice == 1)
		{

			FILE* savefptr = fopen(BACKUP_FILE, "wb");
			for (int i = 0; i < itemCount; i++)
			{
				fwrite(&items[i], sizeof(items[i]), 1, savefptr);
			}
			fclose(savefptr);
			system("cls");
			printf("Backup Saved Successfully!\n");
			break;
		}

		else if (backupChoice == 2)
		{
			itemCount = 0;
			FILE* loadfptr = fopen(BACKUP_FILE, "rb");
			FILE* loadfptr2 = fopen(PRODUCT_FILE, "wb");

			while (fread(&items[itemCount], sizeof(items[itemCount]), 1, loadfptr)) {
				itemCount++;
			}

			for (int i = 0; i < itemCount; i++)
			{
				fwrite(&items[i], sizeof(items[i]), 1, loadfptr2);
			}

			fclose(loadfptr);
			fclose(loadfptr2);
			system("cls");
			printf("Backup Loaded Successfully!\n");
			break;
		}

		else if (backupChoice == 3)
		{
			system("cls");
		}
	} while (backupChoice != 3);
	return itemCount;
}

void stockMenu(Warehouse items[], int itemCount) {
	int selection;

	FILE* itemptr = fopen(PRODUCT_FILE, "rb");

	if (itemptr == NULL) {
		printf("Fail to open\n");
		return;
	}

	while (fread(&items[itemCount], sizeof(items[itemCount]), 1, itemptr)) {
		itemCount++;
	}
	do
	{
		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		//	"@@@@                   @@@@@@@@  @@@@@@  @@@@@@@@@@@@  @@@@  @@@@  @@@@@@@@\n"
		//	"@@@@@@@@@@  @@@@@@@@@@@@@@@                  @@@@@@@@@  @@@  @@@  @@@@@@@@@\n"
		//	"@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@  @@@@@@  @@@@@@@@@@                    @@@@\n"
		//	"@@@@                   @@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@  @@@@\n"
		//	"@@@@  @@@@@@@@@@@@@@@  @@@@@  @@@@@@  @@@@@@@@@@@@@@@@@            @@@@@@@@\n"
		//	"@@@@  @@@@@@@@@@@@@@@  @@@@  @@  @@            @@@@@@@@ @@@@@@@@@@ @@@@@@@@\n"
		//	"@@@@  @@@@@@@@@@@@@@@  @@@      @@  @@@@@@@@@  @@@@@@@@ @@@@@@@@@@ @@@@@@@@\n"
		//	"@@@@                   @@@@@@  @@@@@@  @@@@@@  @@@@@@@@            @@@@@@@@\n"
		//	"@@@@  @@@@@@@@@@@@@@@  @@@@@  @@@@@@@@  @@@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@\n"
		//	"@@@@  @@@@@@@@@@@@@@@  @@@@      @@@@@@  @@@@  @@@@@@@@            @@@@@@@@\n"
		//	"@@@@  @@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@\n"
		//	"@@@@                   @@@       @@@@@@@@@     @@@@                   @@@@@\n"
		//	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n");
		printf("Main Menu\n"
			"Enter a choice\n"
			"1. Display Products\n"
			"2. Add Products\n"
			"3. Search Products\n"
			"4. Modify Products\n"
			"5. View Item\n"
			"6. Delete\\Reactivate Item\n"
			"7. Backup\n"
			"8. Exit\n"
			"Choice : ");
		rewind(stdin);
		scanf("%d", &selection);


		switch (selection)
		{
		case 1:
			displayProducts(items, itemCount);
			break;
		case 2:
			itemCount = addProducts(items, itemCount);
			break;
		case 3:
			searchProduct(items, itemCount);
			break;
		case 4:
			modifyProducts(items, itemCount);
			break;
		case 5:
			viewProduct(items, itemCount);
			break;
		case 6:
			deleteProducts(items, itemCount);
			break;
		case 7:
			itemCount = backup(items, itemCount);
			break;
		case 8:
			system("cls");
			break;
		default:
			system("cls");
			printf("Enter range between 1-8!\n\n");
			break;
		}
	} while (selection != 8);
}