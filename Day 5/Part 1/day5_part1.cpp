#include <bits/stdc++.h>
using namespace std;

bool validateLine(const vector<int>& sequence, const map<int, vector<int>>& hashTable) {
    unordered_map<int, int> positionMap;
    for (int i = 0; i < sequence.size(); i++) {
        positionMap[sequence[i]] = i;
    }

    for (int i = 0; i < sequence.size(); i++) {
        int key = sequence[i];
        if (hashTable.find(key) != hashTable.end()) {
            for (int value : hashTable.at(key)) {
                if (positionMap.find(value) != positionMap.end() && positionMap[value] < i) {
                    return false;
                }
            }
        }
    }
    return true;
}

int getMiddleValue(const vector<int>& sequence) {
    int n = sequence.size();
    if (n % 2 == 1) {
        return sequence[n / 2]; 
    } else {
        return sequence[n / 2 - 1]; 
    }
}

int main() {
    map<int, vector<int>> hashTable;
    string line;

    ifstream inputFile1("input_1.txt");
    if (!inputFile1) {
        cerr << "Error: Unable to open sample_case.txt." << endl;
        return 1;
    }

    while (getline(inputFile1, line)) {
        if (line.find('|') != string::npos) {
            size_t delimiterPos = line.find('|');
            int key = stoi(line.substr(0, delimiterPos));
            int value = stoi(line.substr(delimiterPos + 1));
            hashTable[key].push_back(value);
        }
    }
    inputFile1.close();

    for (const auto& pair : hashTable) {
        cout << pair.first << "-> ";
        for (const int& value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }

    ifstream inputFile2("input_2.txt");
    if (!inputFile2) {
        cerr << "Error: Unable to open sample_case2.txt." << endl;
        return 1;
    }

    int result = 0;
    while (getline(inputFile2, line)) {
        stringstream ss(line);
        string number;
        vector<int> sequence;

        while (getline(ss, number, ',')) {
            sequence.push_back(stoi(number));
        }
		
        if (validateLine(sequence, hashTable)) {
        	int middleValue = getMiddleValue(sequence);
        	result += middleValue;
            cout << line << ": Valid" << endl;
        } else {
            cout << line << ": Invalid" << endl;
        }
    }

    inputFile2.close();
    
    cout << "Result : " << result << endl;
    
	return 0;
}

