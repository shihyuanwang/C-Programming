// Assignment 3 - Shih-Yuan Wang

// C Libraries

#include <stdio.h>
#include <math.h>

// Constant definitions

#define TRANSLENGTH 11             // length of the transaction type
const float BEGBALANCE = 1000.00;  // beginning balance of operating account
    
// Variable declarations

FILE *reportfile;                  // report file (for output)
FILE *inputfile;                   // disk file (for input)
char transaction[TRANSLENGTH];     // input transaction type

float amount;                      // input amount of money that belongs to a particular transaction
float netbalance;                  // accumulated - net balance of operating account
int count;                         // accumulated - count of all transactions

// Function Prototypes

void header (void);
void process (void);
void summary (void);

//*************************************************
//*************************************************
// M A I N   F U N C T I O N
//*************************************************
//*************************************************

int main (void) {

   inputfile = fopen("c:\\class\\transactions.txt","r");   // Open input file
   reportfile = fopen("c:\\class\\swang_tr.txt","w");      // Open output file
   
// Initialize accumulating variables

   netbalance = BEGBALANCE;  // beginning balance of operating account
   count = 0;

// Produce Report

   header();
   process();
   summary();

   fclose(inputfile);
   fclose(reportfile);
   system("pause");
   return 0;

}

// *************************************************************
// Header - prints a header to the report file
// *************************************************************

void header (void){

   fprintf(reportfile, "Turtle Bay Traders\n");
   fprintf(reportfile, "4800 Palawan Way\n");
   fprintf(reportfile, "Mandalay Beach, CA 99499\n");
   fprintf(reportfile, "\n");
   fprintf(reportfile, "Operating Account Starting Balance:%9.2f\n", BEGBALANCE);
   fprintf(reportfile, "\n");
   fprintf(reportfile, "Transaction       Amount                 Net\n");
   fprintf(reportfile, "-----------       ------                 ---\n");

}

// *************************************************************
// Process - produces the detail lines of the report and print to the report file
// *************************************************************

void process (void) {

   while(!feof(inputfile)){

      fgets(transaction, TRANSLENGTH, inputfile);
      fscanf(inputfile,"%f\n", &amount);

      netbalance = netbalance + amount;    // accumulate net balance 
      fprintf(reportfile,"%-10s%14.2f%20.2f\n", transaction, fabs(amount), netbalance);   // detail

      count++;   // update accumulators
      
  }

}

// *************************************************************
// Summary - prints the report summary to the report file (including accumulators)
// *************************************************************

void summary (void) {

    fprintf(reportfile,"\n");
	fprintf(reportfile,"Operating Account Ending Balance:%11.2f\n", netbalance);
	fprintf(reportfile,"There were %d transactions processed.\n", count);

}

