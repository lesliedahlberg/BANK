#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Bank.h"
#include "shared.h"

#define MAXLINE 80
#define MAXRECORDS 10

void showOptions() {
	int input;
	int loop = 0;

	if(loggedIn){
		printf("Option:\n");
		printf("Logout..............(1)\n");
		printf("Quit................(2)\n");
		do{
			loop = 0;

			printf("Enter number to select option: ");
			scanf("%d", &input);

			switch (input) {
				case 1:
					logOut();
					break;
				case 2:
					quitProgram();
					break;
				default:
					printf("Error, please choose again!\n");
					loop = 1;
					break;
			}
		}while(loop);
	}else if(!loggedIn){

		printf("Option:\n");
		printf("Login...............(1)\n");
		printf("Register............(2)\n");
		printf("Quit................(3)\n");
		do{
			loop = 0;

			printf("Enter number to select option: ");
			scanf("%d", &input);

			switch (input) {
				case 1:
					logIn();
					break;
				case 2:
					registerClient();
					break;
				case 3:
					quitProgram();
					break;
				default:
					printf("Error, please choose again!\n");
					loop = 1;
					break;
			}
		}while(loop);
	}
}

int logIn() {
	//system("cls");
	char username[100];
	char password[100];
	int loop = 0;

	if(loggedIn){
		logOut();
	}

	do {

		printf("Login (Enter \"cancel\" as username to cancel)\n");
		//getchar();
		
		printf("Username: ");
		scanf("%s", username);

		if(!strcmp(username, "cancel")){
			return 0;
		}
		//getchar();
		//fgets(username, 100, stdin);
		
		printf("Password: ");
		scanf("%s", password);
		//getchar();
		//fgets(password, 100, stdin);
		
		/*
		if (username[strlen(username) - 1] == '\n') //fgets() sätter automatisk ett '\n' i slutet av varje string, denna funktion kollar om det är en '\n' i slutet ersätter  den med 0
			username[strlen(username) - 1] = '';
		if (password[strlen(password) - 1] == '\n') //fgets() sätter automatisk ett '\n' i slutet av varje string, denna funktion kollar om det är en '\n' i slutet ersätter  den med 0
			password[strlen(password) - 1] = '';
		*/

		for(int i = 0; i < userCount; i++){
			if (strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0) {
				printf("Successfull login!\n");
				loggedIn = 1;
				strcpy(LOGGED_IN_USER_ID, user[i].user_id);
				LOGGED_IN_INDEX = i;
				system("cls");
				i = userCount;
			}
		}
		if(!loggedIn){
			printf("Wrong username or password, try again!\n");
		}
		
	} while (!loggedIn);

	return 1;
}

void registerClient() {
	printf("Fill in the form below");

}

void showClientOptions() {




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
		newRequest();
		break;
	case 5:
		quitProgram(running);
		break;
	default:
		printf("Bad input, quitting!");
		break;
	}
}

void listAccounts() {
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

void newTransaction() {
	int numTo;
	int i = 0;
	int input;

	puts("Välj från vilket av dina konto du vill överföra ifrån!");
	scanf("%d", &input);

	//while (account[i].account_id != NULL ) {
		if (account[i].user_id == LOGGED_IN_USER_ID) {
			printf("Option: %d, Account Number: %d :Balance: %d ", i,account[i].account_number, account[i].balance);

		}
		i++;
	//}



	puts("Till vilket bank nummer vill du göra en överförning?\n");
	scanf("%d", &numTo);

}

void showAdminOptions() {
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

void newRequest() {

}

void logOut() {

}

void quitProgram() {
	printf("Quitting, Thank you for using our bank service!");
	running = 0;

}

void saveDataToFile() {

}
