//-----------------------------------------------------------------------------
// DictionaryTest.c
// Test client for the Dictionary ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){
   Dictionary A = newDictionary();
   char* k;
   char* v;
   char* word1[] = {"Rachel","Ross","Monica","Chandler","Joey","Phoebe","Janice"};
   char* word2[] = {"Green","Geller","Geller","Bing","Tribbiani","Buffay","Hosenstein"};
   int i;

   for(i=0; i<7; i++){
      insert(A, word1[i], word2[i]);
   }

   printDictionary(stdout, A);

   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }

   // insert(A, "five", "glow"); // error: duplicate keys

   delete(A, "Rachel");
   delete(A, "Monica");
   delete(A, "Janice");

   printDictionary(stdout, A);

   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }

   // delete(A, "one");  // error: key not found

   printf("%s\n", (isEmpty(A)?"true":"false"));
   printf("%d\n", size(A));
   makeEmpty(A);
   printf("%s\n", (isEmpty(A)?"true":"false"));

   freeDictionary(&A);

   return(EXIT_SUCCESS);
}
