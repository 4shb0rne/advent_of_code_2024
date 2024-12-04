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

    stack<int> stk;   
    int result = 0;   
    int i = 0;       

    while (i < fileContent.size()) {
       
        if (fileContent.substr(i, 4) == "mul(") {
            i += 4; 

            int num1 = 0;
            while (i < fileContent.size() && isdigit(fileContent[i])) {
                num1 = num1 * 10 + (fileContent[i] - '0');
                i++;
            }

            while (i < fileContent.size() && (fileContent[i] == ',')) {
                i++;
            }

            int num2 = 0;
            while (i < fileContent.size() && isdigit(fileContent[i])) {
                num2 = num2 * 10 + (fileContent[i] - '0');
                i++;
            }

            if (i < fileContent.size() && fileContent[i] == ')') {
                i++;
                int mulResult = num1 * num2;
                stk.push(mulResult);
            } else {
                while (i < fileContent.size() && fileContent[i] != 'm') { 
                    i++;
                }
            }
        } else {
            i++;
        }
    }

    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    cout << result << endl;

    return 0;
}


