// Include practico para compilar con geany: puede ser necesario borrarlo en otros entornos.
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <unordered_map>
#define forn(i,N) for(int i = 0; i < int(N); i++)

using namespace std;

const int maxn = 1000;

unordered_map<char,int> amounts;
unordered_map<string,bool> checked;

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
  int sum = 0;
  forn(i,s.size()){
    amounts.insert({s[i],0});
  }
  string test;
  forn(i,s.size()-1){
    test.clear();
    int high = maxn - sum;
    int low = 0;
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
  }
  amounts[s.back()] = N - sum;
}

/// checks in the most efficient way I could come up with if a string is valid
bool checkTree(string c){
  //cout << "checkTree(" << c << ")" << endl;
  /// if already checked, return it
  if(checked.find(c) != checked.end() || c.size() < 2){
    assert(c.size() > 0);
    return true;
  }
  /// call the check on first half of string and second half of string
  /// if both are true, store medir(c), else store false and return it
  //cout << fh << "/" << sh << endl;
  if(checkTree(c.substr(0,c.size()/2)) && checkTree(c.substr(c.size()/2))){
    checked.insert({c,medir(c)});
    return checked[c];
  }
  return false;
}

string mergeString(string a, string b){
  //cout << "Started mergestring with " << a << " and " << b << "\n----------------\n";
  if(a.size() == 0){
    //cout << "First string was empty...\n";
    return b;
  }
  if(b.size() == 0){
    //cout << "Second string was empty...\n";
    return a;
  }
  //cout << "b_iterator = " << b.size()-1 << endl << "a_iterator = " << a.size() << endl << endl; 
  int bit = b.size()-1;
  for(int ait = a.size(); bit >= 0 && ait >= 0; bit--){
    //cout << a << endl;
    a.insert(ait,b,bit,1);
    //cout << a << endl << "-------" << endl;
    for(;!checkTree(a);){
      //cout << "loop, a = ";
      ait--;
      char aux = a[ait];
      a[ait] = a[ait+1];
      a[ait+1] = aux;
      //cout << a << endl;
    }
  }
  if(bit > 0){
    a.insert(0,b,0,bit);
  }
  return a;
}

string splitMergers(vector<string> &m, int low, int high){
  //cout << "splitMergers : low = " << low << " high " << high << endl;
  if(high <= low + 1){
    return m[low];
  }
  return mergeString(splitMergers(m,low,(low+high)/2),splitMergers(m,((low+high)/2),high));
}

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
  vector<string> mergers;
  forn(i,s.size()){
    mergers.push_back(string(amounts[s[i]],s[i]));
  }
  /*for(const auto &a : checked){
    cout << a.first << " : " << a.second << endl;
  }
  for(const auto &a : mergers){
    cout << a << endl;
  }
  */
  return splitMergers(mergers,0,mergers.size());
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
