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
    int _line;
    unsigned int _column;
};

vector<string> lineToTokens(const string &line){
    vector<string> tokenizedString;
    auto iss = istringstream {line};
    string temp;
    while (iss >> temp){
        tokenizedString.push_back(temp);
    }
    return tokenizedString;
};

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
            for (auto i = 0; i < tempVec.size(); ++i) {
                string str = tempVec[i];
                int found = lineInFile.find(tempVec[i]);
                readLineElement._line = lineCount;
                readLineElement._column = found;
                readLineElement._token = tempVec[i];
                readLine.push_back(readLineElement);
            }
            lineCount++;
        }
    }
    return readLine;
};

void printTokens(ostream &os, const vector<TokenAndPosition> &tokens){
    for (auto i = 0; i < tokens.size(); ++i){
        std::ostringstream ss1;
        int lineWidth = std::to_string(tokens[i]._line).length();
        int columnWidth = std::to_string(tokens[i]._column).length();
        ss1 << "Line" << std::setw(lineWidth + 2) << tokens [i]._line
        << ", Column" << std::setw(columnWidth + 2) << tokens[i]._column
        << ": " << std::setw(2) << tokens[i]._token;
        os << ss1.str() << endl;
    }
};

int main() {
    ifstream myFile("jane eyre.txt", std::ios::binary | std::ios::in);
    printTokens(cout,readLines(myFile));

    return 0;
}