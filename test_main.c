#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Bank.h"
#include "xml.h"

int main(){
	int running;
	int logedIn;
	int currentUserId;

	running = 1;
	logedIn = 0;

	FILE *file;
	//char c;

	char filePath[500] = "/Users/lesliedahlberg/Documents/DVA117/BANK/BANK/data.xml";
	//file = fopen("/data.xml", "r");

	struct User *user;
	struct Account *account;
	struct Transaction *transaction;
	struct Request *request;

	int userCount;
	int accountCount;
	int transactionCount;
	int requestCount;
	
	/*
	if(file == NULL){
		printf("FAILED!\n");
	}*/
	
		/*
	for(int i = 0; 1; i++){
		c = fgetc(file);
		if(c == EOF){
			break;
		}
		printf("%c", c);
	}*/

	readXML(filePath, &user, &account, &transaction, &request, &userCount, &accountCount, &transactionCount, &requestCount);
	//printf("%s\n", (user)[0].password);
	

	/*do {
		showOptions(); //on-start visar vad man har för alternativ
		if(stricmp(users.user_type, "client") == 0) {
			do {
				showClientOptions();
			}while(logedIn);
		}else if(stricmp(users.user_type, "admin") == 0) {
			do{
				showAdminOptions();
			}while(logedIn);
		}
	}while(running == 1);*/

	return 0;
}