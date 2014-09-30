#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Bank.h" //HEADER
#include "shared.h" //GLOBALS

/*****************
 LEVEL 1 FUNCTIONS
 *****************/

//GENERAL OPRIONS
void showOptions() {
    
    //LOOP & Y/N
    int input;
    int loop;
    
    newScreen();
    
    printf("WELCOME TO OUR ELECTRONIC BANKING SYSTEM\n");
    printf("OPTIONS (enter number and press enter):\n");
    
    //IF LOGGED IN
    if(loggedIn){
        
        printf("[1] Logout\n");
        printf("[2] Quit\n");
        
        do{
            loop = 0;
            input = 0;
            
            scanf("%d", &input);
            
            switch (input) {
                case 1:
                    logOut();
                    break;
                case 2:
                    quitProgram();
                    break;
                default:
                    printf("Invalid input!\n");
                    loop = 1;
                    break;
            }
        }while(loop);
        
    //IF LOGGED OUT
    }else if(!loggedIn){
        
        printf("[1] Login\n");
        printf("[2] Register\n");
        printf("[3] Quit\n");
        
        do{
            loop = 0;
            input = 0;
            
            scanf("%d", &input);
            
            switch (input) {
                case 1:
                    logIn();
                    break;
                case 2:
                    registerClient();
                    break;
                case 3:
                    quitProgram();
                    break;
                default:
                    printf("Invalid input!\n");
                    loop = 1;
                    break;
            }
        }while(loop);
    }
}

//LOG IN
int logIn() {
    char username[100];
    char password[100];
    int loop = 0;
    
    
    
    if(loggedIn){
        logOut();
    }
    
    do {
        newScreen();
        printf("LOG IN (enter # to cancel): \n");
        if(loop){
            printf("Invalid login credentials!\n");
        }
        
        printf("Username: ");
        scanf("%s", username);
        
        if(!strcmp(username, "#")){
            return 0;
        }
        
        printf("Password: ");
        scanf("%s", password);
        
        for(int i = 0; i < userCount; i++){
            if (strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0 && user[i].active == 1) {
                //DATE FOR LOG
                char date[100];
                char message[100];
                getDate(date);
                
                //SET ENV. VARS
                loggedIn = 1;
                loop = 1;
                loggedInUserID = user[i].user_id;
                loggedInUserIndex = i;
               
                //CREATE LOG MESSAGE
                strcat(message, user[i].username);
                strcat(message, " logged in: ");
                strcat(message, date);
                logMessage(message);
                
                //EXIT LOOP
                i = userCount;
            }
        }
        
    } while (!loggedIn);
    
    //RETURN
    return 1;
}

//LOG OUT
void logOut() {
    //DATE FOR LOG
    char date[100];
    char message[100];
    getDate(date);
    
    //CREATE LOG MESSAGE
    message[0] = '\0';
    
    strcat(message, user[loggedInUserIndex].username);
    strcat(message, " logged out: ");
    strcat(message, date);
    logMessage(message);
    
    //SET ENV. VARS
    loggedIn = 0;
    loggedInUserIndex = 0;
    loggedInUserID = 0;
}

//REGISTER CLIENT
void registerClient() {
    
    //TEMP VARS
    char personal_number[100];
    char username[100];
    char first_name[100];
    char last_name[100];
    char address[100];
    char password[100];
    
    newScreen();
    printf("REGISTRATION (enter # to cancel):\n");
    
    while(1){
        while(getchar() != '\n');
        printf("National identification number (10 digits): ");
        if(scanf("%s", personal_number))
            break;
        if (!strcmp(personal_number, "#")) {
            return;
        }
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Username: ");
        if(scanf("%s", username))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("First name: ");
        if(scanf("%s", first_name))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Last name: ");
        if(scanf("%s", last_name))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Address: ");
        if(scanf("%s", address))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Password: ");
        if(scanf("%s", password))
            break;
        printf("Invalid input!\n");
    }
    
    //SAVE TO STRUCT
    user[userCount].user_id = ++info[0].last_user_id;
    user[userCount].active = 1;
    strcpy(user[userCount].personal_number, personal_number);
    strcpy(user[userCount].username, username);
    strcpy(user[userCount].first_name, first_name);
    strcpy(user[userCount].last_name, last_name);
    strcpy(user[userCount].address, address);
    strcpy(user[userCount].password, password);
    strcpy(user[userCount].user_type, "client");
    
    //ALLOC MORE MEM.
    userCount++;
    user = realloc(user, (userCount + 1)*sizeof(struct User));
    
    //SUCCESS
    newScreen();
    printf("Registration successfull!\n");
    waitForEnter();
    
}

//QUIT
void quitProgram() {
    logOut();
    running = 0;
    
}

/*****************
 LEVEL 2 FUNCTIONS
 *****************/

//GEN. CLIENT OPTIONS
void showClientOptions() {
    
    int input;
    int loop;
    
    newScreen();
    printf("OPTIONS (enter number and press enter):\n");
    printf("[1] Accounts\n");
    printf("[2] Transactions\n");
    printf("[3] Transfer own accounts\n");
    printf("[4] Transfer to other\n");
    printf("[5] Request new/delet account\n");
    printf("[6] Logout\n");
    printf("[7] Quit\n");
    
    
    do{
        loop = 0;
        input = 0;
        
        scanf("%d", &input);
        
        switch (input) {
            case 1:
                listAccountsWithNewScreen();
                break;
            case 2:
                showTransactions();
                break;
            case 3:
                newTransactionToPA();
                break;
            case 4:
                newTransaction();
                break;
            case 5:
                newRequest();
                break;
            case 6:
                logOut();
                break;
            case 7:
                quitProgram();
                break;
            default:
                printf("Invalid input!\n");
                loop = 1;
                break;
        }
    }while(loop);
}

//LIST ACCOUNTS
void listAccountsWithNewScreen() {
    newScreen();
    listAccounts();
    waitForEnter();
}

//SHOW TRANSACTIONS
void showTransactions() {
    int i;
    
    newScreen();
    
    for (i=0; i < transactionCount; i++){
        if(transaction[i].user_id == user[loggedInUserIndex].user_id){
            if (i == 0) {
                printf("FROM      TO        AMOUNT    DATE           \n");
            }
            printf("%-10d%-10d%-10d%-15s\n", transaction[i].from, transaction[i].to, transaction[i].ammount, transaction[i].date);
            //printf("From: %d\nTo: %d\nAmmount: %d\nDate: %s\n||||||||||||||||||\n", transaction[i].from, transaction[i].to, transaction[i].ammount, transaction[i].date);
        }
    }
    
    waitForEnter();
}

//NEW PERSONAL TRANSACTION
void newTransactionToPA() {
    int fromAcc = 0, toAcc = 0, ammount = 0;
    char accept;
    char date[100];
    getDate(date);
    
    //Get source account
    newScreen();
    puts("SELECT SOURCE ACCOUNT (enter account number and press enter):");
    listAccounts();
    scanf("%d", &fromAcc);
    if(account[getAccountIndexByNumber(fromAcc)].user_id != user[loggedInUserIndex].user_id || account[getAccountIndexByNumber(fromAcc)].active != 1){
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    //Get target account
    newScreen();
    puts("SELECT TARGET ACCOUNT (enter account number and press enter):");
    listAccounts();
    scanf("%d", &toAcc);
    if((account[getAccountIndexByNumber(toAcc)].user_id != user[loggedInUserIndex].user_id || fromAcc == toAcc) || account[getAccountIndexByNumber(toAcc)].active != 1){
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    newScreen();
    printf("AMOUNT TO TRANSFER:");
    while(!scanf("%d", &ammount));
    
    newScreen();
    printf("TRANSFERE %d SEK FROM %d TO %d (y/n)?\n", ammount, fromAcc, toAcc);
    scanf(" %c", &accept);
    
    if (accept == 'y') {
        if (account[getAccountIndexByNumber(fromAcc)].balance < ammount) {
            newScreen();
            puts("Insufficient balance on account!");
            waitForEnter();
            return;
        }else{
            
            //TRANSFERE MONEY
            account[getAccountIndexByNumber(fromAcc)].balance = account[getAccountIndexByNumber(fromAcc)].balance - ammount;
            account[getAccountIndexByNumber(toAcc)].balance = account[getAccountIndexByNumber(toAcc)].balance + ammount;
            
            //SAVE TRANSACTION
            transaction[transactionCount].from = account[getAccountIndexByNumber(fromAcc)].account_number;
            transaction[transactionCount].to = account[getAccountIndexByNumber(toAcc)].account_number;
            transaction[transactionCount].ammount = (int) ammount;
            transaction[transactionCount].user_id = user[loggedInUserIndex].user_id;
            transaction[transactionCount].active = 1;
            strncpy(transaction[transactionCount].date, date, 20);
            
            //ALLOC MORE MEM.
            transactionCount++;
            transaction = realloc(transaction, (transactionCount + 1)*sizeof(struct Transaction));
            
            //NOTIFY
            newScreen();
            puts("Transfer succesfull!");
            
        }
        
    } else if (accept == 'n') {
        newScreen();
        printf("Transfere canceled!");
        waitForEnter();
        return;
    }
    waitForEnter();
}

//NEW GENERAL TRANSACTION
void newTransaction() {
    int fromAcc = 0, toAcc = 0, ammount = 0;
    char accept;
    char date[100];
    getDate(date);
    int transactionSuccesfull = 1;
    int looping;
    
    //Get source account
    looping = 0;
    do{
        newScreen();
        
        puts("Your accounts:");
        listAccounts();
        
        if(looping){
            puts("We are sorry, but something went wrong. Please choose an account again!\n");
        }
        
        puts("What account do you want to tranfer money from (Enter account number)?");
        scanf("%d", &fromAcc);
        
        looping = 1;
        
    }while(account[getAccountIndexByNumber(fromAcc)].user_id != user[loggedInUserIndex].user_id && account[getAccountIndexByNumber(fromAcc)].active != 1);
    
    //Get target account
    looping = 0;
    do{
        newScreen();
        
        if(looping){
            puts("We are sorry, but something went wrong. Please choose an account again!\n");
        }
        
        puts("What account do you want to tranfer money to (Enter account number)?");
        scanf("%d", &toAcc);
        
        looping = 1;
        
    }while((getAccountIndexByNumber(toAcc) >= accountCount || fromAcc == toAcc) && account[getAccountIndexByNumber(toAcc)].active != 1);
    
    
    
    printf("Enter ammount to transfer from account: %d to account: %d.", fromAcc, toAcc);
    while(!scanf("%d", &ammount));
    
    printf("Are you sure you want to transfer %d kr from account %d to account %d (y/n)?\n", ammount, fromAcc, toAcc);
    scanf(" %c", &accept);
    
    if (accept == 'y') {
        if (account[getAccountIndexByNumber(fromAcc)].balance < ammount) {
            puts("We are sorry, but your account balance is insufficent for this tranfer.");
            transactionSuccesfull = 0;
        }else{
            //överför pengarna mellan kontonen
            account[getAccountIndexByNumber(fromAcc)].balance = account[getAccountIndexByNumber(fromAcc)].balance - ammount;
            account[getAccountIndexByNumber(toAcc)].balance = account[getAccountIndexByNumber(toAcc)].balance + ammount;
            
            //loggar transaktionen
            transaction[transactionCount].from = account[getAccountIndexByNumber(fromAcc)].account_number;
            transaction[transactionCount].to = account[getAccountIndexByNumber(toAcc)].account_number;
            
            transaction[transactionCount].ammount = (int) ammount;
            
            transaction[transactionCount].user_id = user[loggedInUserIndex].user_id;
            
            transaction[transactionCount].active = 1;
            
            strncpy(transaction[transactionCount].date, date, 20);
            //printf("%d\n", transaction[transactionCount].ammount);
            
            
            transactionCount++;
            transaction = realloc(transaction, (transactionCount + 1)*sizeof(struct Transaction));
            
            puts("Transfer complete!");
            printf("Account %d: %d kr\nAccount %d: %d kr\n",
                   account[getAccountIndexByNumber(fromAcc)].account_number, account[getAccountIndexByNumber(fromAcc)].balance,
                   account[getAccountIndexByNumber(toAcc)].account_number, account[getAccountIndexByNumber(toAcc)].balance);
            
        }
        
    } else if (accept == 'n') {
        return;
    }
    waitForEnter();
}

//NEW REQUEST
void newRequest() {
    int loop, loop2;
    int input;
    int accountNumber;
    newScreen();
    printf("Request\n");
    printf("Options:\n");
    printf("New account.........(1)\n");
    printf("Delete account......(2)\n");
    do{
        loop = 0;
        input = 0;
        accountNumber = 0;
        
        printf("Enter number to select option: ");
        scanf("%d", &input);
        
        switch (input) {
            case 1:
                requestNewAccount();
                break;
            case 2:
                listAccounts();
                loop2 = 0;
                while(!loop2){
                    printf("Enter account number of account to be deleted: ");
                    loop2 = scanf("%d", &accountNumber);
                }
                requestRemovalOfAccount(accountNumber);
                break;
            default:
                printf("Error, please choose again!\n");
                loop = 1;
                break;
        }
    }while(loop);
    waitForEnter();
    
}

//GEN. ADMIN OPTIONS
void showAdminOptions() {
    
    int input;
    int loop;
    
    newScreen();
    
    printf("Options:\n");
    printf("Clients ......................(1)\n");
    printf("Account Requests..............(2)\n");
    printf("User log......................(3)\n");
    printf("Logout........................(4)\n");
    printf("Quit..........................(5)\n");
    
    do{
        loop = 0;
        input = 0;
        
        printf("Enter number to select option: ");
        scanf("%d", &input);
        
        switch (input) {
            case 1:
                listClient();
                break;
            case 2:
                showRequests();
                break;
            case 3:
                listLog();
                break;
            case 4:
                logOut();
                break;
            case 5:
                quitProgram();
                break;
            default:
                printf("Error, please choose again!\n");
                loop = 1;
                break;
        }
    }while(loop);
}

//LIST CLIENTS
void listClient() {
    
    char fullName[203];
    
    newScreen();
    printf("Clients:\n");
    printf("NAME                ID NUMBER      ACCOUNT ID     ADDRESS             \n");
    for(int i = 0; i < userCount; i ++){
        if(!strcmp(user[i].user_type, "client") ){
            fullName[0] = '\0';
            strcat(fullName, user[i].first_name);
            strcat(fullName, " ");
            strcat(fullName, user[i].last_name);
            
            printf("%-20s%-15s%-15d%-20s\n", fullName, user[i].personal_number, user[i].user_id, user[i].address);
        }
        
        
    }
    waitForEnter();
}

//SHOW REQUESTS
void showRequests() {
    int request_nr;
    char answer;
    
    if(requestCount == 0){
        puts("No requests at this time.");
    }else{
        for(int loop=0; loop < requestCount; loop++){
            if(request[loop].active != 0){
                printf("Request Nr. [%d]\nFrom User: %d\nAccount ID: %d\nAction: %s\nDate: %s\n////////////////////////////////\n\n", loop,request[loop].user_id, request[loop].account_id, request[loop].action, request[loop].date);
            }
        }
        puts("Select a request to answer (enter # to cancel)!");
        if (scanf("%d", &request_nr)) {
            getchar();
            printf("Would you'd like to take the action %s for the request nr [%d], y/n??", request[request_nr].action, request_nr);
            answer = getchar();
            
            if(answer == 'y'){
                
                
                if(!strcmp(request[request_nr].action, "ADD ACCOUNT")){
                    addAccount(request[request_nr].user_id);
                    
                    
                } else if(!strcmp(request[request_nr].action, "REMOVE ACCOUNT")){
                    account[getAccountIndexByID(request[request_nr].account_id)].active = 0;
                    
                    
                }
                request[request_nr].active = 0;
            }else if(answer == 'n'){
                
            }
        }
        
        
    }
    
    waitForEnter();
}

//SHOW LOG
void listLog() {
    
    newScreen();
    
    FILE * file;
    file = fopen(logPath, "r");
    char letter;
    
    while (1) {
        letter = fgetc(file);
        if(letter == EOF){
            break;
        }else{
            printf("%c", letter);
        }
    }
    
    fclose(file);
    waitForEnter();
    
}

/*****************
 SUPPORT FUNCTIONS
 *****************/

//GENERAL
//DATE
void getDate(char *date){
    
    time_t now = time(NULL );
    struct tm *t = localtime(&now);
    strftime(date, 20, "%d %m %Y %H:%M", t);
    //printf("%s\n", date);
    
}
//ID, ACCOUNT NUMBER AND INDEX COORDINATOR
int getAccountIndexByNumber(int accountNumber){
    for(int i = 0; i < accountCount; i++){
        if(account[i].account_number == accountNumber){
            return i;
        }
    }
    return -1;
}

int getAccountIndexByID(int account_id){
    for(int i = 0; i < accountCount; i++){
        if(account[i].account_id == account_id){
            return i;
        }
    }
    return -1;
}

int getAccountIdByNumber(int accountNumber){
    for(int i = 0; i < accountCount; i++){
        if(account[i].account_number == accountNumber){
            return account[i].account_id;
        }
    }
    return -1;
}

int uniqueAccountNumberGenerator(){
    int accountNumber;
    srand((unsigned) time(NULL ));
    accountNumber = rand() % 9999 + 1;
    for(int loop=0; loop < accountCount; loop++){
        if(accountNumber == account[loop].account_number){
            accountNumber = rand() % 9999 + 1;
        }
    }
    return accountNumber;
}

//BANK
//REQUEST NEW ACCOUNT
void requestNewAccount(){
    char date[20];
    getDate(date);
    
    request[requestCount].user_id = user[loggedInUserIndex].user_id;
    strcpy(request[requestCount].action, "ADD ACCOUNT");
    strcpy(request[requestCount].date, date);
    request[requestCount].active = 1;
    
    printf("Request successfull!\n");
    
    
    requestCount++;
    request = realloc(request, (requestCount + 1)*sizeof(struct Request));
    
}

//REQUEST REMOVAL OF ACCOUNT
void requestRemovalOfAccount(int accountNumber){
    char date[20];
    getDate(date);
    
    request[requestCount].user_id = user[loggedInUserIndex].user_id;
    strcpy(request[requestCount].action, "REMOVE ACCOUNT");
    request[requestCount].account_id = getAccountIdByNumber(accountNumber);
    strcpy(request[requestCount].date, date);
    request[requestCount].active = 1;
    
    printf("Request successfull!\n");
    
    
    requestCount++;
    request = realloc(request, (requestCount + 1)*sizeof(struct Request));
}

//REMOVE ACCOUNT
void removeAccount(int accountIndex) {
    account[accountIndex].active = 0;
    printf("The account was successfully deleted!\n");
}

//EDIT ACCOUNT
void editClient() {
    
}

//ADD ACCOUNT
void addAccount(int user_id) {
    
    
    account[accountCount].account_id = accountCount;
    account[accountCount].account_number = uniqueAccountNumberGenerator();
    account[accountCount].balance = 100;
    account[accountCount].user_id = user_id;
    account[accountCount].active = 1;
    
    accountCount++;
    account = realloc(account, (accountCount + 1)*sizeof(struct Account));
    
}

//ADD CLIENT
void addClient() {
    
}
/*
//LIST ACCOUNTS
void listAccounts() {
    int i;
    int userAccCount = 0;
    for (i = 0; i < accountCount; i++) {
        if (account[i].user_id == user[loggedInUserIndex].user_id && account[i].active == 1) {
            printf("Account Number: %d : Balance: %d\n",
                   account[i].account_number, account[i].balance);
            userAccCount++;
        }
    }
}*/


//LIST ACCOUNTS
void listAccounts() {
    int i;
    int userAccCount = 0;
    
    for (i = 0; i < accountCount; i++) {
        if (account[i].user_id == user[loggedInUserIndex].user_id && account[i].active == 1) {
            if (userAccCount == 0) {
                printf("ACCOUNT NUMBER      BALANCE\n");
            }
            printf("%-20d%d SEK\n", account[i].account_number, account[i].balance);
            userAccCount++;
        }
    }
    
    if (userAccCount == 0) {
        printf("You do not have any accounts!\n");
    }

    
}

//LOG
void logMessage(char logMessage[]){
    FILE * file;
    file = fopen(logPath, "a");
    char date[100];
    getDate(date);
    fprintf(file, "%s\n", logMessage);
    fclose(file);
}

//NEW SCREEN
void newScreen(){
    //system("cls");
}

//WAIT FOR USER
void waitForEnter(){
    while(getchar() != '\n');
    printf("Press ENTER to continue...");
    getchar();
}

