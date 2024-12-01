#include <bits/stdc++.h>
#include <unordered_map>
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
    
    unordered_map<int, int> countMap;
    while (getline(inputFile, line)) {
        istringstream stream(line);
        int l, r;

        if (stream >> l >> r) {
            left.push_back(l); 
            right.push_back(r);
            countMap[r]++;
        } 
    }

    inputFile.close(); 
	
	int sum = 0;
	for(int i = 0; i < left.size(); i++) {
		if(countMap.find(left[i]) != countMap.end()) {
			int occurence = countMap[left[i]];
			sum += (occurence * left[i]);	
		}
    }
    
    cout << sum << endl;
    
	return 0;
}
