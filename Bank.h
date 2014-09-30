#ifndef BANK_H_
#define BANK_H_

//STRUCTS FOR BANK STORAGE
struct Info {
	char bank_name[50];
	int last_user_id;
	int last_account_id;
};

struct User {
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
	int account_id;
	char action[21];
	char date[21];
	short active;
};

//LEVEL 1 FUNCTIONS
void showOptions();
void registerClient();
int logIn();
void logOut();
void quitProgram();

//LEVEL 2 FUNCTIONS
//client level
void showClientOptions();
void listAccountsWithNewScreen();
void showTransactions();
void newTransactionToPA();
void newTransaction();
void newRequest();
//admin level
void showAdminOptions();
void listClient();
void showRequests();
void listLog();

//SUPPORT FUNCTIONS
//GENERAL
void getDate(char *date);
int getAccountIdByNumber(int accountNumber);
int getAccountIndexByNumber(int accountNumber);
int getAccountIndexByID(int account_id);
int uniqueAccountNumberGenerator();
//BANK
void requestNewAccount();
void requestRemovalOfAccount(int accountNumber);
void listAccounts();
void addClient();
void editClient();
void addAccount();
void removeAccount();
void logMessage(char * logMessage);
//GRAPHICS
void newScreen();
void waitForEnter();

#endif