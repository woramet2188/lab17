#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &name,vector<int> &scores,vector<char> &grades){
    char format[]={"%[^:]: %d %d %d"};
    char name2[100];
    int a=0,b=0,c=0;
    ifstream source;
    source.open(filename.c_str());
    string textline;
    while(getline(source,textline)){
        sscanf(textline.c_str(),format,name2,&a,&b,&c);
        name.push_back(name2);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }

}

void getCommand(string &command,string &key){
    int key2;
    cout<<"Please input your command: ";
    getline(cin,key);
    key2 = key.find_first_of(' ');
    key.find_first_of(' ');
    command = key.substr(0,key2);
    key = key.substr(key2+1);
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int j=0;
    cout<<"---------------------------------\n";
    for(unsigned int i=0;i<names.size();i++){
        if(key == toUpperStr(names[i])){
            cout<<names[i]<<"'s score "<<"= "<<scores[i]<<"\n";
            cout<<names[i]<<"'s grade "<<"= "<<grades[i]<<"\n";
            j++;
        }

    }
    if(j==0) cout<<"Cannot found.\n";
    cout<<"---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int j=0;
    
    cout<<"---------------------------------\n";
     for(unsigned int i=0;i<scores.size();i++){
        if(key[0]==grades[i]){
            cout<<names[i]<<" "<<"("<<scores[i]<<")\n";
            j++;
        }

    }
    if(j==0) cout<<"Cannot found.\n";
    cout<<"---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
