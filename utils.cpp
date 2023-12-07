#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

vector<int> line_to_numbers(string line)
{
    vector<int> numbers = {};

    bool in_number = false;
    int temp_number = 0;

    for (int i = 0; i < line.length(); i++)
    {
        if (isdigit(line[i]))
        {
            in_number = true;
            temp_number = 10 * temp_number + (line[i] - '0');
        }
        else if (in_number)
        {
            numbers.push_back(temp_number);
            temp_number = 0;
            in_number = false;
        }
    }
    if (in_number)
    {
        numbers.push_back(temp_number);
        temp_number = 0;
        in_number = false;
    }

    return numbers;
}