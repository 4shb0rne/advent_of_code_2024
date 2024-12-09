#include <bits/stdc++.h>
using namespace std;

long long int findCombinationIterative(const vector<long long int>& values, long long int target) {
    if (values.empty()) {
        return -1; 
    }

    stack<pair<int, long long int>> states;
    states.push({1, values[0]});

    while (!states.empty()) {
        pair<int, long long int> state = states.top();
        states.pop();

        int index = state.first;
        long long int current = state.second;

        if (index == values.size()) {
            if (current == target) {
                return target;
            }
            continue;
        }

        states.push(make_pair(index + 1, current + values[index]));
        states.push(make_pair(index + 1, current * values[index]));
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
		
        long long int result = findCombinationIterative(values, target);
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

