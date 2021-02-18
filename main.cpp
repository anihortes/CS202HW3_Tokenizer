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
#include <sstream>
#include <iterator>

struct TokenAndPosition{
    string _token;
    int _line;
    unsigned int _column;
};

vector<string> lineToTokens(){
    ifstream myFile("data.dat");
    string temp;
    vector <string> dataVector;
    int dataInfile;
    while (true) {
        if (!myFile) {
            if (myFile.eof()) {
                cout << "reached end of file" << endl;
            }
            break;
        }
        myFile.read(reinterpret_cast<char*>(&dataInfile),sizeof(dataInfile));
        if(!myFile) break;
        temp = std::to_string(dataInfile);
        dataVector.push_back(temp);
    }
    return dataVector;
}

int main() {
    vector<string> lineToTokens();
    vector <TokenAndPosition> readLines;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
