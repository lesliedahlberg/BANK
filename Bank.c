#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Bank.h"
#include "shared.h"

#define MAXLINE 80
#define MAXRECORDS 10

void showOptions() {
	int input;
	int loop = 0;

	newScreen();

	if (loggedIn) {
		newScreen();
		printf("Options:\n");
		printf("Logout..............(1)\n");
		printf("Quit................(2)\n");
		do {
			loop = 0;
			input = 0;

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
		} while (loop);
	} else if (!loggedIn) {
		newScreen();
		printf("Options:\n");
		printf("Login...............(1)\n");
		printf("Register............(2)\n");
		printf("Quit................(3)\n");
		do {
			loop = 0;
			input = 0;

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
		} while (loop);
	}
}

int logIn() {
	//system("cls");
	char username[100];
	char password[100];
	int loop = 0;

	if (loggedIn) {
		logOut();
	}

	do {
		newScreen();
		if (loop) {
			printf("Wrong username or password, try again!\n");
		}
		printf("Login (Enter \"cancel\" as username to cancel)\n");
		//getchar();

		printf("Username: ");
		scanf("%s", username);

		if (!strcmp(username, "cancel")) {
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

		for (int i = 0; i < userCount; i++) {
			if (strcmp(user[i].username, username) == 0
					&& strcmp(user[i].password, password) == 0) {

				loggedIn = 1;
				loop = 1;
				LOGGED_IN_USER_ID = user[i].user_id;
				LOGGED_IN_INDEX = i;
				i = userCount;
				newScreen();
				printf("Successfull login!\n");
				waitForEnter();
			}
		}

	} while (!loggedIn);

	return 1;
}

void registerClient() {

	char input;
	int user_id;
	char personal_number[100];
	char username[100];
	char first_name[100];
	char last_name[100];
	char address[100];
	char user_type[10];
	char password[100];

	newScreen();
	printf("Register new user\n");

	while (1) {
		while (getchar() != '\n')
			;
		printf("National identification number (10 digits): ");
		if (scanf("%d", &user_id))
			break;
		printf("Error, please try again!\n");
	}

	while (1) {
		while (getchar() != '\n')
			;
		printf("Username: ");
		if (scanf("%s", username))
			break;
		printf("Error, please try again!\n");
	}

	while (1) {
		while (getchar() != '\n')
			;
		printf("First name: ");
		if (scanf("%s", first_name))
			break;
		printf("Error, please try again!\n");
	}

	while (1) {
		while (getchar() != '\n')
			;
		printf("Last name: ");
		if (scanf("%s", last_name))
			break;
		printf("Error, please try again!\n");
	}

	while (1) {
		while (getchar() != '\n')
			;
		printf("Address: ");
		if (scanf("%s", address))
			break;
		printf("Error, please try again!\n");
	}

	while (1) {
		while (getchar() != '\n')
			;
		printf("Password: ");
		if (scanf("%s", password))
			break;
		printf("Error, please try again!\n");
	}

	user[userCount].user_id = ++info[0].last_user_id;
	strcpy(user[userCount].personal_number, personal_number);
	strcpy(user[userCount].username, username);
	strcpy(user[userCount].first_name, first_name);
	strcpy(user[userCount].last_name, last_name);
	strcpy(user[userCount].address, address);
	strcpy(user[userCount].password, password);
	strcpy(user[userCount].user_type, "client");

	userCount++;
	user = realloc(user, (userCount + 1) * sizeof(struct User));

	accountCount++;
	account[accountCount].account_id = accountCount;
	account[accountCount].account_number = 1337;
	account[accountCount].balance = 100;
	account[accountCount].user_id = ++info[0].last_user_id;
	account[accountCount].active = 1;

	accountCount++;
	account = realloc(account, (accountCount + 1) * sizeof(struct Account));

	printf("Registration successfull!\n");
	waitForEnter();

}

void showClientOptions() {

	int input;
	int loop;

	newScreen();
	printf("Options:\n");
	printf("Accounts......................(1)\n");
	printf("Transactions..................(2)\n");
	printf("Transfer own accounts.........(3)\n");
	printf("Transfer to other.............(4)\n");
	printf("Request new/delet account.....(5)\n");
	printf("Logout........................(6)\n");
	printf("Quit..........................(7)\n");

	do {
		loop = 0;
		input = 0;

		printf("Enter number to select option: ");
		scanf("%d", &input);

		switch (input) {
		case 1:
			listAccounts();
			break;
		case 2:
			showTransactions();
			break;
		case 3:
			newTransactionToPA();
			break;
		case 4:
			newTransaction();
			break;
		case 5:
			newRequest();
			break;
		case 6:
			logOut();
			break;
		case 7:
			quitProgram();
			break;
		default:
			printf("Error, please choose again!\n");
			loop = 1;
			break;
		}
	} while (loop);
}
void listAccounts() {
	int i;
	int userAccCount = 0;

	newScreen();

	for (i = 0; i < accountCount; i++) {
		if (account[i].user_id == user[LOGGED_IN_INDEX].user_id) {
			if (account[i].active == 0) {

			} else {
				printf("Account Number: %d : Balance: %d => [%d]\n",
						account[i].account_number, account[i].balance, i);
				userAccCount++;
			}
		}
	}

	waitForEnter();

}

void showTransactions() {
	int i;

	newScreen();

	for (i = 0; i < transactionCount; i++) {
		if (transaction[i].user_id == user[LOGGED_IN_INDEX].user_id) {
			printf(
					"From: %d\nTo: %d\nAmmount: %d\nDate: %s\n||||||||||||||||||\n",
					transaction[i].from, transaction[i].to,
					transaction[i].ammount, transaction[i].date);
		}
	}

	waitForEnter();
}

void newTransactionToPA() {
	int fromAcc = 0, toAcc = 0, ammount = 0;
	char accept;
	char date[100];
	getDate(date);
	int transactionSuccesfull = 1;

	newScreen();

	puts("Your accounts:");
	listAccounts();
	puts("What account do you want to tranfer money from?");
	scanf("%d", &fromAcc);
	while (account[fromAcc].user_id != user[LOGGED_IN_INDEX].user_id) {	//Kollar om det valda konton verkligen tillhör användaren
		newScreen();
		puts("Your accounts:");
		listAccounts();
		puts(
				"We are sorry, but something went wrong. Please choose an account again!\n");
		scanf("%d", &fromAcc);
	}
	puts("Choose target account for transaction:");
	scanf("%d", &toAcc);
	while (account[toAcc].user_id != user[LOGGED_IN_INDEX].user_id
			|| account[fromAcc].account_id == account[toAcc].account_id) {//Kollar om det valda konton verkligen tillhör användaren
		newScreen();
		puts("Your accounts:");
		listAccounts();
		puts(
				"We are sorry, but something went wrong. Please choose an account again!\n");
		scanf("%d", &toAcc);
	}

	printf("Enter ammount to transfer from account: %d to account: %d.",
			account[fromAcc].account_number, account[toAcc].account_number);
	scanf("%d", &ammount);

	printf(
			"Are you sure you want to transfer %d kr from account %d to account %d (y/n)?\n",
			ammount, account[fromAcc].account_number,
			account[toAcc].account_number);
	scanf(" %c", &accept);
	if (accept == 'y') {
		if (account[fromAcc].balance < ammount) {//Kollar om det konto som pengarna skall överföras ifrån innehar den summan pengar
			puts(
					"We are sorry, but your account balance is insufficent for this tranfer.");
			transactionSuccesfull = 0;
		} else {
			//överför pengarna mellan kontonen
			account[fromAcc].balance = account[fromAcc].balance - ammount;
			account[toAcc].balance = account[toAcc].balance + ammount;

			//loggar transaktionen
			transaction[transactionCount].from =
					account[fromAcc].account_number;
			transaction[transactionCount].to = account[toAcc].account_number;

			transaction[transactionCount].ammount = (int) ammount;

			transaction[transactionCount].user_id =
					user[LOGGED_IN_INDEX].user_id;

			transaction[transactionCount].active = 1;

			strncpy(transaction[transactionCount].date, date, 20);
			printf("%d\n", transaction[transactionCount].ammount);

			transactionCount++;
			transaction = realloc(transaction,
					(transactionCount + 1) * sizeof(struct Transaction));

			puts("Transfer complete!");
			printf("Account: %d, Balance: %d\nAccount: %d, Balance: %d\n",
					account[fromAcc].account_number, account[fromAcc].balance,
					account[toAcc].account_number, account[toAcc].balance);

		}

	} else if (accept == 'n') {
		return;
	}
	waitForEnter();
}

void newTransaction() {
	int numTo = 0, i = 0, toAcc = 0, fromAcc = 0, ammount = 0;
	char accept;
	char date[100];
	time_t now = time(NULL );
	struct tm *t = localtime(&now);
	strftime(date, sizeof(date) - 1, "%d %m %Y %H:%M", t);

	puts("Your accounts:");
	listAccounts();
	puts("What account do you want to tranfer money from?");
	scanf("%d", &fromAcc);

	while (account[fromAcc].user_id != user[LOGGED_IN_INDEX].user_id) {	//Kollar om det valda konton verkligen tillhör användaren
		puts("Your accounts:");
		listAccounts();
		puts(
				"We are sorry, but something went wrong. Please choose an account again!\n");
		scanf("%d", &fromAcc);
	}

	//CREATE DO WHILE LOOP
	//CREATE DO WHILE LOOP
	//CREATE DO WHILE LOOP

	puts("Enter the destination account number:");
	scanf("%d", &numTo);
	for (i = 0; i < accountCount; i++) { //loopar igenom account struktur arrayen och letar efter ett konto med samma nummer som blev insrkivet
		if (account[i].account_number == numTo) {
			//printf("Account Number: %d found!\n", numTo);
			toAcc = i;
		}
	}
	while (account[fromAcc].account_id == account[toAcc].account_id) { //loopar och kollar om man överför tillsamma bankkonto
		newScreen();
		puts(
				"We are sorry, but you can't transfer money back to the same account!");
		puts("Enter a bank number to transfer money to!");
		scanf("%d", &numTo);
		for (i = 0; i < accountCount; i++) { //loopar igenom account struktur arrayen och letar efter ett konto med samma nummer som blev insrkivet
			if (account[i].account_number == numTo) {
				//printf("Account Number: %d found!\n", numTo);
				toAcc = i;
			}
		}
	}

	puts("Enter the ammount to tranfer?");
	scanf("%d", &ammount);
	printf(
			"Are you sure you want to transfer %d kr from account %d to account %d y/n\n",
			ammount, account[fromAcc].account_number, numTo);
	scanf(" %c", &accept);
	if (accept == 'y') {
		if (account[fromAcc].balance < ammount) { //Kollar om det konto som pengarna skall överföras ifrån innehar den summan pengar
			puts(
					"We are sorry, but your account balance is insufficent for this tranfer.");
		} else {
			//överförningern av pengarna görs
			account[fromAcc].balance = account[fromAcc].balance - ammount;
			account[toAcc].balance = account[toAcc].balance + ammount;

			//loggar transkationerna
			printf("Before: %d", transactionCount);
			transaction[transactionCount].from =
					account[fromAcc].account_number;
			transaction[transactionCount].to = account[toAcc].account_number;
			transaction[transactionCount].ammount = ammount;

			transaction[transactionCount].user_id =
					user[LOGGED_IN_INDEX].user_id;
			transaction[transactionCount].active = 1;
			strncpy(transaction[transactionCount].date, date, 20);
			printf("After: %d", transactionCount);

			transactionCount++;
			transaction = realloc(transaction,
					(transactionCount + 1) * sizeof(struct Transaction));

			puts("Transfer complete!");
		}

	} else if (accept == 'n') {
		return;
	}
	waitForEnter();
}

void showAdminOptions() {

	int input;
	int loop;

	newScreen();

	printf("Options:\n");
	printf("Clients ......................(1)\n");
	printf("Account Requests..............(2)\n");
	printf("User log......................(3)\n");
	printf("Logout........................(4)\n");
	printf("Quit..........................(5)\n");

	do {
		loop = 0;
		input = 0;

		printf("Enter number to select option: ");
		scanf("%d", &input);

		switch (input) {
		case 1:
			listClient();
			break;
		case 2:
			showRequests();
			break;
		case 3:
			listLog();
			break;
		case 4:
			logOut();
			break;
		case 5:
			quitProgram();
			break;
		default:
			printf("Error, please choose again!\n");
			loop = 1;
			break;
		}
	} while (loop);
}

void addClient() {

}

void listClient() {

	char fullName[203];

	newScreen();
	printf("Clients:\n");
	printf(
			"NAME                ID NUMBER      ACCOUNT ID     ADDRESS             \n");
	for (int i = 0; i < userCount; i++) {

		fullName[0] = '\0';
		strcat(fullName, user[i].first_name);
		strcat(fullName, " ");
		strcat(fullName, user[i].last_name);

		printf("%-20s%-15s%-15d%-20s\n", fullName, user[i].personal_number,
				user[i].user_id, user[i].address);
	}
	waitForEnter();
}

void editClient() {

}

int uniqueAccountNumberGenerator() {
	int accountNumber;
	srand((unsigned) time(NULL ));
	accountNumber = rand() % 9999 + 1;
	for (int loop = 0; loop < accountCount; loop++) {
		if (accountNumber == account[loop].account_number) { //Checks if the generated number really is unique for the database
			accountNumber = rand() % 9999 + 1;
		}
	}
	return accountNumber;
}

void addAccount(int user_id) {

	account[accountCount].account_id = accountCount;
	account[accountCount].account_number = uniqueAccountNumberGenerator();
	account[accountCount].balance = 100;
	account[accountCount].user_id = user_id;
	account[accountCount].active = 1;

	accountCount++;
	account = realloc(account, (accountCount + 1) * sizeof(struct Account));

}

int getAccountIndexByNumber(int accountNumber) {
	for (int i = 0; i < accountCount; i++) {
		if (account[i].account_number == accountNumber) {
			return i;
		}
	}
	return -1;
}

int getAccountIndexByID(int account_id) {
	for (int i = 0; i < accountCount; i++) {
		if (account[i].account_id == account_id) {
			return i;
		}
	}
	return -1;
}

int getAccountIdByNumber(int accountNumber) {
	for (int i = 0; i < accountCount; i++) {
		if (account[i].account_number == accountNumber) {
			return account[i].account_id;
		}
	}
	return -1;
}

/*FOR USER: void removeAccount() {
 int ID;
 char verify[1];
 int loop = 1;
 printf("Remove account\n");

 listAccounts();

 while(loop){
 printf("Enter account number of account to be deleted: ");
 loop = scanf("%d", &ID);
 }

 printf("Are you sure you want to delete the account (y/n)?\n");
 while(!scanf("%s", verify));

 if(!strcmp(verify, "y")){
 account[getAccountIdByNumber(ID)].active = 0;
 printf("The account was successfully deleted!\n");
 }else{
 printf("The account was not deleted!\n");
 }

 }*/

void removeAccount(int accountIndex) {
	//account[getAccountIndexByNumber(accountNumber)].active = 0;
	accountIndex = getAccountIndexByID(accountIndex);
	account[accountIndex].active = 0;
	printf("The account was successfully deleted!\n");
	getchar();

}

void showRequests() {
	int request_nr;
	char answer;

	for (int loop = 0; loop < requestCount; loop++) {
		if (request[loop].active == 0) {

		} else
			printf(
					"Request Nr. [%d]\nFrom User: %d\nAccount ID: %d\nAction: %s\nDate: %s\n////////////////////////////////\n\n",
					loop, request[loop].user_id, request[loop].account_id,
					request[loop].action, request[loop].date);
	}
	puts("Select a request to answer!");
	scanf("%d", &request_nr);
	printf(
			"Would you'd like to take the action %s for the request nr [%d], y/n??",
			request[request_nr].action, request_nr);
	scanf("%s", &answer);
	if (answer == 'y') {

		if (!strcmp(request[request_nr].action, "NEW ACCOUNT")) {
			addAccount(request[request_nr].user_id);
		}

		if (!strcmp(request[request_nr].action, "REMOVE ACCOUNT")) {
			removeAccount(request[request_nr].account_id);
		}

		request[request_nr].active = 0;

	} else if (answer == 'n') {
		showRequests();
	}

}

void listLog() {

}

void newRequest() {
	int loop, loop2;
	int input;
	int accountNumber;
	newScreen();
	printf("Request\n");
	printf("Options:\n");
	printf("New account.........(1)\n");
	printf("Delete account......(2)\n");
	do {
		loop = 0;
		input = 0;

		printf("Enter number to select option: ");
		scanf("%d", &input);

		switch (input) {
		case 1:
			requestNewAccount();
			break;
		case 2:
			listAccounts();
			loop2 = 0;
			while (!loop2) {
				printf("Enter account number of account to be deleted: ");
				loop2 = scanf("%d", &accountNumber);
			}
			requestRemovalOfAccount(accountNumber);
			break;
		default:
			printf("Error, please choose again!\n");
			loop = 1;
			break;
		}
	} while (loop);
	waitForEnter();

}

void requestNewAccount() {
	char date[20];
	getDate(date);

	request[requestCount].user_id = user[LOGGED_IN_INDEX].user_id;
	strcpy(request[requestCount].action, "NEW ACCOUNT");
	request[requestCount].account_id = 0;
	strcpy(request[requestCount].date, date);
	request[requestCount].active = 1;

	printf("Request successfull!\n");

	requestCount++;
	request = realloc(request, (requestCount + 1) * sizeof(struct Request));

}

void requestRemovalOfAccount(int accountNumber) {
	char date[20];
	getDate(date);

	request[requestCount].user_id = user[LOGGED_IN_INDEX].user_id;
	strcpy(request[requestCount].action, "REMOVE ACCOUNT");
	request[requestCount].account_id = getAccountIdByNumber(accountNumber);
	strcpy(request[requestCount].date, date);
	request[requestCount].active = 1;

	printf("Request successfull!\n");

	requestCount++;
	request = realloc(request, (requestCount + 1) * sizeof(struct Request));
}

void getDate(char *date) {

	time_t now = time(NULL );
	struct tm *t = localtime(&now);
	strftime(date, 20, "%d %m %Y %H:%M", t);
	//printf("%s\n", date);

}

void logOut() {
	loggedIn = 0;
	LOGGED_IN_INDEX = 0;
	LOGGED_IN_USER_ID = 0;
}

void quitProgram() {
	logOut();
	running = 0;

}

void newScreen() {
	system("cls");
	//CLEARSCREEN
}

void waitForEnter() {
	while (getchar() != '\n')
		;
	printf("Press ENTER to continue...");
	getchar();
}
