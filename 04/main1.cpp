#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

pair<vector<set<int>>, vector<vector<int>>> get_input(string input_name)
{
    vector<vector<int>> my_numbers_vec = {};
    vector<set<int>> winning_numbers_vec = {};
    string line;
    ifstream file(input_name);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<int> my_numbers;
            set<int> winning_numbers;

            int temp_num = 0;
            bool found_digit = false;
            int start_pos = line.find(":") + 2;
            int i = start_pos;

            for (; i < line.length(); i++)
            {
                if (line[i] == '|')
                {
                    i++;
                    break;
                }

                if (isdigit(line[i]))
                {
                    temp_num = 10 * temp_num + (line[i] - '0');
                    found_digit = true;
                }
                else if (found_digit)
                {
                    winning_numbers.insert(temp_num);
                    temp_num = 0;
                    found_digit = false;
                }
            }
            if (found_digit)
            {
                winning_numbers.insert(temp_num);
                temp_num = 0;
                found_digit = false;
            }
            
            for (; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    temp_num = 10 * temp_num + (line[i] - '0');
                    found_digit = true;

                }
                else if (found_digit)
                {
                    my_numbers.push_back(temp_num);
                    temp_num = 0;
                    found_digit = false;

                }
            }
            if (found_digit) my_numbers.push_back(temp_num);

            my_numbers_vec.push_back(my_numbers);
            winning_numbers_vec.push_back(winning_numbers);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open the file." << endl;
    }
    return make_pair(winning_numbers_vec, my_numbers_vec);
}

int main()
{
    string input_name = "input.txt";

    pair<vector<set<int>>, vector<vector<int>>> input = get_input(input_name);
    vector<set<int>> winning_numbers_vec = input.first;
    vector<vector<int>> my_numbers_vec = input.second;

    int total = 0;
    int hits_count = 0;

    for (int i = 0; i < winning_numbers_vec.size(); i++)
    {
        for (int j = 0; j < my_numbers_vec[i].size(); j++)
        {
            int c = my_numbers_vec[i][j];
            auto find_elem = winning_numbers_vec[i].find(c);
            if (find_elem != winning_numbers_vec[i].end())
            {
                hits_count++;
            }
        }

        if (hits_count > 0)
        {
            total += pow(2, hits_count - 1);
        }
        hits_count = 0;
    }

    cout << "The answer is: " << total << endl;

    return 0;
}
