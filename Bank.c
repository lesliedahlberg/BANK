/*
 Created by: Leslie Dahlberg (ldg14001), Mattias Johansson (mjn14021)
 Projekt: Banksystem
 Mälardalens högskola
 DVA117 - Programmering i C, HT14
 30 September 2014
 */

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
    printf("OPTIONS:\n");
    
    //IF LOGGED IN
    if(loggedIn){
        
        printf("[1] Logout\n");
        printf("[2] Quit\n");
        
        do{
            loop = 0;
            input = 0;
            
            
            if (scanf(" %d", &input)) {
            }else{
                getchar();
            }
            
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
            
            if (scanf(" %d", &input)) {
            }else{
                getchar();
            }
            
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
        scanf(" %s", username);
        
        if(!strcmp(username, "#")){
            return 0;
        }
        
        printf("Password: ");
        scanf(" %s", password);
        
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
    
    printf("National identification number (10 digits): ");
    if (scanf(" %s", personal_number)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    if (!strcmp(personal_number, "#")) {
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }

    printf("Username: ");
    if (scanf(" %s", username)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("First name: ");
    if (scanf(" %s", first_name)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Last name: ");
    if (scanf(" %s", last_name)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Address: ");
    if (scanf(" %s", address)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Password: ");
    if (scanf(" %s", password)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    
    /*
    while(1){
        while(getchar() != '\n');
        printf("National identification number (10 digits): ");
        if(scanf(" %s", personal_number))
            break;
        if (!strcmp(personal_number, "#")) {
            return;
        }
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Username: ");
        if(scanf(" %s", username))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("First name: ");
        if(scanf(" %s", first_name))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Last name: ");
        if(scanf(" %s", last_name))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Address: ");
        if(scanf(" %s", address))
            break;
        printf("Invalid input!\n");
    }
    
    while(1){
        while(getchar() != '\n');
        printf("Password: ");
        if(scanf(" %s", password))
            break;
        printf("Invalid input!\n");
    }*/
    
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
    printf("OPTIONS:\n");
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
        
        if (scanf(" %d", &input)) {
        }else{
            getchar();
        }
        
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
                loop = 0;
                break;
            case 7:
                quitProgram();
                loop = 0;
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
    int accountNumber;
    newScreen();
    printf("ENTER ACCOUNT NUMBER FOR TRANSACTION HISTORY (enter # to cancel):\n");
    listAccounts();
    if (scanf(" %d", &accountNumber)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    showTransactionForAccount(accountNumber);
    
    
}

void showTransactionForAccount(int accountNumber){
    int i;
    int accountExist = 0;
    
    newScreen();
    printf("FROM      TO        AMOUNT    DATE           \n");
    
    for (i=0; i < transactionCount; i++){
        if(transaction[i].user_id == user[loggedInUserIndex].user_id && ( transaction[i].from == accountNumber || transaction[i].to == accountNumber)){
            accountExist = 1;
            
            
            
            printf("%-10d%-10d%-10d%-15s\n", transaction[i].from, transaction[i].to, transaction[i].amount, transaction[i].date);
            //printf("From: %d\nTo: %d\nAmount: %d\nDate: %s\n||||||||||||||||||\n", transaction[i].from, transaction[i].to, transaction[i].amount, transaction[i].date);
        }
    }
    
    if (!accountExist) {
        printf("You do not have any transactions for this account!\n");
    }
    
    waitForEnter();
}



//NEW PERSONAL TRANSACTION
void newTransactionToPA() {
    int fromAcc = 0, toAcc = 0, amount = 0;
    char accept;
    char date[100];
    getDate(date);
    
    //Get source account
    newScreen();
    printf("ENTER SOURCE ACCOUNT NUMBER (enter # to cancel):\n");
    listAccounts();
    
    if (scanf(" %d", &fromAcc)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    if(account[getAccountIndexByNumber(fromAcc)].user_id != user[loggedInUserIndex].user_id || account[getAccountIndexByNumber(fromAcc)].active != 1){
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    //Get target account
    newScreen();
    printf("ENTER TARGET ACCOUNT NUMBER (enter # to cancel):\n");
    listAccounts();
    if (scanf(" %d", &toAcc)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    if((account[getAccountIndexByNumber(toAcc)].user_id != user[loggedInUserIndex].user_id || fromAcc == toAcc) || account[getAccountIndexByNumber(toAcc)].active != 1){
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    newScreen();
    printf("AMOUNT TO TRANSFER (enter # to cancel): ");
    if (scanf(" %d", &amount)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    newScreen();
    printf("TRANSFER %d FROM %d TO %d (y/n)? ", amount, fromAcc, toAcc);
    if (scanf(" %c", &accept)) {
    }else{
        getchar();
    }
    
    if (accept == 'y') {
        if (account[getAccountIndexByNumber(fromAcc)].balance < amount) {
            newScreen();
            printf("Insufficient balance on account!\n");
            waitForEnter();
            return;
        }else{
            
            //TRANSFERE MONEY
            account[getAccountIndexByNumber(fromAcc)].balance = account[getAccountIndexByNumber(fromAcc)].balance - amount;
            account[getAccountIndexByNumber(toAcc)].balance = account[getAccountIndexByNumber(toAcc)].balance + amount;
            
            //SAVE TRANSACTION
            transaction[transactionCount].from = account[getAccountIndexByNumber(fromAcc)].account_number;
            transaction[transactionCount].to = account[getAccountIndexByNumber(toAcc)].account_number;
            transaction[transactionCount].amount = amount;
            transaction[transactionCount].user_id = user[loggedInUserIndex].user_id;
            transaction[transactionCount].active = 1;
            strncpy(transaction[transactionCount].date, date, 20);
            
            //ALLOC MORE MEM.
            transactionCount++;
            transaction = realloc(transaction, (transactionCount + 1)*sizeof(struct Transaction));
            
            //NOTIFY
            newScreen();
            printf("Transfer succesfull!\n");
            waitForEnter();
            return;
            
        }
        
    } else if (accept == 'n') {
        newScreen();
        printf("Transfer canceled!\n");
        waitForEnter();
        return;
    }
    
}


//NEW GENERAL TRANSACTION
void newTransaction() {
    int fromAcc = 0, toAcc = 0, amount = 0;
    char accept;
    char date[100];
    getDate(date);
    
    //Get source account
    newScreen();
    printf("ENTER SOURCE ACCOUNT NUMBER (enter # to cancel):\n");
    listAccounts();
    if (scanf(" %d", &fromAcc)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    if(account[getAccountIndexByNumber(fromAcc)].user_id != user[loggedInUserIndex].user_id || account[getAccountIndexByNumber(fromAcc)].active != 1){
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    //Get target account
    newScreen();
    printf("ENTER TARGET ACCOUNT NUMBER (enter # to cancel):\n");
    if (scanf(" %d", &toAcc)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
    }
    if((getAccountIndexByNumber(toAcc) >= accountCount || fromAcc == toAcc) || account[getAccountIndexByNumber(toAcc)].active != 1){
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    newScreen();
    printf("AMOUNT TO TRANSFER:");
    if (scanf(" %d", &amount)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    newScreen();
    printf("TRANSFER %d FROM %d TO %d (y/n)? ", amount, fromAcc, toAcc);
    if (scanf(" %c", &accept)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    if (accept == 'y') {
        if (account[getAccountIndexByNumber(fromAcc)].balance < amount) {
            newScreen();
            printf("Insufficient balance on account!\n");
            waitForEnter();
            return;
        }else{
            
            //TRANSFERE MONEY
            account[getAccountIndexByNumber(fromAcc)].balance = account[getAccountIndexByNumber(fromAcc)].balance - amount;
            account[getAccountIndexByNumber(toAcc)].balance = account[getAccountIndexByNumber(toAcc)].balance + amount;
            
            //SAVE TRANSACTION
            transaction[transactionCount].from = account[getAccountIndexByNumber(fromAcc)].account_number;
            transaction[transactionCount].to = account[getAccountIndexByNumber(toAcc)].account_number;
            transaction[transactionCount].amount = amount;
            transaction[transactionCount].user_id = user[loggedInUserIndex].user_id;
            transaction[transactionCount].active = 1;
            strncpy(transaction[transactionCount].date, date, 20);
            
            //ALLOC MORE MEM.
            transactionCount++;
            transaction = realloc(transaction, (transactionCount + 1)*sizeof(struct Transaction));
            
            //NOTIFY
            newScreen();
            printf("Transfer succesfull!\n");
            waitForEnter();
            return;
            
        }
        
    } else if (accept == 'n') {
        newScreen();
        printf("Transfer canceled!\n");
        waitForEnter();
        return;
    }
    
}

//NEW REQUEST
void newRequest() {
    int input;
    int accountNumber;
    
    newScreen();
    printf("CREATE REQUEST (enter # to cancel):\n");
    printf("[1] New account\n");
    printf("[2] Delete account\n");
    
    if (scanf(" %d", &input)) {
        switch (input) {
            case 1:
                requestNewAccount();
                waitForEnter();
                return;
                break;
            case 2:
                newScreen();
                printf("CHOOSE ACCOUNT TO REMOVE (enter # to cancel):\n");
                listAccounts();
                if (scanf(" %d", &accountNumber)) {
                    if (account[getAccountIndexByNumber(accountNumber)].active == 1) {
                        requestRemovalOfAccount(accountNumber);
                        waitForEnter();
                        return;
                    }else{
                        printf("Invalid input!\n");
                        waitForEnter();
                        return;
                    }
                }else{
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                break;
            default:
                printf("Invalid input!\n");
                waitForEnter();
                return;
                break;
        }
    }else{
        getchar();
    }
}

//GEN. ADMIN OPTIONS
void showAdminOptions() {
    
    int input;
    int loop;
    
    newScreen();
    
    printf("OPTIONS:\n");
    printf("[1] Users\n");
    printf("[2] Account Requests\n");
    printf("[3] Accounts\n");
    printf("[4] User log\n");
    printf("[5] Logout\n");
    printf("[6] Quit\n");
    
    do{
        loop = 0;
        input = 0;
        
        if (scanf(" %d", &input)) {
        }else{
            getchar();
        }
        
        
        switch (input) {
            case 1:
                clients();
                break;
            case 2:
                showRequests();
                break;
            case 3:
                manageAccounts();
                break;
            case 4:
                listLog();
                break;
            case 5:
                logOut();
                loop = 0;
                break;
            case 6:
                quitProgram();
                loop = 0;
                break;
            default:
                printf("Invalid input!\n");
                loop = 1;
                break;
        }
    }while(loop);
}

//CLIENTS MENU
void clients(){
    
    int input;
    int loop;
    
    
    
    do{
        loop = 1;
        input = 0;
        
        newScreen();
        
        printf("USERS:\n");
        printf("[1] List clients\n");
        printf("[2] List client accounts\n");
        printf("[3] Edit user information\n");
        printf("[4] Add users\n");
        printf("[5] Delete users\n");
        printf("[6] Return\n");
        
        if (scanf(" %d", &input)) {
        }else{
            getchar();
        }
        
        
        switch (input) {
            case 1:
                listClientsWithNewScreen();
                break;
            case 2:
                listClientAccount();
                break;
            case 3:
                editClient();
                break;
            case 4:
                addClient();
                break;
            case 5:
                deleteClient();
                break;
            case 6:
                loop = 0;
                return;
                break;
            default:
                printf("Invalid input!\n");
                loop = 1;
                break;
        }
    }while(loop);

}

//LIST CLIENT ACCOUNTS
void listClientAccount(){
    int userID;
    newScreen();
    printf("ENTER CLIENT (USER ID) TO DISPLAY ACCOUNTS FOR (enter # to cancel):\n");
    listClients();
    if (scanf(" %d", &userID)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    listAccountsForUser(userID);
    waitForEnter();
}

//ADD CLIENTS
void addClient(){
    registerClientByAdmin();
}

//REGISTER CLIENT BY ADMIN
void registerClientByAdmin() {
    
    //TEMP VARS
    char personal_number[100];
    char username[100];
    char first_name[100];
    char last_name[100];
    char address[100];
    char password[100];
    char userType[100];
    
    newScreen();
    
    printf("REGISTRATION (enter # to cancel):\n");
    
    printf("National identification number (10 digits): ");
    if (scanf(" %s", personal_number)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    if (!strcmp(personal_number, "#")) {
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Username: ");
    if (scanf(" %s", username)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("First name: ");
    if (scanf(" %s", first_name)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Last name: ");
    if (scanf(" %s", last_name)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Address: ");
    if (scanf(" %s", address)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("Password: ");
    if (scanf(" %s", password)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    printf("User type: ");
    if (scanf(" %s", userType)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
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
    strcpy(user[userCount].user_type, userType);
    
    //ALLOC MORE MEM.
    userCount++;
    user = realloc(user, (userCount + 1)*sizeof(struct User));
    
    //SUCCESS
    newScreen();
    printf("Registration successfull!\n");
    waitForEnter();
    
}


//DELETE CLIENTS
void deleteClient(){
    int userID;
    newScreen();
    printf("ENTER USER ID OF USER TO BE DELETED (enter # to cancel):\n");
    listUsers();
    if (scanf(" %d", &userID)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    user[getUserIndexByID(userID)].active = 0;
    waitForEnter();
}

//EDIT CLIENTS
void editClient(){
    int userID;
    int userIndex;
    int input;
    int loop;
    
    
    newScreen();
    printf("ENTER USER ID TO EDIT USER (enter # to cancel):\n");
    listUsers();
    if (scanf(" %d", &userID)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    //user[getUserIndexByID(userID)].active = 0;

    userIndex = getUserIndexByID(userID);
    
    do{
        loop = 1;
        input = 0;
        
        newScreen();
        
        printf("EDIT USER INFORMATION:\n");
        printf("[1] National indentification number\n");
        printf("[2] Username\n");
        printf("[3] First name\n");
        printf("[4] Last name\n");
        printf("[5] Address\n");
        printf("[6] User type\n");
        printf("[7] Password\n");
        printf("[8] Return\n");
        
        
        if (scanf(" %d", &input)) {
        }else{
            getchar();
        }
        
        
        switch (input) {
            case 1:
                newScreen();
                printf("Current national indentification number: %s\n", user[userIndex].personal_number);
                printf("Enter new: ");
                if (scanf(" %s", user[userIndex].personal_number)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 2:
                newScreen();
                printf("Current username: %s\n", user[userIndex].username);
                printf("Enter new: ");
                if (scanf(" %s", user[userIndex].username)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 3:
                newScreen();
                printf("Current first name: %s\n", user[userIndex].first_name);
                printf("Enter new: ");
                if (scanf(" %s", user[userIndex].first_name)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 4:
                newScreen();
                printf("Current last name: %s\n", user[userIndex].last_name);
                printf("Enter new: ");
                if (scanf(" %s", user[userIndex].last_name)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 5:
                newScreen();
                printf("Current address: %s\n", user[userIndex].address);
                printf("Enter new: ");
                if (scanf(" %s", user[userIndex].address)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 6:
                newScreen();
                printf("Current user type: %s\n", user[userIndex].user_type);
                printf("Enter new: ");
                if (scanf(" %s", user[userIndex].user_type)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 7:
                newScreen();
                printf("Enter new password: ");
                if (scanf(" %s", user[userIndex].password)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                printf("Change succesfull!\n");
                waitForEnter();
                break;
            case 8:
                loop = 0;
                return;
                break;
            default:
                printf("Invalid input!\n");
                loop = 1;
                break;
        }
    }while(loop);
    
    //
    
    waitForEnter();
}

//LIST CLIENTS
void listClientsWithNewScreen() {
    
    newScreen();
    listClients();
    waitForEnter();
}

//LIST CLIENTS
void listClients() {
    
    char fullName[203];
    
    
    printf("CLIENTS:\n");
    printf("NAME                ID NUMBER      USER ID        ADDRESS             \n");
    for(int i = 0; i < userCount; i ++){
        if(!strcmp(user[i].user_type, "client") && user[i].active == 1){
            fullName[0] = '\0';
            strcat(fullName, user[i].first_name);
            strcat(fullName, " ");
            strcat(fullName, user[i].last_name);
            
            printf("%-20s%-15s%-15d%-20s\n", fullName, user[i].personal_number, user[i].user_id, user[i].address);
        }
        
        
    }
    
}

//LIST USERS
void listUsers() {
    
    char fullName[203];
    
    
    printf("CLIENTS:\n");
    printf("NAME                ID NUMBER      USER ID        ADDRESS             \n");
    for(int i = 0; i < userCount; i ++){
        if(user[i].active == 1){
            fullName[0] = '\0';
            strcat(fullName, user[i].first_name);
            strcat(fullName, " ");
            strcat(fullName, user[i].last_name);
            
            printf("%-20s%-15s%-15d%-20s\n", fullName, user[i].personal_number, user[i].user_id, user[i].address);
        }
        
        
    }
    
}

void manageAccounts(){
    int userID;
    int accountNumber;
    newScreen();
    printf("ENTER A USER ID TO ADD/REMOVE ACCOUNTS FOR  (enter # to cancel):\n");
    listClients();
    if (scanf(" %d", &userID)) {
    }else{
        getchar();
        printf("Invalid input!\n");
        waitForEnter();
        return;
    }
    
    int input;
    int loop;
    
    newScreen();
    
    do{
        loop = 1;
        input = 0;
        
        newScreen();
        
        printf("ACTIONS:\n");
        printf("[1] Add account\n");
        printf("[2] Remove account\n");
        printf("[3] Return\n");
        
        if (scanf(" %d", &input)) {
        }else{
            getchar();
        }
        
        
        switch (input) {
            case 1:
                addAccount(userID);
                printf("Account added succesfully!\n");
                waitForEnter();
                break;
            case 2:
                newScreen();
                printf("ENTER A ACCOUNT ID TO DELETE (enter # to cancel):\n");
                listAccountsForUser(userID);
                if (scanf(" %d", &accountNumber)) {
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                account[getAccountIndexByNumber(accountNumber)].active = 0;
                printf("Account deleted succesfully!\n");
                break;
            case 3:
                loop = 0;
                return;
                break;
            default:
                printf("Invalid input!\n");
                loop = 1;
                break;
        }
    }while(loop);

    
    
    
    waitForEnter();
    
    
};


//SHOW REQUESTS
void showRequests() {
    int request_nr;
    char answer;
    
    if(requestCount == 0){
        printf("There are no requests!\n");
    }else{
        printf("SELECT REQUEST TO ANSWER (enter # to cancel):\n");
        printf("NUMBER    USER      ACCOUNT ID     ACTION              DATE                ACTIVE\n");
        for(int loop=0; loop < requestCount; loop++){
            if(request[loop].active == 1){
                printf("%-10d%-10d%-15d%-20s%-20s%d\n", loop,request[loop].user_id, request[loop].account_id, request[loop].action, request[loop].date, request[loop].active);
            }
        }
        
        if (scanf(" %d", &request_nr)) {
            if (request_nr < requestCount && request_nr >= 0) {
                newScreen();
                printf("DO YOU WANT TO ANSWER REQUEST NR.%d: %s (y/n)? ", request_nr, request[request_nr].action);
                
                if(scanf(" %c", &answer)){
                    if(answer == 'y'){
                        if(!strcmp(request[request_nr].action, "ADD ACCOUNT")){
                            addAccount(request[request_nr].user_id);
                            request[request_nr].active = 0;
                            newScreen();
                            printf("Account added succesfully!\n");
                            waitForEnter();
                            return;
                        }else if(!strcmp(request[request_nr].action, "REMOVE ACCOUNT")){
                            account[getAccountIndexByID(request[request_nr].account_id)].active = 0;
                            request[request_nr].active = 0;
                            newScreen();
                            printf("Account removed succesfully!\n");
                            waitForEnter();
                            return;
                        }
                        
                    }else if(answer == 'n'){
                        printf("Invalid input!\n");
                        waitForEnter();
                        return;
                    }
                }else{
                    getchar();
                    printf("Invalid input!\n");
                    waitForEnter();
                    return;
                }
                
                
            }
            
            
        }else{
            getchar();
            printf("Invalid input!\n");
            waitForEnter();
            return;
        }
        
        
    }
    
 
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

int getUserIndexByID(int userID){
    for (int i = 0; i < userCount; i++) {
        if (user[i].user_id == userID) {
            return i;
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




//LIST ACCOUNTS
void listAccounts() {
    int i;
    int userAccCount = 0;
    
    for (i = 0; i < accountCount; i++) {
        if (account[i].user_id == user[loggedInUserIndex].user_id && account[i].active == 1) {
            if (userAccCount == 0) {
                printf("ACCOUNT NUMBER      BALANCE\n");
            }
            printf("%-20d%d\n", account[i].account_number, account[i].balance);
            userAccCount++;
        }
    }
    
    if (userAccCount == 0) {
        printf("No accounts available!\n");
    }

    
}

//LIST ACCOUNTS FOR USER
void listAccountsForUser(int userID) {
    int i;
    int userAccCount = 0;
    
    for (i = 0; i < accountCount; i++) {
        if (account[i].user_id == user[getUserIndexByID(userID)].user_id && account[i].active == 1) {
            if (userAccCount == 0) {
                printf("ACCOUNT NUMBER      BALANCE\n");
            }
            printf("%-20d%d\n", account[i].account_number, account[i].balance);
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
    
    //printf("___________________________________________________\n");
    system("cls");
}

//WAIT FOR USER
void waitForEnter(){
    while(getchar() != '\n');
    printf("Press ENTER to continue...");
    getchar();
}

