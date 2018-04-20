/*
Shaon Islam
CS 2750 PA 4
Simple File Statistics

*/

#include <stdio.h>


int main(int argc, char **argv[])
{
	
	char character;

	/* Check to see if anything was written on command line */
	if (argc > 1)
	{

		/* Initialize variables */
		int i;
		int total_words = 0;	
		int total_char = 0;
		int total_lines = 0;
	
		/* Iterate through each entry on command line */	
		for (i = 1; i < argc; i++)
		{
			int char_counter = 0;
	        	int word_counter = 0;
        		int line_counter = 0;
			
			/* Attempt to open file from command line */
			FILE *tfile;
			tfile = fopen(argv[i], "r"); 
		
			/* Check if file successfully opened */
			if (!tfile)
			{
				printf("\nERROR OPENING FILE\n");
				return 0;
			}
	
			/* Iterate through each character in file and add up counters */
			while ((character = getc(tfile)) != EOF)
			{
				if (character != ' ' && character != '\n')
				{
					char_counter++;
				}
				if (character == ' ' || character == '\n')
				{
					word_counter++;
				}
				if (character == '\n')
				{
					line_counter++;
				}

			}
			fclose(tfile);	

			/* Print out stats for each file */
			printf("\n----- Stats for FILE %d out of %d: -----\n", i, argc-1);
			printf("\nNumber of Lines: %d", line_counter);
			printf("\nNumber of Words: %d", word_counter);
			printf("\nNumber of Characters: %d\n", char_counter);
		
			/* Add stats to total amounts */
			total_words += word_counter;
			total_char += char_counter;
			total_lines += line_counter;
		}
	
	/* Printing Overall file stat summary if there are multiple files */

	if (argc > 2)
	{
	printf("\nTotal Lines: %d\n", total_lines);
	printf("Total Characters: %d\n", total_char);
	printf("Total Words: %d\n", total_words);	
	}
	}



	/* When nothing is written on command line */
	else
	{
	
	/* Initializing */
	char input[100];
    	int i = 0;
	int word_counter = 0;
	int char_counter = 0;
	int line_counter = 0;

	/* Get string input from user */
    	gets(input);

    	/* Iterate through whole string and add to the counters */
    	while(input[i] != '\0')
    	{
      
        	if (input[i] == ' ')
        	{
            		word_counter++;
        	}

		if (input[i] == '\n')
                {
                        line_counter++;
                }

		if (character != ' ' && character != '\n')
		{
			char_counter++;
		}	

        	i++;
    	}
	
	/* Print stat statements */
	printf("\nNumber of words: %d\n", word_counter + 1);
	printf("Number of characters: %d\n", char_counter);	
	printf("Number of lines: %d\n", line_counter);
	
	}
return 0;
}

