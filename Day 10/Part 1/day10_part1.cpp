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

int find_reachable_nines(const vector<vector<int>>& grid, int start_x, int start_y) {
    int height = grid.size();
    int width = grid[0].size();
    set<pair<int, int>> visited;
    set<pair<int, int>> reachable_nines;
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(start_x, start_y, 0));
    
    while (!q.empty()) {
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int current_height = get<2>(q.front());
        q.pop();
        
        if (visited.count(make_pair(x, y))) continue;
        visited.insert(make_pair(x, y));
        
        if (grid[x][y] == 9) {
            reachable_nines.insert(make_pair(x, y));
            continue;
        }
        
        for (const auto& next : get_neighbors(x, y, height, width)) {
            if (grid[next.first][next.second] == current_height + 1) {
                q.push(make_tuple(next.first, next.second, current_height + 1));
            }
        }
    }
    
    return reachable_nines.size();
}

int solve_hiking_trails(const string& input) {
    auto grid = parse_map(input);
    int height = grid.size();
    int width = grid[0].size();
    int total_score = 0;
    
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (grid[x][y] == 0) {
                total_score += find_reachable_nines(grid, x, y);
            }
        }
    }
    
    return total_score;
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

    cout << "Sum of trailhead scores: " << solve_hiking_trails(test_input) << endl;

    ifstream inputFile("input.txt");
    string input, line;
    while (getline(inputFile, line)) {
        input += line + "\n";
    }
    inputFile.close();
    
    cout << "Sum of trailhead scores (from file): " << solve_hiking_trails(input) << endl;
    
    return 0;
}
