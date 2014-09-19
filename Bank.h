/*
 * Bank.h
 *
 *  Created on: 19 sep 2014
 *      Author: Mattias
 */

#ifndef BANK_H_
#define BANK_H_

struct User {
	short user_ID;
	short personal_number;
	char firstname;
	char lastname;
	char adress;
	short userType;
	char password;
	short active;
};

struct Account {
	short account_ID;
	short account_number;
	short user_ID;
	int money;
	short active;
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
