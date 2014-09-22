#include <stdio.h>
#include <string.h>
#include <stdlib.h>
<<<<<<< HEAD

=======
>>>>>>> origin/master

#include "Bank.h"

#define MAXLINE 80
#define MAXRECORDS 10

void showOptions(struct User *user, int logedIn) {
	int i;
	int input;
	char *options[3] = { "Login", "Register", "Quit" };

	for (i = 0; i < 3; i++) {
		printf("\n%10s:   => %20d.", options[i], i);
	}
	printf("\n Watcha'd like to do?");
	scanf("%d", &input);
	switch (input) {
	case 0:
		logIn(user, logedIn);
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

void logIn(struct User *user, int logedIn) {
	//system("cls");
	char username[100];
	char password[100];
	int badLogin = 1;
	int i = 0;

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

		while (i < 2 ) {
			if (strcmp(user[i].username, username) == 0
					&& strcmp(user[i].password, password) == 0) {
				puts("Successfull login!");
				badLogin = 0;
				logedIn = 1;
				strcpy(LOGGED_IN_USER_ID, user[i].user_id);
				LOGGED_IN_INDEX = i;
				system("cls");
			} else {
				puts("Bad login!");
			}
			i++;
		}

	} while (badLogin == 1);
}

void registerClient() {
	printf("Fill in the form below");

}

void showClientOptions(struct Account *account, struct User *user, int accountCount) {
	int i;
	int input;
	char *options[6] = { "Accounts", "Transactions", "Transfer own accounts",
			"Transfer to other", "Request new/delet account", "Quit" };

	for (i = 0; i < 6; i++) {
		printf("\n%25s: => %20d.", options[i], i);
	}
	printf("\nWatcha'd like to do?");
	scanf("%d", &input);
	switch (input) {
	case 0:
		listAccounts(account, user, accountCount);
		break;
	case 1:
		showTransactions();
		break;
	case 2:
		newTransactionToPA();
		break;
	case 3:
		newTransaction(account);
		break;
	case 4:
		request();
		break;
	case 5:
		quitProgram(running);
		break;
	default:
		printf("Bad input, quitting!");
		break;
	}
}

void listAccounts(struct Account *account, struct User *user, int accountCount) {
	int i;

	//printf("User ID: %s \nBalance: %d ", user[LOGGED_IN_INDEX].user_id, account[0].balance);
	for(i=0; i < accountCount; i++){
		if (strcmp(account[LOGGED_IN_INDEX].user_id, user[LOGGED_IN_INDEX].user_id) == 0) {

			printf("Account Number: %d \nBalance: %d ", account[i].account_number, account[i].balance);
		}
	}

	getchar();
}

void showTransactions() {

}

void newTransactionToPA() {

}

void newTransaction(struct Account *account) {
	int numTo;
	int i = 0;
	int input;

	puts("Välj från vilket av dina konto du vill överföra ifrån!");
	scanf("%d", &input);

	while (account[i].account_id != NULL ) {
		if (account[i].user_id == LOGGED_IN_USER_ID) {
			printf("Option: %d, Account Number: %d :Balance: %d ", i,account[i].account_number, account[i].balance);

		}
		i++;
	}



	puts("Till vilket bank nummer vill du göra en överförning?\n");
	scanf("%d", &numTo);

}

void showAdminOptions(struct Account *account, struct User *user, int accountCount) {
	int i;
	int input;
	char *options[5] = { "Clients","My Account(s)" ,"Account Requests", "User log", "Quit" };

	for (i = 0; i < 5; i++) {
		printf("\n%35s: => %25d.", options[i], i);
	}
	printf("\n Watcha'd like to do?");
	scanf("%d", &input);
	switch (input) {
	case 0:
		listClient();
		break;
	case 1:
		listAccounts(account, user, accountCount);
		break;
	case 2:
		showRequests();
		break;
	case 3:
		listLog();
		break;
	case 4:
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

void quitProgram(int running) {
	printf("Quitting, Thank you for using our bank service!");
	running = 0;

}

void saveDataToFile() {

}
