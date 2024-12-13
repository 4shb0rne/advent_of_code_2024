#include <bits/stdc++.h>
using namespace std;

struct Region {
    char type;
    int area;
    int perimeter;
    int price;
};

vector<vector<bool>> visited;
int rows, cols;

int countPerimeter(const vector<string>& grid, int r, int c, char type) {
    int perimeter = 0;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (const auto& dir : directions) {
        int newR = r + dir.first;
        int newC = c + dir.second;
        
        if (newR < 0 || newR >= rows || newC < 0 || newC >= cols || grid[newR][newC] != type) {
            perimeter++;
        }
    }
    return perimeter;
}

void dfs(const vector<string>& grid, int r, int c, char type, Region& region) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || 
        visited[r][c] || grid[r][c] != type) {
        return;
    }
    
    visited[r][c] = true;
    region.area++;
    region.perimeter += countPerimeter(grid, r, c, type);
    
    dfs(grid, r-1, c, type, region);
    dfs(grid, r+1, c, type, region);
    dfs(grid, r, c-1, type, region);
    dfs(grid, r, c+1, type, region);
}

int main() {
    ifstream inputFile("input.txt");
    vector<string> grid;
    string line;
    
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    inputFile.close();
    
    rows = grid.size();
    cols = grid[0].size();
    visited.resize(rows, vector<bool>(cols, false));
    
    vector<Region> regions;
    int totalPrice = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!visited[i][j]) {
                Region region = {grid[i][j], 0, 0, 0};
                dfs(grid, i, j, grid[i][j], region);
                if (region.area > 0) {
                    region.price = region.area * region.perimeter;
                    regions.push_back(region);
                    totalPrice += region.price;
                }
            }
        }
    }
    
    for (const auto& region : regions) {
        cout << "Region " << region.type << ": Area=" << region.area 
             << ", Perimeter=" << region.perimeter 
             << ", Price=" << region.price << endl;
    }
	cout << "Total price : " << totalPrice << endl;
    
    return 0;
}
