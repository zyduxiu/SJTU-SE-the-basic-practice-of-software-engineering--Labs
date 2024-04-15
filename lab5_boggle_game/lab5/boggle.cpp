#include "lexicon.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
int size1;
char **map;
int score;
int autoscore;
vector<string> yourwords;
vector<string> autowords;
Lexicon dictionary("../EnglishWords.txt");
int removing(vector<string>a,string str){
    transform(str.begin(),str.end(),str.begin(),::toupper);
    for(int i=0;i<a.size();i++){
        if(a[i]==str){
           return i;
        }
    }
    return -1;
}
void automode(){
    if(autowords.size()==0){
        cout<<"Computer Score: "<<0<<endl;
        cout<<"Computer Words: ";
    }
    else {
        cout << "Computer Score: " << autoscore << endl;
        cout << "Computer Words: ";
        for (int i = 0; i < autowords.size() - 1; i++) {
            for (int j = 0; j < autowords.size() - i - 1; j++) {
                if (autowords[j] > autowords[j + 1]) {
                    string tmp;
                    tmp = autowords[j];
                    autowords[j] = autowords[j + 1];
                    autowords[j + 1] = tmp;
                }
            }
        }
        for (int i = 0; i < autowords.size(); i++) {
            cout << autowords[i] << " ";
        }
        cout << endl;
    }
}
bool containing2(vector<string>a,string str){
    for(int i=0;i<a.size();i++){
        transform(a[i].begin(),a[i].end(),a[i].begin(),::tolower);
        transform(str.begin(),str.end(),str.begin(),::tolower);
        if(a[i]==str){
            return true;
        }
    }
    return false;
}
bool containing(vector<string>a,string str){
    transform(str.begin(),str.end(),str.begin(),::toupper);
    for(int i=0;i<a.size();i++){
        if(a[i]==str){
            return true;
        }
    }
    return false;
}
void autodetect(string a,bool** b,int q=0,int t=0){
    if(q<0||q>=size1||t<0||t>=size1)return;
    if(b[q][t]==false)return;
    a+=map[q][t];
    if(a.length()>=4&&dictionary.contains(a)){
        if(!containing(autowords,a)) {
            autowords.push_back(a);
            autoscore+=a.length()-3;
        }
    }
    if(dictionary.containsPrefix(a)) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    b[q][t] = false;
                    autodetect(a, b, q + i, t + j);
                    b[q][t] = true;
                }
            }
        }
    }
}
void showmap(){
    for(int i=0;i<size1;i++){
        for(int j=0;j<size1;j++){
            cout<<map[i][j];
        }
        cout<<endl;
    }
}
void showscore(){
    cout<<"Your Score: "<<score<<endl;
}
void showyourword(){
    cout<<"Your Words: ";
    for(int i=0;i<yourwords.size();i++){
        transform(yourwords[i].begin(),yourwords[i].end(),yourwords[i].begin(),::tolower);
        cout<<yourwords[i]<<" ";
    }
    cout<<endl;
}
int main() {
    cin >> size1;
    char test;
  map=new char*[size1];
  for(int i=0;i<size1;i++){
      map[i]=new char[size1];
  }
  for(int i=0;i<size1;i++){
      for(int j=0;j<size1;j++){
          char tmp;
          cin>>tmp;
          map[i][j]=tmp;
      }
  }
  showmap();
  showscore();
  showyourword();
    for(int i=0;i<size1;i++){
        for(int j=0;j<size1;j++){
            bool **b;
            b = new bool *[size1];
            for (int q = 0; q < size1; q++) {
                b[q] = new bool[size1];
            }
            for (int q = 0; q < size1; q++) {
                for (int t = 0; t < size1; t++) {
                    b[q][t] = 1;
                }
            }
            string c="";
            autodetect(c,b,i,j);
        }
    }
    char a=cin.get();
  while(true){
      string tmp;
      getline(cin,tmp);
      if(tmp=="???"){
          automode();
          break;
      }transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
      if(tmp.length()<=3){
          cout<<tmp<<" "<<"is too short."<<endl;
      }
      else if(containing(autowords,tmp)){
          autowords.erase(autowords.begin()+removing(autowords,tmp));
          autoscore-=tmp.length()-3;
          transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
          yourwords.push_back(tmp);
          score+=tmp.length()-3;
      }
      else if(containing2(yourwords,tmp)){
          cout<<tmp<<" "<<"is already found."<<endl;
      }
      else if(dictionary.contains(tmp)){
          cout<<tmp<<" "<<"is not on board."<<endl;
      }
      else{
          cout<<tmp<<" "<<"is not a word."<<endl;
      }
      showmap();
      showscore();
      showyourword();
  }
  return 0;
}
