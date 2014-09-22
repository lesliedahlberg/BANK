#ifndef XML_H_
#define XML_H_

void writeToXML(char filePath[], struct User *user, struct Account *account, struct Transaction *transaction, struct Request *request, int userCount, int accountCount, int transactionCount, int requestCount);

void readXML(char filePath[], struct User **user, struct Account **account, struct Transaction **transaction, struct Request **request, int *userCount, int *accountCount, int *transactionCount, int *requestCount);

#endif