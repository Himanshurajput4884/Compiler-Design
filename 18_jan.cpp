#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define mm 100
using namespace std;

int stoi(string s){
	int res = 0;
	bool is_neg = false;
	int i=0;
	if(s[0]=='-'){
		is_neg = true;
		i=1;
	}
	while(i<s.size()){
		res = res*10 + (s[i]-'0');
		i++;
	}
	if(is_neg){
		res = -res;
	}
	return res;
}


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
		// cout << "open\n";
		while(fio){
			getline(fio, line);

			// cout << line << endl;
			if(i==0){
				q0 = stoi(line);
				cout << q0 << endl;;
			}
			else if(i==1){
				states = convertt(line);
				for(int k=0; k<states.size(); k++){
					cout << states[k] << " "; 
				} 
				cout<<"\n";
			}
			else{
				int index = i-2;
				vector<int> temp = convertt(line);
				for(int j=0; j<temp.size(); j++){
					mat[index][j] = temp[j];
				}
				for(int k=0; k<temp.size(); k++){
					cout << temp[k] << " "; 
				}
				cout << "\n";
			}
			i++;	
		}
	}
	cout<<"\n\n";

	// for(int i=0; i<10; i++){
	// 	for(int j=0; j<10; j++){
	// 		cout << mat[i][j] << "  ";
	// 	}
	// 	cout << "\n";
	// }

	string input;
	cout << "\n Enter the input string : ";
	cin>>input;

	vector<int> inn = convertt(input);

	// for(int i=0; i<inn.size(); i++){
	// 	cout << inn[i] <<"  ";
	// }

	int j=0, curr = q0;
	while(j<inn.size() && curr != -1){
		curr = mat[curr][inn[j]];
		j++;
	}

	if(curr == -1 || j<inn.size()){
		cout << "Not accepted\n";
	}
	else{
		cout << "Accepted\n";
	}

	fio.close();

	return 0;
}