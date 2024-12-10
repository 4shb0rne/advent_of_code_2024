#include <bits/stdc++.h>
using namespace std;

bool are_collinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1);
}

int main() {
    string line;
    vector<string> map;
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
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

    set<pair<int, int>> antinodes;
    
    //for each frequency
    for (const auto& entry : antenna_positions) {
        const vector<pair<int, int>>& positions = entry.second;
        
        //skip if there's only one antenna of this frequency
        if (positions.size() < 2) continue;

        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                //count how many antennas are collinear with this point
                int flag = 0;
                
                //check each pair of antennas
                for (size_t i = 0; i < positions.size(); i++) {
                    for (size_t j = i + 1; j < positions.size(); j++) {
                        if (are_collinear(positions[i].first, positions[i].second,
                                        positions[j].first, positions[j].second,
                                        x, y)) {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) break;  // Already found a collinear pair
                }
                
                if (flag) {
                    antinodes.emplace(x, y);
                }
            }
        }
        
        //Add all antenna positions of this frequency as antinodes
        //(since there are at least 2 antennas of this frequency)
        for (const auto& pos : positions) {
            antinodes.emplace(pos);
        }
    }

    cout << "Total unique antinodes: " << antinodes.size() << endl;
    return 0;
}
