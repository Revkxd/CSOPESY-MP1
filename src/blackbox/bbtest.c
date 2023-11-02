/*
   Filename   : bbtest.c
   Description: blackbox test program (for checking the difference between two files)
   Author     : Florante R. Salvador

   version 2 update: retval = fscanf(fp1, "%s", expected);                     
     	             if (retval != 1) // no more value 
     	                 break;
     	                 
   Compile as : gcc -Wall bbtest.c -o bbtest.exe

   Usage      : On the DOS prompt type
                  bbtest <correct file> <student output file> 

                Example:

                  bbtest expected_output.txt actual_output.txt
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN  80
#define PRINT

int 
main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int temp;
    int ctr = 0, diff_ctr = 0;
    int retval;
    char expected[MAXLEN], actual[MAXLEN];

        
    if (argc != 3) {
	    fprintf(stderr, "Usage: bbtest <sample file> <your file>\n");
        return 1;
    }
    
    /* open the text files */
	fp1 = fopen(argv[1], "r");  /* correct file (expected) */
    fp2 = fopen(argv[2], "r");  /* student's file (actual) */
 
    if (fp1 == NULL) {
    	printf("\n");
    	fprintf(stderr, "bbtest.exe: Fatal error, %s file NOT FOUND. Terminating...\n\n", argv[1]);
    	exit(1);    	
	}
	
	if (fp2 == NULL) {
		printf("\n");
    	fprintf(stderr, "bbtest.exe: Fatalerror, %s file NOT FOUND. Terminating...\n\n", argv[2]);
    	exit(1);    	
	}
	
    
    /* compare pairs of tokens */

#ifdef PRINT
	printf("+----------+------------------------+-------------------------+\n");   
    printf("|          |  %20s  |  %20s   |\n", "EXPECTED", "ACTUAL");
    printf("+----------+------------------------+-------------------------+\n");
#endif
    
    while (!feof(fp1)) {
     	retval = fscanf(fp1, "%s", expected);
     	fscanf(fp2, "%s", actual);     	
     	
     	if (retval != 1) // no more value 
     	   break;
		 
		ctr++;        
	
		temp = (strcmp(expected, actual) != 0);            
        if (temp) {
		   diff_ctr++;		   
#ifdef PRINT		   
		   printf("| [%5d]  |  %20s  |  %20s   |  RED_FLAG!\n", ctr, expected, actual);     	
#endif
     	}    
		else {		
#ifdef PRINT		   
		   printf("| [%5d]  |  %20s  |  %20s   |\n", ctr, expected, actual);		   
#endif
     	}

	}

#ifdef PRINT	
	printf("+----------+------------------------+-------------------------+\n");
    printf("\nBLACK BOX TEST RESULT(S):\n");
#endif
    printf("           Differences = %d.\n", diff_ctr);
	
	/* 
	    NOTE: if diff_ctr is 0, then it means that there is no difference.  
	          If diff_ctr > 0 then there is a difference between expected and actual results.
	*/ 
    
	 
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}


