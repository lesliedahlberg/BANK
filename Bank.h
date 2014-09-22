/*
 * Bank.h
 *
 *  Created on: 19 sep 2014
 *      Author: Mattias
 */

#ifndef BANK_H_
#define BANK_H_

struct User {
	char user_id[10];
	char personal_number[10];
	char username[100];
	char first_name[100];
	char last_name[100];
	char address[100];
	char user_type[10];
	char password[100];
	char active[10];

};


struct Account {
	short account_id;
	int account_number;
	int balance;
	short active;
	short user_id;
};

struct Transaction {
	short from;
	short to;
	char date[9];
	int ammount;
	short active;
};

struct Request {
	short user_id;
	char action[10];
	short active;
};

#endif
