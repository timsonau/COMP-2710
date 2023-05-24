/**
 * Student Name: Heeyoon Son
 * StudentId: hzs0093
 * Project Name: Trivia Game
 * File Name: project3_son_hzs0093.cpp
 * Compiler Version: default g++
 */

////////////////////////
//     sources        //
////////////////////////

/**
 * used this source below to understand how to use the toLower method so
 * I could implement a method where two string coul be compared without being case sensitive
 * I implemented the compareIgnoreCase method because I felt if the user put in the right
 * answer but with differing cases that should not matter because the answer was right
 * for example before this implementation wii sports != Wii Sports, but we can see that
 * clearly both should be "equal" and correct answer  
 */
//https://www.tutorialspoint.com/case-insensitive-string-comparison-in-cplusplus

//This source I used to understand more about how dynamic memory allocation works using the new keyword
//https://stackoverflow.com/questions/38803949/why-use-dynamic-memory-allocationi-e-malloc-when-implementing-linked-list-i#:~:text=By%20dynamically%20allocating%20each%20node,limited%20by%20your%20available%20memory.&text=This%20is%20psedo%2Dcode%20that,the%20lifetime%20of%20the%20program.


//Referenced this material for cin.ignore for the askQuestion method in the LinkedTriviaNodes class
//https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input

//Referenced some Dr.Li's Source Code for general formatting/

#include <iostream>
#include <cassert>
#include <limits>
//algorithm class only used so I could access the tolower method for my convinence method
#include <algorithm>
using namespace std;


//protoypes

/**
 * Test case to check if the methods work 
 */
void UnitTest();

/**
 * Convinence method that checks if two strings are equivlent ignoring case 
 * @param s1 the first string being compared
 * @param s2 the second string being compared
 * @return true if two string are equivalent case insesnsitve false otherwise
 */
bool compareIgnoreCase(string s1, string s2);


struct TriviaNode {
   string question;
   string answer;
   int point;
   TriviaNode* next;

   TriviaNode() {
      question = "";  
      answer = "";
      point = 0;
      next = NULL; 
   }
   
   //convinence constrcutor
   TriviaNode(string question, string answer, int point) {
      this -> question = question;
      this -> answer = answer;
      this -> point = point;
      next = NULL;
   }
};

class LinkedTriviaNodes {
   private:
      TriviaNode * front;
      TriviaNode * back;
      int size;
      int currIndex;
      
      /**
       * Finds the pointer the the trivia node at a given index.
       * @param n index of the trivia node wanting to be found
       * @return the pointer the the trivia node found at the index
       **/
      TriviaNode* getTriviaNode(int n) {
         //case 0: invalid index
         if(n >= size) {
            return NULL;
         }

         int i = 0;
         TriviaNode* nodeFound = front;
         while(i < n) {
               nodeFound = nodeFound -> next;
               i++;
         }
         return nodeFound;
      }
   
   public:
      
      /**
       * Intializes the LinkedTriviaNodes by adding 3 default Trivia Nodes 
       * Equivalent to the "init_question_list" in the hints
       */
      LinkedTriviaNodes() {
         size = 0;
         currIndex = 0;
         
         string question1 = "How long was the shortest war on record?"
            " (Hint: how many minutes)";
         string answer1 = "38";
         int points1 = 100;
         addTriviaNode(question1, answer1, points1);
         
         string question2 = "What was Bank of America's original name?" 
            " (Hint: Bank of Italy or Bank of Germany)";
         string answer2 = "Bank of Italy";
         int points2 = 50;
         addTriviaNode(question2, answer2, points2);

         string question3 = "What is the best-selling video game of all time? "
            "(Hint: Call of Duty or Wii Sports)?";
         string answer3 = "Wii Sports";
         int points3 = 20;
         addTriviaNode(question3, answer3, points3);
      }
      
      /**
       * Gets the number of trivia nodes in the trivia node list
       * @return size the #of nodes in the linked strucutre
       */
      int getSize() {
         return size;
      }

      /**
       * Adds a new trivia node to the existing list of trivia node
       * @param question the question you want in the new node
       * @param answer the answer to the question
       * @param point the #of points being awarded for the right answer to the question
       * Equivalent to the add_question method in the hints
       */       
      void addTriviaNode(string question, string answer, int point) {
         TriviaNode* newNode = new TriviaNode(question, answer, point);
         //case 0: adding the new first node
         if(size == 0) {
            front = newNode;
            back = newNode;
            size++;
            newNode = NULL;
            return;
         }

         //case 1: adding anywhere else
         back -> next = newNode;
         //update the new back of the list
         back = newNode;
         size++;
      }

      /**
       * Ask the user trivia question and starts the game
       * @param numAsk the number of trivia question the user wants to play
       * @return 1 if the numAsk is valid 0 if numAsk is invalid
       * equivalent to ask_qeustion method in the hints.
       */
      int askQuestion(int numAsk) {
         //first asks the question that is current
         if(numAsk < 1) {
            cout << "Warning - the number of trivia to be asked must be equal to or be larger than 1" << endl;
            return 0;
         }
         
         if(size < numAsk) {
            cout << "Warning -There is only " << size << " trivia in the list" << endl;
            return 0; 
         }
         
         int totalPoints = 0;
         TriviaNode* currNode;
         for(int i = 0; i < numAsk; i++) {
            currNode = getTriviaNode(i);
            currIndex++;
            cout << "Question: " << currNode -> question << endl;
            cout << "Answer: ";
            string userAnswer;
            string trueAnswer = currNode -> answer;
            getline(cin, userAnswer);
            //right answer
            if(compareIgnoreCase(userAnswer, trueAnswer)) {
               cout << "Your answer is correct. You recieve " << currNode -> point << " points" << endl;
               totalPoints += currNode -> point;
            }
            //wrong answer
            else {
               cout << "Your answer is wrong. The correct answer is: " << trueAnswer << endl;

            }
            cout << "Your total points: " << totalPoints << endl << "\n";
         }
         currNode = NULL;
         return 1;
      }


};


//TWO VERSIONS
//uncomment the version you would like to compile
//#define UNIT_TESTING
#define trivia_quiz

int main() {
   LinkedTriviaNodes triviaList;
   
   cout << "*** Welcome to Tim's trivia quiz game ***" << endl;
   bool wishToContinue = true;
#ifdef trivia_quiz
   do {
      cout << "Enter a question: ";
      string userQuestion; 
      getline(cin, userQuestion);

      cout << "Enter an answer: ";
      string userAnswer;
      getline(cin, userAnswer);

      bool validInput = false;
      do {
         cout << "Enter award points: ";
         int userPoints;
         cin >> userPoints;

         if(cin.fail()) {
            cout << "Award points must be an integer value\n";
         }else {
            validInput = true;
            triviaList.addTriviaNode(userQuestion, userAnswer, userPoints);
         }

         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');

      }while(!validInput);
      

      cout << "Continue? (Yes/No): ";
      string answer;
      getline(cin, answer);
      
      if(compareIgnoreCase(answer, "No")) {
         wishToContinue = false;
         cout << "\n";
      }

   }while(wishToContinue == true);

   int size = triviaList.getSize();

   triviaList.askQuestion(size);
   return 0;
}
#endif

#ifdef UNIT_TESTING
   UnitTest();
   return 0;
}
#endif

/**
 * Test case to check if the methods work 
 */
void UnitTest() {
   //intializes list with 3 trivia nodes
   LinkedTriviaNodes testList;
   bool testPassed;
   cout << "***This is a debugging version*** " << endl;
   cout << "FOR DEBUGGING PURPOSES THE ANSWER FOR EACH QUESTION IS LISTED BELOW" << endl;
   cout << "1. Q: Length of Shortest War | A: 38" << endl;
   cout << "2. Q: Original Name of the Bank of America | A: Bank of Italy" << endl;
   cout << "3. Q: The best selling video game | A: Wii Sports " << endl;
   //case 1
   cout << "\nUnit Test Case 1: Ask no question. The program should give a warning message." << endl;
   assert(0 == testList.askQuestion(0));
   cout << "Case 1 Passed" << endl;
   
   //case 2.1
   cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list.The tester enters an incorrect answer." << endl;
   assert(1 == testList.askQuestion(1));
   cout << "Case 2.1 Passed" << endl;

   //case 2.2
   cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list.The tester enters an correct answer." << endl;
   assert(1 == testList.askQuestion(1));
   cout << "Case 2.2 Passed" << endl;

   //case 3
   cout << "\nUnit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
   assert(1 == testList.askQuestion(3));
   cout << "Case 3 Passed" << endl;

   //case 3
   cout << "\nUnit Test Case 4: Ask 5 questions in the linked list. " << endl;
   assert(0 == testList.askQuestion(5));
   cout << "Case 4 Passed" << endl << "\n";
   cout << "***End of the Debugging Version***" << endl;
}


/**
 * Convinence method that checks if two strings are equivlent ignoring case 
 * @param s1 the first string being compared
 * @param s2 the second string being compared
 * @return true if two string are equivalent case insesnsitve false otherwise
 */
bool compareIgnoreCase(string s1, string s2) {
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

   return s1.compare(s2) == 0;
}

