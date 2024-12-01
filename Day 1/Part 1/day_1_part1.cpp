#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> left;
    vector<int> right;
    string line;

    ifstream inputFile("input.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        istringstream stream(line);
        int l, r;

        if (stream >> l >> r) {
            left.push_back(l); 
            right.push_back(r);
        } 
    }

    inputFile.close(); 

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    int result = 0;
    for(int i = 0; i < left.size(); i++) {
    	result += abs(left[i] - right[i]);
	}
	
	cout << result << endl;

    return 0;
}
