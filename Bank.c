/*
 ============================================================================
 Name        : Bank.c
 Author      : Mattias
 Version     :
 Copyright   : nan
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Bank.h"
int running = 1;

void loadDataFromFile() {

}
void showOptions();
void registerClient();
void showClientOptions();
void listAccounts();
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

			do {
				showOptions(); //on-start visar vad man har för alternativ
				if(user) {
					do {
						showClientOptions();

					}while(logedIn);
				} else if(admin) {
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
	printf("Enter your Username and Password");
}

void registerClient() {
	printf("Fill in the form below");

}

void showClientOptions() {

}

void listAccounts() {

}

void newTransactionToPA() {

}

void newTransaction() {

}

void showAdminOptions() {

}

void addClient() {

}

void listClient() {

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
