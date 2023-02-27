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
    fio.open("nfa_to_dfa.txt");
    unsigned int i = 0, ss=0;
    map<string, map<string,string>> mat;
    string start="";
    set<string> final;
    if (fio.is_open())
    {
        while (fio)
        {
            getline(fio, line);
            if (i == 0)
            {
                start = line;
            }
            else if(i==1){
                unsigned int j=0;
                while(j<line.size()){
                    string temp = "";
                    while(j<line.size() && line[j]!=' '){
                        temp += line[j++];
                    }
                    j++;
                    final.insert(temp);
                }
            }
            else
            {
                string index = to_string(i-2);
                unsigned int j = 0, k = 0;
                while(j<line.size()){
                    string temp = "", input = to_string(k);
                    while(j<line.size() && line[j]!=' '){
                        temp += line[j++];
                    }
                    j++;
                    mat[index][input] = temp;
                    k++;
                }
                if(i==3){ss = k;
                
                }
            }
            i++;
        }
    }

    cout << "NFA is : \n";
    for(auto &a : mat){
        cout << a.first << " ->  ";
        for(auto &x : a.second){
            cout << x.second << "\t";
        }
        cout << "\n";
    }

    map<string, map<string,string> > dfa;
    for(int i=0; i<ss; i++){
        string input = to_string(i);
        dfa["trap"][input] = "trap";
    }
    set<string> dfa_final;
    set<string> visit;
    queue<string> q;
    bool is_trap = false;
    q.push(start);
    visit.insert(start);
    while(!q.empty()){
        int x = q.size();
        while(x--){
            string state = q.front();
            q.pop();
            bool is_final = false;
            int i=0;
            while(i < state.size()){
                if(state[i]==','){state.erase(state.begin()+i);}
                else{i++;}
            }
            for(i=0; i<ss; i++){
                string input = to_string(i);
                string new_state;
                for(auto a : state){
                    string tt = ""; tt+=a;
                    if(final.find(tt) != final.end()){
                        is_final = true;
                    }
                    string next = mat[tt][input];
                    if(next != "-1"){new_state+=next;}
                }
                if(is_final){dfa_final.insert(state);}
                if(!new_state.size()){
                    is_trap = true;
                    dfa[state][input] = "trap";
                }
                else{
                    int k=0;
                    while(k < new_state.size()){
                    if(new_state[k]==','){new_state.erase(new_state.begin()+k);}
                        else{k++;}
                    }
                    sort(new_state.begin(), new_state.end());
                    new_state.erase(unique(new_state.begin(), new_state.end()), new_state.end());
                    dfa[state][input] = new_state;
                    if(visit.find(new_state) == visit.end()){
                        visit.insert(new_state);
                        q.push(new_state);
                    } 
                }
            }
        }
    }
    if(!is_trap){
        dfa.erase("trap");
    }

    cout << "\nDFA : \n";
    cout << "Starting state: " << start << endl;
    cout << "Final state: ";
    for(auto a : dfa_final){
        cout << a << "   ";
    }
    cout << "\n";
    for(auto &a : dfa){
        cout << "\n |\t";
        cout << a.first << "\t\t| ";
        for(auto &x : a.second){
            cout << x.second << "\t\t| ";
        }
    }
    cout << "\n\n\n";
    fio.close();
    return 0;
}
