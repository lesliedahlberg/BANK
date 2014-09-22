#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "Bank.h"
//#include "xml.h"

int main(){
	setvbuf(stdout, NULL, _IONBF, 0); // Fixar delayen i min Eclipse konsol
	int running = 1;
	int logedIn = 0;
	int currentUserId;


	char filePath[50];

	struct User *users;
	struct Account *account;
	struct Transaction *transaction;
	struct Request *request;

	//readXML(filePath, user, account, transaction, request);

	do {
		showOptions(users); //on-start visar vad man har för alternativ
		if(stricmp(users->user_type, "client") == 0) {
			do {
				showClientOptions();
			}while(logedIn);
		}else if(stricmp(users->user_type, "admin") == 0) {
			do{
				showAdminOptions();
			}while(logedIn);
		}
	}while(running == 1);

	return 0;
}
