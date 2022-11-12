


/********************************************************/
/********************************************************/

/*

11 November 2022 - attempting to work with a list of words 
28 August 2022

*/
/********************************************************/

/******************* includes ***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/******************* defines ****************************/
#define  MIN_PARAMS 4
#define  MAX_PARAMS 4
#define  VERSION "indexg Version 2.0 - 11 November 2022"
#define  B 1000

/**************** function declarations *****************/
void print_usage(void);

/********************************************************/
/*
   main

*/

char in_line[B], out_line[B];

int main (int argc, char *argv[])
{
   size_t ip = 0, op = 0;
   int first_time = 1;
   FILE *word_file, *input_file, *output_file;
   size_t bytes_read = 0;
   char chapter [20];
   char word[80];
   char response[80];

   printf("\n\n%s\n", VERSION);

   if(argc < MIN_PARAMS  ||  argc > MAX_PARAMS){
      print_usage();
      exit(0);
   }  /* ends if argc */

   if((word_file = fopen(argv[1], "r")) == NULL){
      printf("\nERROR: Cannot open file %s", argv[1]);
      exit(1);
   }  /* ends if word_file */

   if((input_file = fopen(argv[2], "r")) == NULL){
      printf("\nERROR: Cannot open file %s", argv[2]);
      exit(1);
   }  /* ends if input_file */

   if((output_file = fopen(argv[3], "w")) == NULL){
      printf("\nERROR: Cannot create file %s", argv[3]);
      fclose(input_file);
      exit(1);
   }  /* ends if output_file */

/************************************************************/
/************ now we start the program **********************/


   memset(word, 0, strlen(word)); /* fill word with nothing */

while (fgets(word, sizeof(in_line), word_file)) { /* reading word list file */
if(first_time == 0){
   input_file = fopen(argv[2], "r");
} /* ends if first_time == 0 */

/* Had a problem in that the word list file had carriage return at the end of the string */
int wsl = strlen(word);
if(word[wsl-1] == '\n')
   word[wsl-1] = 0;

strcpy(out_line, word);
strcat(out_line, ", ");

while (fgets(in_line, sizeof(in_line), input_file)) { /* Read the lines of the Bible file */
   memset(chapter, 0, strlen(chapter)); /* fill chapter with nothing */
   ip=0; op=0;

  
   if(strstr(in_line, word) != 0){
     while(in_line[ip] != ']'){
        chapter[ip] = in_line[ip];
        ip++;
     } 
     strcat(out_line, chapter);
     strcat(out_line, ", ");
   } /* ends if word is in the in_line */ 
} /* ends while reading the lines of the Bible text file */

if(first_time == 1){
   first_time = 0;
   fclose(input_file);
} /* ends if first time */


strcat(out_line, "\n");
fputs(out_line, output_file);

   memset(word, 0, strlen(word)); /* fill word with nothing */
} /* ends while reading the lines of the word list file */

   fclose(input_file);
   fclose(output_file);
   fclose(word_file);

   printf("\n\n%s\n\n", VERSION);

}  /* ends main */





/********************************************************/
/*
   print_usage()
*/

void print_usage()
{
   printf("\nusage: index-word-list word-list-file in-file out-file\n\n");
   printf("\n" );
}  /* ends print_usage */


