#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
#define show(x) cout << x << endl
#define showIn(x) cout << x

int solution(vector<string> matrix);

int main() {

    std::fstream File;
    vector<string> matrix;
    File.open("input/day3.txt", ios::in);

    string line;
    int answer = 0;

    while (getline(File, line)) {
        matrix.emplace_back(line);
    }

    File.close();
    int ans = solution(matrix);
    cout << endl << "The final answer is " << ans << endl;
}

bool isSymbol(char c) {
    return !std::isalpha(c) && !std::isdigit(c) && (c != '.');
}

bool isSymboll(char c) { return !std::isalpha(c) && !std::isdigit(c); }

struct Cordinate {
    int x;
    int y;
};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool isPartNumber(vector<string> matrix, vector<Cordinate> cords,
                  string number) {
    // INFO: this function is to tell us is to tell us if it is a part
    bool response = false;

    int rows = matrix.size();
    int cols = matrix[0].size();

    for (Cordinate point : cords) {
        int i = point.x, j = point.y;
        for (int x = i - 1; x <= i + 1; ++x) {
            for (int y = j - 1; y <= j + 1; ++y) {
                if (isValid(x, y, rows, cols) && isSymbol(matrix[x][y])) {
                    if (!isdigit(matrix[x][y])) {
                        return true; // Return true if at least one adjacent
                                     // non-digit symbol is found
                    }
                }
            }
        }
    }

    return response;
}

int solution(vector<string> matrix) {
    int answer = 0;
    string number;
    vector<Cordinate> points;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].length(); ++j) {
            char x = matrix[i][j];
            if (std::isdigit(x)) {
                points.push_back({i, j});
                number += x;
                continue;
            } else {
                if (number.length() > 0) {
                    if (isPartNumber(matrix, points, number)) {
                        answer += stoi(number);
                        // cout << "+ " << number << " makes it " << answer
                        //      << endl;
                    }
                }
                points.clear();
                number.clear();
            }
        }
    }
    // show(answer);
    return answer;
}
