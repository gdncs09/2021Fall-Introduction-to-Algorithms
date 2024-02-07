#pragma GCC optimize("Ofast")
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

int calc(pair<double, double> x[], int N, int l)
{
          double now = 0;
          int i = 0, ans = 0;
          while (now < l)
          {
                    int left = -1;
                    for (; i < N; i++)
                    {
                              if (x[i].first > now)
                                        break;
                              if (x[i].second < now)
                                        continue;
                              if (left == -1 || x[left].second < x[i].second)
                                        left = i;
                    }
                    if (left == -1)
                              return -1;
                    now = x[left].second;
                    ans++;
          }
          return ans;
}

int main()
{
          ifstream input("input.txt"); ofstream output("output.txt");
          int n, l, w, p, r; // n: number of circles, l: long, w: wide, p:position, r: radius
          for (int i = 0; i < 936; i++) //936 test cases
          {
                    pair<double, double> x[10000]; //n <= 10000
                    int N = 0;
                    input >> n >> l >> w;
                    for (int i = 0; i < n; i++)
                    {
                              input >> p >> r;
                              if (r <= w/2.0) continue;
                              double  dis= sqrt(r*r - w*w/4.0);
                              if (p-dis >= l) continue;
                              x[N].first = p-dis; x[N].second = p+dis;  //first->left point, second->right point
                              N++;
                    }
                    sort(x, x+N);
                    output << calc(x, N, l) << endl;
          }
          input.close(); output.close();
          return 0;
}
