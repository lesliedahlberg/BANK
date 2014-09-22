#include "bank.h"
#include "xml.h"

void readXML(char filePath[], struct User *user, struct Account *account, struct Transaction *transaction, struct Request *request){

	//DEKLARATIONS
	char entry[20];
	char tag[20];

	char currentFile[20];
	char currentRecord[20];

	int lineLength;
	int isEOF;

	int isSetFileEntry;
	int isSetRecordEntry;

	int userStructIndex;
	int accountStructIndex;
	int transactionStructIndex;
	int requestStructIndex;

	//ALLOC STRUCTS
	user = malloc(sizeof(struct User));
	account = malloc(sizeof(struct Account));
	transaction = malloc(sizeof(struct Transaction));
	request = malloc(sizeof(struct Request));

	//LOOP VARS
	int tagOpen;
	int tagClosed;
	int entryClosed;
	int tagIndex;
	int entryIndex;
	int endTagOpen;
	int endTagIndex;
	int endCategoryTag;

	FILE *file;

	//INIT
	isSetFileEntry = 0;
	isSetRecordEntry = 0;

	userStructIndex = 0;
	accountStructIndex = 0;
	transactionStructIndex = 0;
	requestStructIndex = 0;

	//OPEN FILE
	file = fopen(filePath, "r");

	//LOOP THROUGH FILE
	for(int row = 0; !isEOF; row++){
		line = malloc(sizeof(char))
		lineLength = 0;

		//LOAD LINE
		for (int i = 0; 1; i++){
	            line[i] = fgetc(file);
	            if (line[i] == '\n') {
	                lineLength = i + 1;
	                break;
	            }
	            if (line[i] == EOF) {
	                isEOF = 1;
	                break;
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

	    //LOOP THROUGH LINE
	    for(int i = 0; i < lineLength; i++){

	  		//LOAD ENTRIES AND TAGS
	    	if(!tagClosed){
		    	if(!tagOpen){
		    		if(line[i] == "<"){
		    			if(line[i+1] == "/"){
		    				endCategoryTag = 1;
		    				i = lineLength;
		    			}
		    			tagOpen = 1;
		    		}
		    	}else if(tagOpen){
		    		if(line[i] == ">"){
		    			tagClosed = 1;
		    		}else{
		    			tag[tagIndex] = line[i];
		    			tagIndex++;
		    		}
		    	}
			}else if(!entryClosed){
				if(line[i] == "<"){
					entryClosed = 1;
				}else{
					entry[entryIndex] = line[i];
					entryIndex++;
				}
			}else if(entryClosed){
				if(endTagIndex == 1){
					if(line[i] != "/"){
						error = 1;
					}
				}else if(i == lineLength - 1){
					if(line[i] != ">"){
						error = 1;
					}
				}else{
					if(line[i] != tag[endTagIndex]{
						error = 1;
					}
					endTagIndex++;
				}
			}
	    }

	    //EVALUATE TAGS AND ENTRIES
	    if(!entryClosed){
	    	if(!strcmp(tag, "FILE")){
	    		isSetFileEntry = 1;
	    	}
	    	if(!strcmp(tag, "RECORD")){
	    		isSetRecordEntry = 1;
	    	}

	    }else if(entryClosed){
	    	if(isSetFileEntry){
	    		//SET FILE_ENTRY
	    		if(!strcmp(tag, "FILE_NAME")){
	    			strcpy(currentFile, tag);
	    		}
	    	}
	    	if(isSetRecordEntry){
	    		//SAVE ENTRIES
	    		if(currentFile == "USER"){
	    			if(!strcmp(tag, "USER_ID")){
	    				strcpy(user[userStructIndex].user_id, entry);
	    			}
	    			else if(!strcmp(tag, "PERSONAL_NUMBER")){
	    				strcpy(user[userStructIndex].personal_number, entry);
	    			}
	    			else if(!strcmp(tag, "USERNAME")){
	    				strcpy(user[userStructIndex].user_name, entry);
	    			}
	    			else if(!strcmp(tag, "FIRST_NAME")){
	    				strcpy(user[userStructIndex].first_name, entry);
	    			}
	    			else if(!strcmp(tag, "LAST_NAME")){
	    				strcpy(user[userStructIndex].last_name, entry);
	    			}
	    			else if(!strcmp(tag, "ADDRESS")){
	    				strcpy(user[userStructIndex].address, entry);
	    			}
	    			else if(!strcmp(tag, "USER_TYPE")){
	    				strcpy(user[userStructIndex].user_name, entry);
	    			}
	    			else if(!strcmp(tag, "PASSWORD")){
	    				strcpy(user[userStructIndex].password, entry);
	    			}
	    		}else if(currentFile == "ACCOUNT"){
	    			if(!strcmp(tag, "ACCOUNT_ID")){
	    				strcpy(account[accountStructIndex]., entry);
	    			}
	    			else if(!strcmp(tag, "ACCOUNT_NUMBER")){
	    				strcpy(account[accountStructIndex].account_number, entry);
	    			}
	    			else if(!strcmp(tag, "BALANCE")){
	    				strcpy(account[accountStructIndex].balance, entry);
	    			}
	    			else if(!strcmp(tag, "USER_ID")){
	    				strcpy(account[accountStructIndex].user_id, entry);
	    			}
	    		}else if(currentFile == "TRANSACTION"){
	    			if(!strcmp(tag, "FROM")){
	    				strcpy(transaction[transactionStructIndex].from, entry);
	    			}
	    			else if(!strcmp(tag, "TO")){
	    				strcpy(transaction[transactionStructIndex].to, entry);
	    			}
	    			else if(!strcmp(tag, "DATE")){
	    				strcpy(transaction[transactionStructIndex].date, entry);
	    			}
	    			else if(!strcmp(tag, "AMMOUNT")){
	    				strcpy(transaction[transactionStructIndex].ammount, entry);
	    			}
	    		}else if(currentFile == "REQUEST"){
	    			if(!strcmp(tag, "USER_ID")){
	    				strcpy(request[requestStructIndex].user_id, entry);
	    			}
	    			else if(!strcmp(tag, "ACTION")){
	    				strcpy(request[requestStructIndex].action, entry);
	    			}
	    			else if(!strcmp(tag, "DATE")){
	    				strcpy(request[requestStructIndex].date, entry);
	    			}
	    		}
	    	}

	    }else if(endCategoryTag){
	    	//++INDEXES
	    	if(isSetRecordEntry){
	    		isSetRecordEntry = 0;
	    		if(currentFile == "USER"){
	    			userStructIndex++;
	    			user = realloc(user, (1 + userStructIndex)*sizeof(struct User));
	    		}else if(currentFile == "ACCOUNT"){
	    			accountStructIndex++;
	    			account = realloc(account, (1 + accountStructIndex)*sizeof(struct Account));
	    		}else if(currentFile == "TRANSACTION"){
	    			transactionStructIndex++;
	    			transaction = realloc(transaction, (1 + transactionStructIndex)*sizeof(struct Transaction));
	    		}else if(currentFile == "REQUEST"){
	    			requestStructIndex++;
	    			request = realloc(request, (1 + requestStructIndex)*sizeof(struct Request));
	    		}

	    	}else{
	    		//RESET FILE_ENTRY
	    		isSetFileEntry = 0;
	    		strcpy(currentFile, "");
	    	}
	    }

	}

	free(line);

}