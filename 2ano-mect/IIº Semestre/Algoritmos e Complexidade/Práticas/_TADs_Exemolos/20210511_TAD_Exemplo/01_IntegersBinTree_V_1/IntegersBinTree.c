//
// Joaquim Madeira, AlgC, April 2020
//
// Adapted from an old example (ca. 2003)
//
// Integers Binary Tree --- FIRST VERSION --- INCOMPLETE
//

#include "IntegersBinTree.h"

#include <assert.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct _TreeNode
{
  ItemType item;
  struct _TreeNode *left;
  struct _TreeNode *right;
};

Tree *TreeCreate(void) { return NULL; }

void TreeDestroy(Tree **pRoot)
{
  Tree *root = *pRoot;

  if (root == NULL)
  {
    return;
  }
  TreeDestroy(&(root->left));

  TreeDestroy(&(root->right));

  free(root);

  *pRoot = NULL;
}

int TreeIsEmpty(const Tree *root) { return root == NULL; }

int TreeEquals(const Tree *root1, const Tree *root2)
{
  if (root1 == NULL && root2 == NULL)
  {
    return 1;
  }

  if (root1 == NULL || root2 == NULL)
  {
    return 0;
  }
  if (root1->item != root2->item)
  {
    return 0;
  }

  return TreeEquals(root1->left, root2->left) && TreeEquals(root1->right, root2->right);
}

int TreeMirrors(const Tree *root1, const Tree *root2)
{
  if (root1 == NULL && root2 == NULL)
  {
    return 1;
  }

  if (root1 == NULL || root2 == NULL)
  {
    return 0;
  }
  /*if (root1->item != root2->item)
  {
    return 0;
  }*/

  return TreeMirrors(root1->left, root2->left) && TreeMirrors(root1->right, root2->right);
}

int TreeGetNumberOfNodes(const Tree *root)
{
  if (root == NULL)
  {
    return 0;
  }

  return 1 + TreeGetNumberOfNodes(root->left) + TreeGetNumberOfNodes(root->right);
}

int TreeGetHeight(const Tree *root)
{
  if (root == NULL)
  {
    return -1;
  }
  int heightLeftSubTree = TreeGetHeight(root->left);
  int heightRightSubTree = TreeGetHeight(root->right);
  if (heightLeftSubTree > heightRightSubTree)
  {
    return 1 + heightLeftSubTree;
  }

  return 1 + heightRightSubTree;
}

void TreeTraverseInPREOrder(Tree *root, void (*function)(ItemType *p))
{
  if (root == NULL)
  {
    return;
  }
  function(&(root->item));

  TreeTraverseInPREOrder(root->left, function);

  TreeTraverseInPREOrder(root->right, function);
}

void TreeTraverseINOrder(Tree *root, void (*function)(ItemType *p))
{
  if (root == NULL)
  {
    return;
  }

  TreeTraverseINOrder(root->left, function);

  function(&(root->item));

  TreeTraverseINOrder(root->right, function);
}

void TreeTraverseInPOSTOrder(Tree *root, void (*function)(ItemType *p))
{
  if (root == NULL)
  {
    return;
  }

  TreeTraverseInPOSTOrder(root->left, function);

  TreeTraverseInPOSTOrder(root->right, function);

  function(&(root->item));
}

// Completed
int TreeContains(const Tree *root, const ItemType item)
{
  if (root == NULL)
  {
    return 0;
  }
  if (root->item == item)
  {
    return 1;
  }
  return TreeContains(root->left, item) || TreeContains(root->right, item);
}

int TreeAdd(Tree **pRoot, const ItemType item)
{
  Tree *root = *pRoot;

  struct _TreeNode *new = (struct _TreeNode *)malloc(sizeof(*new));
  assert(new != NULL);

  new->item = item;
  new->left = new->right = NULL;

  if (root == NULL)
  {
    *pRoot = new;
    return 1;
  }

  struct _TreeNode *prev = NULL;
  struct _TreeNode *current = root;

  while (current != NULL)
  {
    if (current->item == item)
    {
      free(new);
      return 0;
    } //Note allowed

    prev = current;
    if (current->item > item)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  if (prev->item > item)
  {
    prev->left = new;
  }
  else
  {
    prev->right = new;
  }

  return 0;
}

int TreeRemove(Tree **pRoot, const ItemType item)
{
  Tree *root = *pRoot;

  if (root == NULL)
  {
    return 0;
  }
  if (root->item == item)
  {
    _removeNode(pRoot);
    return 1;
  }
  if (root->item > item)
  {
    return TreeRemove(&(root->left), item);
  }

  return TreeRemove(&(root->right), item);
}
void _removeNode(Tree **pPointer)
{
  Tree *nodePointer = *pPointer;

  if ((nodePointer->left == NULL) && (nodePointer->right == NULL))
  { //A LEAF node

    free(nodePointer);

    *pPointer = NULL;
  }
  return;
}

// ...

// JUST FOR RUNNING EXAMPLES - REMOVE FROM THE INTERFACE

Tree *createExampleTree(void)
{
  // SHOULD NEVER BE DONE LIKE THIS !!!???!!!

  int numNodes = 8;

  Tree *nodes[numNodes];

  for (int i = 0; i < numNodes; i++)
  {
    nodes[i] = (Tree *)malloc(sizeof(Tree));
    nodes[i]->item = i + 1;
    nodes[i]->left = nodes[i]->right = NULL;
  }

  nodes[3]->left = nodes[7];

  nodes[1]->left = nodes[3];
  nodes[1]->right = nodes[4];

  nodes[2]->left = nodes[5];
  nodes[2]->right = nodes[6];

  nodes[0]->left = nodes[1];
  nodes[0]->right = nodes[2];

  return nodes[0];
}
