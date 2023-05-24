/**
 * Student Name: Heeyoon Son
 * StudentId: hzs0093
 * Project Name: Sorting Program
 * File Name: project3_son_hzs0093.cpp
 * Compiler Version: default g++
 */

//sources
//https://www.tutorialspoint.com/how-to-print-out-the-contents-of-a-vector-in-cplusplus

//I used the source above to find out the push_back method on vectors and how to print out vector contents.

//http://www.cplusplus.com/reference/string/string/c_str/
//I used to source above to know how to correctly open a file.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//method declarations

/**
   Reads and copies the values in the file to a given integer vector
   @param input_values the integer vector where the values read are stored. Pointer
   @param instream the stream of values from the file with the values. 
*/
void readFile(vector<int>&input_values, ifstream& instream);

/**
   prints a given value of integers vertically
   @param input_values the integer vector containg the values
*/
void printValuesVertically(vector<int> input_values);

/**
   prints a given value of integers Horizonatally
   @param input_values the integer vector containg the values
*/
void printValuesHorizontally(vector<int> input_values);

/**
   merges and sorts two integer vectors into one.
   @param input1 the first integer vector containg the values
   @param input2 the second integer vector containg the values
   @return a sorted list of merged values of both input1 and input2

*/
vector<int> sortList(vector<int> input1, vector<int> input2);

/**
   Writes a given vectors value onto a file
   @param input the integer vector containg the values
   @param output_file_name the name of the file you want the values to be written in
*/
void writeFile(vector<int> input, string output_file_name);


/*
* The main method runs the sorting program by merging two files into one in sorted order. 
*
*/
int main() {
   bool is_file_open;
   string file_name_1;
   string file_name_2;
   string output_file_name;
   
   ifstream instream1;
   ifstream instream2;

   //the values read from the files will be stored in the vector.
   //Vectors == dynamic resizing great data structure as we don't know how long the file is
   vector<int> input_value_1;
   vector<int> input_value_2;

   cout << "***Welcome to Tim's Sorting Program***" << endl;
   
   //do while statement to retrieve the correct file name from the user
   do {
      //intial state of the file should not be opened yet
      is_file_open = false;
      cout << "Enter the first input file name: ";
      getline(cin, file_name_1);
      instream1.open(file_name_1.c_str());
      
      if(!instream1.is_open()) {
         cout << "Invalid File Name Try Again" << endl;
      }
      else {
         //reaching this statement implies the file was succefully opened
         is_file_open = true;
      }

   }while(cin.fail() || !is_file_open);

   readFile(input_value_1, instream1);
   cout << "The list of " << input_value_1.size() << " numbers in file " 
        << file_name_1 << " is:" << endl;
   printValuesVertically(input_value_1);

   do {
      
      //intial state of the file should not be opened yet
      is_file_open = false;
      cout << "Enter the second input file name: ";
      getline(cin, file_name_2);
      instream2.open(file_name_2.c_str());
      
      if(!instream2.is_open()) {
         cout << "Invalid File Name Try Again" << endl;
      }
      else {
         //reaching this statement implies the file was succefully opened
         is_file_open = true;
      }

   }while(cin.fail() || !is_file_open);
   
   readFile(input_value_2, instream2);
   cout << "The list of " << input_value_2.size() << " numbers in file " 
        << file_name_2 << " is:" << endl;
   printValuesVertically(input_value_2);
   
   vector<int> sortedList = sortList(input_value_1, input_value_2);
   cout << "The Sorted list of " << sortedList.size() << " numbers is: ";
   printValuesHorizontally(sortedList);
   
   cout << "Enter the output file name: ";
   getline(cin, output_file_name);
   writeFile(sortedList, output_file_name);
   cout << "***Please check the new file - " << output_file_name << "***" << endl;
   cout << "***Goodbye. ***" << endl;

   instream1.close();
   instream2.close();

   return 0;
}

void readFile(vector<int>& inputValues, ifstream& instream) {
   int val;
   while(instream >> val) {
      inputValues.push_back(val);
   }
}

void printValuesVertically(vector<int> inputValues) {
   for(int i = 0; i < inputValues.size(); i++) {
      cout << inputValues.at(i) << endl;
   }
   cout << "\n";
}

vector<int> sortList(vector<int> input1, vector<int> input2) {
   vector<int> sortedList;
   int i = 0;
   int j = 0;
   while((i < input1.size()) && (j < input2.size())) {
      int val1 = input1.at(i);
      int val2 = input2.at(j);
      if(val1 <= val2) {
         sortedList.push_back(val1);
         i++;
      }
      else{
         sortedList.push_back(val2);
         j++;
      }
   }
   
   //check which vector was exahsuted first then add the remaining inputs to the sorted list
   //case 1: input1 got exhausted first
   if(i == input1.size()) {
      while(j < input2.size()) {
         sortedList.push_back(input2.at(j));
         j++;
      }
   }
   //case 2: input2 got exhausted first
   else {
      while(i < input1.size()) {
         sortedList.push_back(input1.at(i));
         i++;
      }
   }
   return sortedList;
}

void writeFile(vector<int> input, string output_file_name) {
   ofstream outputFile(output_file_name.c_str());
   for(int i = 0; i < input.size(); i++) {
      outputFile << input.at(i) << " ";
   }
   outputFile.close();
}

void printValuesHorizontally(vector<int> inputValues) {
   for(int i = 0; i < inputValues.size(); i++) {
      cout << inputValues.at(i) << " ";
   }
   cout << endl;
}
