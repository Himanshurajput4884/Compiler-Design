#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define mm 100
using namespace std;

vector<int> convertt(string s){
	vector<int> res;
	int i=0;
	while(i<s.size()){
		string temp = "";
		while(i<s.size() && (s[i]!=' ')){
			temp += s[i];
			i++;
		}
		if(temp.size()){
			res.push_back(stoi(temp));
		}
		i++;
	}
	return res;
}

int main(){
	ifstream fio;
	string line;

	fio.open("dfa.txt");
	int i=0, q0;
	vector<int> states;
	vector<vector<int> > mat(mm, vector<int>(mm, -1));
	if(fio.is_open()){
		while(fio){
			getline(fio, line);
			if(i==0){
				q0 = stoi(line);
			}
			else if(i==1){
				states = convertt(line);
							}
			else{
				int index = i-2;
				vector<int> temp = convertt(line);
				for(int j=0; j<temp.size(); j++){
					mat[index][j] = temp[j];
				}
			}
			i++;	
		}
	}
	string input;
	cout << "\n Enter the input string : ";
	getline(cin, input);

	vector<int> inn = convertt(input);

	int j=0, curr = q0;
	while(j<inn.size() && curr != -1){
		curr = mat[curr][inn[j]];
		j++;
	}
	bool is_true = false;
	for(auto a : states){
		if(curr == a){
			is_true = true;
			break;
		}
	}

	if((curr == -1 || j<inn.size()) || !is_true){
		cout << "Not accepted\n";
	}
	else{
		cout << "Accepted\n";
	}

	fio.close();

	return 0;
}
