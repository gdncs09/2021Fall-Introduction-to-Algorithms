#include <stdio.h>
#include <bitset>
#include "data.hpp"
#define LIMIT 50
#define LIMIT_DIAG 2*LIMIT-1

using namespace std;

int ans;
bitset<LIMIT> hori;
bitset<LIMIT> vert;
bitset<LIMIT_DIAG> diag_right; //row-col+N-1
bitset<LIMIT_DIAG> diag_left; //row+col

void Nqueen(int N, int row)
{
          if (hori[row]==0)
          {
                    for (int col = 0; col < N; col++)
                    {
                              if (vert[col]==0 && diag_right[row-col+N-1]==0 && diag_left[col+row]==0)
                              {
                                        if (row+1==N)
                                                  ans++;
                                        else
                                        {
                                                  vert[col]=1; diag_right[row-col+N-1] = 1; diag_left[col+row] = 1;
                                                  Nqueen(N, row+1);
                                                  vert[col]=0; diag_right[row-col+N-1] = 0; diag_left[col+row] = 0;
                                        }
                              }
                    }
          }
          else
          {
                    if (row+1==N)
                              ans++;
                    else Nqueen(N, row+1);
          }
}

void solve(tTestData* test_data)
{
          FILE* fout = fopen("output.txt", "w");
          int T, N, M, row, col;
          for (int i = 0, T = test_data->t; i < T; i++)
          {
                    ans = 0;
                    N = test_data->testcase[i].n;
                    M = test_data->testcase[i].m;
                    for (int k = 0; k < M; k++)
                    {
                              row = test_data->testcase[i].preplace[k][0];
                              col = test_data->testcase[i].preplace[k][1];
                              hori[row] = 1; //True 1 False 0
                              vert[col] = 1; //True 1 False 0
                              diag_right[row-col+N-1] = 1; //True 1 False 0
                              diag_left[row+col] = 1; //True 1 False 0
                    }
                    Nqueen(N, 0);
                    hori.reset();
                    vert.reset();
                    diag_right.reset();
                    diag_left.reset();
                    fprintf(fout, "%d\n", ans);
          }
          fclose(fout);
          return;
}
