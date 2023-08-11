#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#pragma warning (disable:4996)

#define MAX_MEMBER 100

struct Date {
	int day, month, year;
};

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

void readMember(Member member[], int* nMember);
void memberMenu(Member member[], int nMember);
void displayMember(Member member[], int nMember);
void searchMember(Member member[], int nMember);
void viewMember(Member member[], int nMember);
void editMember(Member member[], int indexToEdit, int nMember);
void addMember(Member member[], int* nMember);
void saveMember(Member member[], int nMember);
void removeMember(Member member[], int nMember);

void viewMember(Member member[], int nMember) {
	char memberId[10];
	int foundIndex = -1;

	printf("Enter ID of Member to view (MBXXX): ");
	rewind(stdin);
	gets(memberId);

	for (int i = 0; i < nMember; i++) {
		while (memberId[0] != 'M' || memberId[1] != 'B' || !isdigit(memberId[2]) || !isdigit(memberId[3]) || !isdigit(memberId[4]) || strlen(memberId) != 5) {
			printf("Invalid input!\n");
			printf("Please enter member id in format MBXXX: ");
			rewind(stdin);
			gets(memberId);
		}
		for (int j = 0; j < nMember; j++) {
			if (strcmp(memberId, member[j].memberId) == 0) {
				foundIndex = j;
				printf("Member ID     : %s\n", member[j].memberId);
				printf("Name          : %s\n", member[j].name);
				printf("Gender        : %c\n", member[j].gender);
				printf("Age           : %d\n", member[j].age);
				printf("Date of Birth : %02d/%02d/%04d\n", member[j].dob.day, member[j].dob.month, member[j].dob.year);
				printf("Date Joined   : %02d/%02d/%04d\n", member[j].JoinedDate.day, member[j].JoinedDate.month, member[j].dob.year);
				printf("Tier          :");
				switch (member[j].tier)
				{
				case 'M':
					printf("M - Normal Member\n");
					break;
				case 'S':
					printf("S - Silver Member\n");
					break;
				case 'G':
					printf("G - Gold Member\n");
					break;
				case 'P':
					printf("P - Platinium Member\n");
					break;
				default:
					break;
				}
				printf("Upline: %s\n", member[j].upline);
				printf("Downline: %s\n", member[j].downline);

				printf("Do you want to edit ? Y/N : ");
				char yesNo;
				rewind(stdin);
				scanf("%c", &yesNo);

				if (yesNo == 'Y') {
					editMember(member, foundIndex, nMember);
				}
			}
		}
	}
	if (foundIndex == -1) {
		printf("Record not found\n");
	}
}

void editMember(Member member[], int indexToEdit, int nMember) {
	int validDate = 1, found;
	Member editingMember;
	char upline[10], downline[10];
	printf("\nEditing %s\n", member[indexToEdit].memberId);
	printf("Enter name : ");
	rewind(stdin);
	gets(member[indexToEdit].name);
	printf("Enter gender : ");
	rewind(stdin);
	member[indexToEdit].gender = toupper(getchar());
	while (member[indexToEdit].gender != 'M' && member[indexToEdit].gender != 'F') {
		printf("Invalid input. Please enter M or F: ");
		rewind(stdin);
		member[indexToEdit].gender = toupper(getchar());
	}
	printf("Enter age : ");
	scanf("%d", &member[indexToEdit].age);
	printf("Enter Date of Birth (DD/MM/YYYY) : ");
	scanf("%d/%d/%d", &member[indexToEdit].dob.day, &member[indexToEdit].dob.month, &member[indexToEdit].dob.year);
	SYSTEMTIME t;
	GetLocalTime(&t);
	while (!validDate) {
		if (member[indexToEdit].dob.day < 1 || member[indexToEdit].dob.day > 31 || member[indexToEdit].dob.month < 1 || member[indexToEdit].dob.month > 12 || member[indexToEdit].dob.year <1900 || member[indexToEdit].dob.year > t.wYear - 18) {
			validDate = 0;
		}
		else if (member[indexToEdit].dob.month == 2 && (member[indexToEdit].dob.day > 29 || (member[indexToEdit].dob.day == 29 && (member[indexToEdit].dob.year % 4 != 0 || (member[indexToEdit].dob.year % 100 == 0 && member[indexToEdit].dob.year % 400 != 0))))) {
			validDate = 0;
		}
		else if ((member[indexToEdit].dob.month == 4 || member[indexToEdit].dob.month == 6 || member[indexToEdit].dob.month == 9 || member[indexToEdit].dob.month == 11) && member[indexToEdit].dob.day > 30) {
			validDate = 0;
		}
		else {
			validDate = 1;
		}
		if (validDate != 1) {
			printf("Invalid Date! Enter valid date (DD/MM/YYYY) : ");
			scanf("%d/%d/%d", &member[indexToEdit].dob.day, &member[indexToEdit].dob.month, &member[indexToEdit].dob.year);
		}
	}
	printf("Date Joined : Cannot Modify\n");
	printf("Tier : Cannot Modify\n");
	printf("Enter Upline ID :");
	gets(upline);
	do {
		while ((upline[0] != 'M' || upline[1] != 'B' || !isdigit(upline[2]) || !isdigit(upline[3]) || !isdigit(upline[4]) || strlen(upline) != 5) || (upline[0] != 'M' || upline[1] != 'B' || !isdigit(upline[2]) || !isdigit(upline[3]) || !isdigit(upline[4]) || strlen(upline) != 5)) {
			printf("Invalid input!\n");
			printf("Please enter upline id in format MBXXX or STXXX : ");
			rewind(stdin);
			gets(upline);
		}
		for (int i = 0; i < nMember; i++) {
			if ((strcmp(upline, member[i].memberId) == 0)   /* || (strcmp(upline, staff[i].staffId)*/) {
				found = 1;
			}
		}
		if (found != 1) {
			printf("Upline ID not found, ID is invalid!\n\n");
		}
	} while (found != 1);
	printf("Enter Downline ID :");
	gets(downline);
	do {
		while ((downline[0] != 'M' || downline[1] != 'B' || !isdigit(downline[2]) || !isdigit(downline[3]) || !isdigit(downline[4]) || strlen(downline) != 5) || (downline[0] != 'M' || downline[1] != 'B' || !isdigit(downline[2]) || !isdigit(downline[3]) || !isdigit(downline[4]) || strlen(downline) != 5)) {
			printf("Invalid input!\n");
			printf("Please enter downline id in format MBXXX or STXXX : ");
			rewind(stdin);
			gets(downline);
		}
		for (int i = 0; i < nMember; i++) {
			if ((strcmp(downline, member[i].memberId) == 0)/* || (strcmp(downline, staff[i].staffId)*/) {
				found = 1;
			}
		}
		if (found != 1) {
			printf("Upline ID not found, ID is invalid!\n\n");
		}
	} while (found != 1);

	printf("\nEdited %s, \nNew Member Detail is : \n", member[indexToEdit].memberId);
	printf("Member ID     : %s\n", member[indexToEdit].memberId);
	printf("Name          : %s\n", member[indexToEdit].name);
	printf("Gender        : %c\n", member[indexToEdit].gender);
	printf("Age           : %d\n", member[indexToEdit].age);
	printf("Date of Birth : %02d/%02d/%04d\n", member[indexToEdit].dob.day, member[indexToEdit].dob.month, member[indexToEdit].dob.year);
	printf("Date Joined   : %02d/%02d/%04d\n", member[indexToEdit].JoinedDate.day, member[indexToEdit].JoinedDate.month, member[indexToEdit].dob.year);
	printf("Tier          :");
	switch (member[indexToEdit].tier)
	{
	case 'M':
		printf("M - Normal Member\n");
		break;
	case 'S':
		printf("S - Silver Member\n");
		break;
	case 'G':
		printf("G - Gold Member\n");
		break;
	case 'P':
		printf("P - Platinium Member\n");
		break;
	default:
		break;
	}
	printf("Upline: %s\n", member[indexToEdit].upline);
	printf("Downline: %s\n", member[indexToEdit].downline);
}


void addMember(Member member[], int* nMember) {
	char newId[10], confirm, validDate = 0;
	int found;
	if (*nMember >= MAX_MEMBER) {
		printf("Storage Full\n");
	}
	else {
		printf("Adding New Member: \n");
		char upline[10], downline[10];
		printf("\nEditing %s\n", member[*nMember].memberId);
		printf("Enter name : ");
		rewind(stdin);
		gets(member[*nMember].name);
		printf("Enter gender : ");
		rewind(stdin);
		member[*nMember].gender = toupper(getchar());
		while (member[*nMember].gender != 'M' && member[*nMember].gender != 'F') {
			printf("Invalid input. Please enter M or F: ");
			rewind(stdin);
			member[*nMember].gender = toupper(getchar());
		}
		printf("Enter age : ");
		scanf("%d", &member[*nMember].age);
		printf("Enter Date of Birth (DD/MM/YYYY) : ");
		scanf("%d/%d/%d", &member[*nMember].dob.day, &member[*nMember].dob.month, &member[*nMember].dob.year);
		SYSTEMTIME t;
		GetLocalTime(&t);
		while (!validDate) {
			if (member[*nMember].dob.day < 1 || member[*nMember].dob.day > 31 || member[*nMember].dob.month < 1 || member[*nMember].dob.month > 12 || member[*nMember].dob.year <1900 || member[*nMember].dob.year > t.wYear - 18) {
				validDate = 0;
			}
			else if (member[*nMember].dob.month == 2 && (member[*nMember].dob.day > 29 || (member[*nMember].dob.day == 29 && (member[*nMember].dob.year % 4 != 0 || (member[*nMember].dob.year % 100 == 0 && member[*nMember].dob.year % 400 != 0))))) {
				validDate = 0;
			}
			else if ((member[*nMember].dob.month == 4 || member[*nMember].dob.month == 6 || member[*nMember].dob.month == 9 || member[*nMember].dob.month == 11) && member[*nMember].dob.day > 30) {
				validDate = 0;
			}
			else {
				validDate = 1;
			}
			if (validDate != 1) {
				printf("Invalid Date! Enter valid date (DD/MM/YYYY) : ");
				scanf("%d/%d/%d", &member[*nMember].dob.day, &member[*nMember].dob.month, &member[*nMember].dob.year);
			}
		}
		printf("Date Joined : Cannot Modify\n");
		printf("Tier : Cannot Modify\n");
		printf("Enter Upline ID :");
		gets(upline);
		do {
			while ((upline[0] != 'M' || upline[1] != 'B' || !isdigit(upline[2]) || !isdigit(upline[3]) || !isdigit(upline[4]) || strlen(upline) != 5) || (upline[0] != 'M' || upline[1] != 'B' || !isdigit(upline[2]) || !isdigit(upline[3]) || !isdigit(upline[4]) || strlen(upline) != 5)) {
				printf("Invalid input!\n");
				printf("Please enter upline id in format MBXXX or STXXX : ");
				rewind(stdin);
				gets(upline);
			}
			for (int i = 0; i < nMember; i++) {
				if ((strcmp(upline, member[i].memberId) == 0)   /* || (strcmp(upline, staff[i].staffId)*/) {
					found = 1;
				}
			}
			if (found != 1) {
				printf("Upline ID not found, ID is invalid!\n\n");
			}
		} while (found != 1);
		printf("Enter Downline ID :");
		gets(downline);
		do {
			while ((downline[0] != 'M' || downline[1] != 'B' || !isdigit(downline[2]) || !isdigit(downline[3]) || !isdigit(downline[4]) || strlen(downline) != 5) || (downline[0] != 'M' || downline[1] != 'B' || !isdigit(downline[2]) || !isdigit(downline[3]) || !isdigit(downline[4]) || strlen(downline) != 5)) {
				printf("Invalid input!\n");
				printf("Please enter downline id in format MBXXX or STXXX : ");
				rewind(stdin);
				gets(downline);
			}
			for (int i = 0; i < nMember; i++) {
				if ((strcmp(downline, member[i].memberId) == 0)/* || (strcmp(downline, staff[i].staffId)*/) {
					found = 1;
				}
			}
			if (found != 1) {
				printf("Upline ID not found, ID is invalid!\n\n");
			}
		} while (found != 1);
		system("cls");
		printf("\nNew Member Detail is : \n", member[*nMember].memberId);
		printf("Member ID     : %s\n", member[*nMember].memberId);
		printf("Name          : %s\n", member[*nMember].name);
		printf("Gender        : %c\n", member[*nMember].gender);
		printf("Age           : %d\n", member[*nMember].age);
		printf("Date of Birth : %02d/%02d/%04d\n", member[*nMember].dob.day, member[*nMember].dob.month, member[*nMember].dob.year);
		printf("Date Joined   : %02d/%02d/%04d\n", member[*nMember].JoinedDate.day, member[*nMember].JoinedDate.month, member[*nMember].dob.year);
		printf("Tier          :");
		switch (member[*nMember].tier)
		{
		case 'M':
			printf("M - Normal Member\n");
			break;
		case 'S':
			printf("S - Silver Member\n");
			break;
		case 'G':
			printf("G - Gold Member\n");
			break;
		case 'P':
			printf("P - Platinium Member\n");
			break;
		default:
			break;
		}
		printf("Upline: %s\n", member[*nMember].upline);
		printf("Downline: %s\n", member[*nMember].downline);
		printf("Confirm add? Y/N");
		confirm = toupper(getchar());
		if (confirm == 'Y') {
			printf("New member added.");
			(*nMember)++;
			nMember = *nMember;
			saveMember(member, nMember);

		}
		else if (confirm == 'N') {
			printf("New member NOT added.");
		}
	}
}


void removeMember(Member member[], int nMember) {
	char memberId[10];
	int foundIndex = -1;
	for (int i = 0; i < nMember; i++) {
		printf("\nEnter ID of Member to delete : ");
		rewind(stdin);
		gets(memberId);
		for (int j = 0; j < nMember; j++) {
			if (strcmp(member[j].memberId, memberId) == 0) {
				foundIndex = j;
				printf("Member ID     : %s\n", member[j].memberId);
				printf("Name          : %s\n", member[j].name);
				printf("Gender        : %c\n", member[j].gender);
				printf("Age           : %d\n", member[j].age);
				printf("Date of Birth : %02d/%02d/%04d\n", member[j].dob.day, member[j].dob.month, member[j].dob.year);
				printf("Date Joined   : %02d/%02d/%04d\n", member[j].JoinedDate.day, member[j].JoinedDate.month, member[j].dob.year);
				printf("Tier          :");
				switch (member[j].tier)
				{
				case 'M':
					printf("M - Normal Member\n");
					break;
				case 'S':
					printf("S - Silver Member\n");
					break;
				case 'G':
					printf("G - Gold Member\n");
					break;
				case 'P':
					printf("P - Platinium Member\n");
					break;
				default:
					break;
				}
				printf("Upline: %s\n", member[j].upline);
				printf("Downline: %s\n", member[j].downline);
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
				strcpy(member[foundIndex].status, "Inactive");
				printf("\nMember %s deleted successfully!\n", member[foundIndex].memberId);
			}
			else if (yesNo == 'N') {
				printf("\nMember %s in NOT deleted !\n", member[foundIndex].memberId);
			}
		}
	}
}

void saveMember(Member member[], int nMember) {
	FILE* sMember = fopen("member.txt", "w");
	for (int i = 0; i < nMember; i++) {
		fprintf(sMember, "%s|%s|%c|%d|%d/%d/%d|%d/%d/%d|%c|%s|%s|%s|\n",
			member[i].memberId,
			member[i].name,
			member[i].gender,
			member[i].age,
			member[i].dob.day, member[i].dob.month, member[i].dob.year,
			member[i].JoinedDate.day, member[i].JoinedDate.month, member[i].JoinedDate.year,
			member[i].tier,//member m ,silver s, gold g,platinium p
			member[i].status,
			member[i].upline,
			member[i].downline);
	}
	fclose(sMember);
}

void searchMember(Member member[], int nMember) {
	int month, year, selection, matchNum = 0;
	char search[100];
	Member matchMember[MAX_MEMBER];
	do {
		printf("1.Search By Date of Birth\n");
		printf("2.Search By Date Joined\n");
		printf("3.Search By Data\n");
		printf("4.Back\n");
		printf("Enter your selection : ");
		rewind(stdin);
		scanf("%d", &selection);
		if (selection == 1) {
			printf("Enter month and year (MM/YYYY) : ");
			scanf("%d/%d", &month, &year);
			for (int i = 0; i < nMember; i++) {
				if (member[i].dob.month == month && member[i].dob.year == year) {
					matchMember[matchNum] = member[i];
					matchNum++;
				}
			}
			if (matchNum == 0) {
				printf("No matching member found.\n");
			}
			else {
				displayMember(matchMember, matchNum);
				matchNum = 0;
			}
		}
		else if (selection == 2) {
			printf("Enter month and year (MM/YYYY) : ");
			scanf("%d/%d", &month, &year);
			for (int i = 0; i < nMember; i++) {
				if (member[i].JoinedDate.month == month && member[i].JoinedDate.year == year) {
					matchMember[matchNum] = member[i];
					matchNum++;
				}
			}
			if (matchNum == 0) {
				printf("No matching member found.\n");
			}
			else {
				displayMember(matchMember, matchNum);
				matchNum = 0;
			}
		}
		else if (selection == 3) {
			printf("Enter search term : ");
			rewind(stdin);
			gets(search);
			for (int i = 0; i < nMember; i++) {
				if (strlen(search) == 1 && toupper(member[i].gender) == toupper(search[0])) {
					matchMember[matchNum] = member[i];
					matchNum++;
				}
				else if (strcmp(member[i].memberId, search) == 0 ||
					strcmp(member[i].name, search) == 0 ||
					strcmp(member[i].upline, search) == 0 ||
					strcmp(member[i].downline, search) == 0 ||
					member[i].age == atoi(search) ||
					strcmp(member[i].status, search) == 0) {
					matchMember[matchNum] = member[i];
					matchNum++;
				}
			}
			if (matchNum == 0) {
				printf("No matching member found.\n");
			}
			else {
				displayMember(matchMember, matchNum);
				matchNum = 0;
			}
		}
		else if (selection == 4) {
			system("cls");
		}

		else {
			printf("Invalid selection. Please 1, 2, 3 or 4 only!\n");
		}
	} while (selection != 4);
}

void displayMember(Member member[], int nMember) {
	system("cls");
	printf("===========MEMBER===========\n");
	printf("%-10s %-15s %-6s %-3s %-10s %-11s %-4s %-10s %-6s\n",
		"Member ID", "Name", "Gender", "Age", "D.O.B", "Date Joined", "Tier", "Status", "Upline");
	printf("%-10s %-15s %-6s %-3s %-10s %-11s %-4s %-10s %-6s\n",
		"=========", "===============", "======", "===", "==========", "===========", "====", "==========", "======");
	for (int i = 0; i < nMember; i++) {
		printf("%-10s %-15s %-6c %-3d %02d/%02d/%-0004d %02d/%02d/%-0005d %-4c %-10s %-6s\n",
			member[i].memberId, member[i].name, member[i].gender, member[i].age,
			member[i].dob.day, member[i].dob.month, member[i].dob.year,
			member[i].JoinedDate.day, member[i].JoinedDate.month, member[i].JoinedDate.year,
			member[i].tier, member[i].status, member[i].upline);
	}
	printf("\n< %d member  Available> \n", nMember);

}

void memberMenu(Member member[], int nMember) {
	int selection;
	readMember(member, &nMember);
	do {
		printf("============Member Menu==============\n");
		printf("Please enter your selection:\n");
		printf("1. Display All Member\n");
		printf("2. Search Member\n");
		printf("3. View and Edit Member\n");
		printf("4. Add Member\n");
		printf("5. Remove Member\n");
		printf("6. Back\n");

		printf("Enter your selection : ");
		rewind(stdin);
		//scanf%c  isdigit atoi
		scanf("%d", &selection);
		system("cls");
		switch (selection)
		{
		case 1:
			displayMember(member, nMember);
			break;
		case 2:
			searchMember(member, nMember);
			break;
			//case 3:
			//	viewMember(member, nMember);
			//	break;
			//case 4:
			//	addMember(member, nMember);
			//	break;
			//case 5:
			//	removeMember(member, nMember);
			//	break;
		case 6:
			printf("Back To Main Menu");
			//		//writeMember(member, nMember);
			//		int loginStatus = 0;
			break;
		default:
			printf("Invalid selection. Please re-enter your selection.\n\n");
			break;
		}
	} while (selection != 6);
}

void readMember(Member member[], int* nMember) {
	FILE* memberfptr = fopen("member.txt", "r");
	if (memberfptr == NULL) {
		printf("Unable to open the member.txt file\n");
		exit(-1);
	}
	while (fscanf(memberfptr, "%[^|]|%[^|]|%c|%d|%d/%d/%d|%d/%d/%d|%c|%[^|]|%[^|]|%[^|]|\n",
		&member[*nMember].memberId,
		&member[*nMember].name,
		&member[*nMember].gender,
		&member[*nMember].age,
		&member[*nMember].dob.day, &member[*nMember].dob.month, &member[*nMember].dob.year,
		&member[*nMember].JoinedDate.day, &member[*nMember].JoinedDate.month, &member[*nMember].JoinedDate.year,
		&member[*nMember].tier,//member m ,silver s, gold g,platinium p
		&member[*nMember].status,
		&member[*nMember].upline,
		&member[*nMember].downline) != EOF) {
		(*nMember)++;
	}
}