// Include practico para compilar con geany: puede ser necesario borrarlo en otros entornos.
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <assert.h>
#include <unordered_map>
#define forn(i,N) for(int i = 0; i < int(N); i++)

using namespace std;

const int maxn = 1000;

unordered_map<char,int> amounts;

string secret;
int preguntas = 0;

int medir(string cad)
{
  //cout << "!!!\nmedir was called = " << cad << "\n!!!\n";
  preguntas++;
  int i=0;
  for (int j=0;j<int(secret.size()); j++)
  if (i < int(cad.size()) && cad[i] == secret[j])
    i++;
  return i == int(cad.size());
}

void letter_amount(int N, string s){
  cout << "SIZE = " << N;
  int sum = 0;
  forn(i,s.size()){
    amounts.insert({s[i],0});
  }
  string test;
  forn(i,s.size()-1){
    test.clear();
    int high = N - sum;
    int low = 0;
    cout << "high : " << high << " low : " << low << endl;
    // if there is 1 letter unknown, each of the untested letters has to be tested at least once
    // until there are no letters left, then nothing will happen for real
    if(high == 1){
      test.push_back(s[i]);
      sum += amounts[s[i]] = medir(test);
      //cout << "There is " << amounts[s[i]] << " repetition of " << s[i] << endl;
    }
    else{
      while(high > low+1){
        int m = (high+low)/2;       
        test.resize(m,s[i]);
        if(medir(test)){
          low = m;
        }
        else{
          high = m;
        }
      }
      sum += amounts[s[i]] = low;
      //cout << "There are " << low << " repetitions of " << s[i] << endl;
    }
  }
  amounts[s.back()] = N - sum;
  for(auto &a : amounts){
    if(a.second)
    cout << a.first << " : " << a.second << endl;
  }
}

string mergeString(string a, string b){
  cout << "Started mergestring with " << a << " and " << b << "\n----------------\n";
  if(a.size() == 0){
    cout << "First string was empty...\n";
    return b;
  }
  if(b.size() == 0){
    cout << "Second string was empty...\n";
    return a;
  }
  cout << "b_iterator = " << b.size()-1 << endl << "a_iterator = " << a.size() << endl << endl; 
  int bit = b.size()-1;
  for(int ait = a.size(); bit >= 0 && ait >= 0; bit--){
    cout << a << endl;
    a.insert(ait,b,bit,1);
    cout << a << endl << "-------" << endl;
    for(;!medir(a);){
      cout << "loop, a = ";
      ait--;
      char aux = a[ait];
      a[ait] = a[ait+1];
      a[ait+1] = aux;
      cout << a << endl;
    }
  }
  if(bit > 0){
    a.insert(0,b,0,bit);
  }
  return a;
}

struct Comparator{
  bool operator ()(const string &a, const string &b) const {
    return a.size() > b.size();
  }
};

string secuenciar(int N, string s)
{
  letter_amount(N,s);
  string answer;
  if(s == "AC"){
    forn(i,s.size()){
      forn(j,amounts[s[i]]){
        answer.push_back(s[i]);
      }
    }
    return answer;
  }
  priority_queue<string,vector<string>,Comparator> mergers;
  forn(i,s.size()){
    mergers.push(string(amounts[s[i]],s[i]));
  }
  for(;mergers.size() > 1;){
    //cout << "FOR\n";
    string first = mergers.top();
    //cout << first << endl;
    mergers.pop();
    string second = mergers.top();
    //cout << second << endl;
    mergers.pop();
    mergers.push(mergeString(first,second));
  }
  return mergers.top();
}

int main()
{
  string s;
  freopen("in.txt","r",stdin);
  getline(cin, s);
  getline(cin, secret);
  string resultado = secuenciar(int(secret.size()), s);

  if (resultado != secret)
  {
    cout << "Resultado erroneo: " << resultado << endl;
  }
  else
  {
    cout << "Se adivino con exito!!" << endl;
    cout << preguntas << " preguntas realizadas." << endl;
  }
  return 0;
}
