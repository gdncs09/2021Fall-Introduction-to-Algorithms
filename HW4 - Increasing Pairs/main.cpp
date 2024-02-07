#include <fstream>
#include <vector>

using namespace std;

int BinarySearch1(vector <long long> seq, int x)
{
          int l = 0;
          int r = seq.size()-1;
          while (l <= r)
          {
                    int mid = l+(r-l)/2;
                    if (2*seq[mid] <= x && x < 2*seq[mid+1])
                              return mid;
                    else if (2*seq[mid] > x)
                              r = mid-1;
                    else l = mid+1;
          }
          return -1;
}

int BinarySearch(vector <long long> seq, int x)
{
          int l = 0;
          int r = seq.size()-1;
          while (l <= r)
          {
                    int mid = l+(r-l)/2;
                    if (seq[mid] <= x && x <= seq[mid+1])
                              return mid;
                    else if (seq[mid] > x)
                              r = mid-1;
                    else l = mid+1;
          }
          return -1;
}

int main()
{
          ifstream input("input.txt"); ofstream output("output.txt");
          int T, N, num, index;
          unsigned long long count;
          vector <long long> seq;
          input >> T;
          for (int t = 0; t < T; t++)
          {
                    input >> N;
                    count = 0;
                    input >> num;
                    seq.push_back(num);
                    for (int j = 1; j < N; j++)
                    {
                              input >> num;
                              index = -1;
                              if (num >= 2*seq.back())
                              {
                                         index = seq.size()-1;
                              }
                              else if (num >= 2*seq.front())
                              {
                                        index = BinarySearch1(seq, num);
                             }
                              count += (index + 1);
                              if (num > 1073741824)  //2^30
                                        continue;
                              if (num >= seq.back())
                              {
                                        seq.push_back(num);
                                        continue;
                              }
                              index = BinarySearch(seq, num);
                              seq.emplace(seq.begin()+ index +1, num);
                    }
                    output << count  << endl;
                    seq.clear();
          }
          input.close();
          output.close();
          return 0;
}
