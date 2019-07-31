#include <iostream>
#include <vector>
#include <algorithm>
#define forn(i,N) for(int i = 0; i < int(N); i++)

using namespace std;

const int maxn = 3*1e5;

struct Fecha
{
  int dia, mes, anno;
  
  bool operator <(const Fecha b) const {
    return (anno > b.anno) || (anno == b.anno && mes > b.mes) || (anno == b.anno && mes == b.mes && dia > b.dia);
  }

  bool operator ==(const Fecha b) const {
    return (anno == b.anno) && (mes == b.mes) && (dia == b.dia); 
  }

  bool operator >(const Fecha b) const {
    return (anno < b.anno) || (anno == b.anno && mes < b.mes) || (anno == b.anno && mes == b.mes && dia < b.dia);
  }

};

struct anger{
  int index;
  int angery;
};

vector<Fecha> order;

bool byOrden(int a, int b){
  return order[a] < order[b];
}

bool byAnger(anger a, anger b){
  if(a.angery == b.angery)
    return a.index < b.index;
  return a.angery > b.angery;
}

int fila(vector<Fecha> orden, vector<int> &enojados)
{
  int minIndex = maxn+1;
  vector<anger> angers;
  // global variable for sorting purposes
  order = orden;
  // minIndex = 2
  // 54 7 1 9 13 6 (orden)
  // n  n 0 n n  n (answer)

  // 2 5 1 3 4 0 (index)
  vector<int> ordered;
  forn(i,orden.size()){
    ordered.push_back(i);
  }
  // de mas joven a mas viejo
  sort(ordered.begin(),ordered.end(),byOrden);
  forn(i,ordered.size()){
    minIndex = ordered[i] < minIndex ? ordered[i] : minIndex;
    if(order[minIndex] < order[ordered[i]]){
      angers.push_back({ordered[i],(ordered[i] - minIndex)});
    }
  }
  sort(angers.begin(),angers.end(),byAnger);
  forn(i,angers.size()){
    enojados.push_back(angers[i].index+1);
  }
  return angers[0].angery;
}

int main()
{
  freopen("fila.txt","r",stdin);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int C; cin >> C;
  vector<Fecha> v(C);
  for (int i=0;i<C;i++)
    cin >> v[i].dia >> v[i].mes >> v[i].anno;
  vector<int> enojados;
  cout << "Con una fila de " << C << " personas la maxima intensidad de enojo es " << fila(v, enojados) << " y su orden:" << endl;
  for (int i=0;i<int(enojados.size()); i++)
  {
    if (i) cout << " ";
    cout << enojados[i];
  }
  cout << endl;
  return 0;
}
