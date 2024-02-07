#include <fstream>
#include <sstream>
#include <vector>
#define ipfile "input.txt"
#define opfile "output.txt"

using namespace std;

//Sparse matrix
struct Node
{
          int row;
          int col;
          int value;
          struct Node *next;
};

struct Matrix
{
          string name;
          //int number_of_rows;
          //int number_of_cols;
          Node *head;
};

void CreateNewNode(Matrix *mt, Node *start, int row_index, int col_index, int val)
{
          Node *tmp, *r;
          start = mt->head;
          tmp = start;
          if (tmp == NULL)
          {
                    tmp = new Node();
                    tmp->row = row_index;
                    tmp->col = col_index;
                    tmp->value = val;
                    tmp->next = NULL;
                    mt->head = tmp;
          }
          else
          {
                    if ((row_index < tmp->row) || (row_index == tmp->row && col_index < tmp->col)) //add head
                    {
                              r = new Node();
                              r->row = row_index;
                              r->col = col_index;
                              r->value = val;
                              tmp = r;
                              tmp->next = start;
                              mt->head = tmp;
                    }
                    else //insert
                    {
                              Node *now = tmp->next;
                              while (now != NULL)
                              {
                                        if ((row_index > now->row || (row_index == now->row && col_index > now->col)))
                                        {
                                                  now = now->next;
                                                  tmp = tmp->next;
                                        }
                                        else break;
                              }
                              r = new Node();
                              r->row = row_index;
                              r->col = col_index;
                              r->value = val;
                              if(now != NULL) r->next = now;
                              else r->next = NULL;
                              tmp->next = r;
                    }
          }
}

void deleteList(Node **start)
{
          Node *curr = *start;
          Node *next = NULL;
          while (curr != NULL)
          {
                    next = curr->next;
                    delete(curr);
                    curr = next;
          }
          *start = NULL;
}

void PrintMatrix(Matrix mt, Node *start, string file)
{
          ofstream output(file, ios::app);
          Node *curr;
          start = mt.head;
          curr = start;
          while (curr != NULL)
          {
                    if (curr->value != 0)
                              output << "(" << curr->row << " " << curr->col << " " << curr->value << ")" << " ";
                    curr = curr->next;
          }
          output << endl;
          output.close();
}

void AddMatrix(Matrix A, Matrix B, Matrix *C)
{

          Node *nodeA = A.head;
          Node *nodeB = B.head;
          while (nodeA != NULL && nodeB != NULL)
          {
                    if (nodeA->row == nodeB->row)
                    {
                              if (nodeA->col == nodeB->col)
                              {
                                        int sum = nodeA->value + nodeB->value;
                                        CreateNewNode(C, C->head, nodeA->row, nodeA->col, sum);
                                        nodeA = nodeA->next;
                                        nodeB = nodeB->next;
                              }
                              else
                              {
                                        if (nodeA->col < nodeB->col)
                                        {
                                                  CreateNewNode(C, C->head, nodeA->row, nodeA->col, nodeA->value);
                                                  nodeA = nodeA->next;
                                        }
                                        else
                                        {
                                                  CreateNewNode(C, C->head, nodeB->row, nodeB->col, nodeB->value);
                                                  nodeB = nodeB->next;
                                        }
                              }
                    }
                    else
                    {
                              if (nodeA->row < nodeB->row)
                              {
                                        CreateNewNode(C, C->head, nodeA->row, nodeA->col, nodeA->value);
                                        nodeA= nodeA->next;
                              }
                              else
                              {
                                        CreateNewNode(C, C->head, nodeB->row, nodeB->col, nodeB->value);
                                        nodeB = nodeB->next;
                              }
                    }
          }
          while (nodeA != NULL)
          {
                    CreateNewNode(C, C->head, nodeA->row, nodeA->col, nodeA->value);
                    nodeA= nodeA->next;
          }
          while (nodeB != NULL)
          {
                    CreateNewNode(C, C->head, nodeB->row, nodeB->col, nodeB->value);
                    nodeB= nodeB->next;
          }
}

void MultMatrix(Matrix A, Matrix B, Matrix *C)
{
          Node *nodeA = A.head;
          Node *nodeB = B.head;
          Node *nodeC = C->head;
          int val;

          while (nodeA != NULL)
          {
                    while (nodeB != NULL)
                    {
                              if (nodeB->row > nodeA->col)
                                        break;
                              if (nodeA->col == nodeB->row)
                              {
                                        val = nodeA->value*nodeB->value;
                                        while(nodeC != NULL)
                                        {
                                                  if (nodeC->row > nodeA->row)
                                                            break;
                                                  if (nodeC->row == nodeA->row && nodeC->col == nodeB->col)
                                                  {
                                                            nodeC->value += val;
                                                            val = 0;
                                                  }
                                                  nodeC = nodeC->next;
                                        }
                                        if (val != 0)
                                        {
                                                  CreateNewNode(C, C->head, nodeA->row, nodeB->col, val);
                                        }
                                        nodeC = C->head;
                              }
                              nodeB = nodeB->next;
                    }
                    nodeA = nodeA->next;
                    nodeB = B.head;
          }
}

int main()
{
          ifstream input(ipfile);
          ofstream output(opfile); output.close(); //clear output file
          string line, comm, matrix, a, b;
          int row, col, val;
          vector <Matrix> table;

          while (getline(input, line))
          {
                    stringstream ss(line);
                    ss >> comm;
                    //7 kinds of commands
                    if (comm == "Matrix")
                    {
                              ss >> matrix;
                              Matrix tmp;
                              tmp.name = matrix;
                              table.push_back(tmp);
                    }
                    else if (comm == "Init")
                    {
                              ss >> matrix;
                              for (vector<int>::size_type i = 0, size = table.size(); i < size; i++)
                                        if (table[i].name == matrix)
                                        {
                                                  //ss >> row; ss >> col;
                                                  //table[i].number_of_rows = row;
                                                  //table[i].number_of_cols = col;
                                                  table[i].head = NULL;
                                                  break;
                                        }
                    }
                    else if (comm == "Assign")
                    {
                              ss >> matrix;
                              for (vector<int>::size_type i = 0, size = table.size(); i < size; i++)
                                        if (table[i].name == matrix)
                                        {
                                                  ss >> row; ss >> col; ss >> val;
                                                  CreateNewNode(&table[i], table[i].head, row, col, val);
                                                  break;
                                        }
                    }
                    else if (comm == "Print")
                    {
                              ss >> matrix;
                              for (vector<int>::size_type i = 0, size = table.size(); i < size; i++)
                                        if (table[i].name == matrix)
                                        {
                                                  PrintMatrix(table[i], table[i].head, opfile);
                                                  break;
                                        }
                    }
                    else if (comm == "Delete")
                    {
                              ss >> matrix;
                              for (vector<int>::size_type i = 0, size = table.size(); i < size; i++)
                                        if (table[i].name == matrix)
                                        {
                                                  deleteList(&table[i].head);
                                                  table.erase(table.begin()+i);
                                                  break;
                                        }
                    }
                    else if (comm == "Add")
                    {
                              ss >> a; ss >> b; ss >> matrix;
                              int a_index = 0, b_index = 0, matrix_index = 0;
                              for (vector<int>::size_type i = 0, size = table.size(); i < size; i++)
                              {
                                        if (table[i].name == a)
                                                  a_index = i;
                                        else if (table[i].name == b)
                                                  b_index = i;
                                        else if (table[i].name == matrix)
                                                  matrix_index = i;
                                        if (a_index != 0 && b_index != 0 && matrix_index !=0)
                                                  break;
                              }
                              AddMatrix(table[a_index], table[b_index], &table[matrix_index]);
                    }
                    else if (comm == "Mult")
                    {
                              ss >> a; ss >> b; ss >> matrix;
                              int a_index = 0, b_index = 0, matrix_index = 0;
                              for (vector<int>::size_type i = 0, size = table.size(); i < size; i++)
                              {
                                        if (table[i].name == a)
                                                  a_index = i;
                                        else if (table[i].name == b)
                                                  b_index = i;
                                        else if (table[i].name == matrix)
                                                  matrix_index = i;
                                        if (a_index != 0 && b_index != 0 && matrix_index !=0)
                                                  break;
                              }
                              MultMatrix(table[a_index], table[b_index], &table[matrix_index]);
                    }
          }
          input.close();
          return 0;
}
