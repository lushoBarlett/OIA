#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int medir ( string cad );

string num_occur ( char letra, int maximo ) {

  string secuencia;
  int izq = 0, der = maximo+1, med;
  secuencia.reserve(der);

  while( der - izq != 1) {
    med = ( der + izq ) / 2;

    secuencia.resize( med, letra );
    if( medir(secuencia) ) izq = med;
    else                   der = med;
  }

  secuencia.resize( izq, letra );
  return secuencia;
}

string merge(const string& a, const string& b) {
  string result(b);

  int insert_at = 0;

  for(int i = 0; i < a.size(); i++) {
    result.insert(insert_at++, 1, a[i]);

    while( !medir(result) ) {
      swap( result[insert_at-1], result[insert_at] );
      insert_at++;
    }
  }

  return result;
}

// string num_occur ( char letra, int maximo ) {
//   int izq = 0;
//   int der = maximo+1;
//
//   while( izq < der - 1) {
//     int med = ( der + izq ) / 2;
//
//     if( medir(string(med, letra)) )
//       izq = med;
//     else
//       der = med;
//   }
//
//   return string(izq, letra);
// }

string secuenciar ( int N, string s ) {

  if(s == "AC") {
    auto res = num_occur('A', N);
    return res + string(N-res.size(), 'C');
  }

  struct by_length { bool operator()(const string& a, const string& b) const {return a.size() > b.size();}};
  priority_queue<string, vector<string>, by_length> pq;

  int len = 0;

  for (int i = 0; i < s.size() - 1; ++i) {
    auto t = num_occur(s[i], N);
    len += t.size();
    pq.push(t);
  }

  pq.push(string(N-len, s.back()));


  while(pq.size() > 1) {
    auto left_operand = pq.top(); pq.pop();
    auto right_operand = pq.top(); pq.pop();

    pq.push(merge(left_operand, right_operand));
  }

  return pq.top();
}
