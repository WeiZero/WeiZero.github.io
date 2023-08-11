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

void main() {
	Staff staff[MAX_STAFF];
	int nStaff = 0;
	readStaff(staff, &nStaff);
	loginStaff(staff, nStaff);
}