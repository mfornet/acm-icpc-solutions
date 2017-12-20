#include <bits/stdc++.h>

using namespace std;

bool G[100][7][7];

int main(){
  vector<string> name(100);

  int t = 0;

  for (int i = 0; i < 10; ++i){
    for (int j = 0; j < 10; ++j){
      cin >> name[t];
      int m; cin >> m;

      for (int k = 0; k < m; ++k){
        int u, v; cin >> u >> v;
        G[t][u][v] = G[t][v][u] = true;
        // cout << name[t] << " " << u << " " << v << endl;
      }

      t++;
    }
  }

  vector< vector<int> > p;

  for (int i = 0; i < 7; ++i){
    vector<int> cur(7);
    for (int j = 0; j < 7; ++j)
      cur[j] = (i + j) % 7;
    p.push_back(cur);
  }

  int n = 2;

  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j){

      for (auto per : p){

        bool ok = true;

        for (int u = 0; u < 7 && ok; ++u)
          for (int v = 0; v < 7 && ok; ++v)
            if (G[i][u][v] != G[j][ per[u] ][ per[v] ])
              ok = false;

        if (ok)
          cout << name[i] << " " << name[j] << endl;

      }

    }
}