#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

set<char> non_symbols = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

pair<int, int> getDimensions(const vector<vector<char>> &input)
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

void update_schematic_count(int curr_line, int start, int end, const pair<int, int> &dimensions, const vector<vector<char>> &input, vector<vector<vector<int>>> &schematic_number_loc_info)
{
    int number = 0;
    for (int i = start; i <= end; i++)
    {
        number = number * 10 + (input[curr_line][i] - '0');
    }

    // top-left
    if ((start > 0) && (0 < curr_line))
        schematic_number_loc_info[curr_line - 1][start - 1].push_back(number);
    // left
    if (0 < start)
        schematic_number_loc_info[curr_line][start - 1].push_back(number);
    // down-left
    if ((start > 0) && (curr_line + 1 < dimensions.first))
        schematic_number_loc_info[curr_line + 1][start - 1].push_back(number);

    for (int i = start; i <= end; i++)
    {
        if (0 < curr_line)
            schematic_number_loc_info[curr_line - 1][i].push_back(number);
        // down
        if (curr_line + 1 < dimensions.first)
            schematic_number_loc_info[curr_line + 1][i].push_back(number);
    }

    // top-right
    if ((end +1 < dimensions.second) && (0 < curr_line))
        schematic_number_loc_info[curr_line - 1][end + 1].push_back(number);
    // right
    if (end + 1 < dimensions.second)
        schematic_number_loc_info[curr_line][end + 1].push_back(number);
    // down-right
    if ((end +1< dimensions.second) && (curr_line + 1 < dimensions.first))
        schematic_number_loc_info[curr_line + 1][end + 1].push_back(number);
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

    vector<vector<vector<int>>> schematic_number_loc_info(dimensions.first, vector<vector<int>>(dimensions.second, vector<int>({})));

    int total = 0;
    int curr_line = 0;
    int start = -1;
    int end = -1;
    int gear1 = 0;
    int gear2 = 0;

    for (int curr_line = 0; curr_line < dimensions.first; curr_line++)
    {
        for (int i = 0; i < dimensions.second; i++)
        {
            char c = input[curr_line][i];
            if (isdigit(c))
            { // Element is a symbol
                if (start == -1)
                {
                    start = i;
                    end = i;
                }
                else
                {
                    end = i;
                }
            }
            else
            {
                if (start != -1)
                    update_schematic_count(curr_line, start, end, dimensions, input, schematic_number_loc_info);
                start = -1;
                end = -1;
            }
        }
        if (start != -1)
            update_schematic_count(curr_line, start, end, dimensions, input, schematic_number_loc_info);
        start = -1;
        end = -1;
    }

    for (int curr_line = 0; curr_line < dimensions.first; curr_line++)
    {
        for (int i = 0; i < dimensions.second; i++)
        {
            char c = input[curr_line][i];
            if ((c == '*') && (schematic_number_loc_info[curr_line][i].size() == 2))
            {
                gear1 = schematic_number_loc_info[curr_line][i][0];
                gear2 = schematic_number_loc_info[curr_line][i][1];
                total += gear1 * gear2;
            }
        }
    }

    cout << "The answer is: " << total << endl;

    return 0;
}