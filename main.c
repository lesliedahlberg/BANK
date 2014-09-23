#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Bank.h"
#include "xml.h"
#include "shared.h"

//DECLARE GLOBALS
//NEW ONES MUST BE ADDED TO SHARED.H

int infoCount;
int userCount;
int accountCount;
int transactionCount;
int requestCount;

int running;
int loggedIn;

int LOGGED_IN_USER_ID;
int LOGGED_IN_INDEX;

struct Info *info;
struct User *user;
struct Account *account;
struct Transaction *transaction;
struct Request *request;

int main() {


	running = 1;
	loggedIn = 0;

	//setvbuf(stdout, NULL, _IONBF, 0); // Fixar delayen i min Eclipse konsol

	//char filePath[500] = "src/data.xml";
	char filePath[500] = "/Users/lesliedahlberg/Documents/DVA117/BANK/BANK/data.xml";
	//char targetFilePath[500] = "/Users/lesliedahlberg/Documents/DVA117/BANK/BANK/data_written.xml";

	readXML(filePath);
	
	while(running){
		showOptions();
		
		while(loggedIn){
			if(!strcmp(user[LOGGED_IN_INDEX].user_type, "client")){
				showClientOptions();

			}else if(!strcmp(user[LOGGED_IN_INDEX].user_type, "admin")){
				showAdminOptions();

			}
		}
	}

	

	writeToXML(filePath);



	/*
	do {
		showOptions(user, loggedIn); //on-start visar vad man har för alternativ

		if (strcmp(user[LOGGED_IN_INDEX].user_type, "client") == 0) {
			do {
				showClientOptions(account, user, accountCount);
			} while (loggedIn);
		} else if (strcmp(user[LOGGED_IN_INDEX].user_type, "admin") == 0) {
			do {
				showAdminOptions(account, user, accountCount);
			} while (*loggedIn);
		}
	} while (running == 1);
	*/
	return 0;
}
