#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct input {
    vector<int> seeds = {};
    map<pair<string, string>, int> source_destination_to_index = {};
    vector<map<int, int>> source_desinations_map = {};
};
  

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

pair<string, string> get_source_destination(string map_name)
{
    int pos_sep = map_name.find("-to-");
    int pos_end = map_name.find(" ");

    string source = map_name.substr(0, pos_sep);
    string destination = map_name.substr(pos_sep + 4, pos_end - (pos_sep + 4));

    return make_pair(source, destination);
}

void update_source_destinations_maps(int index, vector<int> map_parms, vector<map<int, int>> &source_desinations){
    for (int i = 0; i < map_parms[2]; i ++){
        source_desinations[i].insert({(map_parms[0] + i), (map_parms[1]+i) });
    }
}
vector<vector<char>> get_input(string input_name)
{
    vector<vector<char>> input = {};
    string line;
    ifstream file(input_name);
    vector<int> seeds = {};
    map<pair<string, string>, int> source_destination_map = {};
    vector<map<int, int>> source_desinations = {};
    pair<string, string> source_destination = {};
    bool map_open = false;
    vector<int> map_params;
    int source_dest_index = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            // Check if start of a new map/vector
            auto pos_semicolon = line.find(':');

            if (pos_semicolon != string::npos)
            { // Start of a new map/vec
                auto pos_sep = line.find("-to-");
                if (pos_sep != string::npos)
                { // Start of new map
                    source_destination = get_source_destination(line);
                    source_destination_map.insert({source_destination, source_dest_index});
                    map_open = true;
                }
                else
                { // Seed vector
                    seeds = line_to_numbers(line);
                    map_open = false;
                }
            } else if(!line.empty()){
                if (map_open){
                    map_params = line_to_numbers(line);
                    update_source_destinations_maps(source_destination_map[source_destination], map_params, source_desinations);
                }
            }
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

    int total, curr_line = 0;

    cout << "The answer is: " << total << endl;

    return 0;
}
