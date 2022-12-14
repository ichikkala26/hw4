#include "equal-paths.h"
using namespace std;
#include <iostream>


// You may add any prototypes of helper functions here

int calculatePathLength(Node* root)
{
  if(root == nullptr) 
  {
    return 0;
  }


  int pathLeft = calculatePathLength(root->left);
  int pathRight = calculatePathLength(root->right);


  if(root->left!=nullptr || root->right!=nullptr)
  {
    pathLeft++;
    pathRight++;
  }

  if(pathLeft==pathRight)
  {
    return pathLeft;
  }


  return -1;

}

bool equalPaths(Node* root)
{
    int path = calculatePathLength(root);
    if(path==-1)
    {
      return false;
    }

  return true;
}

