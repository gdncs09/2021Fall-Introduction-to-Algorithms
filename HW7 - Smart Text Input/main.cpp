#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

#define MAX_SENTENCE 32769
#define MAX_WORD 129

using namespace std;

int result(set <string> dict, int M, int min_len, int max_len, string word)
{
          int n = word.size();
          if (M == 0 || n == 0)
                    return -1;
          if (dict.find(word) != dict.end())
                    return 1;
          string w;
          vector <int> dp(n+1);
          dp[0] = 0;
          for (int i = 1; i <= n; i++)
          {
                    dp[i] = MAX_SENTENCE;
                    for (int j =min(max_len, i); j >= min_len ; j--)
                    {
                              w = word.substr(i-j, j);
                              if (dict.find(w) != dict.end())
                              {
                                        dp[i] = min(dp[i], dp[i-j]+1);
                              }
                    }
          }
          if (dp[n] != MAX_SENTENCE) return dp[n];
          else return -1;
}

int main()
{
          int N, M;
          string word;
          ifstream input("input.txt"); ofstream output("output.txt");
          input >> N;
          for (int t = 1; t <= N; t++)
          {
                    input >> M;
                    int max_len = 0, min_len = MAX_WORD;
                    set <string> dict;
                    for (int i = 0; i < M; i++)
                    {
                              input >> word;
                              int w_len = word.size();
                              max_len = max(max_len, w_len);
                              min_len = min(min_len, w_len);
                              dict.insert(word);
                    }
                    input >> word;
                    output << result(dict, M, min_len, max_len, word) << endl;
          }
          input.close(); output.close();
          return 0;
}
