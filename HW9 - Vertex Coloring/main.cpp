#pragma GCC optimize("Ofast")
#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

bool bfs(int s, vector<int>adj[], set<int> &res, int N)
{
          queue<int> q;
          q.push(s);
          vector<int> colors(N);
          colors[s] = 1;
          while (!q.empty())
          {
                    int u = q.front();
                    q.pop();
                    for (auto v: adj[u])
                    {
                              if (colors[v] == 0)
                              {
                                        if (colors[u] == 1)
                                                  colors[v] = 2;
                                        else
                                        {
                                                  colors[v] = 1;
                                                  res.insert(v);
                                        }
                                        q.push(v);
                              }
                              else if (colors[v] == colors[u])
                                        return false;
                    }
          }
          return true;
}

int main()
{
          ifstream input("input.txt"); ofstream output("output.txt");
          int N, u, v;
          for (int t = 0; t < 2; t++)
          {
                    input >> N;
                    vector<int> adj[N];
                    set<int> res;
                    for (int i = 0; i < N; i++)
                    {
                              input >> u >> v;
                              adj[u].push_back(v);
                              adj[v].push_back(u);
                    }
                    if(bfs(0, adj, res, N))
                    {
                              output << 0;
                              for (set<int>::iterator i = res.begin(); i != res.end(); i++)
                                        output << "," << *i;
                              output << endl;
                    }
                    else output << -1 << endl;
          }
          input.close(); output.close();
          return 0;
}
