#include <bits/stdc++.h>
using namespace std;

bool isIncreasing(const vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] <= nums[i - 1]) return false;
    }
    return true;
}

bool isDecreasing(const vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] >= nums[i - 1]) return false;
    }
    return true;
}

bool hasValidIndexDifference(const vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        if (abs(nums[i] - nums[i-1]) > 3) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<vector<int>> sequences;
    string line;

    ifstream inputFile("input.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    
    int result = 0;

    while (getline(inputFile, line)) {
        istringstream stream(line);
        vector<int> nums((istream_iterator<int>(stream)), istream_iterator<int>());
        
        if (nums.empty()) continue;

        bool increasing = isIncreasing(nums);
        bool decreasing = isDecreasing(nums);
        bool validDiff = hasValidIndexDifference(nums);

        if ((increasing || decreasing) && validDiff) {
        	result++;
        } 
    }

    inputFile.close();
    
    cout << result << endl;
    return 0;
}

