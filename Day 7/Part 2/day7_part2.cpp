#include <bits/stdc++.h>
using namespace std;

bool evaluate(const vector<long long int>& numbers, const vector<string>& operators, long long int target) {
    long long int current = numbers[0];

    for (int i = 0; i < operators.size(); ++i) {
        if (operators[i] == "+") {
            current += numbers[i + 1];
        } else if (operators[i] == "*") {
            current *= numbers[i + 1];
        } else if (operators[i] == "||") {

            string concatenated = to_string(current) + to_string(numbers[i + 1]);
            current = stoll(concatenated);
        }
    }

    return current == target;
}

void findCombination(const vector<pair<long long int, vector<long long int>>>& equations, long long int& totalCalibrationResult) {
    for (const auto& eq : equations) {
        long long int target = eq.first;
        const vector<long long int>& numbers = eq.second;

        long long int n = numbers.size();
        vector<string> operators(n - 1);

        int possibleCombinations = pow(3, n - 1);
        bool found = false;

        for (int mask = 0; mask < possibleCombinations; ++mask) {
            long long int tempMask = mask;

            for (int i = 0; i < n - 1; ++i) {
                int opIndex = tempMask % 3; 
                tempMask /= 3;

                if (opIndex == 0) {
                    operators[i] = "+";
                } else if (opIndex == 1) {
                    operators[i] = "*";
                } else if (opIndex == 2) {
                    operators[i] = "||";
                }
            }

            if (evaluate(numbers, operators, target)) {
            	cout << "Target " << target << " can be achieved with values." << endl;
                found = true;
                break;
            }
        }

        if (found) {
            totalCalibrationResult += target;
        }
    }
}


int main() {
    string line;
    vector<pair<long long int, vector<long long int>>> parsedData;

    ifstream inputFile1("input.txt");
    if (!inputFile1) {
        cerr << "Error: Unable to open input.txt." << endl;
        return 1;
    }

    while (getline(inputFile1, line)) {
        istringstream ss(line);
        string token;

        getline(ss, token, ':');
        
        long long int key = stoll(token);

        vector<long long int> values;
        while (ss >> token) {
            values.push_back(stoi(token));
        }

        parsedData.push_back({key, values});
    }

    inputFile1.close();
    
    long long int answer = 0;
    
    findCombination(parsedData, answer);
    
    cout << "Sum : " << answer << endl;

    return 0;
}

