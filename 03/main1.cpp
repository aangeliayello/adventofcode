#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<char> non_symbols = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

pair<int, int> getDimensions(vector<vector<char>> &input)
{
    int n_lines = input.size();
    int n_chars = 0;

    if (n_lines > 0)
    {
        n_chars = input[0].size();
        for (const vector<char> &row : input)
        {
            if (row.size() != n_chars)
            {
                cerr << "Rows of the input are not all of the same size." << endl;
            }
        }
    }
    return make_pair(n_lines, n_chars);
}

void update_schematic_valid(int curr_line, int i, pair<int, int> dimensions, vector<vector<bool>> &schematic_valid)
{
    if (0 < i)
        schematic_valid[curr_line][i - 1] = true;
    // right
    if (i + 1 < dimensions.second)
        schematic_valid[curr_line][i + 1] = true;

    // up
    if (0 < curr_line)
        schematic_valid[curr_line - 1][i] = true;
    // down
    if (curr_line + 1 < dimensions.first)
        schematic_valid[curr_line + 1][i] = true;

    // top-left
    if ((i > 0) && (0 < curr_line))
        schematic_valid[curr_line - 1][i - 1] = true;
    // top-right
    if ((i < dimensions.second) && (0 < curr_line))
        schematic_valid[curr_line - 1][i + 1] = true;

    // down-left
    if ((i > 0) && (curr_line + 1 < dimensions.first))
        schematic_valid[curr_line + 1][i - 1] = true;
    // down-right
    if ((i < dimensions.second) && (curr_line + 1 < dimensions.first))
        schematic_valid[curr_line + 1][i + 1] = true;
}

vector<vector<char>> get_input(string input_name)
{
    vector<vector<char>> input = {};
    string line;
    ifstream file(input_name);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<char> row;

            for (int i = 0; i < line.length(); i++)
            {
                row.push_back(line[i]);
            }

            input.push_back(row);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open the file." << endl;
    }
    return input;
}

int main()
{
    string input_name = "input.txt";

    vector<vector<char>> input = get_input(input_name);
    pair<int, int> dimensions = getDimensions(input);

    vector<vector<bool>> schematic_valid(dimensions.first, vector<bool>(dimensions.second, false));

    int total, curr_line = 0;

    for (int curr_line = 0; curr_line < dimensions.first; curr_line++)
    {
        for (int i = 0; i < dimensions.second; i++)
        {
            char c = input[curr_line][i];
            auto find_elem = non_symbols.find(c);
            if (find_elem == non_symbols.end())
            { // Element is a symbol
                update_schematic_valid(curr_line, i, dimensions, schematic_valid);
            }
        }
    }

    bool number_is_valid = false;
    int partial_number = 0;
    char c;

    for (int curr_line = 0; curr_line < dimensions.first; curr_line++)
    {

        for (int i = 0; i < dimensions.second; i++)
        {
            c = input[curr_line][i];

            if (isdigit(c))
            {
                if (schematic_valid[curr_line][i])
                {
                    number_is_valid = true;
                }
                partial_number = partial_number * 10 + (c - '0');
            }
            else
            {
                if (number_is_valid)
                    total += partial_number;

                number_is_valid = false;
                partial_number = 0;
            }
        }
        if (number_is_valid)
            total += partial_number;

        number_is_valid = false;
        partial_number = 0;
    }

    cout << "The answer is: " << total << endl;

    return 0;
}
