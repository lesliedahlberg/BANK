/*
 * Bank.h
 *
 *  Created on: 19 sep 2014
 *      Author: Mattias
 */

#ifndef BANK_H_
#define BANK_H_

struct User {
	char user_ID[10];
	char personal_number[10];
	char username[100];
	char firstname[100];
	char lastname[100];
	char adress[100];
	char userType[10];
	char password[100];
	char active[10];

};


struct Account {
	short account_ID;
	int account_number;
	int money;
	short active;
	short user_ID;
};

struct Transaction {
	short transaction_from;
	short transaction_to;
	int amount;
	int money;
	short active;
};

struct Request { //�ndrade s� vi bara har en struct med request, sen identifieras det var det �r f�r request.
	short user_ID;
	short remove_account; //Om det �r en request om att f� bort konto �r det 1, annars 0
	short new_account; //Om det �r en request om att f� ett nytt konto �r det 1, annars 0
	short active;
};

#endif /* BANK_H_ */
