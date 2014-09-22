#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "Bank.h"
#include "xml.h"

int main(){
	int running;
	int logedIn;
	int currentUserId;

	int running = 1;
	int logedIn = 0;

	char filePath[50];

	struct User *user;
	struct Account *account;
	struct Transaction *transaction;
	struct Request *request;

	readXML(filePath, user, account, transaction, request);

	do {
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
	}while(running == 1);

	return 0;
}