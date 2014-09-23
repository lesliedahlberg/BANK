/*
 * Bank.h
 *
 *  Created on: 19 sep 2014
 *      Author: Mattias
 */

#ifndef BANK_H_
#define BANK_H_

struct Info {
	char bank_name[50];
	int last_user_id;
	int last_account_id;
};

struct User {
	//char user_id[100];
	int user_id;
	char personal_number[100];
	char username[100];
	char first_name[100];
	char last_name[100];
	char address[100];
	char user_type[10];
	char password[100];
	short active;

};


struct Account {
	short account_id;
	int account_number;
	int balance;
	short active;
	int user_id;
};

struct Transaction {
	short from;
	short to;
	char date[21];
	int ammount;
	short active;
	int user_id;
};

struct Request {
	int user_id;
	char action[21];
	char date[21];
	short active;
};





void showOptions();
void registerClient();
void showClientOptions();
void listAccounts();
void showTransactions();
void newTransactionToPA();
void newTransaction();
void newRequest();
int logIn();
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

int getAccountIdByNumber(int accountNumber);
void requestNewAccount();
void requestRemovalOfAccount(int accountNumber);
void getDate(char *date);

#endif
