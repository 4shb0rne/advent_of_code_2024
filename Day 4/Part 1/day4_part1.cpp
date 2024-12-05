#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> directions = {
    {0, 1}, 
    {0, -1},  
    {1, 0},  
    {-1, 0},  
    {1, 1},   
    {1, -1},  
    {-1, 1}, 
    {-1, -1}  
};

bool searchWord(const vector<string>& grid, int row, int col, int dir, vector<vector<bool>>& used) {
    int rows = grid.size();
    int cols = grid[0].size();
    string word = "XMAS";
    int len = word.length();
    int dx = directions[dir].first;  
    int dy = directions[dir].second;

    for (int i = 0; i < len; i++) {
        int newRow = row + i * dx;
        int newCol = col + i * dy;
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] != word[i]) {
            return false;
        }
    }

    for (int i = 0; i < len; i++) {
        int newRow = row + i * dx;
        int newCol = col + i * dy;
        used[newRow][newCol] = true;
    }

    return true;
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
            for (int dir = 0; dir < directions.size(); dir++) {
                bool result = searchWord(grid, row, col, dir, used);
                if(result) {
                	count++;
				}
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

