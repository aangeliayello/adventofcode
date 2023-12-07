#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_map>

using namespace std;
bool compareTuples(const std::tuple<int, int>& a, const std::tuple<int, int>& b) {
    return std::get<0>(a) < std::get<0>(b);
}

enum cards
{
    TWO = 0,
    THREE = 1,
    FOUR = 2,
    FIVE = 3,
    SIX = 4,
    SEVEN = 5,
    EIGHT = 6,
    NINE = 7,
    TEN = 8,
    J = 9,
    Q = 10,
    K = 11,
    A = 12
};

enum hand_strengths
{
    HIGH_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIRS = 2,
    THREE_OF_A_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_OF_A_KIND = 5,
    FIVE_OF_A_KIND = 6,
};

map<char, cards> char_to_cards{{'2', TWO},
                               {'3', THREE},
                               {'4', FOUR},
                               {'5', FIVE},
                               {'6', SIX},
                               {'7', SEVEN},
                               {'8', EIGHT},
                               {'9', NINE},
                               {'T', TEN},
                               {'J', J},
                               {'Q', Q},
                               {'K', K},
                               {'A', A}};



hand_strengths get_hand_streng(vector<cards> hand)
{

    int max_count = 0;
    int second_max_count = 0;

    std::unordered_map<cards, int> freq;
    for (auto &i : hand)
    {
        freq[i]++;
    }

    for (auto const &[key, val] : freq)
    {
        if (val >= max_count)
        {
            second_max_count = max_count;
            max_count = val;
        }
        else if (val > second_max_count)
        {
            second_max_count = val;
        }
    }

    if (max_count == 5)
        return FIVE_OF_A_KIND;
    else if (max_count == 4)
        return FOUR_OF_A_KIND;
    else if (max_count + second_max_count == 5)
        return FULL_HOUSE;
    else if (max_count == 3)
        return THREE_OF_A_KIND;
    else if (max_count + second_max_count == 4)
        return TWO_PAIRS;
    else if (max_count == 2)
        return ONE_PAIR;

    else
        return HIGH_CARD;
}

int get_hand_value(vector<cards> hand)
{
    int value = 0;
    int multiplier = 1;

    for (int i = 0; i < 5; i++)
    {
        value += hand[4-i]*multiplier;
        multiplier *= 13;
    }

    hand_strengths hand_strength = get_hand_streng(hand);
    value += hand_strength*multiplier;

    return value;
}

vector<tuple<int, int>> get_input(string input_name)
{
    vector<tuple<int, int>> values_bids = {};

    vector<cards> current_hand(5);
    int current_bid;
    int current_hand_value;

    string line;
    ifstream file(input_name);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            // Get Hands
            for (int i = 0; i < 5; i++)
            {
                current_hand[i] = char_to_cards.at(line[i]);
            }

            current_bid = stoi(line.substr(6));
            current_hand_value = get_hand_value(current_hand);
            values_bids.push_back(make_pair(current_hand_value, current_bid));
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open the file." << endl;
    }
    return values_bids;
}

int main()
{
    vector<tuple<int, int>> values_bids = get_input("input.txt");

    sort(values_bids.begin(), values_bids.end());
    int total = 0;
    int rank = 1;
    for (const auto& tuple : values_bids) {
        total +=  get<1>(tuple)*rank;
        rank++;
    } 
    cout << "This is the sorted vector:  " << total <<endl;
    return 0;
}