#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

int medir(string s);



struct comparator_string {
    bool operator()(const string& a, const string& b) const {
      return a.size() > b.size();
    }
};

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

string secuenciar ( int N, string s ) {

  if(s == "AC"){
    auto res = num_occur('A', N);
    return res + string(N-res.size(), 'C');
  }

  priority_queue<string, vector<string>, comparator_string> m;
  int len = 0;

  for (int i = 0; i < s.size() - 1; ++i) {
    auto t = num_occur(s[i], N);
    m.push(t);
    len += t.size();
  }

  m.push(string(N-len, s.back()));


  while(m.size() > 1) {
    auto left_operand = m.top(); m.pop();
    auto right_operand = m.top(); m.pop();

    m.push(merge(left_operand, right_operand));
  }


  return m.top();
}
