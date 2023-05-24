/**
 * Student Name: Heeyoon Son
 * StudentId: hzs0093
 * Project Name: Loan Calculator
 * File Name: project1_son_hzs0093.cpp
 * Compiler Version: default g++
 */

///////////////////////////////////
//            Sources            //
///////////////////////////////////

//I  used c++.com to look at how to allign values using the setw method. http://www.cplusplus.com/reference/iomanip/setw/ . (General Syntax learning)

//I used c++.com to look how to handle errors when a user puts in the wrong data type. Ex: putting in a string input when the loan amount asks for a real number. http://www.cplusplus.com/forum/beginner/26821/ I learned to use Line(17-18) cin.ignore() and cin.clear() through this forum.

// I used stack overflow forum to find out how to make it so that if the user were to put in multiple chars for the input how I could make it so that only one line of "The loan amount must be a positive number" would be outputted for the user instead of each otput per char character pertically how to use "numeric_limits<streamsize>::max()" . site : https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n 

//Spoke with Trejon Goldsborough about properly using setw() method.

#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
   float loanAmt, yearlyRate, monthlyPayment, monthlyRate;
   float totalInterest = 0;
   bool validInput = false;

   //currency format
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   //prompts the user to input a loan amount until it is valid (i.e positive value)
   while(!validInput) {
      cout << "Loan Amount: ";
      cin >> loanAmt;
      
      if(cin.fail()) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "(Invalid loan) Loan Amount must be a positive number with no char values!\n";
      }else {
         validInput = loanAmt > 0;
         if(!validInput) cout << "!(Invalid loan) Loan Amount must be a positive number!\n";
      }
   }

   //valid input set to false so the other while loops can use this variables to check for valid inputs.
   validInput = false;

   //prompts the user to input a yearly rate until it is valid(i.e a postive value)
   while(!validInput) {
      //APR (Annual Percentage Rate)
      cout << "Inerest Rate (% per year): ";
      cin >> yearlyRate;
      
      if(cin.fail()) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "!(Invalid interest rate) Interest rate must be a non-negative number with no char values!\n";
      }
      else {
         //MPR (Monthly Percentage Rate)
         monthlyRate = yearlyRate / 12;
         validInput = yearlyRate >= 0;
         if(!validInput) cout << "!(Invalid interest rate) The Interest rate must be a non-negative number!\n";
      }
   }

   validInput = false;

   //prompts the user to input a monthly payment until it is valid(i.e. big enough value for the loan to be payable with monthly interest)
   while(!validInput) {
      cout << "Monthly Payment: ";
      cin >> monthlyPayment;
      
      if(cin.fail()) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "!(Invalid Payment) Monthly payment must be a positive number with no char values!\n";
      }
      else if(monthlyPayment < 0) {
         cout << "!(Invalid Payment) Monthly payment must be a positive number with no char value!\n";
      }
      else {
         validInput = monthlyPayment > ((monthlyRate * 0.01) * loanAmt);
         if(!validInput) cout << "!(Insufficient Payment) Monthly payment is too low, select a higher monthly payment!\n";
      }
   }
  

   //the top part of the table
   cout << "**********************************************************\n";
   cout << "\tAmortization Table\n";
   cout << "**********************************************************";

   //setw used becaused of the varying amount of space betwwen each variable in the sample outputs on canvas
   cout << setw(9)<< left << "\nMonth" << setw(10)<< left << "Balance" << setw(13) << left << "Payment" << setw(8) << left << "Rate" << setw(10) << left << "Interest" << "Principal\n";

   float balance = loanAmt;
   int month = 0;
   
   ///////////////
   //month 0 row//
   ///////////////
   
   //[month]
   cout << setw(8)<< left << 0;
   
   //[balance]
   cout << "$" << setw(9)<< left << balance ;
   
   //[payment]
   cout << setw(13) << left << "N/A";
   
   //[rate]
   cout << setw(8) << left << "N/A";
   
   //[Interest]
   cout << setw(10) << left << "N/A";
   
   //[principal]
   cout << "N/A\n";

   //calculates + generates the row (after month 0) each iteration until the loan is paid off.
   while(balance > 0) {
      
      //////////////////////////////////////
      //intial calculations made every row//
      //////////////////////////////////////

      //every iteraiton == month.
      month++;
      
      //monthly rate x 0.01 to convert % --> decimal
      //had to make this a double for it to match with the sample outputs
      double monthlyInterest = ((monthlyRate * 0.01) * balance);
      
      
      //the amount left after paying off the intrest for the month
      float principal = monthlyPayment - monthlyInterest;


      ///add this month's intrest to the total to keep track of the total intrest paid
      totalInterest += monthlyInterest;

      //special case when the principal payment exceedes the amount needed to be paid off
      if(balance - principal < 0) {
         principal = balance;
         balance = 0;
         monthlyPayment = principal + monthlyInterest;
         
      }else {
         balance -= principal;
      }
      
      //////////////////////////////////////
      //output of the calculations made   //
      //////////////////////////////////////
      
      /**
       * The output formatting matches the sample outputs on the pdf exactly. 
       * That is why I used setw since in the sample outputs the space between data values differed.
       * Ex: the space between month and balance is 3 but between payment and rate is 6.
       */
     
      
      //[Month] indicates which month we are calculating 
      cout << setw(8)<< left << month;
      
      //[Balance] amount of $ left to pay off
      cout << "$" << setw(9)<< left << balance ;
      
      //[Payment] amount of $ paid this month
      cout << "$" << setw(12)<< left << monthlyPayment;

      //[Rate] the monthly intrest rate in %
      cout << setw(8) << left << monthlyRate;

      //[Interest] the amount of $ in intrest that needs to be paid this month
      cout << "$" << setw(9) << left << monthlyInterest;

      //[Principal] the amount of $ left to pay off the balance after interest us paid off.
      cout << "$" << principal << "\n";
   }

   cout << "**********************************************************\n";
   if(month == 1) {
      cout << "\nIt takes " << month << " month to pay off the loan.\n";
   }
   else{
      cout << "\nIt takes " << month << " months to pay off the loan.\n";
   }
   cout << "Total interest paid is: $" << totalInterest << '\n';
   
   return 0;
}