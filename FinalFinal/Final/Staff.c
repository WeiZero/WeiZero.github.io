#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#pragma warning (disable:4996)
#define PRODUCT_FILE "product.dat"
#define BACKUP_FILE "productBackup.dat"
#define MAX_PRODUCTS 20
#define MAX_STAFF 20
#define MAX_MEMBER 100

//structure for Staff
struct Date {
	int day, month, year;
};

typedef struct {
	char staffId[10];
	char name[20];
	char gender;
	int age;
	char position[50];
	struct Date dob;
	char password[20];
	char status[10];
	int currentLogin;
	int secQuestion;
	char secAnswer[20];
	char downline[10];
}Staff;

//Structure for Member Module
typedef struct {
	char memberId[10];
	char name[20];
	char gender;
	int age;
	struct Date dob;
	struct Date JoinedDate;
	char tier;
	char status[10];
	char upline[10], downline[10];
}Member;

//Structure for Stock Module
typedef struct {
	char itemCode[6], itemName[40];
	double costPrice, sellPrice;
	char supplierName[40];
	int quantityInStock, totalQuantitySold, minimumLevel, reorderQuantity;
	struct Date itemRestockDate;
	char itemStatus[22];
}Warehouse;

//function declaration
void readStaff(Staff staff[], int* nStaff);
void mainMenu(Staff staff[], int* nStaff);
void loginStaff(Staff staff[], int nStaff);
void passRecovery(Staff staff[], int nStaff); void secQ(Staff staff[], int nStaff);
void staffMenu(Staff staff[], int* nStaff);
void displayStaff(Staff staff[], int nStaff);
void searchStaff(Staff staff[], int nStaff);
void viewStaff(Staff staff[], int nStaff);
void addStaff(Staff staff[], int* nStaff);
void removeStaff(Staff staff[], int nStaff);
void editStaff(Staff staff[], int indexToEdit); //problem
void saveStaff(Staff staff[], int nStaff);

void loginStaff(Staff staff[], int nStaff) {
	char staffId[99], password[20];   //array size
	int loginStatus = -1, staffIndex = 0;
	do {
		printf("=========STAFF LOGIN============\n");
		printf("Please enter your Staff ID and password to login:\n");
		printf("Staff ID (STXXX) : ");
		rewind(stdin);
		gets(staffId);
		while (staffId[0] != 'S' || staffId[1] != 'T' || !isdigit(staffId[2]) || !isdigit(staffId[3]) || !isdigit(staffId[4]) || strlen(staffId) != 5) {
			printf("Invalid input!\n");
			printf("Please enter staff id in format STXXX: ");
			rewind(stdin);
			gets(staffId);
		}
		printf("Password : ");
		rewind(stdin);
		scanf("%s", &password);

		for (int i = 0; i < nStaff; i++) {
			if (strcmp(staffId, staff[i].staffId) == 0) {
				staffIndex = i;
				if (strcmp(password, staff[staffIndex].password) == 0) {
					loginStatus = 1;
					if (strcmp(staff[staffIndex].status, "Inactive") == 0) {
						loginStatus = 2;
					}
				}
			}
		}
		if (loginStatus == 1) {
			staff[staffIndex].currentLogin = 1;
			system("cls");
			printf("Login Successful!\nWelcome, %s!\n\n", staff[staffIndex].name);
			printf("Staff ID  : %s\n", staff[staffIndex].staffId);
			printf("Name      : %s\n", staff[staffIndex].name);
			printf("Gender    : %c\n", staff[staffIndex].gender);
			printf("Position  : %s\n\n", staff[staffIndex].position);
			//printf("D.O.B: %02d/%02d/%d\n", staff[staffIndex].dob.day, staff[staffIndex].dob.month, staff[staffIndex].dob.year);
			mainMenu(staff, &nStaff);
		}
		else if (loginStatus == 2) {
			printf("\nStaff account are currently not available. \nPlease contact the Administrator.\n");
			printf("Staff ID: %s\n", staff[staffIndex].staffId);
			printf("Name: %s\n", staff[staffIndex].name);
			printf("Gender: %c\n", staff[staffIndex].gender);
			printf("Position: %s\n", staff[staffIndex].position);
			system("pause");
		}
		else {
			printf("Invalid staff ID or password. Please try again.\n");
			printf("Forget Password ? Y/N  : ");
			char yesNo;
			rewind(stdin);
			yesNo = toupper(getchar());
			while (yesNo != 'Y' && yesNo != 'N') {
				printf("Invalid Input! Enter 'Y' for yes or 'N' for No only.\n");
				printf("Forget Password ? Y/N  : ");
				rewind(stdin);
				yesNo = toupper(getchar());
			}system("cls");
			if (yesNo == 'Y') {
				passRecovery(staff, nStaff);
			}
		}
	} while (loginStatus != 1);

}

void passRecovery(Staff staff[], int nStaff) {
	char secAns[20], staffId[6];
	struct Date dobRecovery;
	int attempt = 0, maxAttempt = 2, found = 0, foundIndex, validDate = 0;
	printf("Password Recovery:\n");
	printf("Staff ID : ");
	rewind(stdin);
	gets(staffId);
	while (staffId[0] != 'S' || staffId[1] != 'T' || !isdigit(staffId[2]) || !isdigit(staffId[3]) || !isdigit(staffId[4]) || strlen(staffId) != 5) {
		printf("Invalid input!\n");
		printf("Please enter staff id in format STXXX: ");
		rewind(stdin);
		gets(staffId);
	}
	for (int i = 0; i < nStaff; i++) {
		if (strcmp(staffId, staff[i].staffId) == 0) {
			found = 1;
			foundIndex = i;
			do {
				printf("Enter Date of Birth dd/mm/yyyy (-100 to back) : ");
				rewind(stdin);
				scanf("%d/%d/%d", &dobRecovery.day, &dobRecovery.month, &dobRecovery.year);
				if (dobRecovery.day == -100) {
					system("cls");
					return;
				}
				SYSTEMTIME t;
				GetLocalTime(&t);
				while (!validDate) {
					if (dobRecovery.day < 1 || dobRecovery.day > 31 || dobRecovery.month < 1 || dobRecovery.month > 12 || dobRecovery.year <1900 || dobRecovery.year > t.wYear - 18) {
						validDate = 0;
					}
					else if (dobRecovery.month == 2 && (dobRecovery.day > 29 || (dobRecovery.day == 29 && (dobRecovery.year % 4 != 0 || (dobRecovery.year % 100 == 0 && dobRecovery.year % 400 != 0))))) {
						validDate = 0;
					}
					else if ((dobRecovery.month == 4 || dobRecovery.month == 6 || dobRecovery.month == 9 || dobRecovery.month == 11) && dobRecovery.day > 30) {
						validDate = 0;
					}
					else {
						validDate = 1;
					}
					if (validDate != 1) {
						printf("Invalid Date! Enter v date (DD/MM/YYYY) : ");
						scanf("%d/%d/%d", &dobRecovery.day, &dobRecovery.month, &dobRecovery.year);
					}
				}
				secQ(staff, i);
				rewind(stdin);
				scanf("%[^\n]", &secAns);
				if (dobRecovery.day == staff[i].dob.day
					&& dobRecovery.month == staff[i].dob.month
					&& dobRecovery.year == staff[i].dob.year
					&& strcmp(secAns, staff[i].secAnswer) == 0) {
					printf("Your password is: %s\n", staff[i].password);
					return;
				}
				else {
					printf("Incorrect. %d attempts left.\n", maxAttempt - attempt);
					attempt++;
				}
			} while (attempt <= maxAttempt);

			if (attempt >= maxAttempt) {
				printf("Maximum number of attempts reached. Please try again later.\n\n");
			}
		}
	}
	if (found != 1) {
		printf("Staff ID not found, please contact Administrator\n\n");
	}
}

void secQ(Staff staff[], int staffIndex) {
	switch (staff[staffIndex].secQuestion)
	{
	case 1:
		printf("What is your favorite color?\n");
		break;
	case 2:
		printf("What was the name of your first pet?\n");
		break;
	case 3:
		printf("What is your favorite movie?\n");
		break;
	default:
		break;
	}
}

void mainMenu(Staff staff[], int* nStaff) {
	int choice;
	//Stock Module
	Warehouse items[MAX_PRODUCTS];
	int itemCount = 0;
	//Member Module
	Member member[MAX_MEMBER];
	int nMember = 0;
	do {
		printf("=============Main Menu=============\n");
		printf("Choose what to do next : \n");
		printf("1. Staff\n");
		printf("2. Member\n");
		printf("3. Stock\n");
		printf("4. Sales\n");
		printf("5. Logout\n");
		//6.exit program
		printf("Enter your choice : ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			staffMenu(staff, nStaff);
			break;
		case 2:
			system("cls");
			memberMenu(member, nMember);
			break;
		case 3:
			system("cls");
			stockMenu(items, itemCount);
			break;
			//case 4:
			//system("cls");
			//    salesMenu();
			//    break;
		case 5:
			printf("Exiting program...\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 5);
}

void staffMenu(Staff staff[], int* nStaff) {
	int selection;
	do {
		printf("============Staff Menu==============\n");
		printf("Please enter your selection:\n");
		printf("1. Display All Staff\n");
		printf("2. Search Staff\n");
		printf("3. View and Edit Staff\n");
		printf("4. Add Staff\n");
		printf("5. Remove Staff\n");
		printf("6. Back\n");

		printf("Enter your selection : ");
		rewind(stdin);
		//scanf%c  isdigit atoi
		scanf("%d", &selection);
		system("cls");
		switch (selection)
		{
		case 1:
			displayStaff(staff, *nStaff);
			break;
		case 2:
			searchStaff(staff, *nStaff);
			break;
		case 3:
			viewStaff(staff, *nStaff);
			break;
		case 4:
			addStaff(staff, &(*nStaff));
			break;
		case 5:
			removeStaff(staff, *nStaff);
			break;
			//case 6:
			//	printf("Goodbye\n\n");
			//	writeStaff(staff, nStaff);
			//	int loginStatus = 0;
			//	break;
		default:
			printf("Invalid selection. Please re-enter your selection.\n\n");
			break;
		}
	} while (selection != 6);
}

void displayStaff(Staff staff[], int nStaff) {
	system("cls");
	printf("======STAFF===========\n");
	printf("%-10s %-15s %-10s %-15s %-15s %-10s\n",
		"Staff ID", "Name", "Gender", "Position", "Date of Birth", "Status");
	printf("%-10s %-15s %-10s %-15s %-15s %-10s\n",
		"=========", "==============", "=========", "==============", "=============", "=========");
	for (int i = 0; i < nStaff; i++) {
		printf("%-10s %-15s %-10c %-15s %02d/%02d/%-0009d %-10s\n",
			staff[i].staffId, staff[i].name, staff[i].gender, staff[i].position, staff[i].dob.day, staff[i].dob.month, staff[i].dob.year, staff[i].status);
	}
	printf("\n< %d staff  Available> \n", nStaff);

}

void searchStaff(Staff staff[], int nStaff) {
	int month, year, selection, matchNum = 0;
	char search[100];
	Staff matchStaff[MAX_STAFF];
	do {
		printf("1.Search By Date of Birth\n");
		printf("2.Search By Data\n");
		printf("3.Back\n");
		printf("Enter your selection : ");
		rewind(stdin);
		scanf("%d", &selection);
		if (selection == 1) {
			printf("Enter month and year (MM/YYYY) : ");
			scanf("%d/%d", &month, &year);
			for (int i = 0; i < nStaff; i++) {
				if (staff[i].dob.month == month && staff[i].dob.year == year) {
					matchStaff[matchNum] = staff[i];
					matchNum++;
				}
			}
			if (matchNum == 0) {
				printf("No matching staff found.\n");
			}
			else {
				displayStaff(matchStaff, matchNum);
				matchNum = 0;
			}
		}
		else if (selection == 2) {
			printf("Enter search term : ");
			rewind(stdin);
			gets(search);
			for (int i = 0; i < nStaff; i++) {
				if (strlen(search) == 1 && toupper(staff[i].gender) == toupper(search[0])) {
					matchStaff[matchNum] = staff[i];
					matchNum++;
				}
				else if (strcmp(staff[i].staffId, search) == 0 ||
					strcmp(staff[i].name, search) == 0 ||
					staff[i].age == atoi(search) ||
					strcmp(staff[i].position, search) == 0 ||
					strcmp(staff[i].status, search) == 0) {
					matchStaff[matchNum] = staff[i];
					matchNum++;
				}
			}
			if (matchNum == 0) {
				printf("No matching staff found.\n");
			}
			else {
				displayStaff(matchStaff, matchNum);
				matchNum = 0;
			}
		}
		else if (selection == 3) {
			system("cls");
		}

		else {
			printf("Invalid selection. Please 1 or 2 only!\n");
		}
	} while (selection != 3);
}

void viewStaff(Staff staff[], int nStaff) {
	char staffId[10];
	int foundIndex = -1;

	for (int i = 0; i < nStaff; i++) {
		if (staff[i].currentLogin == 1 && strcmp(staff[i].position, "Administrator") == 0) {
			printf("As an Administrator, you are able to view and modify OWN and OTHERS staff details.\n\n");
			printf("Enter ID of Staff to view : ");
			rewind(stdin);
			gets(staffId);
			while (staffId[0] != 'S' || staffId[1] != 'T' || !isdigit(staffId[2]) || !isdigit(staffId[3]) || !isdigit(staffId[4]) || strlen(staffId) != 5) {
				printf("Invalid input!\n");
				printf("Please enter staff id in format STXXX: ");
				rewind(stdin);
				gets(staffId);
			}
			for (int j = 0; j < nStaff; j++) {
				if (strcmp(staffId, staff[j].staffId) == 0) {
					foundIndex = j;
					printf("Staff ID : %s\n", staff[j].staffId);
					printf("Name : %s\n", staff[j].name);
					printf("Gender: %c\n", staff[j].gender);
					printf("Age: %d\n", staff[j].age);
					printf("Position: %s\n", staff[j].position);
					printf("Date of Birth : %02d/%02d/%04d\n", staff[j].dob.day, staff[j].dob.month, staff[j].dob.year);
					printf("Password: %s\n", staff[j].password);
					secQ(staff, j);
					printf("Security Question Answer: %s\n", staff[j].secAnswer);
					//printf("Downline: %s\n", staff[j].downline);
					printf("Do you want to edit ? Y/N : ");
					char yesNo;
					rewind(stdin);
					scanf("%c", &yesNo);

					if (yesNo == 'Y') {
						editStaff(staff, foundIndex);
					}
				}
			}
		}
		else if (staff[i].currentLogin == 1 && strcmp(staff[i].position, "Administrator") != 0) {
			foundIndex = i;
			printf("As an staff, you are able to view and modify OWN staff details.\n\n");
			printf("Staff ID : %s\n", staff[i].staffId);
			printf("Name : %s\n", staff[i].name);
			printf("Gender: %c\n", staff[i].gender);
			printf("Age: %d\n", staff[i].age);
			printf("Position: %s\n", staff[i].position);
			printf("Date of Birth : %02d/%02d/%04d\n", staff[i].dob.day, staff[i].dob.month, staff[i].dob.year);
			printf("Password: %s\n", staff[i].password);
			secQ(staff, i);
			printf("Security Question Answer: %s\n", staff[i].secAnswer);
			//printf("Downline: %s\n", staff[nStaff].downline);
			printf("Do you want to edit ? Y/N : ");
			char yesNo;
			rewind(stdin);
			scanf("%c", &yesNo);

			if (yesNo == 'Y') {
				editStaff(staff, foundIndex);
			}
		}

	}
	if (foundIndex == -1) {
		printf("Record not found\n");
	}
}

void editStaff(Staff staff[], int indexToEdit) {
	int validDate = 1;
	Staff editingStaff;
	printf("\nEditing %s\n", staff[indexToEdit].staffId);
	printf("Enter name : ");
	rewind(stdin);
	gets(staff[indexToEdit].name);
	printf("Enter gender : ");
	rewind(stdin);
	staff[indexToEdit].gender = toupper(getchar());
	while (staff[indexToEdit].gender != 'M' && staff[indexToEdit].gender != 'F') {
		printf("Invalid input. Please enter M or F: ");
		rewind(stdin);
		staff[indexToEdit].gender = toupper(getchar());
	}
	printf("Enter age : ");
	scanf("%d", &staff[indexToEdit].age);
	printf("Enter position : ");
	rewind(stdin);
	gets(staff[indexToEdit].position);
	printf("Enter Date of Birth (DD/MM/YYYY) : ");
	scanf("%d/%d/%d", &staff[indexToEdit].dob.day, &staff[indexToEdit].dob.month, &staff[indexToEdit].dob.year);
	SYSTEMTIME t;
	GetLocalTime(&t);
	while (!validDate) {
		if (staff[indexToEdit].dob.day < 1 || staff[indexToEdit].dob.day > 31 || staff[indexToEdit].dob.month < 1 || staff[indexToEdit].dob.month > 12 || staff[indexToEdit].dob.year <1900 || staff[indexToEdit].dob.year > t.wYear - 18) {
			validDate = 0;
		}
		else if (staff[indexToEdit].dob.month == 2 && (staff[indexToEdit].dob.day > 29 || (staff[indexToEdit].dob.day == 29 && (staff[indexToEdit].dob.year % 4 != 0 || (staff[indexToEdit].dob.year % 100 == 0 && staff[indexToEdit].dob.year % 400 != 0))))) {
			validDate = 0;
		}
		else if ((staff[indexToEdit].dob.month == 4 || staff[indexToEdit].dob.month == 6 || staff[indexToEdit].dob.month == 9 || staff[indexToEdit].dob.month == 11) && staff[indexToEdit].dob.day > 30) {
			validDate = 0;
		}
		else {
			validDate = 1;
		}
		if (validDate != 1) {
			printf("Invalid Date! Enter valid date (DD/MM/YYYY) : ");
			scanf("%d/%d/%d", &staff[indexToEdit].dob.day, &staff[indexToEdit].dob.month, &staff[indexToEdit].dob.year);
		}
	}
	printf("Enter new passsword : ");
	rewind(stdin);
	gets(staff[indexToEdit].password);
	printf("Select a security question:\n");
	printf("\t1. What is your favorite color?\n");
	printf("\t2. What was the name of your first pet?\n");
	printf("\t3. What is your favorite movie?\nSecurity question : ");
	rewind(stdin);
	scanf("%d", &staff[indexToEdit].secQuestion);
	while (staff[indexToEdit].secQuestion != 1 && staff[indexToEdit].secQuestion != 2 && staff[indexToEdit].secQuestion != 3) {
		printf("Please enter 1, 2 or 3 only!\nSecurity question : ");
		scanf("%d", &staff[indexToEdit].secQuestion);
	}
	printf("Enter security question answer : ");
	rewind(stdin);
	gets(staff[indexToEdit].secAnswer);


	//display
	printf("\nEdited %s, \nNew Staff Detail is : \n", staff[indexToEdit].staffId);

	printf("Staff ID : %s\n", staff[indexToEdit].staffId);
	printf("Name : %s\n", staff[indexToEdit].name);
	printf("Gender: %c\n", staff[indexToEdit].gender);
	printf("Age: %d\n", staff[indexToEdit].age);
	printf("Position: %s\n", staff[indexToEdit].position);
	printf("Date of Birth : %02d/%02d/%04d\n", staff[indexToEdit].dob.day, staff[indexToEdit].dob.month, staff[indexToEdit].dob.year);
	printf("New Password: %s\n", staff[indexToEdit].password);
}

void addStaff(Staff staff[], int* nStaff) {
	char newId[10], confirm, validDate = 0;
	if (*nStaff >= MAX_STAFF) {
		printf("Storage Full\n");
	}
	else {
		printf("Adding New Staff: \n");
		printf("Enter name : ");
		rewind(stdin);
		gets(staff[*nStaff].name);
		printf("Enter gender (M/F) : ");
		rewind(stdin);
		staff[*nStaff].gender = toupper(getchar());
		while (staff[*nStaff].gender != 'M' && staff[*nStaff].gender != 'F') {
			printf("Invalid input. Please enter M or F: ");
			rewind(stdin);
			staff[*nStaff].gender = toupper(getchar());
		}
		printf("Enter age : ");
		rewind(stdin);
		scanf("%d", &staff[*nStaff].age);
		printf("Enter position : ");
		rewind(stdin);
		gets(staff[*nStaff].position);
		printf("Enter Date of Birth (DD/MM/YYYY) : ");
		scanf("%d/%d/%d", &staff[*nStaff].dob.day, &staff[*nStaff].dob.month, &staff[*nStaff].dob.year);
		SYSTEMTIME t;
		GetLocalTime(&t);
		while (!validDate) {
			if (staff[*nStaff].dob.day < 1 || staff[*nStaff].dob.day > 31 || staff[*nStaff].dob.month < 1 || staff[*nStaff].dob.month > 12 || staff[*nStaff].dob.year <1900 || staff[*nStaff].dob.year > t.wYear - 18) {
				validDate = 0;
			}
			else if (staff[*nStaff].dob.month == 2 && (staff[*nStaff].dob.day > 29 || (staff[*nStaff].dob.day == 29 && (staff[*nStaff].dob.year % 4 != 0 || (staff[*nStaff].dob.year % 100 == 0 && staff[*nStaff].dob.year % 400 != 0))))) {
				validDate = 0;
			}
			else if ((staff[*nStaff].dob.month == 4 || staff[*nStaff].dob.month == 6 || staff[*nStaff].dob.month == 9 || staff[*nStaff].dob.month == 11) && staff[*nStaff].dob.day > 30) {
				validDate = 0;
			}
			else {
				validDate = 1;
			}
			if (validDate != 1) {
				printf("Invalid Date! Enter v date (DD/MM/YYYY) : ");
				scanf("%d/%d/%d", &staff[*nStaff].dob.day, &staff[*nStaff].dob.month, &staff[*nStaff].dob.year);
			}
		}
		printf("Enter password : ");
		rewind(stdin);
		scanf("%[^\n]", &staff[*nStaff].password);
		sprintf(newId, "ST%03d", *nStaff + 1);
		strcpy(staff[*nStaff].staffId, newId);
		strcpy(staff[*nStaff].status, "Active");
		printf("Select a security question:\n");
		printf("\t1. What is your favorite color?\n");
		printf("\t2. What was the name of your first pet?\n");
		printf("\t3. What is your favorite movie?\nSecurity question : ");
		rewind(stdin);
		scanf("%d", &staff[*nStaff].secQuestion);
		while (staff[*nStaff].secQuestion != 1 && staff[*nStaff].secQuestion != 2 && staff[*nStaff].secQuestion != 3) {
			printf("Please enter 1, 2 or 3 only!\nSecurity question : ");
			scanf("%d", &staff[*nStaff].secQuestion);
		}
		printf("Enter security question answer : ");
		rewind(stdin);
		gets(staff[*nStaff].secAnswer);
		system("cls");
		printf("New Staff Detail:\n");
		printf("Staff ID                 : %s\n", staff[*nStaff].staffId);
		printf("Name                     : %s\n", staff[*nStaff].name);
		printf("Gender                   : %c\n", staff[*nStaff].gender);
		printf("Age                      : %d\n", staff[*nStaff].age);
		printf("Position                 : %s\n", staff[*nStaff].position);
		printf("Date of Birth            : %02d/%02d/%04d\n", staff[*nStaff].dob.day, staff[*nStaff].dob.month, staff[*nStaff].dob.year);
		printf("Password                 : %s\n", staff[*nStaff].password);
		printf("Security Question        : ");
		secQ(staff, *nStaff);
		printf("Security Question Answer : %s\n", staff[*nStaff].secAnswer);
		//(*nStaff)++;
		printf("Confirm Add? (Y/N) ");
		confirm = toupper(getchar());
		while (confirm != 'Y' && confirm != 'N') {
			printf("Invalid Input! Enter 'Y' for yes or 'N' for No only.\n");
			printf("Forget Password ? Y/N  : ");
			rewind(stdin);
			confirm = toupper(getchar());
		}
		if (confirm == 'Y') {
			printf("New staff added.");
			(*nStaff)++;
			nStaff = *nStaff;
			saveStaff(staff, nStaff);

		}
		else if (confirm == 'N') {
			printf("New staff NOT added.");
		}
	}
}


void removeStaff(Staff staff[], int nStaff) {
	char staffId[10];
	int foundIndex = -1;
	for (int i = 0; i < nStaff; i++) {
		if (staff[i].currentLogin == 1 && strcmp(staff[i].position, "Administrator") == 0) {
			printf("\nEnter ID of Staff to delete : ");
			rewind(stdin);
			gets(staffId);
			for (int j = 0; j < nStaff; j++) {
				if (strcmp(staff[j].staffId, staffId) == 0) {
					foundIndex = j;
					printf("Staff ID : %s\n", staff[j].staffId);
					printf("Name : %s\n", staff[j].name);
					printf("Gender: %c\n", staff[j].gender);
					printf("Age: %d\n", staff[j].age);
					printf("Position: %s\n", staff[j].position);
					printf("Date of Birth : %02d/%02d/%04d\n", staff[j].dob.day, staff[j].dob.month, staff[j].dob.year);
					printf("Password: %s\n", staff[j].password);
					secQ(staff, j);
					printf("Security Question Answer: %s\n", staff[j].secAnswer);
				}
			}
		}
		else if (staff[i].currentLogin == 1 && strcmp(staff[i].position, "Administrator") != 0) {
			foundIndex = i;
			printf("Only Administrator can delete a staff!");
		}
	}
	if (foundIndex == -1) {
		printf("Record not found\n");
	}
	else {
		char yesNo;
		printf("Are you sure want to delete ? Y/N : ");
		rewind(stdin);
		yesNo = toupper(getchar());
		while (yesNo != 'Y' && yesNo != 'N') {
			printf("Invalid input. Please enter Y or N: ");
			yesNo = toupper(getchar());
		}

		if (yesNo == 'Y') {
			strcpy(staff[foundIndex].status, "Inactive");
			printf("\nStaff %s deleted successfully!\n", staff[foundIndex].staffId);
		}
		else if (yesNo == 'N') {
			printf("\nStaff %s in NOT deleted !\n", staff[foundIndex].staffId);
		}
	}
}

void readStaff(Staff staff[], int* nStaff) {
	//read from the staff.txt
	FILE* stafffptr = fopen("staff.txt", "r");
	if (stafffptr == NULL) {
		printf("Unable to open the staff.txt file\n");
		exit(-1);
	}
	while (fscanf(stafffptr, "%[^|]|%[^|]|%c|%d|%[^|]|%d/%d/%d|%[^|]|%[^|]|%d|%[^|]|\n",
		&staff[*nStaff].staffId,
		&staff[*nStaff].name,
		&staff[*nStaff].gender,
		&staff[*nStaff].age,
		&staff[*nStaff].position,
		&staff[*nStaff].dob.day, &staff[*nStaff].dob.month, &staff[*nStaff].dob.year,
		&staff[*nStaff].password,
		&staff[*nStaff].status,
		//&staff[*nStaff].currentLogin,
		&staff[*nStaff].secQuestion,
		&staff[*nStaff].secAnswer) != EOF) {
		(*nStaff)++;
	}
	fclose(stafffptr);
}

void saveStaff(Staff staff[], int nStaff) {
	FILE* sStaff = fopen("staff.txt", "w");
	for (int i = 0; i < nStaff; i++) {
		fprintf(sStaff, "%s|%s|%c|%d|%s|%d/%d/%d|%s|%s|%d|%s|\n",
			staff[i].staffId,
			staff[i].name,
			staff[i].gender,
			staff[i].age,
			staff[i].position,
			staff[i].dob.day, staff[i].dob.month, staff[i].dob.year,
			staff[i].password,
			staff[i].status,
			staff[i].secQuestion,
			staff[i].secAnswer);
	}
	fclose(sStaff);
}