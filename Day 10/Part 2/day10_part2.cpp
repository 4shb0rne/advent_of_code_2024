#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> parse_map(const string& input) {
    vector<vector<int>> grid;
    stringstream ss(input);
    string line;
    while (getline(ss, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
    }
    return grid;
}

vector<pair<int, int>> get_neighbors(int x, int y, int height, int width) {
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<pair<int, int>> neighbors;
    for (const auto& dir : directions) {
        int new_x = x + dir.first;
        int new_y = y + dir.second;
        if (0 <= new_x && new_x < height && 0 <= new_y && new_y < width) {
            neighbors.push_back(make_pair(new_x, new_y));
        }
    }
    return neighbors;
}

void count_paths(const vector<vector<int>>& grid, int x, int y, int current_height,
                vector<vector<bool>>& visited, int& path_count) {
    int height = grid.size();
    int width = grid[0].size();
    
    if (grid[x][y] == 9) {
        path_count++;
        return;
    }
    
    visited[x][y] = true;
    
    for (const auto& next : get_neighbors(x, y, height, width)) {
        int nx = next.first;
        int ny = next.second;
        
        if (!visited[nx][ny] && grid[nx][ny] == current_height + 1) {
            count_paths(grid, nx, ny, current_height + 1, visited, path_count);
        }
    }
    
    visited[x][y] = false; 
}

int find_distinct_trails(const vector<vector<int>>& grid, int start_x, int start_y) {
    int height = grid.size();
    int width = grid[0].size();
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    int path_count = 0;
    
    count_paths(grid, start_x, start_y, 0, visited, path_count);
    
    return path_count;
}

int solve_hiking_trails_part2(const string& input) {
    auto grid = parse_map(input);
    int height = grid.size();
    int width = grid[0].size();
    int total_rating = 0;
    
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (grid[x][y] == 0) {
                int rating = find_distinct_trails(grid, x, y);
                total_rating += rating;
            }
        }
    }
    
    return total_rating;
}

int main() {
    string test_input = "89010123\n"
                       "78121874\n"
                       "87430965\n"
                       "96549874\n"
                       "45678903\n"
                       "32019012\n"
                       "01329801\n"
                       "10456732";

    cout << "Sum of trailhead ratings: " << solve_hiking_trails_part2(test_input) << endl;

    ifstream inputFile("input.txt");
    string input, line;
    while (getline(inputFile, line)) {
        input += line + "\n";
    }
    inputFile.close();
    
    cout << "Sum of trailhead ratings (from file): " << solve_hiking_trails_part2(input) << endl;
    
    return 0;
}