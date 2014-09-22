#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bank.h"
#include "xml.h"

void readXML(char filePath[], struct User **user, struct Account **account, struct Transaction **transaction, struct Request **request){

	//DEKLARATIONS
	char *entry;
	char *tag;
	char *line;

	FILE *file;

	char *currentFile;
	char *currentRecord;

	int lineLength;
	int isEOF = 0;
	int readingLine;

	int isSetFileEntry;
	int isSetRecordEntry;

	int userStructIndex;
	int accountStructIndex;
	int transactionStructIndex;
	int requestStructIndex;

	//LOOP VARS
	int tagOpen;
	int tagClosed;
	int entryClosed;
	int tagIndex;
	int entryIndex;
	int endTagOpen;
	int endTagIndex;
	int endCategoryTag;

	//INIT
	isSetFileEntry = 0;
	isSetRecordEntry = 0;

	userStructIndex = 0;
	accountStructIndex = 0;
	transactionStructIndex = 0;
	requestStructIndex = 0;

	//ALLOC STRUCTS
	*user = malloc(sizeof(struct User));
	*account = malloc(sizeof(struct Account));
	*transaction = malloc(sizeof(struct Transaction));
	*request = malloc(sizeof(struct Request));

	//OPEN FILE
	file = fopen(filePath, "r");
	currentFile = calloc(20, sizeof(char));
	//LOOP THROUGH FILE
	for(int row = 0; !isEOF; row++){
				
		//LOAD LINE
		line = malloc(sizeof(char));
		readingLine = 1;
		lineLength = 0;
		for (int i = 0; readingLine; i++){

	            line[i] = fgetc(file);
	            if (line[i] == EOF) {
	                isEOF = 1;
	                readingLine = 0;
	            }else if (line[i] != '\n') {
	                lineLength++;
	                
	            }else{
	            	readingLine = 0;
	            }
	            
	            line = realloc(line, (2 + i)*sizeof(char));
	    }

	    //INIT VARS
	    tagOpen = 0;
	    tagClosed = 0;
	    entryClosed = 0;
	    tagIndex = 0;
	    entryIndex = 0;
	    endTagOpen = 0;
	    endTagIndex = 0;
	    endCategoryTag = 0;
	    
	    entry = malloc(sizeof(char));
		tag = malloc(sizeof(char));
		
	    //LOOP THROUGH LINE
	    for(int i = 0; i < lineLength; i++){
			
	  		//LOAD ENTRIES AND TAGS
	  		if(!tagOpen && !tagClosed){
	  			
	  			if(line[i] == '<' && line[i + 1] != '/'){
	  				tagOpen = 1;
	  			}else if(line[i] == '<' && line[i + 1] == '/'){
	  				endCategoryTag = 1;
	  			}
	  		}
	    	else if(tagOpen && !tagClosed){
	    		if(line[i] == '>'){
	    			tagClosed = 1;
	    		}else{
	    			tag[tagIndex] = line[i];
	    			tagIndex++;
	    			tag = realloc(tag, (1 + tagIndex)*sizeof(char));
	    			tag[tagIndex] = '\0';
	    		}
		    }else if(tagClosed){
				entry[entryIndex] = line[i];
				entryIndex++;
				entry = realloc(entry, (1 + entryIndex)*sizeof(char));
				entry[entryIndex] = '\0';
			}
	    }

	    //EVALUATE TAGS AND ENTRIES	    
    	if(!strcmp(tag, "FILE")){
    		isSetFileEntry = 1;
    		
	
    	}
    	if(!strcmp(tag, "RECORD")){
    		isSetRecordEntry = 1;
	    }
	    if(entryIndex > 0){
	    	
	    	if(isSetFileEntry){
	    		//SET FILE_ENTRY
	    		if(!strcmp(tag, "FILE_NAME")){
	    			printf("%s\n", entry);
	    			strcpy(currentFile, entry);
	    			printf("%s\n", currentFile);
	    		}
	    	}

	    	if(isSetRecordEntry){
	    		
	    		//SAVE ENTRIES
	    		
	    		if(!strcmp(currentFile, "USER")){
	    			
	    			if(!strcmp(tag, "USER_ID")){
	    				strncpy((*user)[userStructIndex].user_id, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "PERSONAL_NUMBER")){
	    				strncpy((*user)[userStructIndex].personal_number, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "USERNAME")){
	    				strncpy((*user)[userStructIndex].username, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "FIRST_NAME")){
	    				strcpy((*user)[userStructIndex].first_name, entry);
	    			}
	    			else if(!strcmp(tag, "LAST_NAME")){
	    				strncpy((*user)[userStructIndex].last_name, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "ADDRESS")){
	    				strncpy((*user)[userStructIndex].address, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "USER_TYPE")){
	    				strncpy((*user)[userStructIndex].user_type, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "PASSWORD")){
	    				strncpy((*user)[userStructIndex].password, entry, entryIndex);
	    			}
	    		}else if(!strcmp(currentFile, "ACCOUNT")){
	    			if(!strcmp(tag, "ACCOUNT_ID")){
	    				(*account)[accountStructIndex].account_id = (short) entry;
	    				//strncpy(account[accountStructIndex].account_id, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "ACCOUNT_NUMBER")){
	    				(*account)[accountStructIndex].account_number = (int) entry;
	    				//strncpy(account[accountStructIndex].account_number, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "BALANCE")){
	    				(*account)[accountStructIndex].balance = (int) entry;
	    				//strncpy(account[accountStructIndex].balance, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "USER_ID")){
	    				(*account)[accountStructIndex].user_id = (short) entry;
	    				//strncpy(account[accountStructIndex].user_id, entry, entryIndex);
	    			}
	    		}else if(!strcmp(currentFile, "TRANSACTION")){
	    			if(!strcmp(tag, "FROM")){
	    				(*transaction)[transactionStructIndex].from = (short) entry;
	    				//strncpy(transaction[transactionStructIndex].from, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "TO")){
	    				(*transaction)[transactionStructIndex].to = (short) entry;
	    				//strncpy(transaction[transactionStructIndex].to, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "DATE")){
	    				strncpy((*transaction)[transactionStructIndex].date, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "AMMOUNT")){
	    				(*transaction)[transactionStructIndex].ammount = (int) entry;
	    				//strncpy(transaction[transactionStructIndex].ammount, entry, entryIndex);
	    			}
	    		}else if(!strcmp(currentFile, "REQUEST")){
	    			if(!strcmp(tag, "USER_ID")){
	    				(*request)[requestStructIndex].user_id = (short) entry;
	    				//strncpy(request[requestStructIndex].user_id, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "ACTION")){
	    				strncpy((*request)[requestStructIndex].action, entry, entryIndex);
	    			}
	    			else if(!strcmp(tag, "DATE")){
	    				strncpy((*request)[requestStructIndex].date, entry, entryIndex);
	    			}
	    		}
	    	}

	    }else if(endCategoryTag){
	    	//++INDEXES
	    	if(isSetRecordEntry){
	    		isSetRecordEntry = 0;
	    		if(!strcmp(currentFile, "USER")){
	    			userStructIndex++;
	    			*user = realloc(*user, (1 + userStructIndex)*sizeof(struct User));
	    		}else if(!strcmp(currentFile, "ACCOUNT")){
	    			accountStructIndex++;
	    			*account = realloc(*account, (1 + accountStructIndex)*sizeof(struct Account));
	    		}else if(!strcmp(currentFile, "TRANSACTION")){
	    			transactionStructIndex++;
	    			*transaction = realloc(*transaction, (1 + transactionStructIndex)*sizeof(struct Transaction));
	    		}else if(!strcmp(currentFile, "REQUEST")){
	    			requestStructIndex++;
	    			*request = realloc(*request, (1 + requestStructIndex)*sizeof(struct Request));
	    		}

	    	}else{
	    		//RESET FILE_ENTRY
	    		isSetFileEntry = 0;
	    		currentFile[0] = '\0';
	    		
	    		
	    	}
	    }
	   
	   	free(line);
		free(tag);
		free(entry);
		
	}
}