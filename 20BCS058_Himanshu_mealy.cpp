#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#define mm 100
#define pp pair<int, char>
using namespace std;
int main()
{
    ifstream fio;
    string line;
    fio.open("mealy.txt");
    unsigned int i = 0, q0;
    vector<vector<pp>> mat(mm, vector<pp>(mm, {-1, '*'}));
    if (fio.is_open())
    {
        while (fio)
        {
            getline(fio, line);
            cout << line << "\n";
            if (i == 0)
            {
                q0 = stoi(line);
            }
            else
            {
                int index = i - 1;
                unsigned int j = 0, k = 0;
                while (j < line.size())
                {
                    string temp = "";
                    int x;
                    char r;
                    while (j < line.size() && line[j] != ',')
                    {
                        temp += line[j++];
                    }
                    x = stoi(temp);
                    j++;
                    r = line[j];
                    j += 2;
                    mat[index][k] = {x, r};
                    k++;
                }
            }
            i++;
        }
    }

    cout << " Enter the input string : ";
    string input, res = "";
    getline(cin, input);

    vector<int> inn;
    i = 0;
    while (i < input.size())
    {
        string temp = "";
        while (i < input.size() && input[i] != ' ')
        {
            temp += input[i];
            i++;
        }
        inn.push_back(stoi(temp));
        i++;
    }

    int curr = q0;
    i = 0;
    while (i < inn.size() && curr != -1)
    {
        res += mat[curr][inn[i]].second;
        curr = mat[curr][inn[i]].first;
        i++;
    }

    cout << "\n Result: " << res << endl;
    fio.close();
    return 0;
}