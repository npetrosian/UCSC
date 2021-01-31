//-----------------------------------------------------------------------------
// File name: charType.c
// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// This lab extracts alpha, digits, punctuation, and whitespace  characters
// from each line of the input file  and places them in the output file. When
// each of the lines in the input file is placed in the output file, it prints 
// what each line contains in accordance to alpha, digits, punctuation, and
// whitespace characters.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100

// function prototype 
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// function main which takes command line arguments 
int main(int argc, char* argv[]){
   FILE* in;        // handle for input file                  
   FILE* out;       // handle for output file                 
   char* line;      // string holding input line              
   char* alpha;     // string holding all alpha chars 
   char* digit;     // string holding all digits
   char* punct;     // string holding all punctuation
   char* white;     // string holding all white space
   int lineCounter = 1;
   int i;

   // check command line for correct number of arguments 
   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading 
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate strings line and alpha on the heap 
   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert( line!=NULL );
  
   // allocate memory for the various arrays
   alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   digit = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punct = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   white = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert(alpha!=NULL && digit!=NULL && punct!=NULL && white!= NULL);

   // read each line in input file, extract alpha-numeric characters 
   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      
      fprintf(out, "line %d contains:\n", lineCounter++);

    
      extract_chars(line, alpha, digit, punct, white);

      if(strlen(alpha) == 1){ 
          fprintf(out, "%d alphabetic character: %s\n",(int)strlen(alpha), alpha);
      }
      else{
          fprintf(out, "%d alphabetic characters: %s\n",(int)strlen(alpha), alpha);
      }

      if(strlen(digit) == 1){
           fprintf(out, "%d numeric character: %s\n",(int)strlen(digit), digit);
      }
      else {
           fprintf(out, "%d numeric characters: %s\n",(int)strlen(digit), digit);
      }

      if(strlen(punct) == 1){
           fprintf(out, "%d punctuation character: %s\n",(int)strlen(punct), punct);
      }
      else {
           fprintf(out, "%d punctuation characters: %s\n",(int)strlen(punct), punct);
      }

      if(strlen(digit) == 1){
           fprintf(out, "%d whitespace character:\n",(int)strlen(white));
      }
      else {
           fprintf(out, "%d whitespace characters:\n",(int)strlen(white));
      }

      // write a carriage return at the end of the line
      fprintf(out, "\n");
  
      for(i=0; i < MAX_STRING_LENGTH-1; i++){
          alpha[i] = '\0';
          digit[i] = '\0';
          punct[i] = '\0';
          white[i] = '\0';
      }
   }

   // free heap memory 
   free(line);

   // we need to free the memory we allocated for the arrays
   free(alpha);
   free(digit);
   free(punct);
   free(white);

   // close input and output files 
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}

// function definition 
void extract_chars(char* s, char* a, char* d, char* p, char* w){
   int i=0;  // index to chars in s
   int j=0;  // index to chars in a
   int k=0;  // index to digits in d
   int l=0;  // index to punctuation in p
   int m=0;  // index to white space in w
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){

      // add alphabetic characters to a[]
      if( isalpha( s[i]) ) {
            a[j++] = s[i];
      }
      
      // add digit characters to d[]
      if(isdigit(s[i])){
            d[k++] = s[i];
      }

      // add punctuation characters to p[]
      if(ispunct(s[i])){
            p[l++] = s[i];
      }

      // add white space characters to w[]
      if(isspace(s[i])){
            w[m++] = s[i];
      }
      i++;
      
   }
   a[j] = '\0';
}
