#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> directions = { 
    {1, 1},   
    {-1, -1},  
    {-1, 1}, 
    {1, -1}  
};

bool searchWord(const vector<string>& grid, int row, int col, vector<vector<bool>>& used) {
    int rows = grid.size();
    int cols = grid[0].size();
	
	if(grid[row][col] != 'A') {
		return false;
	}
	
	int leftRightRow1 = row - 1, leftRightCol1 = col - 1;
    int leftRightRow2 = row + 1, leftRightCol2 = col + 1;

    int rightLeftRow1 = row - 1, rightLeftCol1 = col + 1;
    int rightLeftRow2 = row + 1, rightLeftCol2 = col - 1;

    bool isLeftRightValid = leftRightRow1 >= 0 && leftRightCol1 >= 0 &&
                            leftRightRow2 < rows && leftRightCol2 < cols &&
                            ((grid[leftRightRow1][leftRightCol1] == 'M' && grid[leftRightRow2][leftRightCol2] == 'S') ||
                             (grid[leftRightRow1][leftRightCol1] == 'S' && grid[leftRightRow2][leftRightCol2] == 'M'));

    bool isRightLeftValid = rightLeftRow1 >= 0 && rightLeftCol1 < cols &&
                            rightLeftRow2 < rows && rightLeftCol2 >= 0 &&
                            ((grid[rightLeftRow1][rightLeftCol1] == 'M' && grid[rightLeftRow2][rightLeftCol2] == 'S') ||
                             (grid[rightLeftRow1][rightLeftCol1] == 'S' && grid[rightLeftRow2][rightLeftCol2] == 'M'));

    
    if (isLeftRightValid && isRightLeftValid) {
        used[row][col] = true;
        used[leftRightRow1][leftRightCol1] = true;
        used[leftRightRow2][leftRightCol2] = true;
        used[rightLeftRow1][rightLeftCol1] = true;
        used[rightLeftRow2][rightLeftCol2] = true;
        return true;
    }
    return false;
}

int main() {
	vector<string> grid;
    string line;

    ifstream inputFile("input.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    
    int result = 0;

    while (getline(inputFile, line)) {
        grid.push_back(line);
    }

    inputFile.close();
	
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    vector<vector<bool>> used(rows, vector<bool>(cols, false));
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (searchWord(grid, row, col, used)) {
                count++;
            }
        }
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (!used[row][col]) {
                grid[row][col] = '.';
            }
        }
    }
	
	cout << "Result : " << count << endl;
    for (const auto& line : grid) {
        cout << line << endl;
    }

    return 0;
}

