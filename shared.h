#ifndef SHARED_H_
#define SHARED_H_

extern int userCount;
extern int accountCount;
extern int transactionCount;
extern int requestCount;

extern int running;
extern int loggedIn;
extern int currentUserId;

extern char LOGGED_IN_USER_ID[100];
extern int LOGGED_IN_INDEX;

extern struct User *user;
extern struct Account *account;
extern struct Transaction *transaction;
extern struct Request *request;

#endif