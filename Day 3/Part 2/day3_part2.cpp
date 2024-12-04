#include <bits/stdc++.h>
using namespace std;

int main() {
    string fileContent;
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    
    ostringstream oss;
    oss << inputFile.rdbuf();
    fileContent = oss.str();
    inputFile.close();
    
    vector<long long> results;
    bool mulEnabled = true;
    int i = 0;
    
    while (i < fileContent.size()) {
        if (fileContent.substr(i, 6) == "don't(") {
            while (i < fileContent.size() && fileContent[i] != ')') i++;
            i++;
            mulEnabled = false;
        } 
        else if (fileContent.substr(i, 3) == "do(") {
            while (i < fileContent.size() && fileContent[i] != ')') i++;
            i++;
            mulEnabled = true;
        } 
        else if (fileContent.substr(i, 4) == "mul(") {
            i += 4;
            long long num1 = 0;
            bool validNum1 = false;
            
            while (i < fileContent.size() && isdigit(fileContent[i])) {
                num1 = num1 * 10 + (fileContent[i] - '0');
                validNum1 = true;
                i++;
            }
            
            if (!validNum1 || i >= fileContent.size() || fileContent[i] != ',') {
                i++;
                continue;
            }
            
            i++;
            long long num2 = 0;
            bool validNum2 = false;
            
            while (i < fileContent.size() && isdigit(fileContent[i])) {
                num2 = num2 * 10 + (fileContent[i] - '0');
                validNum2 = true;
                i++;
            }
            
            if (validNum2 && i < fileContent.size() && fileContent[i] == ')') {
                i++;
                if (mulEnabled) {
                    results.push_back(num1 * num2);
                }
            }
        } 
        else {
            i++;
        }
    }
    
    long long result = accumulate(results.begin(), results.end(), 0LL);
    cout << result << endl;
    
    return 0;
}

