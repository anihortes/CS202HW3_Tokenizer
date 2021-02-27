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

struct TokenAndPosition{
    string _token;
    int _line{};
    unsigned int _column{};
};

vector<string> lineToTokens(const string &line){
    vector<string> tokenizedString;
    istringstream iss;
    iss = istringstream{line};
    string temp;
    while (iss >> temp){
        tokenizedString.push_back(temp);
    }
    return tokenizedString;
}

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
        getline(is, lineInFile);
        if (!(lineInFile.empty())) {
            auto tempVec = lineToTokens(lineInFile);
            for (auto & i : tempVec) {
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

void printTokens(ostream &os, const vector<TokenAndPosition> &tokens){
    for (const auto & token : tokens){
        std::ostringstream ss1;
        int lineWidth = std::to_string(token._line).length();
        int columnWidth = std::to_string(token._column).length();
        ss1 << "Line" << std::setw(lineWidth + 2) << token._line
        << ", Column" << std::setw(columnWidth + 2) << token._column
        << ": " << std::setw(2) << token._token;
        os << ss1.str() << endl;
    }
}

int main() {
    StopWatch time1;
    ifstream myFile("jane eyre.txt", std::ios::binary | std::ios::in);
    time1.start();
    printTokens(cout,readLines(myFile));
    time1.stop();
    StopWatch time2;
    time2.start();
    readLines(myFile);
    time2.stop();
    cout << "Time to read and print: " << time1.timeSecond() << " seconds"<< endl;
    cout << "Time to read: " << time2.timeMilliSec() << " milliseconds" << endl;

    return 0;
}