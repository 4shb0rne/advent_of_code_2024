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

vector<int> fixSequence(vector<int> sequence, const map<int, vector<int>>& hashTable) {
    for (int i = 0; i < sequence.size(); i++) {
        int key = sequence[i];

        if (hashTable.find(key) != hashTable.end()) {
            //list of all numbers that should appear before the key
            const vector<int>& numbers = hashTable.at(key);

            for (int value : numbers) {
                //search for index of the value
                auto it = find(sequence.begin(), sequence.end(), value);

                //if value exists
                if (it != sequence.end()) {
                    //calculate how far is the value
                    int valueIndex = distance(sequence.begin(), it);

                    //if index is smaller than index of current number
                    if (valueIndex < i) { 
                        //delete the value 
                        sequence.erase(sequence.begin() + valueIndex);
                        
                        //move it before the key
                        if (valueIndex < i) i--;
                        sequence.insert(sequence.begin() + i + 1, value);
                    }
                }
            }
        }
    }

    return sequence;
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
        cerr << "Error: Unable to open input_1.txt." << endl;
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
        cerr << "Error: Unable to open input_2.txt." << endl;
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
            cout << line << ": Valid" << endl;
        } else {
            cout << line << ": Invalid" << endl;
            cout << "Fixing :" << endl;
            vector<int> fixedSequence = fixSequence(sequence, hashTable);
            cout << line << " -> Fixed: ";
	        for (int num : fixedSequence) {
	            cout << num << ",";
	        }
            int middleValue = getMiddleValue(fixedSequence);
            result += middleValue;
        }
    }

    inputFile2.close();
    
    cout << "\nResult : " << result << endl;
    
    return 0;
}

