loadDataFromFile();

do{
	showOption()
		//CASE
		login();
		exit();
		//END CASE
	if(user){
		do{
			showClientOptions()
				//CASE
				listAccounts();
					loop through accounts
				listTransactions();
					loop through transactions
				newTransactionToPA();
					listAccounts;
					select source account;
					select target account;
					transfer money;
				newTransaction();
					select source account;
						listAccounts;
					input target account;
					transfer money;
				requestNewAccount();
				requestDeletionOfAccount();
					listAccounts;
					select account;
				logOut();
				//END CASE
		}while(loggedIn);
	}else if(admin){
		do{
			showAdminOptions()
				//CASE
				listClient();
				addClient();
				removeClient();
				editClient();
				showRequests();
				addAccount();
				removeAccount();
				listLog();
				logOut();
				//END CASE
		}while(loggedIn);
	}
	
}while(running)

saveDataToFile();