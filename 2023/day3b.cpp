#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Coordinate {
    int x;
    int y;
};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool isDigit(char c) { return std::isdigit(c); }

bool isSymbol(char c) {
    return !std::isalpha(c) && !std::isdigit(c) && (c != '.');
}

int calculateGearRatio(vector<string> &matrix, int x, int y) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int part1 = -1, part2 = -1;

    // Check adjacent cells
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (isValid(i, j, rows, cols) && isDigit(matrix[i][j])) {
                if (part1 == -1) {
                    part1 = matrix[i][j] - '0';
                } else {
                    part2 = matrix[i][j] - '0';
                }
            }
        }
    }

    // Return the product if two adjacent part numbers are found, otherwise,
    // return 0
    return (part1 != -1 && part2 != -1) ? (part1 * part2) : 0;
}

int solution(vector<string> &matrix) {
    int answer = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].length(); ++j) {
            if (isSymbol(matrix[i][j])) {
                answer += calculateGearRatio(matrix, i, j);
            }
        }
    }

    return answer;
}

int main() {
    ifstream file("input/day3.txt"); // Replace with the actual file name
    vector<string> matrix;

    string line;
    while (getline(file, line)) {
        // vector<string> fixedLine = fixTheLine(line);
        // matrix.emplace_back(fixedLine);
    }

    file.close();

    int answer = solution(matrix);
    cout << "Sum of gear ratios: " << answer << endl;

    return 0;
}
