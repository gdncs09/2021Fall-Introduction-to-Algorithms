#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
          int N;
          string line;
          ifstream input;
          ofstream output;
          input.open("input.txt", ios::in);
          output.open("output.txt", ios::out);
          input >> N;
          while (getline(input, line))
          {
                    vector <int> seq;
                    int value;
                    istringstream ss(line);
                    while (ss >> value)
                    {
                              seq.push_back(value);
                    }
                    sort(seq.begin(), seq.end());
                    for (vector <int>::size_type i = 0, size = seq.size(); i < size; i++)
                    {
                              output << seq[i] << " ";
                    }
                    output << "\n";
          }
          input.close();
          output.close();
          return 0;
}
