#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string line;
    ifstream file("input.txt");
    int total = 0;

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
            }

            for (int i = line_len - 1; i >= 0; --i)
            {
                if (isdigit(line[i]))
                {
                    total += line[i] - '0';
                    break;
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
