/**
 * Student Name: Heeyoon Son
 * StudentId: hzs0093
 * Project Name: Standoff Simulator
 * File Name: project2_son_hzs0093.cpp
 * Compiler Version: default g++
 */

///////////////////
//    Sources    //
///////////////////

//Referenced Dr. Li's Hint source code for the shoot method structure and testing structure.

# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include<ctime>
using namespace std;

/////////////////////
//   prototypes   ///
/////////////////////


/* Input:  A_alive indicates whether Aaron is alive */
/*         B_alive indicates whether Bob is alive */
/*         C_alive indicates whether Charlie is alive */
/* Return: true if at least two are alive */
/*         otherwise return false */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);

/* Strategy 1: shoot the most accurate shooter alive
 * Input:  B_alive indicates whether Bob alive or dead 
 *         C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed.  
 *         Change C_alive into false if Charlie is killed. 
 */
void Aaron_shoots1(bool& B_alive, bool& C_alive);

/* Call by reference
 * Input:  A_alive indicates if Aaron is alive or dead 
 *         C_alive indicates whether Charlie is alive or dead 
 * Return: Change A_alive into false if Aaron is killed.
 *         Change C_alive into false if Charlie is killed.
 */
void Bob_shoots(bool& A_alive, bool& C_alive);

/* Call by reference
 * Input:  A_alive indicates if Aaron is alive or dead 
 *         B_alive indicates whether Bob is alive or dead 
 * Return: Change A_alive into false if Aaron is killed.
 *         Change B_alive into false if Bob is killed.
 */
void Charlie_shoots(bool& A_alive, bool& B_alive);

/* Strategy 2: Do not shoot if both alive
 * Input:  B_alive indicates whether Bob alive or dead 
 *         C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed.  
 *         Change C_alive into false if Charlie is killed. 
 */
void Aaron_shoots2(bool& B_alive, bool& C_alive);


/////////////////////////////
// Test Drivers for method //
/////////////////////////////

void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

//Simple method to implement pause function in linux
void Press_any_key(void);

//Constants
const int num_of_runs = 10000;
const int to_percent = 100;
const int aaron_success = 33;
const int bob_success = 50;

/* The main method of the shooting simulation between Aaron, Bob, and Charlie
*  The summary of the win percentages of 10,000 simulations will be printed.
*/
int main(){
   cout << "*** Welcome to Tim's Duel Simulator ***\n";
   srand(time(0));
   test_at_least_two_alive();
   Press_any_key();
   test_Aaron_shoots1();
   Press_any_key();
   test_Bob_shoots();
   Press_any_key();
   test_Charlie_shoots();
   Press_any_key();
   test_Aaron_shoots2();
   Press_any_key();

   
   /////////////////////////////////
   // strategy 1 simulation       //
   /////////////////////////////////
   cout << "Ready to test strategy 1 (run 10000 times):\n";
   Press_any_key();
   
   //aaron win using strategy 1 needs to be remebered to compare to startegy 2
   int num_aaron_wins_1 = 0;
   int num_bob_wins = 0;
   int num_charlie_wins = 0;

   for (int i = 0; i < num_of_runs; i++) {
      bool aaron_alive = true;
      bool bob_alive = true;
      bool charlie_alive = true;
      while(at_least_two_alive(aaron_alive, bob_alive, charlie_alive)){
         if(aaron_alive) Aaron_shoots1(bob_alive, charlie_alive);
         if(bob_alive) Bob_shoots(aaron_alive, charlie_alive);
         if(charlie_alive) Charlie_shoots(aaron_alive, bob_alive);
      }
      if(aaron_alive) num_aaron_wins_1 ++;
      if(bob_alive) num_bob_wins ++;
      if(charlie_alive) num_charlie_wins++;
   }

   double aaron_win_per_1 = (static_cast<double>(num_aaron_wins_1)/num_of_runs) * to_percent;
   double bob_win_per = (static_cast<double>(num_bob_wins)/num_of_runs) * to_percent;
   double charlie_win_per = (static_cast<double>(num_charlie_wins)/num_of_runs) * to_percent;
   
   cout.setf(ios::fixed);
   cout.precision(2);
   cout.setf(ios::showpoint);

   cout << "Aaron won " << num_aaron_wins_1 << "/" << num_of_runs << " duels or " << aaron_win_per_1 << "%\n";
   cout << "Bob won " << num_bob_wins << "/" << num_of_runs << " duels or " << bob_win_per << "%\n";
   cout << "Charlie won " << num_charlie_wins << "/" << num_of_runs << " duels or " << charlie_win_per << "%\n\n";
   
   /////////////////////////////////
   // strategy 2 simulation       //
   /////////////////////////////////

   cout << "Ready to test strategy 2 (run 10000 times):\n";
   Press_any_key();
   
   //num of wins reset for new simulation
   //since aarons strategy 1 variables need to be remebered new variables will be created for aaron
   double num_aaron_wins_2 = 0;
   num_bob_wins = 0;
   num_charlie_wins = 0;

   for (int i = 0; i < num_of_runs; i++) {
      bool aaron_alive = true;
      bool bob_alive = true;
      bool charlie_alive = true;
      while(at_least_two_alive(aaron_alive, bob_alive, charlie_alive)){
         if(aaron_alive) Aaron_shoots2(bob_alive, charlie_alive);
         if(bob_alive) Bob_shoots(aaron_alive, charlie_alive);
         if(charlie_alive) Charlie_shoots(aaron_alive, bob_alive);
      }
      if(aaron_alive) num_aaron_wins_2++;
      if(bob_alive) num_bob_wins ++;
      if(charlie_alive) num_charlie_wins++;
   }

   double aaron_win_per_2 = (static_cast<double>(num_aaron_wins_2)/num_of_runs) * to_percent;
   bob_win_per = (static_cast<double>(num_bob_wins)/num_of_runs) * to_percent;
   charlie_win_per = (static_cast<double>(num_charlie_wins)/num_of_runs) * to_percent;

   cout << "Aaron won " << num_aaron_wins_2 << "/" << num_of_runs << " duels or " << aaron_win_per_2 << "%\n";
   cout << "Bob won " << num_bob_wins << "/" << num_of_runs << " duels or " << bob_win_per << "%\n";
   cout << "Charlie won " << num_charlie_wins << "/" << num_of_runs << " duels or " << charlie_win_per << "%\n\n";
   
   if(num_aaron_wins_2 > num_aaron_wins_1) {
      cout <<  "Strategy 2 is better than strategy 1.\n";
   }
   else {
       cout <<  "Strategy 1 is better than strategy 2.\n";
   }

   return 0;

}

/* Implementation of at_least_two_alive() */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
   return (A_alive && B_alive) || (A_alive && C_alive) || (B_alive && C_alive);
}
   
/* Implementation of the test driver for at_least_two_alive() */
void test_at_least_two_alive(void) {
   cout << "Unit Testing 1: - Function at_least_two_alive()\n";
   
   //case 1
   cout << "\tCase 1: Aaron Alive, Bob Alive, Charlie Alive\n";
   assert(true == at_least_two_alive(true, true, true));
   cout << "\tCase Passed...\n";

   //case 2
   cout << "\tCase 2: Aaron Dead, Bob Alive, Charlie Alive\n";
   assert(true == at_least_two_alive(false, true, true));
   cout << "\tCase Passed...\n";

   //case 3
   cout << "\tCase 3: Aaron Alive, Bob Dead, Charlie Alive\n";
   assert(true == at_least_two_alive(true, false, true));
   cout <<"\tCase Passed\n";
   
   //case 4
   cout << "\tCase 4: Aaron Alive, Bob Alive, Charlie Dead\n";
   assert(true == at_least_two_alive(true, true, false));
   cout << "\tCase Passed\n";

   //case 5
   cout << "\tCase 5: Aaron Dead, Bob Dead, Charlie Alive\n";
   assert(false == at_least_two_alive(false, false, true));
   cout << "\tCase Passed...\n";

   //case 6
   cout << "\tCase 6: Aaron Dead, Bob Alive, Charlie Dead\n";
   assert(false == at_least_two_alive(false, true, false));
   cout << "\tCase Passed...\n";

   //case 7
   cout << "\tCase 7: Aaron Alive, Bob Dead, Charlie Dead\n";
   assert(false == at_least_two_alive(true, false, false));
   cout << "\tCase Passed...\n";

   //case 8
   cout << "\tCase 8: Aaron Dead, Bob Dead, Charlie Dead\n";
   assert(false == at_least_two_alive(false, false, false));
   cout << "\tCase Passed...\n";
}

/* Implementation of Aaron_shoots1(bool& B_alive, bool& C_alive) */
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
   assert(B_alive || C_alive);
   int shootResult = rand() % 100;
   if(C_alive) {
      if(shootResult < aaron_success) C_alive = false;
   }
   else{

      if(shootResult < aaron_success) B_alive = false;
   }
   
}

/* Implementation of the test driver for Aaron_shoots1()  */
void test_Aaron_shoots1(void) {
   bool bob_alive;
   bool charlie_alive;
   
   cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
   
   //case 1
   cout << "\tCase 1: Bob Alive, Charlie Alive\n";
   cout << "\t\tAaron is shooting at Charlie\n";
   bob_alive = true;
   charlie_alive = true;
   Aaron_shoots1(bob_alive, charlie_alive);

   //case 2
   cout << "\tCase 2: Bob Dead, Charlie Alive\n";
   cout << "\t\tAaron is shooting at Charlie\n";
   bob_alive = false;
   charlie_alive = true;
   Aaron_shoots1(bob_alive, charlie_alive);

   //case 3
   cout << "\tCase 3: Bob Alive, Charlie Dead\n";
   cout << "\t\tAaron is shooting at Bob\n";
   bob_alive = true;
   charlie_alive = false;
   Aaron_shoots1(bob_alive, charlie_alive);
}

/* Implementation of Bob_shoots(bool& A_alive, bool& C_alive */
void Bob_shoots(bool& A_alive, bool& C_alive){
   assert(A_alive || C_alive);
   int shootResult = rand() % 100;
   if(C_alive) {
      
      if(shootResult < bob_success) C_alive = false;
   }
   else{
      
      if(shootResult < bob_success) A_alive = false;
   }
}

/* Implementation of the test driver for Bob_shoots()  */
void test_Bob_shoots(void) {
   bool aaron_alive;
   bool charlie_alive;
   bool shotTaken;
   
   cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
   //case 1
   cout << "\tCase 1: Aaron Alive, Charlie Alive\n";
   cout << "\t\tBob is shooting at Charlie\n";
   aaron_alive = true;
   charlie_alive= true;
   
   Bob_shoots(aaron_alive, charlie_alive);

   //case 2
   cout << "\tCase 2: Aaron Dead, Charlie Alive\n";
   cout << "\t\tBob is shooting at Charlie\n";
   aaron_alive = false;
   charlie_alive= true;
   Bob_shoots(aaron_alive, charlie_alive);

   //case 3
   cout << "\tCase 3: Aaron Alive, Charlie Dead\n";
   cout << "\t\tBob is shooting at Aaron\n";
   aaron_alive = true;
   charlie_alive= false;
   Bob_shoots(aaron_alive, charlie_alive);

}

/* Implementation of Charlie_shoots(bool& A_alive, bool& B_alive) */
void Charlie_shoots(bool& A_alive, bool& B_alive) {
   assert(A_alive || B_alive);
   if(B_alive) {
      B_alive = false;
   }
   else{
      A_alive = false;
   }
}

/* Implementation of the test driver for Charlie_shoots()  */
void test_Charlie_shoots(void) {
   bool aaron_alive;
   bool bob_alive;
   
   cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
   
   //case 1
   cout << "\tCase 1: Aaron Alive, Bob Alive\n";
   cout << "\t\tCharlie is shooting at Bob\n";
   aaron_alive = true;
   bob_alive = true;
   Charlie_shoots(aaron_alive, bob_alive);

   //case 2
   cout << "\tCase 2: Aaron Dead, Bob Alive\n";
   cout << "\t\tCharlie is shooting at Bob\n";
   aaron_alive = false;
   bob_alive = true;
   Charlie_shoots(aaron_alive, bob_alive);

   //case 3
   cout << "\tCase 3: Bob Alive, Charlie Dead\n";
   cout << "\t\tCharlie is shooting at Aaron\n";
   aaron_alive = true;
   bob_alive = false;
   Charlie_shoots(aaron_alive, bob_alive);

}

/* Implementation of Aaron_shoots2(bool& B_alive, bool& C_alive) */
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
   assert(B_alive || C_alive);
   int shootResult = rand() % 100;
   
   if(C_alive && !B_alive) {
      if(shootResult < aaron_success) C_alive = false;
   }
   
   if(B_alive && !C_alive){
      if(shootResult < aaron_success) B_alive = false;
   }
   
}

/* Implementation of the test driver for Aaron_shoots2()  */
void test_Aaron_shoots2(void) {
   bool bob_alive;
   bool charlie_alive;
   
   cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
   
   //case 1
   cout << "\tCase 1: Bob Alive, Charlie Alive\n";
   cout << "\t\tAaron intentionally misses his first shot\n";
   cout << "\t\tBoth Bob and Charlie are alive.\n";
   bob_alive = true;
   charlie_alive = true;
   Aaron_shoots2(bob_alive, charlie_alive);

   //case 2
   cout << "\tCase 2: Bob Dead, Charlie Alive\n";
   cout << "\t\tAaron is shooting at Charlie\n";
   bob_alive = false;
   charlie_alive = true;
   Aaron_shoots2(bob_alive, charlie_alive);

   //case 3
   cout << "\tCase 3: Bob Alive, Charlie Dead\n";
   cout << "\t\tAaron is shooting at Bob\n";
   bob_alive = true;
   charlie_alive = false;
   Aaron_shoots2(bob_alive, charlie_alive);
}

/*Refactored way to make user pause before continuing each step*/
void Press_any_key(void) {
   cout << "Press any key and enter to continue...";
   cin.ignore().get();
}
