// Assignment 4 - Shih-Yuan Wang

// C Libraries

#include <stdio.h>
#include <strings.h>

// Constant definitions

const float OVERRATE = 1.5;  // the overtime rate of pay is how many times more than the regular rate of pay
const float THRESHOLD = 40;  // threshold for overtime hours

// Variable declarations

FILE *reportfile;       // report file (for output)
char project[21];       // the name of project
char firstname[15];     // the first name of staff
char lastname[15];      // the last name of staff
char fullname[30];      // the full name of staff (interactive)
char fullname2[31];     // the full name of staff (for report file)
float regwage;          // the hourly regular wage of staff 
float overwage;         // the hourly overtime wage of staff 
float tothr;            // total number of hours worked
float reghr;            // the number of regular hours worked
float overhr;           // the number of overtime hours worked
float grosswage;        // gross amount of wage
float sumwage;          // total wages of the period
float percenover;       // percentage of total hours that are overtime

float sumreghr;         // accumulated - total regular hours worked
float sumoverhr;        // accumulated - total overtime hours worked
float sumregwage;       // accumulated - total regular wages
float sumoverwage;      // accumulated - total overtime wages
int count;              // accumulated - count of the number of members
char again;             // answer to question about repeating the process

// Function Prototypes

int clear(void);
void header (void);
void process (void);
void summary (void);

//*************************************************
//*************************************************
// M A I N   F U N C T I O N
//*************************************************
//*************************************************

int main (void) {

// Get project name from user

   printf("NetworkHaus Information Technology, LLC\n");
   printf("Staff Earnings Report Generator\n");
   printf("\n");
   printf("Please enter the project name: ");
   gets(project);
   
   reportfile = fopen("c:\\class\\swang-er.txt","w");      // Open output file

// Initialize accumulating variables

   sumreghr = 0;
   sumoverhr = 0;
   sumregwage = 0;
   sumoverwage = 0;
   count = 0;

// Get information from user and produce report

   header();
   process();
   summary();

   fclose(reportfile);
   return 0;

}

// *************************************************************
// Clear - a loop with no body
// *************************************************************

int clear() {
    while ((getchar())^'\n');
}

// *************************************************************
// Header - prints a header to the report file
// *************************************************************

void header (void){

   fprintf(reportfile, "NetworkHaus Information Technology, LLC\n");
   fprintf(reportfile, "Weekly Staff Earnings Report\n");
   fprintf(reportfile, "\n");
   fprintf(reportfile, "Project: %s\n", project);
   fprintf(reportfile, "\n");
   fprintf(reportfile, "Staff Member                     Reg Hrs        Overtime Hrs       Gross\n");
   fprintf(reportfile, "------------------------------------------------------------------------\n");

}

// *************************************************************
// Process - gets staff information from user, produces the detail lines of the report, and prints to the report file
// *************************************************************

void process (void) {
    
  /* Get information from user */
   do {

      count++; // Increment the counting variable
      printf("\n");
      printf("Enter staff member #%d's first name: ", count);
      gets(firstname);
      printf("Enter staff member #%d's last name: ", count);
      gets(lastname);

      strcpy(fullname, firstname);  // This assigns firstname to fullname
      strcat(fullname, " ");        // This adds " " to the end of fullname
      strcat(fullname, lastname);   // This adds lastname to the end of fullname
      printf("Enter the hourly wage of %s: ", fullname);
      scanf("%f", &regwage);

      printf("Enter total number of hours: ");
      scanf("%f", &tothr);

     /* Ask for another time */

      printf("\n");
      printf("Thank you. Process another employee? ");
      scanf("%s", &again);
      clear();


     /* Caculate output information*/

	  if (tothr > THRESHOLD ){
         reghr = THRESHOLD;
         overhr = tothr - THRESHOLD;
      }
      else {
         reghr = tothr;
         overhr = 0;
      }
      
      overwage = regwage * OVERRATE;
      grosswage = (reghr * regwage) + (overhr * overwage);

      // accumulate hours and wages
      sumreghr = sumreghr + reghr;
      sumoverhr = sumoverhr + overhr;
      sumregwage = sumregwage + (reghr * regwage);
      sumoverwage = sumoverwage + (overhr * overwage);
      
     /* Prints to the report file */

      strcpy(fullname2, lastname);  // This assigns lastname to fullname2
      strcat(fullname2, ", ");       // This adds ", " to the end of fullname2
      strcat(fullname2, firstname);   // This adds firstname to the end of fullname2

      fprintf(reportfile,"%-31s%4.1f ($%5.2f)   %4.1f ($%5.2f)    $%7.2f\n",
              fullname2, reghr, regwage, overhr, overwage, grosswage);             // report body detail

   } while (again=='Y' || again=='y');

   printf("\nEnd of processing.\n");

}

// *************************************************************
// Summary - Caculate and prints the report summary to the report file (including accumulators)
// *************************************************************

void summary (void) {

 /* Caculate percentage of total overtime hours and total wages*/
    percenover = (sumoverhr) / (sumreghr + sumoverhr) *100;
    sumwage = sumregwage + sumoverwage;

 /* Prints the report summary*/
    fprintf(reportfile,"------------------------------------------------------------------------\n");
    fprintf(reportfile,"\n");
	fprintf(reportfile,"Total Regular Hours Worked:%6.1f\n", sumreghr);
	fprintf(reportfile,"Total Overtime Hours Worked:%5.1f\n", sumoverhr);
	fprintf(reportfile,"Percentage of Total Hours That Are Overtime:%5.1f%%\n", percenover);
    fprintf(reportfile,"\n");
    fprintf(reportfile,"Total Regular Wages: $%7.2f\n", sumregwage);
    fprintf(reportfile,"Total Overtime Wages: $%7.2f\n", sumoverwage);
    fprintf(reportfile,"\n");
    fprintf(reportfile,"Total Wages This Period: $%7.2f\n", sumwage);
    
}

