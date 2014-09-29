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

char * dataPath;
char * logPath;

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

    dataPath = "/Users/lesliedahlberg/Documents/GITHUB/BANK/data.xml";
    //dataPath = "src/data.xml";
    
    logPath = "/Users/lesliedahlberg/Documents/GITHUB/BANK/log.txt";
    //logPath = "src/log.txt";

    readXML(dataPath);
    
	
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

	

	writeToXML(dataPath);
	return 0;
}
