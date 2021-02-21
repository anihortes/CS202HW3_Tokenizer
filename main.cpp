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
vector<TokenAndPosition> readLines(istream &is);
void printTokens(ostream &os, const vector<TokenAndPosition> &tokens);

int main() {
    ifstream myFile("jane eyre.txt", std::ios::binary | std::ios::in);
    vector <string> dataVector;
    string lineInFile;
    while (true) {
        if (!myFile) {
            if (myFile.eof()) {
                cout << "reached end of file" << endl;
            }
            break;
        }
        getline(myFile, lineInFile);
        lineToTokens(lineInFile);

    }

    //vector <TokenAndPosition> readLines;




    return 0;
}
