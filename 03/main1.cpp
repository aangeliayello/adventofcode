#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<char> non_symbols = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

pair<int, int> getDimensions(string file_name)
{
    string line;
    ifstream file(file_name);

    int n_lines, n_chars = 0;

    if (file.is_open())
    {
        string line;
        getline(file, line);

        n_chars = line.length();
        n_lines++;

        while (getline(file, line))
        {
            if (n_chars != line.length())
            {
                cerr << "Input file is not a square!" << endl;
            }
            n_lines++;
        }
    }
    else
    {
        cerr << "Unable to open the file." << endl;
    }
    return make_pair(n_lines, n_chars);
}

int main()
{
    string input_name = "input_test.txt";

    auto dimesions = getDimensions(input_name);
    vector<vector<bool>> schematic_valid(dimesions.first, vector<bool>(dimesions.second, false));

    string line;
    ifstream file(input_name);
    int total = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            for (int i = i; i < dimesions.second; i++){
                auto find_elem = non_symbols.find(line[i]);
                if (find_elem == non_symbols.end()){ // Element is a symbol
                    
                }
            }
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open the file." << endl;
        return 1;
    }

    cout << "The answer is: " << total << endl;
    return 0;
}
