


/********************************************************/
/********************************************************/

/*

 28 August 2022
 This works if ...
 In Word, Save As, .txt, Mac OS, CR only, 
 THE BIG ONE IS: Allow Character Substitution

 Take NET Noteless Bible...docx file
 Copy the book you want to a Word file first

*/
/********************************************************/

/******************* includes ***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



/******************* defines ****************************/
#define  MIN_PARAMS 3
#define  MAX_PARAMS 3
#define  VERSION "indexf Version 1.0 - 28 August 2022"
#define  B 500000



/**************** function declarations *****************/
void print_usage(void);



/********************************************************/
/*
   main

*/

char in_buffer[B], out_buffer[B];


int main (int argc, char *argv[])
{
   size_t ip = 0, op = 0;
   FILE *input_file, *output_file;
   size_t bytes_read = 0;

   printf("\n\n%s\n", VERSION);

   if(argc < MIN_PARAMS  ||  argc > MAX_PARAMS){
      print_usage();
      exit(0);
   }  /* ends if argc */

   if(strcmp(argv[1], argv[2]) == 0){
      printf(
       "\nERROR: Input and output file names must be different");
      print_usage();
      exit(0);
   } /* ends if strcmp */

   if((input_file = fopen(argv[1], "r")) == NULL){
      printf("\nERROR: Cannot open file %s", argv[1]);
      exit(1);
   }  /* ends if input_file */

   if((output_file = fopen(argv[2], "w")) == NULL){
      printf("\nERROR: Cannot create file %s", argv[2]);
      fclose(input_file);
      exit(1);
   }  /* ends if output_file */


   bytes_read = B;
   while(bytes_read == B){
      ip = 0;
      op = 0;
      bytes_read = fread(in_buffer, sizeof(char), B, input_file);
      printf("\nRead %ld (%d)", bytes_read, B);
      while(ip < bytes_read){ /* stroll through the bytes that were read */

/************
if(in_buffer[ip] < 32 || in_buffer[ip] > 126){
printf("%d",in_buffer[ip]);}
else{
printf("-%c-",in_buffer[ip]);
}
************/

         if(in_buffer[ip] >= 32 && in_buffer[ip] <= 126){ /* PRINTABLE RANGE */
            /* copy char and increment pointers */
            /* isdigit and isspace */
            if(isdigit(in_buffer[ip])){ /* HIT A DIGIT */
               /****** 
                  insert a new line
                  copy until you hit a space
                  put a "]"
                  put the space 
               ***********/
               out_buffer[op] = '\n'; op++;
               out_buffer[op] = '\n'; op++;
               while(isspace(in_buffer[ip]) == 0){ /* while NOT A SPACE */
                  out_buffer[op] = in_buffer[ip];
                  ip++;
                  op++; 
               } /* ends while NOT A SPACE */ 
               out_buffer[op] = ']'; op++;
            } /* ends HIT A DIGIT */
            else{ /* PRINTABLE RANGE and NOT A DIGIT */
               out_buffer[op] = in_buffer[ip];
               op++;
               ip++;
            } /* ends PRINTABLE RANGE and NOT A DIGIT */
         } /* ends if char is within PRINTABLE RANGE */
         else{ /* not in PRINTABLE RANGE, so increment input pointer */
               /**********
                 4:30 PM Sunday 
                 I would like to strip off the titles that appear before
                 sections of verses. If a space appears right after new line,
                 that is not a title. If a non-space appears right after new line,
                 that is a title, and I want to strip it (do nothing until you hit
                 a new line and a space)
                 THIS SEEMS TO WORK
               ***********/
            ip++;
            if(isspace(in_buffer[ip]) == 0){ /* Hit a Title so stroll thru it */
               while(in_buffer[ip] >= 32 && in_buffer[ip] <= 126){ /* PRINTABLE RANGE */
                 ip++;
               } /* ends while strolling thru the title */
               ip++;
            } /* finished if Hit a Title */
         } /* ends not in PRINTABLE RANGE */
      }  /* ends while strolling through the bytes that have been read */
      fwrite(out_buffer, sizeof(char), op, output_file);
   }  /* ends while */

   fclose(input_file);
   fclose(output_file);

   printf("\n\n%s\n\n", VERSION);

}  /* ends main */





/********************************************************/
/*
   print_usage()
*/

void print_usage()
{
   printf("\nusage: indexf in-file out-file\n\n");
}  /* ends print_usage */


