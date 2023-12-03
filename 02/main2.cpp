#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string colors[3] = {"red", "blue", "green"};
int color_limits[3] = {12, 14, 13};

int getColorIndex(char lastC) {
    if (lastC == 'd') return 0;
    else if (lastC == 'e') return 1;
    else if (lastC == 'n') return 2;
    return -1;
}

pair<int, int> getGameIdPos(string game) {
    int pos = game.find(":");
    int gameId = stoi(game.substr(5, pos - 5));
    return make_pair(gameId, pos + 1);
}

vector<string> splitString(const string& input, const string& delimiter) {
    vector<string> tokens;
    string token = "";
    for (int i = 0; i < input.size(); i++) {
        bool flag = true;
        for (int j = 0; j < delimiter.size(); j++) {
            if (input[i + j] != delimiter[j]) flag = false;
        }
        if (flag) {
            if (token.size() > 0) {
                tokens.push_back(token);
                token = "";
                i += delimiter.size() - 1;
            }
        } else {
            token += input[i];
        }
    }
    tokens.push_back(token);
    return tokens;
}

int main() {
    string line;
    ifstream file("input.txt");
    int total = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            bool gamePossible = true;
            auto result = getGameIdPos(line);
            int gameId = result.first;
            int start_pos = result.second;
            int minimums[3] = {0, 0, 0};

            vector<string> rounds = splitString(line.substr(start_pos), "; ");
            for (const string& round : rounds) {
                vector<string> boxes = splitString(round, ", ");

                for (const string& box : boxes) {
                    char lastC = box[box.length() - 1];
                    int colorNumber = getColorIndex(lastC);
                    int numberOfBoxed = stoi(box.substr(0, box.length() - colorNumber - 4));

                    if (numberOfBoxed > minimums[colorNumber]) {
                        minimums[colorNumber] = numberOfBoxed;
                    }
                }
            }            
            total += minimums[0] * minimums[1] * minimums[2];
        }

        file.close();
    } else {
        cerr << "Unable to open the file." << endl;
        return 1;
    }

    cout << "The answer is: " << total << endl;
    return 0;
}
