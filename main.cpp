/* A. Harrison Owen
 * CS202 Homework 3
 * Professor Hartman
 * 02/26/2021
 */

/*
 * This program reads through a file and records
 * what tokens were at what place in a file.
 */

#include "StopWatch.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ofstream;  //for output files (similar to cout)
using std::ifstream;  //for input files (similar to cin)
using std::istream;
using std::ostream;
#include <sstream>
using std::istringstream;
#include <iterator>
#include <iomanip>


/*
 * _token : a string in the file
 * _line : line in the file
 * _column : column in the file
 */
struct TokenAndPosition{
    string _token;
    int _line{};
    unsigned int _column{};
};

/*
 * runs through a line in the file and puts each token
 * in the line into a vector.
 * "this is a string" -> vector {"this", "is", "a", "string"}
 */
vector<string> lineToTokens(const string &line){
    vector<string> tokenizedString;
    istringstream iss;
    //iss will iterate through line
    iss = istringstream{line};
    string temp;
    while (iss >> temp){
        //push each token in line onto vector
        tokenizedString.push_back(temp);
    }
    return tokenizedString;
}

/*
 * reads through file and makes vector
 * where each element holds a token, the column the token is in,
 * and the line its in
 * istream is : the file the function is reading through
 */
vector<TokenAndPosition> readLines(istream &is){
    vector<TokenAndPosition> readLine;
    TokenAndPosition readLineElement;
    string lineInFile;
    int lineCount = 0;
    while (true) {
        if (!is) {
            if (is.eof()) {
                cout << "reached end of file" << endl;
            }
            break;
        }
        //look at a single line in the file
        getline(is, lineInFile);
        if (!(lineInFile.empty())) {
            //tokenize line onto vector for reading
            auto tempVec = lineToTokens(lineInFile);
            for (auto & i : tempVec) {
                //finds where token is located in the line
                int found = lineInFile.find(i);
                readLineElement._line = lineCount;
                readLineElement._column = found;
                readLineElement._token = i;
                readLine.push_back(readLineElement);
            }
            lineCount++;
        }
    }
    return readLine;
}


/*
 * prints out the vector of token locations
 * ostream os : pass some output parameter, printing to command line, writing to file
 * vector<TokenAndPosition> tokens : vector that will be printed
 */
void printTokens(ostream &os, const vector<TokenAndPosition> &tokens){
    for (const auto & token : tokens){
        std::ostringstream ss1; //ss1 will be used to make the output look decent
        int lineWidth = std::to_string(token._line).length();
        int columnWidth = std::to_string(token._column).length();
        ss1 << "Line" << std::setw(lineWidth + 2) << token._line
        << ", Column" << std::setw(columnWidth + 2) << token._column
        << ": " << std::setw(2) << token._token << endl;
        os << ss1.str(); //turn ss1 to string and pass into os
    }
}

int main() {
    StopWatch time1; //time how long it takes to read and print
    ifstream myFile("jane eyre.txt", std::ios::binary | std::ios::in);
    time1.start();
    printTokens(cout,readLines(myFile));
    time1.stop();
    StopWatch time2; //time how long it takes to jsut read
    time2.start();
    readLines(myFile);
    time2.stop();
    cout << "Time to read and print: " << time1.timeSecond() << " seconds"<< endl;
    cout << "Time to read: " << time2.timeMilliSec() << " milliseconds" << endl;
    return 0;
}