#include <bits/stdc++.h>
using namespace std;

struct State {
    int row, col;
    int nextRow, nextCol;
    
    bool operator==(const State& other) const {
        return row == other.row && col == other.col && 
               nextRow == other.nextRow && nextCol == other.nextCol;
    }
    
    bool operator<(const State& other) const {
        if (row != other.row) return row < other.row;
        if (col != other.col) return col < other.col;
        if (nextRow != other.nextRow) return nextRow < other.nextRow;
        return nextCol < other.nextCol;
    }
};

bool PatrolLoop(pair<int,int> startPos, int nextRow, int nextCol, const vector<string>& grid) {
    int rowCount = grid.size();
    int colCount = grid[0].size();
    int currRow = startPos.first;
    int currCol = startPos.second;
    
    set<State> visited;
    
    while (true) {
        State currentState = {currRow, currCol, nextRow, nextCol};
        if (visited.find(currentState) != visited.end()) {
            return true;
        }
        visited.insert(currentState);
        
        if (currRow + nextRow < 0 || currRow + nextRow >= rowCount || 
            currCol + nextCol < 0 || currCol + nextCol >= colCount) {
            break;
        }
        
        if (grid[currRow + nextRow][currCol + nextCol] == '#' ||
            grid[currRow + nextRow][currCol + nextCol] == 'O') {
            int tempRow = nextRow;
            nextRow = nextCol;
            nextCol = -tempRow;
        } else {
            currRow += nextRow;
            currCol += nextCol;
        }
    }
    return false;
}

int main() {
    string line;
    vector<string> originalMap;
    
    ifstream inputFile("input.txt");
    while (getline(inputFile, line)) {
        originalMap.push_back(line);
    }
    inputFile.close();
    
    pair<int,int> start = {-1, -1};
    for (int i = 0; i < originalMap.size(); i++) {
        for (int j = 0; j < originalMap[i].size(); j++) {
            if (originalMap[i][j] == '^') {
                start = {i, j};
                break;
            }
        }
        if (start.first != -1) break;
    }
    
    set<pair<int,int>> visitedPositions;
    int currX = start.second, currY = start.first;
    int nextRow = -1, nextCol = 0;  
    
    while (true) {
        visitedPositions.insert({currY, currX});
        
        if (currY + nextRow < 0 || currY + nextRow >= originalMap.size() || 
            currX + nextCol < 0 || currX + nextCol >= originalMap[0].size()) {
            break;
        }
        
        if (originalMap[currY + nextRow][currX + nextCol] == '#') {
            int tempRow = nextRow;
            nextRow = nextCol;
            nextCol = -tempRow;
        } else {
            currY += nextRow;
            currX += nextCol;
        }
    }
    
    int loopCount = 0;
    for (const auto& pos : visitedPositions) {
        if (pos.second == start.second && pos.first == start.first) continue;
        
        vector<string> testMap = originalMap;
        testMap[pos.first][pos.second] = '#';
        
        if (PatrolLoop(start, -1, 0, testMap)) {
            loopCount++;
            cout << "Found loop position at (" << pos.first << "," << pos.second << ")" << endl;
        }
    }
    
    cout << "Number of positions that create loops: " << loopCount << endl;
    return 0;
}
