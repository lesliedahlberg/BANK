#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "Bank.h"
#include "xml.h"



int main() {
	int running;
	int logedIn;
	int currentUserId;

	struct User *user;
	struct Account *account;
	struct Transaction *transaction;
	struct Request *request;

	running = 1;
	logedIn = 0;


	int userCount;
	int accountCount;
	int transactionCount;
	int requestCount;

	setvbuf(stdout, NULL, _IONBF, 0); // Fixar delayen i min Eclipse konsol

	char filePath[500] = "src/data.xml";

	readXML(filePath, &user, &account, &transaction, &request, &userCount, &accountCount, &transactionCount, &requestCount);


	do {
		showOptions(user, logedIn); //on-start visar vad man har för alternativ

		if (strcmp(user[LOGGED_IN_INDEX].user_type, "client") == 0) {
			do {
				showClientOptions(account, user, accountCount);
			} while (logedIn);
		} else if (strcmp(user[LOGGED_IN_INDEX].user_type, "admin") == 0) {
			do {
				showAdminOptions(account, user, accountCount);
			} while (logedIn);
		}
	} while (running == 1);

	return 0;
}
