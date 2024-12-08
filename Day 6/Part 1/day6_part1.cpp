#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    vector<string> map;

    ifstream inputFile1("input.txt");
    if (!inputFile1) {
        cerr << "Error: Unable to open input.txt." << endl;
        return 1;
    }

    while (getline(inputFile1, line)) {
        map.push_back(line);
    }
    inputFile1.close();

    int originalLengthY = map.size();
    int originalLengthX = map[0].size();

    int currX = -1;
    int currY = -1;
    string direction = "TOP";

    for (int i = 0; i < originalLengthY; i++) {
        for (int j = 0; j < originalLengthX; j++) {
            if (map[i][j] == '^') {
                currX = j; // X-coordinate is the column index
                currY = i; // Y-coordinate is the row index
                break;
            }
        }
        if (currX != -1 && currY != -1) {
            break;
        }
    }

    if (currX == -1 || currY == -1) {
        cerr << "Error: Player '^' not found in the map." << endl;
        return 1;
    }

    int count = 1;

    while (true) {
        if (currX < 0 || currX >= originalLengthX-1 || currY < 0 || currY >= originalLengthY-1) {
            break;
        }

        if (map[currY][currX] != '#') {
            if (map[currY][currX] != 'X') {
                count++;
                map[currY][currX] = 'X'; 
            }
        }

        if (direction == "TOP") {
            currY -= 1;
            if (map[currY][currX] == '#') {
                direction = "RIGHT";
                currY += 1; 
            }
        } else if (direction == "RIGHT") {
            currX += 1;
            if (map[currY][currX] == '#') {
                direction = "BOTTOM";
                currX -= 1; 
            }
        } else if (direction == "BOTTOM") {
            currY += 1;
            if (map[currY][currX] == '#') {
                direction = "LEFT";
                currY -= 1;
            }
        } else if (direction == "LEFT") {
            currX -= 1;
            if (map[currY][currX] == '#') {
                direction = "TOP";
                currX += 1; 
            }
        }

        cout << "Moving to (" << currY << ", " << currX << ") with direction " << direction << endl;
        //this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "Final map state:" << endl;
    for (const auto &row : map) {
        cout << row << endl;
    }
    cout << "Count of visited cells: " << count << endl;

    return 0;
}

