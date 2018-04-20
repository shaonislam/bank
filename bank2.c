/*

Shaon Islam
CS 2750 PA 4
Bank Account Management System

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/* Declaring the struct
 Creating an array to hold up to 100 account structs */
struct account
{
	char first[20];
	char last[20];
	char middle[1];
	int acc_num;
	float balance;
} acc_list[100] ;

/* Initializing variables to be used throughout multiple functions */
int a;
int num_accounts; 


/* Declaring functions */
int add_account();
int view_accounts();
int deposit();
int withdraw();
int find_acc_num(int account_num);
int remove_account();
int bal_inq();


int main()
{
	
	int input;

	/* Prompting user for input until user enters 0 */
	do
        {
	  /* Presenting options and promting for user input */
          printf("\n0. Exit \n");
          printf("1. Deposit \n");
          printf("2. Withdrawal \n");
          printf("3. Add account\n");
          printf("4. Remove account \n");
          printf("5. Balance inquiry \n");
          printf("6. View accounts\n");
          printf("Enter 0,1,2,3,4,5, or 6: \n ");

          scanf("%d", &input);
          
	  /* Depending on what the user inputted, the corresponding case is used and the appropriate function is called	*/
          switch(input)
          {
            case 0:
		printf("\nEXIT\n");
		return 0;
		break;
	    case 1:
		printf("Deposit Selected\n");
		deposit();
		break;
	    case 2:
		printf("Withdraw Selected\n");
		withdraw();
		break;
            case 3:
		printf("Addition of Account Selected\n");
		add_account();
		num_accounts++;
		break;
	    case 4:
		printf("Account Removal Selected\n");
		remove_account();
	    	break;
	    case 5:
		printf("Balance Inquiry Selected\n");		
		bal_inq();
		break;
            case 6:
		printf("Option 6 has been selected!");	  
		
		view_accounts();
		break;
            default:
                break;
           }
	 } while( input != 0 || !isalpha(input));

  return 0;
}


/* Adding Account Function */
int add_account()
{
	/* Open Binary file and check for error */
	FILE *acc_file;
	acc_file = fopen("accounts.dat", "ab+");
	if (acc_file == NULL) 
		{
		printf("Error opening the file!");
		return(1);
		}

	/* Prompting user for name, account, and balance to create an account */		
	printf("\nEnter first name:\n");
	scanf("%s", &acc_list[a].first);
	
	printf("Enter middle initial:\n");
	scanf("%s", &acc_list[a].middle);
	
	printf("Enter last name:\n");
	scanf("%s", &acc_list[a].last);
	
	printf("Enter 6 digit account number:\n");
	scanf("%d", &acc_list[a].acc_num);
	
	/* Checking if account number inputted is 6 digits */
	if (acc_list[a].acc_num > 999999 || acc_list[a].acc_num < 100000)
	{
		printf("ACCOUNT NUMBER MUST BE 6 DIGITS");
		return 0;
	}
	
	/* Check if account number is already being used
	 if yes, then returns 0 and leaves function */
	int find;
	find = find_acc_num(acc_list[a].acc_num);
        if (find != 0)
        {
                printf("ACCOUNT NUMBER IS ALREADY IN USE\n");
                return 0;
        }

	printf("Enter starting balance:\n");
	scanf("%f", &acc_list[a].balance);

 	
	/* Printing out info of the new account create */
	printf("\n-----------  ACCOUNT  -------------\n");
        printf("First Name: %s\n", acc_list[a].first);
	printf("Middle Initial: %s\n", acc_list[a].middle);
        printf("Last: %s\n", acc_list[a].last);
	printf("Account Number: %d\n", acc_list[a].acc_num);
        printf("Balance: $%.2f\n", acc_list[a].balance);
        printf("\n-----------------------------------\n");

	/* Writting the new account to the binary file */
	fwrite(&acc_list[a], sizeof(struct account), 1, acc_file);	


	a++;
	fclose(acc_file);
	return 0;

}



/* Viewing all the functions */
int view_accounts()
{

	int i;

	/* Opening account.dat file to be read */
	FILE *acc_file;
	acc_file = fopen("accounts.dat", "rb");
        if (acc_file == NULL)
	        {
                printf("Error opening the file!");
                return 1;
       		 }

	/* Setting num_account to figure out how many struct are in the file
         Number of accounts = to size of accounts.dat file divided by the size of one account */

	int file_length;
	fseek(acc_file,0,SEEK_END);
	file_length = ftell(acc_file);
	fseek(acc_file,0,SEEK_SET);
	num_accounts = file_length / sizeof(struct account);
	rewind(acc_file);


	/* Creating an array, client_list, of accounts to go through */
	struct account client_list[num_accounts];

	printf("\n\n========== VIEW ACCOUNTS: ==========\n");

	/* iterating through all the accounts in file  and printing each member of the each account struct */
	for (i = 0; i < num_accounts; i++)
	{
		fread(&client_list[i], sizeof(struct account), 1, acc_file); 
		printf("\n-------------------------------\n");
	
		printf("\nAccount Number: %d\n", client_list[i].acc_num);
		printf("Name: %s %s %s\n",  client_list[i].first, client_list[i].middle, \
                	client_list[i].last);	
		printf("Balance: $%.2f\n", client_list[i].balance);
		printf("\n-------------------------------\n");
	}              	

	fclose(acc_file); 
	return 0;
}


/* Function to remove an account */
int remove_account()
{
	int number;
        int find;
        int i;
	
	/* Open binary file, accounts.dat, holding all the account info to read from */
	FILE *acc_file;
	acc_file = fopen("accounts.dat", "rb");
	
	/* Opening a temporary file to hold all the accounts from accounts.dat that are not being removed */
	FILE *temp_file;
	temp_file = fopen("temp.dat", "wb");

	/* Setting num_account to figure out how many struct are in the file
	   Number of accounts = to size of accounts.dat file divided by the size of one account */	
	int file_length;
        fseek(acc_file,0,SEEK_END);
        file_length = ftell(acc_file);
        fseek(acc_file,0,SEEK_SET);
        num_accounts = file_length / sizeof(struct account);

	/* Prompt user for account number to be removed */
        printf("\nEnter account number to remove:\n");
        scanf("%d", &number);

	/* Check if that account number exists */
        find = find_acc_num(number);
        if (find == 0)
        {
                printf("Account Number Does Not Exist\n");
                return 0;
        }

        else
	{
		/* Going through all the accounts in accounts.dat to find account to be removed */
                struct account client_list[num_accounts];
                for (i = 0; i < num_accounts; i++)
		{
                       	fread(&client_list[i], sizeof(struct account), 1, acc_file);

			/* Checking if account to be deleted is found */
			/* If found, a deletion statement is printed */
                       	if (number == client_list[i].acc_num)
			{
				printf("\nAccount %d is being deleted\n", client_list[i].acc_num);                                
			}

			/* All other accounts in file are written to temp_file */
			else
			{
				fwrite(&client_list[i], sizeof(struct account), 1, temp_file);					
			}     
	 
		}
        	
	}
	/* Files are closed */
	fclose(acc_file);
	fclose(temp_file);
	
	/* accounts.dat is deleted and is to be replaced by temp.dat */
	remove("accounts.dat");
		
	/* temp.dat file is renamed as the accounts.dat file since it now contains all the accounts
	   except for the account that was to be removed */
	rename("temp.dat", "accounts.dat");
	printf("\nACCOUNT REMOVAL SUCCESSFUL\n");
	return 0;
}


/* Function used to find if an inputted account number exists in the bank binary file, accounts.dat
   Returns 1 if the account number exists, otherwise returns 0 */
int find_acc_num(int account_num)
{

	/* Initialize and open file */
	int i;
	FILE *acc_file;
        acc_file = fopen("accounts.dat", "rb");
        rewind(acc_file);

	/* Go through all the structs in file to find if the account number matched one in the file */
        while (!feof (acc_file))
        {
                struct account client_list[num_accounts];
                for (i = 0; i < num_accounts; i++)
		{
                        fread(&client_list[i], sizeof(struct account), 1, acc_file);
			if (account_num == client_list[i].acc_num)
			{
				fclose(acc_file);
				return(1);
			}
		}
	}

	fclose(acc_file);
	return (0);
}


/* Depositing into account function */
int deposit()
{
	float amount; 
	int number; 
	int find;

	/* Prompt user for account number to deposit into */
	printf("\nEnter account number to deposit to:\n");
	scanf("%d", &number);

	/* Check if account number exists */
	find = find_acc_num(number);
	if (find == 0)
		{
		printf("Account Number Does Not Exist\n");
		return (0);
		}
	else
	{
		/* Prompt user for amount to be deposited */
		printf("\nEnter amount to be deposited: ");
		scanf("%f", &amount);
		
		/* Open file and start from the beginning */
		int i;
		FILE *acc_file;	
        	acc_file = fopen("accounts.dat", "rb+");
        	rewind(acc_file);

		/* Going through the whole file to find and add the amount user wants to deposit from their balance */		
        	while (!feof (acc_file))
               	{
                	/* Going through all the structs in the file to find one that matches inputted account number */
			struct account client_list[num_accounts];
                	for (i = 0; i < num_accounts; i++)
			{
      	                 	fread(&client_list[i], sizeof(struct account), 1, acc_file);
                        	if (number == client_list[i].acc_num)
				{
            				/* Adding the inputted amount to the coordinating account balance */
					client_list[i].balance += amount;	
											
					/* Pointing to correct position in file and rewriting account with new balance */
					fseek(acc_file, ftell(acc_file) - sizeof(struct account), SEEK_SET);
					fwrite(&client_list[i], sizeof(struct account), 1, acc_file);					

					/* Printing new balance statement */
					printf("\n\n---------- Deposit Complete ----------\n");
					printf("Account Number: %d\n", client_list[i].acc_num);
					printf("Account Holder: %s, %s %s\n", client_list[i].last, client_list[i].first, client_list[i].middle);
					printf("New Balance: $%.2f\n", client_list[i].balance);
					printf("---------------------------------------\n\n");
					fclose(acc_file);
					return 0;
				}
        		}
                	
		}
		fclose(acc_file);
	}		
	return 0;
}





/* Withdrawing from Account Function */
int withdraw()
{
        float amount;
        int number;
        int find;

	/* Prompt user for Account num to withdraw from */
        printf("\nEnter account number to withdraw from:\n");
        scanf("%d", &number);

	/* Check if Account num exists in the bank by calling find_acc_num function */	
        find = find_acc_num(number);
        if (find == 0)
                {
                printf("Account Number Does Not Exist\n");
                return (0);
                }
        else
	{
		/* Account Exists, now prompt user for amount to be withdrawn */
                printf("\nEnter amount to be withdrawn: ");
                scanf("%f", &amount);
	
		/* Initilize and open file to be read and written to */
                int i;
                FILE *acc_file;
                acc_file = fopen("accounts.dat", "rb+");

                rewind(acc_file);
		

		/* Going through the whole file to find and subtract the amount user wants to withdraw from their balance */
                while (!feof (acc_file))
		{
                       	struct account client_list[num_accounts];
                        for (i = 0; i < num_accounts; i++)
                        {
				/* Reading through each struct in file */
                                fread(&client_list[i], sizeof(struct account), 1, acc_file);
                                /* Finding the struct that fits the user's account number */
				if (number == client_list[i].acc_num)
                                {
					/* Checking if the amount to be withdrawn isn't more than the balance */
					if (amount > client_list[i].balance)
					{
						/* If balance is insufficient, then print statement and leave withdraw function */
						printf("\nBALANCE IS NOT SUFFICIENT TO WITHDRAW $%.2f\n",amount);
						fclose(acc_file);
						return 0;
					}
					
					/* Subtract balance with the withdraw amount */
                                        client_list[i].balance -= amount;

					/* Set the position in the file in which the new balance needs to be written */
                                        fseek(acc_file, ftell(acc_file) - sizeof(struct account), SEEK_SET);
                                        fwrite(&client_list[i], sizeof(struct account), 1, acc_file);
        
					/* Print new balance inquiry */
                                        printf("\n\n---------- Withdraw Complete ----------\n");
                                        printf("Account Number: %d\n", client_list[i].acc_num);
                                        printf("Account Holder: %s, %s %s\n", client_list[i].last, client_list[i].first, client_list[i].middle);
 	                                printf("New Balance: $%.2f\n", client_list[i].balance);
                                        printf("---------------------------------------\n\n");
                                        fclose(acc_file);
                                        return 0;
                                }
                 	}
                
                }
                fclose(acc_file);
	}
	return 0;
}


/* Checking Balance Inquiry Function */
int bal_inq()
{

	int number;
        int find;

	/* Prompt user for account number */
        printf("\nEnter account number:\n");
        scanf("%d", &number);

	/* Check if account number exists in bank */
        find = find_acc_num(number);
 
	if (find == 0)
        {
                printf("Account Number Does Not Exist\n");
  	        return 0;
        }
        else
	{	

		/* Initialize and open bin file to read */
                int i;
                FILE *acc_file;
                acc_file = fopen("accounts.dat", "rb");
                rewind(acc_file);

           	/* Go through all structs in file to find the one that matches inputted account number */
                struct account client_list[num_accounts];
                for (i = 0; i < num_accounts; i++)
                {
                	fread(&client_list[i], sizeof(struct account), 1, acc_file);
                	if (number == client_list[i].acc_num)
			{
				/* Printing balance statement */
				printf("\n\n---------- BALANCE INQUIRY ----------\n");
                                printf("Account Number: %d\n", client_list[i].acc_num);
                                printf("Account Holder: %s, %s %s\n", client_list[i].last, client_list[i].first, client_list[i].middle);
                                printf("Balance: $%.2f\n", client_list[i].balance);
                                printf("-----------------------------------------\n\n");
				
			}	
		}	
		fclose(acc_file);
	}
return 0;
}
