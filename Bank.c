#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "Bank.h"

#define MAXLINE 80
#define MAXRECORDS 10

int running = 1;
int logedIn = 0;

struct User users;
struct Account accounts;

void readData() {
	FILE *fp = NULL;
	int nrecs = 0;
	char line[MAXLINE];
	int i;

	/* Open file */
	fp = fopen("src/db.txt", "r");
	if (!fp) {
		perror("File open error!\n");
		//return 1;
	}

	/* Read file and parse text into your data records */
	while (!feof (fp)) {
		if (fgets(line, sizeof(line), fp)) {
			printf("next line= %s\n", line);
			nrecs++;
		}
	}

	strcpy(users.user_ID, strtok(line, ","));

	//Läser in ifrån en textfil, måste göras en struct array för när vi ska haflera också loopa
	//users.user_ID = 0;
	strcpy(users.personal_number, strtok(NULL, ","));
	strcpy(users.username, strtok(NULL, ","));
	strcpy(users.first_name, strtok(NULL, ","));
	strcpy(users.last_name, strtok(NULL, ","));
	strcpy(users.address, strtok(NULL, ","));
	strcpy(users.user_type, strtok(NULL, ","));
	strcpy(users.password, strtok(NULL, ","));
	strcpy(users.active, strtok(NULL, ","));

	accounts.account_id = 0;
	accounts.account_number = 123456;

}

void showOptions();
void registerClient();
void showClientOptions();
void listAccounts();
void showTransactions();
void newTransactionToPA();
void newTransaction();
void request();
void logIn();
void logOut();
void quitProgram();

void showAdminOptions();
void addClient();
void listClient();
void editClient();
void addAccount();
void removeAccount();
void showRequests();
void listLog();

void saveDataToFile();

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); // Fixar delayen i min Eclipse konsol
			int logedIn = 0;
			int user;
			int admin;
			int argc = 0;
			char *argv[1000];

			//loadDataFromFile(argc, &argv[1000]);

			readData();

			do {

					showOptions(); //on-start visar vad man har för alternativ

					if(stricmp(users.user_type, "0") == 0) {
						do {
							showClientOptions();

						}while(logedIn);
					} else if(stricmp(users.user_type, "1") == 0) {
						do {
							showAdminOptions();

						}while(logedIn);
					}

			}while(running == 1);

			puts("Bank system"); /* prints Bank system */
			return EXIT_SUCCESS;
		}

void showOptions() {
	int i;
	int input;
	char *options[3] = { "Login", "Register", "Quit" };

	for (i = 0; i < 3; i++) {
		printf("\n%10s:   %20=> %20d.", options[i], i);
	}
	printf("\n Watcha'd like to do?");
	scanf("%d", &input);
	switch (input) {
	case 0:
		logIn();
		break;
	case 1:
		registerClient();
		break;
	case 2:
		quitProgram();
		break;
	default:
		printf("Bad input, quitting!");
		break;
	}

}

void logIn() {
	system("cls");
	char username[100];
	char password[100];
	int badLogin = 1;

	do {
		printf("Enter your Username and Password\n");
		getchar();
		puts("Username: ");
		//getchar();
		fgets(username, 100, stdin);
		puts("Password: ");
		//getchar();
		fgets(password, 100, stdin);

		if (username[strlen(username) - 1] == '\n') //fgets() sätter automatisk ett '\n' i slutet av varje string, denna funktion kollar om det är en '\n' i slutet ersätter  den med 0
			username[strlen(username) - 1] = 0;
		if (password[strlen(password) - 1] == '\n') //fgets() sätter automatisk ett '\n' i slutet av varje string, denna funktion kollar om det är en '\n' i slutet ersätter  den med 0
			password[strlen(password) - 1] = 0;

		if (strcmp(users.username, username) == 0
				&& strcmp(users.password, password) == 0) {
			puts("Successfull login!");
			badLogin = 0;
			logedIn = 1;
			system("cls");
		} else
			puts("Bad login!");
	} while (badLogin == 1);
}

void registerClient() {
	printf("Fill in the form below");

}

void showClientOptions() {
	int i;
	int input;
	char *options[6] = { "Accounts", "Transactions", "Transfer own accounts",
			"Transfer to other", "Request new/delet account", "Quit" };

	for (i = 0; i < 3; i++) {
		printf("\n%25s:   %25=> %20d.", options[i], i);
	}
	printf("\nWatcha'd like to do?");
	scanf("%d", &input);
	switch (input) {
	case 0:
		listAccounts();
		break;
	case 1:
		showTransactions();
		break;
	case 2:
		newTransactionToPA();
		break;
	case 3:
		newTransaction();
		break;
	case 4:
		request();
		break;
	case 5:
		quitProgram();
		break;
	default:
		printf("Bad input, quitting!");
		break;
	}
}

void listAccounts() {

}

void showTransactions() {

}

void newTransactionToPA() {

}

void newTransaction() {

}

void showAdminOptions() {
	int i;
	int input;
	char *options[4] = { "Clients", "Account Requests", "User log", "Quit" };

	for (i = 0; i < 3; i++) {
		printf("\n%35s:   %25=> %25d.", options[i], i);
	}
	printf("\n Watcha'd like to do?");
	scanf("%d", &input);
	switch (input) {
	case 0:
		listClient();
		break;
	case 1:
		showRequests();
		break;
	case 2:
		listLog();
		break;
	case 3:
		quitProgram();
		break;
	default:
		printf("Bad input, quitting!");
		break;
	}
}

void addClient() {

}

void listClient() {
//I den här funktionen ska man sen kunna välja vilken klient man vill ta bort/redigera, och kunna lägga till en ny kliet. samt nytt konto åt klient, avsluta bankkonto
}

void editClient() {

}

void addAccount() {

}

void removeAccount() {

}

void showRequests() {

}

void listLog() {

}

void request() {

}

void logOut() {

}

void quitProgram() {
	printf("Quitting, Thank you for using our bank service!");
	running = 0;

}

void saveDataToFile() {

}
