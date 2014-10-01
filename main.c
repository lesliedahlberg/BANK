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

#include "bank.h"   //BANK SYSTEM
#include "xml.h"    //XML FILE HANDLING
#include "shared.h"//GLOBALS

//DECLARE GLOBALS
//NEW ONES MUST BE ADDED TO SHARED.H

int infoCount;
int userCount;
int accountCount;
int transactionCount;
int requestCount;

int running;
int loggedIn;

char * dataPath;
char * logPath;

int loggedInUserID;
int loggedInUserIndex;

struct Info *info;
struct User *user;
struct Account *account;
struct Transaction *transaction;
struct Request *request;


//MAIN
int main() {
    
    int readFileSuccesfully = 0;
    int savedFileSuccesfully = 0;

    //RUNTIME CONTROL VARS
	running = 1;
	loggedIn = 0;

    
    //PATHS
    //dataPath = "/Users/lesliedahlberg/Documents/GITHUB/BANK/data.xml";
    //logPath = "/Users/lesliedahlberg/Documents/GITHUB/BANK/log.txt";
    
    dataPath = "data/data.xml";
    logPath = "data/log.txt";

    //READ DATA FILE AND CHECK FOR ERRORS
    readFileSuccesfully = readXML(dataPath);
    
    
    
    if (readFileSuccesfully) {
        //RUN PROGRAM
        while(running){
            showOptions();
            //SHOW ADMIN || CLIENT OPTIONS WHILE LOGGED IN
            while(loggedIn){
                if(!strcmp(user[loggedInUserIndex].user_type, "client")){
                    showClientOptions();
                    
                }else if(!strcmp(user[loggedInUserIndex].user_type, "admin")){
                    showAdminOptions();
                    
                }
            }
        }
    }else{
        printf("Error reading data file!\n");
        waitForEnter();
    }
    
    //SAVE TO FILE AND CHECK FOR ERRORS
    
    savedFileSuccesfully = writeToXML(dataPath);
	
    if (savedFileSuccesfully) {
        //printf("Exited without errors!\n");
    }else{
        printf("Error occured, changes will not be saved!\n");
        waitForEnter();
    }

    //WAIT FOR USER TO EXIT
    
    
    //RETURN
        waitForEnter();
	return 0;
}
