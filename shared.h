#ifndef SHARED_H_
#define SHARED_H_

extern int infoCount;
extern int userCount;
extern int accountCount;
extern int transactionCount;
extern int requestCount;

extern int running;
extern int loggedIn;
extern int currentUserId;

extern char * dataPath;
extern char * logPath;

extern int LOGGED_IN_USER_ID;
extern int LOGGED_IN_INDEX;

extern struct Info *info;
extern struct User *user;
extern struct Account *account;
extern struct Transaction *transaction;
extern struct Request *request;

#endif