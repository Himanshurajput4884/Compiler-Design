#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#define mm 5
using namespace std;

int main(){
	ifstream fio;
	string line;

	fio.open("dfa.txt");
	int i=0, q0;
    map<int,string> mp;
	vector<vector<int> > mat(mm, vector<int>(mm, -1));
	if(fio.is_open()){
		while(fio){
			getline(fio, line);
			if(i==0){
				q0 = stoi(line);
				cout << q0 << endl;;
			}
			else{
				int index = i-1;
                int j=0, k=0;
                while(j<line.size()){
                    string temp="";
                    while(j<line.size() && line[j]!=' '){
                        temp += line[j];
                        j++;
                    }
                    if(temp[0]>='0' && temp[0]<='9'){
                        mat[index][k] = stoi(temp);
                    }

                    else{
                        mp[index] = temp;
                    }
                    j++;
                    k++;
                }
				cout << "\n";
			}
			i++;	
		}
	}
	cout<<"\n\n";

	// for(int i=0; i<mm; i++){
	// 	for(int j=0; j<mm; j++){
	// 		cout << mat[i][j] << "  ";
	// 	}
	// 	cout << mp[i] <<"\n";
	// }

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

    int curr = q0; i=0;
    res += mp[curr];
    while(i<inn.size() && curr != -1){
        curr = mat[curr][inn[i]];
        res += mp[curr];
        i++;
    }

    if(curr == -1){
        cout << "Invalid Input\n";
    }
    else{
        cout << " Result: " << res <<endl;
    }

	fio.close();

	return 0;
}