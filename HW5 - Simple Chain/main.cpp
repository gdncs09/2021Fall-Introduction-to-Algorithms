//#pragma GCC optimize("Ofast")
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

int run(unordered_map<int, vector<int>> vert, int N, int I)
{
          int dir = 1, index = 0, count = 0, start_value;
          if (N-1-I > I)
          {
                    I = N-1-I;
                    dir = 0;
          }
          if (dir == 1)
                    start_value = -10000001;
          else
                    start_value = 10000001;
          for (unordered_map<int, vector<int>>::iterator x = vert.begin(); x !=vert.end(); x++)
                    if (x->second.size() == 1)
                    {
                              if ((dir == 1 && x->first > start_value) || (dir == 0 && x->first < start_value))
                              {
                                        start_value = x->first;
                                        if (++count == 2) break;
                              }
                    }
          int next_value = start_value;
          while (index != I)
          {
                    index++;
                    if (vert[next_value][0] != start_value)
                    {
                              start_value = next_value;
                              next_value = vert[next_value][0];
                              continue;
                    }
                    else
                    {
                              start_value = next_value;
                              next_value = vert[next_value][1];
                              continue;
                    }
          }
          return next_value;
}

int main()
{
          ifstream input("input.txt"); ofstream output("output.txt");
          int T, N, I, u, v;
          input >> T;
          for (int t = 0; t < T; t++)
          {
                    input >> N >> I;
                    unordered_map<int, vector<int>> vert;
                    for (int n = 0; n < N-1; n++)
                    {
                              input >> u >> v;
                              vert[u].push_back(v);
                              vert[v].push_back(u);
                    }
                    output << run(vert, N, I) << endl;
          }
          input.close(); output.close();
          return 0;
}
