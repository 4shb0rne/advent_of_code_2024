#include <bits/stdc++.h>
using namespace std;

bool evaluate(const vector<long long int>& values, long long int target, int index, long long int current) {
    if (index == values.size()) {
        return current == target;
    }

    if (evaluate(values, target, index + 1, current + values[index])) {
        return true;
    }

    if (evaluate(values, target, index + 1, current * values[index])) {
        return true;
    }

    return false;
}

long long int findCombination(const vector<long long int>& values, long long int target) {
	long long int firstValue = values[0];
    if (evaluate(values, target, 1, firstValue)) {
        return target;
    }

    return -1;
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
        
        //convert string to LL
        long long int key = stoll(token);

        vector<long long int> values;
        while (ss >> token) {
            values.push_back(stoi(token));
        }

        parsedData.push_back({key, values});
    }

    inputFile1.close();
    
    long long int answer = 0;
    
    for (const auto& entry : parsedData) {
        long long int target = entry.first;
        const vector<long long int>& values = entry.second;
		
        long long int result = findCombination(values, target);
        if (result != -1) {
            cout << "Target " << target << " can be achieved with values." << endl;
            answer += result;
        } else {
            cout << "Target " << target << " cannot be achieved." << endl;
        }
    }
    
    cout << "Sum : " << answer << endl;

    return 0;
}

