#include <bits/stdc++.h>
using namespace std;

bool checkBounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

//euclidean distance formula
double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

//collinear mean it exist in same straight line(could be diagonally)
bool areCollinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1);
}

int main() {
    string line;
    vector<string> map;
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open input.txt." << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        map.push_back(line);
    }
    inputFile.close();

    int rows = map.size();
    int cols = map[0].size();

    //combine anthena with same frequency(characters)
    unordered_map<char, vector<pair<int, int>>> antenna_positions;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (isalnum(map[i][j])) {
                antenna_positions[map[i][j]].emplace_back(i, j);
            }
        }
    }

    //calculate antinodes
    set<pair<int, int>> antinodes;
    for (const auto& entry : antenna_positions) {
        const vector<pair<int, int>>& positions = entry.second;
        int n = positions.size();
        
        //check each pair of antennas with the same frequency
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = positions[i].first, y1 = positions[i].second;
                int x2 = positions[j].first, y2 = positions[j].second;

                //check each potential antinode position
                for (int x = 0; x < rows; x++) {
                    for (int y = 0; y < cols; y++) {
                    	// x y is the current index that will create new antinodes
                        if (areCollinear(x1, y1, x2, y2, x, y)) {
                            double d1 = calculateDistance(x, y, x1, y1);
                            double d2 = calculateDistance(x, y, x2, y2);
                            
                            //if distance of athena one and two to current index is equal to distance of
                            //those two athena, then antinode can be placed
                            if (abs(d1 * 2 - d2) == 0 || abs(d2 * 2 - d1) == 0) {
                                antinodes.emplace(x, y);
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Total unique antinodes: " << antinodes.size() << endl;
    return 0;
}

