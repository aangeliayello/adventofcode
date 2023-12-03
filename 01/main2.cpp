#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string spelled_numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

bool checkIfSubword(const string &word, const string &line, int start, bool reverse)
{
    if (word.length() > line.length())
        return false;

    for (int i = 0; i < word.length(); ++i)
    {
        char lineChar = reverse ? line[i + start - word.length() + 1] : line[i + start];
        if (word[i] != lineChar)
        {
            return false;
        }
    }

    return true;
}

int numberStringToInt(const string &line, int start, bool reverse)
{
    for (int i = 0; i < 9; ++i)
    {
        if (checkIfSubword(spelled_numbers[i], line, start, reverse))
        {
            return (i + 1);
        }
    }
    return 0;
}

int main()
{
    string line;
    ifstream file("input.txt");
    int total = 0;
    int counter = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            int line_len = line.length();

            for (int i = 0; i < line_len; ++i)
            {
                if (isdigit(line[i]))
                {
                    total += 10 * (line[i] - '0');
                    break;
                }
                else
                {
                    int spellValue = numberStringToInt(line, i, false);
                    if (spellValue != 0)
                    {
                        total += 10 * spellValue;
                        break;
                    }
                }
            }

            for (int i = 0; i < line_len; ++i)
            {
                if (isdigit(line[line_len - i - 1]))
                {
                    total += (line[line_len - i - 1] - '0');
                    break;
                }
                else
                {
                    int spellValue = numberStringToInt(line, line_len - i - 1, true);
                    if (spellValue != 0)
                    {
                        total += spellValue;
                        break;
                    }
                }
            }

            counter++;
        }

        file.close();
    }
    else
    {
        cerr << "Unable to open the file." << endl;
        return 1; // Return an error code if the file cannot be opened
    }

    cout << "The answer is: " << total << endl;
    return 0;
}
