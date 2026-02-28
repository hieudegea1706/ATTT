#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Playfair {
private:
    char matrix[5][5];

    string preprocessKey(string key) {
        string result = "";
        bool used[26] = {false};

        for (char c : key) {
            if (c >= 'a' && c <= 'z') c -= 32;
            if (c == 'J') c = 'I';

            if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
                result += c;
                used[c - 'A'] = true;
            }
        }

        for (char c = 'A'; c <= 'Z'; c++) {
            if (c == 'J') continue;
            if (!used[c - 'A']) {
                result += c;
            }
        }

        return result;
    }

    void createMatrix(string key) {
        string newKey = preprocessKey(key);
        int k = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                matrix[i][j] = newKey[k++];
    }

    pair<int,int> findPosition(char c) {
        if (c == 'J') c = 'I';
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (matrix[i][j] == c)
                    return {i, j};
        return {-1, -1};
    }

    string preprocessText(string text) {
        string result = "";

        for (char c : text) {
            if (c >= 'a' && c <= 'z') c -= 32;
            if (c == 'J') c = 'I';
            if (c >= 'A' && c <= 'Z')
                result += c;
        }

        string formatted = "";
        for (int i = 0; i < result.length(); i++) {
            formatted += result[i];

            if (i + 1 < result.length()) {
                if (result[i] == result[i + 1]) {
                    formatted += 'X';
                }
            }
        }

        if (formatted.length() % 2 != 0)
            formatted += 'X';

        return formatted;
    }

public:
    Playfair(string key) {
        createMatrix(key);
    }

    void printMatrix() {
        cout << "Playfair Matrix:\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    string encrypt(string text) {
        string prepared = preprocessText(text);
        string cipher = "";

        for (int i = 0; i < prepared.length(); i += 2) {
            char a = prepared[i];
            char b = prepared[i + 1];

            auto pos1 = findPosition(a);
            auto pos2 = findPosition(b);

            if (pos1.first == pos2.first) {
                cipher += matrix[pos1.first][(pos1.second + 1) % 5];
                cipher += matrix[pos2.first][(pos2.second + 1) % 5];
            }
            else if (pos1.second == pos2.second) {
                cipher += matrix[(pos1.first + 1) % 5][pos1.second];
                cipher += matrix[(pos2.first + 1) % 5][pos2.second];
            }
            else {
                cipher += matrix[pos1.first][pos2.second];
                cipher += matrix[pos2.first][pos1.second];
            }
        }

        return cipher;
    }
};