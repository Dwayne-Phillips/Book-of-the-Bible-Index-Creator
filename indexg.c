


/* 31 Aug '22 */

/********************************************************/
/********************************************************/

/*

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
#define  VERSION "indexg Version 1.0 - 28 August 2022"
#define  B 500



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
   FILE *input_file, *output_file;
   size_t bytes_read = 0;
   char chapter [20];
   char word[B];

   printf("\n\n%s\n", VERSION);

   if(argc < MIN_PARAMS  ||  argc > MAX_PARAMS){
      print_usage();
      exit(0);
   }  /* ends if argc */

   if(strcmp(argv[2], argv[3]) == 0){
      printf(
       "\nERROR: Input and output file names must be different");
      print_usage();
      exit(0);
   } /* ends if strcmp */

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

strcpy(word, argv[1]);
strcpy(out_line, word);
strcat(out_line, ", ");


while (fgets(in_line, sizeof(in_line), input_file)) {
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
} /* ends while reading the lines of the file */

strcat(out_line, "\n");
fputs(out_line, output_file);

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
   printf("\nusage: indexg word in-file out-file\n\n");
   printf("\n" );
}  /* ends print_usage */
