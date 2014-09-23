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

	//printf("User ID: %s \nBalance: %d ", user[LOGGED_IN_INDEX].user_id, account[0].balance);
	for(i=0; i < accountCount; i++){
		if (account[LOGGED_IN_INDEX].user_id == user[LOGGED_IN_INDEX].user_id) {

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
	loggedIn = 0;
	LOGGED_IN_INDEX = 0;
	LOGGED_IN_USER_ID = 0;
}

void quitProgram() {
	logOut();
	running = 0;

}

void saveDataToFile() {

}
