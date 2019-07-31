#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <time.h>
#define forn(i,N) for(int i = 0; i < int(N) ; i++)

const int maxm = 1e4;
const int maxn = 1e3+1;

using namespace std;

struct edge{
  int target;
  long long weight;
  bool operator <(const edge b) const {
    return b.weight < weight;
  }
};

/// adjacency list
vector<edge> G[maxn];
priority_queue<edge> Q;
int V[maxn][maxn];

vector<long long> gps(int N,int M,int inicio,int fin,int K,vector<int> from,vector<int> to,vector<int> in){
  vector<long long> answer;
  /// random bolsa
  /// make adjacency list
  forn(i,M){
    G[from[i]].push_back({to[i], in[i]});
  }
  /// push starting point with distance 0
  /// null => start : in 0
  Q.push({inicio,0});
  while(Q.size()){
    //cout << Q.size() << endl;
    /// pop smaller
    edge top;
    top = Q.top();
    Q.pop();
    /// push if target
    if(top.target == fin && int(answer.size()) < K){
      answer.push_back(top.weight);
    }
    /// push neighbors
    forn(i,G[top.target].size()){
      /// push the current point's (top.target) neighbors and its distance to beginning (current + next)
      /// maximum K pushes for a given edge
      /*cout << "current edge {" << top.target << "," << G[top.target][i].target << "} visited: " << V[top.target][G[top.target][i].target]+1 << " times\n";
      if(V[top.target][G[top.target][i].target]+1 == K){
        cout << "will stop using this edge\n";
      }*/
      if(V[top.target][G[top.target][i].target] < K){
        Q.push( {G[top.target][i].target , G[top.target][i].weight + top.weight} );
        V[top.target][G[top.target][i].target]++;
      }
    }
  }
  return answer;
}

void gen(){
  srand (time(NULL));
  cout << maxn - 1 << " " << maxm << endl;
  cout << "1 1000" << endl << "1000" << endl;
  forn(i,maxm){
    int from = (rand() % 1000) + 1;
    int to = (rand() % 1000) + 1;
    if(to == from){
      to++;
      to = (to % 1000) + 1;
    }
    int weight = rand() % 1000000;
    cout << from << " " << to << " " << weight << endl;
  }
}

int main()
{
  freopen("in.txt","r",stdin);
  /*freopen("in.txt","w",stdout);
  gen();
  exit(1);
  */int N, M, inicio, fin, K;
  vector<int> from, to, in;
  cin >> N >> M;
  cin >> inicio >> fin;
  cin >> K;
  forn(i,M){
    int a;
    cin >> a;
    from.push_back(a);
    cin >> a;
    to.push_back(a);
    cin >> a;
    in.push_back(a);
  }

  vector<long long> answer = gps(N,M,inicio,fin,K,from,to,in);
  forn(i,answer.size()){
    cout << answer[i] << " ";
  }
  return 0;
}
