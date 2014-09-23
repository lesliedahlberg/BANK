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

	if(loggedIn){
		printf("Options:\n");
		printf("Logout..............(1)\n");
		printf("Quit................(2)\n");
		do{
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
		}while(loop);
	}else if(!loggedIn){

		printf("Options:\n");
		printf("Login...............(1)\n");
		printf("Register............(2)\n");
		printf("Quit................(3)\n");
		do{
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
				LOGGED_IN_USER_ID = user[i].user_id;
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

	char input;
	int user_id;
	char personal_number[100];
	char username[100];
	char first_name[100];
	char last_name[100];
	char address[100];
	char user_type[10];
	char password[100];

	printf("Register new user\n");
	
	while(1){
		while(getchar() != '\n');
		printf("National identification number (10 digits): ");
		if(scanf("%d", &user_id))
			break;
		printf("Error, please try again!\n");
	}

	while(1){
		while(getchar() != '\n');
		printf("Username: ");
		if(scanf("%s", username))
			break;
		printf("Error, please try again!\n");
	}

	while(1){
		while(getchar() != '\n');
		printf("First name: ");
		if(scanf("%s", first_name))
			break;
		printf("Error, please try again!\n");
	}

	while(1){
		while(getchar() != '\n');
		printf("Last name: ");
		if(scanf("%s", last_name))
			break;
		printf("Error, please try again!\n");
	}

	while(1){
		while(getchar() != '\n');
		printf("Address: ");
		if(scanf("%s", address))
			break;
		printf("Error, please try again!\n");
	}

	while(1){
		while(getchar() != '\n');
		printf("Password: ");
		if(scanf("%s", password))
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
	user = realloc(user, (userCount + 1)*sizeof(struct User));


}

void showClientOptions() {

	int input;
	int loop;

	printf("Options:\n");
	printf("Accounts......................(1)\n");
	printf("Transactions..................(2)\n");
	printf("Transfer own accounts.........(3)\n");
	printf("Transfer to other.............(4)\n");
	printf("Request new/delet account.....(5)\n");
	printf("Logout........................(6)\n");
	printf("Quit..........................(7)\n");

	

	do{
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
	}while(loop);
}
void listAccounts() {
	int i;
	int userAccCount = 0;

	for (i = 0; i < accountCount; i++) {
		if (account[i].user_id == user[LOGGED_IN_INDEX].user_id) {
			printf("Account Number: %d : Balance: %d => [%d]\n",
					account[i].account_number, account[i].balance, i);
			userAccCount++;
		}
	}

}

void showTransactions() {
	int i;
	for (i=0; i < transactionCount; i++){

	}

}

void newTransactionToPA() {
	int fromAcc, toAcc, amount;
	char accept;
	char date[100];
	time_t now = time(NULL );
	struct tm *t = localtime(&now);
	strftime(date, sizeof(date) - 1, "%d %m %Y %H:%M", t);

	puts("Here are your accounts!");
	listAccounts();
	puts("Choose an account to transfer money from!");
	scanf("%d", &fromAcc);
	while (account[fromAcc].user_id != user[LOGGED_IN_INDEX].user_id) {//Kollar om det valda konton verkligen tillhör användaren
		puts("Whops!, something went wrong, try choosing an account again\n");
		listAccounts();
		scanf("%d", &fromAcc);
	}
	puts("Transfer to which account of yours?");
	scanf("%d", &toAcc);
	while (account[toAcc].user_id != user[LOGGED_IN_INDEX].user_id
			|| account[fromAcc].account_id == account[toAcc].account_id) {//Kollar om det valda konton verkligen tillhör användaren
		puts("Whops!, something went wrong, try choosing an account again\n");
		listAccounts();
		scanf("%d", &toAcc);
	}

	printf(
			"How much money would you'd like to transfer from account: %d to account: %d.",
			account[fromAcc].account_number, account[toAcc].account_number);
	scanf("%d", &amount);

	printf(
			"Do you accept this transfer of %d kr, from your account: %d, to your account: %d y/n\n",
			amount, account[fromAcc].account_number,
			account[toAcc].account_number);
	scanf(" %c", &accept);
	if (accept == 'y') {
		if (account[fromAcc].balance < amount) {//Kollar om det konto som pengarna skall överföras ifrån innehar den summan pengar
			puts(
					"Whops!, seems like your have insufficent amount of money on the account you're trying to transfer from");
			puts("You'll have to try with another one!\n");
			system("cls");
			newTransactionToPA();
		}
		//överför pengarna mellan kontonen
		account[fromAcc].balance = account[fromAcc].balance - amount;
		account[toAcc].balance = account[toAcc].balance + amount;

		//loggar transaktionen
		transactionCount++;
		transaction[transactionCount].from = account[fromAcc].account_number;
		transaction[transactionCount].to = account[toAcc].account_number;
		transaction[transactionCount].ammount = amount;
		strcpy(transaction[transactionCount].date, date);

		puts("Transfer complete!\nYour current balance:");
		printf("Account: %d, Balance: %d\nAccount: %d, Balance: %d",
				account[fromAcc].account_number, account[fromAcc].balance,
				account[toAcc].account_number, account[toAcc].balance);
		getchar();
		system("cls");
	} else if (accept == 'n') {

	}
	getchar();
	system("cls");
}

void newTransaction() {
	int numTo = 0, i = 0, toAcc = 0, fromAcc = 0, amount = 0;
	char accept;
	char date[100];
	time_t now = time(NULL );
	struct tm *t = localtime(&now);
	strftime(date, sizeof(date) - 1, "%d %m %Y %H:%M", t);

	puts("Here are your account(s)!");
	listAccounts();
	puts("Choose an account to transfer money from!");
	scanf("%d", &fromAcc);

	while (account[fromAcc].user_id != user[LOGGED_IN_INDEX].user_id) {//Kollar om det valda konton verkligen tillhör användaren
		puts(
				"Whops!, seems something went wrong choosing accounts. Try Again!\n");
		listAccounts();
		scanf("%d", &fromAcc);
	}

	puts("Enter a bank number to transfer money to!");
	scanf("%d", &numTo);
	for (i = 0; i < accountCount; i++) { //loopar igenom account struktur arrayen och letar efter ett konto med samma nummer som blev insrkivet
		if (account[i].account_number == numTo) {
			printf("Account Number: %d found!\n", numTo);
			toAcc = i;
		}
	}
	while (account[fromAcc].account_id == account[toAcc].account_id) { //loopar och kollar om man överför tillsamma bankkonto
		puts(
				"Whops!, you canno't transfer money back to same account, Try with another one!");
		system("cls");
		puts("Enter a bank number to transfer money to!");
		scanf("%d", &numTo);
		for (i = 0; i < accountCount; i++) { //loopar igenom account struktur arrayen och letar efter ett konto med samma nummer som blev insrkivet
			if (account[i].account_number == numTo) {
				printf("Account Number: %d found!\n", numTo);
				toAcc = i;
			}
		}
	}

	puts("Type in the amount of money you'd like to transfer?");
	scanf("%d", &amount);
	getchar();
	printf(
			"Do you accept this transfer of %d kr, from your account: %d, to the account: %d y/n\n",
			amount, account[fromAcc].account_number, numTo);
	scanf(" %c", &accept);
	if (accept == 'y') {
		if (account[fromAcc].balance < amount) { //Kollar om det konto som pengarna skall överföras ifrån innehar den summan pengar
			puts(
					"Whops!, seems like your have insufficent amount of money on the account you're trying to transfer from");
			puts("You'll have to try with another one!\n");
			system("cls");
			newTransactionToPA();
		}
		//överförningern av pengarna görs
		account[fromAcc].balance = account[fromAcc].balance - amount;
		account[toAcc].balance = account[toAcc].balance + amount;

		//loggar transkationerna
		transactionCount++;
		transaction[transactionCount].from = account[fromAcc].account_number;
		transaction[transactionCount].to = account[toAcc].account_number;
		transaction[transactionCount].ammount = amount;
		strcpy(transaction[transactionCount].date, date);


		puts("Transfer complete!");
		getchar();
		system("cls");
	} else if (accept == 'n') {

	}
}


void showAdminOptions() {
	
	int input;
	int loop;

	printf("Options:\n");
	printf("Clients ......................(1)\n");
	printf("Account Requests..............(2)\n");
	printf("User log......................(3)\n");
	printf("Logout........................(4)\n");
	printf("Quit..........................(5)\n");

	do{
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
	}while(loop);
}

void addClient() {

}

void listClient() {

	char fullName[203];

	
	printf("Clients:\n");
	printf("NAME                ID NUMBER      ACCOUNT ID     ADDRESS             \n");
	for(int i = 0; i < userCount; i ++){

		fullName[0] = '\0';
		strcat(fullName, user[i].first_name);
		strcat(fullName, " ");
		strcat(fullName, user[i].last_name);

		printf("%-20s%-15s%-15d%-20s\n", fullName, user[i].personal_number, user[i].user_id, user[i].address);
	}
}

void editClient() {

}

void addAccount() {

}

int getAccountIdByNumber(int accountNumber){
	for(int i = 0; i < accountCount; i++){
		if(account[i].account_number == accountNumber){
			return i;
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

void removeAccount(int accountNumber) {
	account[getAccountIdByNumber(accountNumber)].active = 0;
	printf("The account was successfully deleted!\n");
}

void showRequests() {

}

void listLog() {

}

void newRequest() {
	int loop;
	int input;
	int accountNumber;

	printf("Request\n");
	printf("Options:\n");
		printf("New account.........(1)\n");
		printf("Delete account......(2)\n");
		do{
			loop = 0;
			input = 0;

			printf("Enter number to select option: ");
			scanf("%d", &input);

			switch (input) {
				case 1:
					requestNewAccount();
					break;
				case 2:
					//requestRemovalOfAccount()
					break;
				default:
					printf("Error, please choose again!\n");
					loop = 1;
					break;
			}
		}while(loop);

}

void requestNewAccount(){
	char date[20];
	getDate(date);

	request[requestCount].user_id = user[LOGGED_IN_INDEX].user_id;
	strcpy(request[requestCount].action, "NEW ACCOUNT");
	strcpy(request[requestCount].date, date);
	request[requestCount].active = 1;
	

	requestCount++;
	request = realloc(request, (requestCount + 1)*sizeof(struct Request));

}

void requestRemovalOfAccount(int accountNumber){

}

void getDate(char *date){
	
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
