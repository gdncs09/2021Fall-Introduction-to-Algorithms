#include <fstream>
#include <sstream>
#include <string>
#define MAX 300000

using namespace std;
ofstream output("output.txt");
class node
{
public:
          string key, value;
          node *left, *right;
};

node *newNode(string key, string value)
{
          node *Node = new node();
          Node->key = key;
          Node->value = value;
          Node->left = Node->right = NULL;
          return (Node);
}

node *rightRotate(node *x)
{
          node *y = x->left;
          x->left = y->right;
          y->right = x;
          return y;
}

node *leftRotate(node *x)
{
          node *y = x->right;
          x->right = y->left;
          y->left = x;
          return y;
}

node *splay(node *root, string key)
{
          if (root == NULL || root->key == key)
                    return root;

          if (root->key > key)
          {
                    if (root->left == NULL)
                              return root;

                    if (root->left->key > key) //Zig-Zig
                    {
                              root->left->left = splay(root->left->left, key);
                              root = rightRotate(root);
                    }
                    else if(root->left->key < key) //Zig-Zag
                    {
                              root->left->right = splay(root->left->right, key);
                              if (root->left->right != NULL)
                                        root->left = leftRotate(root->left);
                    }
                    return(root->left == NULL)? root: rightRotate(root);
          }
          else
          {
                    if (root->right == NULL)
                              return root;

                    if (root->right->key > key) //Zig-Zag
                    {
                              root->right->left = splay(root->right->left, key);
                              if (root->right->left != NULL)
                                        root->right = rightRotate(root->right);
                    }
                    else if (root->right->key < key) //Zag-Zig
                    {
                              root->right->right = splay(root->right->right, key);
                              root = leftRotate(root);
                    }
                    return (root->right == NULL)? root:leftRotate(root);
          }
}

node *insert_key(node *root, string k, string v, char *check)
{
          if (root == NULL)
                    return newNode(k, v);

          root = splay(root, k);

          if (root->key == k)
          {
                    *check = 'F';
                    return root;
          }

          node *newnode = newNode(k, v);
          if (root->key > k)
          {
                    newnode->right = root;
                    newnode->left = root->left;
                    root->left = NULL;
          }
          else
          {
                    newnode->left = root;
                    newnode->right = root->right;
                    root->right = NULL;
          }
          return newnode;
}

node *find_key(node *root, string key)
{
          return splay(root, key);
}

node *erase_key(node *root, string key, char *check)
{
          node *tmp;
          if (root == NULL)
          {
                    *check = 'F';
                    return NULL;
          }

          root = splay(root, key);

          if (root->key != key)
          {
                    *check = 'F';
                    return root;
          }

          if (root->left == NULL)
          {
                    tmp = root;
                    root = root->right;
          }
          else
          {
                    tmp = root;
                    root = splay(root->left, key);
                    root->right = tmp->right;
          }
          delete tmp;
          return root;
}

void _clear_tree(node *root)
{
          if (root == NULL)
                    return;
          _clear_tree(root->left);
          _clear_tree(root->right);
          delete root;
}

void clear_tree(node **root_ref)
{
          _clear_tree(*root_ref);
          *root_ref = NULL;
}

void inOrder(node *root, string high_key, char *check)
{
          if (root == NULL || *check == 'T')
                    return;

          inOrder(root->left, high_key, check);
          if (*check == 'F')
                    output << "ENUM " << root->key << ":" << root->value << endl;
          else return;
          if (root->key == high_key)
          {
                    *check = 'T';
                    return;
          }
          inOrder(root->right, high_key, check);
}

int main()
{
          node *root = NULL;
          string line, command, first, second;
          int count = 0;
          ifstream input("input.txt");
          while (getline(input, line))
          {
                    stringstream ss(line);
                    ss >> command;
                    count++;
                    switch (command[2])
                    {
                    case 'S': //INSERT
                              {
                                        ss >> first; //first = key
                                        first.erase(first.begin(), first.begin()+4);
                                        ss >> second; //second = value
                                        second.erase(second.begin(), second.begin()+6);
                                        char check = 'T';
                                        if (count <= MAX)
                                                  root = insert_key(root, first, second, &check);
                                        if (check == 'F' || count > MAX)
                                                  output << "INSERT " << first << " FAIL!" << endl;
                                        else
                                                  output << "INSERT " << first << " SUCCESS!" << endl;
                                        break;
                              }
                    case 'N': //FIND
                              {
                                        ss >> first; //first = key
                                        first.erase(first.begin(), first.begin()+4);
                                        root = find_key(root, first);
                                        if (root == NULL || root->key != first)
                                                  output << first << " NOT FOUND!" << endl;
                                        else
                                                  output << "FIND " << root->key << ":" << root->value << "!" << endl;
                                        break;
                              }
                    case 'A': //ERASE
                              {
                                        ss >> first;
                                        first.erase(first.begin(), first.begin()+4);
                                        char check = 'T';
                                        root = erase_key(root, first, &check);
                                        if (check == 'F')
                                                  output << "ERASE " << first << " FAIL!" << endl;
                                        else
                                                  output << "ERASE " << first << " SUCCESS!" << endl;
                                        break;
                              }
                    case 'U': //ENUM
                              {
                                        ss >> first;
                                        first.erase(first.begin(), first.begin()+4);
                                        ss >> second;
                                        second.erase(second.begin(), second.begin()+4);

                                        if (root != NULL)
                                        {
                                                  root = find_key(root, second);
                                                  if (root->key != second)
                                                  {
                                                            node *x;
                                                            x = root;
                                                            while (x != NULL)
                                                            {
                                                                      if (x->right == NULL)
                                                                                second = x->key;
                                                                      x = x->right;
                                                            }
                                                  }
                                                  root = find_key(root, first);
                                                  char check = 'F';
                                                  if (root->key != first)
                                                  {
                                                            node *x;
                                                            x = root;
                                                            while (x != NULL)
                                                            {
                                                                      if (x->left == NULL)
                                                                                first = x->key;
                                                                      x = x->left;
                                                            }
                                                            root = splay(root, first);
                                                  }
                                                  output << "ENUM " << root->key << ":" << root->value << endl;
                                                  if (first != second)
                                                            inOrder(root->right, second, &check);
                                        }
                                        break;
                              }
                    case 'E': //CLEAR
                              {
                                        clear_tree(&root);
                                        break;
                              }
                    }
          }
          input.close();
          output.close();
          return 0;
}
