#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <map>
#include <string>
#include <set>
#include <vector>
#define mm 5
using namespace std;
char Start;
set<char> variables;
set<char> terminals;

set<char> Cal_First(char x, map<char, vector<string>> &mp)
{
    set<char> res;
    if (terminals.find(x) != terminals.end())
    {
        res.insert(x);
        return res;
    }
    vector<string> tt = mp[x];
    for (auto a : tt)
    {
        if ((a[0] >= 'A' && a[0] <= 'Z'))
        {
            set<char> temp = Cal_First(a[0], mp);
            for (auto e : temp)
            {
                res.insert(e);
            }
        }
        else
        {
            res.insert(a[0]);
        }
    }
    return res;
}

set<char> Cal_Follow(char x, map<char, vector<string>> &mp)
{
    set<char> res;
    if (x == Start)
    {
        res.insert('$');
    }
    for(auto a : mp){
        for(auto vv : a.second){
            for(int i=0; i<vv.size(); i++){
                if(x == vv[i]){
                    if(i == vv.size()-1 && (x!=a.first)){
                        set<char> tempp = Cal_Follow(a.first, mp);
                        for(auto qq : tempp){
                            if(qq != '#'){
                                res.insert(qq);
                            }
                        }
                    }
                    else{
                        if(vv[i+1]>='A' && vv[i+1]<='Z'){
                            set<char> tempp = Cal_First(vv[i+1], mp);
                            bool is_epilson = false;
                            for(auto qq : tempp){
                                if(qq == '#'){is_epilson = true;}
                                else{res.insert(qq);}
                            }
                            if(is_epilson){
                                int j = i+2;
                                while(is_epilson && j<vv.size()){
                                    set<char> temp2 = Cal_First(vv[j], mp);
                                    is_epilson = false;
                                    for(auto qq2 : temp2){
                                        if(qq2 == '#'){is_epilson = true;}
                                        else{
                                            res.insert(qq2);
                                        }
                                    }
                                }
                                if(j == vv.size()){
                                    set<char> tempp = Cal_First(a.first, mp);
                                    for(auto qq : tempp){
                                        if(qq != '#'){
                                            res.insert(qq);
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            res.insert(vv[i+1]);
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main()
{
    ifstream fio;
    string line;

    fio.open("first_follow.txt");

    map<char, vector<string>> mp;
    int k = 0;
    if (fio.is_open())
    {
        while (fio)
        {
            getline(fio, line);
            // cout << line << endl;
            if (k == 0)
            {
                Start = line[0];
            }
            int i = 0;
            for (auto a : line)
            {
                if (!(a >= 'A' && a <= 'Z') && (a != ' ' && a!='#'))
                {
                    terminals.insert(a);
                }
            }
            string temp2 = "";
            i += 2;
            while (i < line.size())
            {
                temp2 += line[i++];
            }
            variables.insert(line[0]);
            mp[line[0]].push_back(temp2);
            k++;
        }
    }

    cout << "\n First of: \n";
    for (auto v : variables)
    {
        cout << v << " ->  { ";
        set<char> res = Cal_First(v, mp);
        for (auto z : res)
        {
            cout << z << "  ";
        }
        cout << "}  \n";
    }
    for(auto t : terminals){
        cout << t << " -> { " << t << " }\n";
    }

    cout << "\n Follow:  \n";

    for(auto v : variables){
        cout << v << " -> { ";
        set<char> res = Cal_Follow(v, mp);
        for (auto z : res)
        {
            cout << z << "  ";
        }
        cout << "}  \n";
    }

    fio.close();

    return 0;
}