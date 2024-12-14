#include <bits/stdc++.h>
using namespace std;

struct Region {
    char type;
    int area;
    int sides;
    int price;
};

const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int rows, cols;

int countSides(const vector<string>& grid, const set<pair<int,int>>& region) {
    map<pair<int,int>, set<pair<int,int>>> perim;
    for (const auto& pos : region) {
        int r = pos.first, c = pos.second;
        for (const auto& dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || 
                !region.count({nr, nc})) {
                perim[dir].insert({r, c});
            }
        }
    }
    
    int sides = 0;
    for (const auto& dir_points : perim) {
        set<pair<int,int>> seen_perim;
        for (const auto& point : dir_points.second) {
            if (!seen_perim.count(point)) {
                sides++;
                
                queue<pair<int,int>> q;
                q.push(point);
                
                while (!q.empty()) {
                    pair<int, int> curr = q.front();
					int r = curr.first;
					int c = curr.second;
                    q.pop();
                    
                    if (seen_perim.count({r, c})) continue;
                    seen_perim.insert({r, c});
                    
                    for (const auto& d : directions) {
                        int nr = r + d.first;
                        int nc = c + d.second;
                        if (dir_points.second.count({nr, nc})) {
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }
    }
    return sides;
}

void findRegion(const vector<string>& grid, int r, int c, char type, set<pair<int,int>>& region) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != type || region.count({r, c})) {
        return;
    }
    region.insert({r, c});
    for (const auto& dir : directions) {
        findRegion(grid, r + dir.first, c + dir.second, type, region);
    }
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
    
    rows = grid.size();
    cols = grid[0].size();
    set<pair<int,int>> seen;
    int totalPrice = 0;
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (!seen.count({r, c})) {
                set<pair<int,int>> region;
                findRegion(grid, r, c, grid[r][c], region);
                seen.insert(region.begin(), region.end());
                
                int area = region.size();
                int sides = countSides(grid, region);
                totalPrice += area * sides;
                
                cout << "Region " << grid[r][c] << ": Area=" << area << ", Sides=" << sides << ", Price=" << area * sides << endl;
            }
        }
    }
    
    cout << "Total price: " << totalPrice << endl;
    return 0;
}


