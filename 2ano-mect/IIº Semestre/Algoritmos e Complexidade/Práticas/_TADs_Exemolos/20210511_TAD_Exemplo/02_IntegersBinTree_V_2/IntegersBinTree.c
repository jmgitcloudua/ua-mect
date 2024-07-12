//
// Joaquim Madeira, AlgC, April 2020
//
// Adapted from an old example (ca. 2003)
//
// Integers Binary Tree --- FIRST VERSION --- INCOMPLETE
//

#include "IntegersBinTree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "PointersQueue.c"
#include "PointersStack.c"

struct _TreeNode {
  ItemType item;
  struct _TreeNode* left;
  struct _TreeNode* right;
};

Tree* TreeCreate(void) { return NULL; }

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

int TreeIsEmpty(const Tree* root) { return root == NULL; }

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

int TreeGetMin(const Tree *root)
{
  if (root == NULL)
  {
    return 0;
  }
  if (root->left == NULL)
  {
    return root->item;
  }

  return TreeGetMin(root->left);
}

int TreeGetMax(const Tree *root)
{
  if (root == NULL)
  {
    return 0;
  }
  while (root->right != NULL)
  {
    root = root->right;
  }
  return root->item;
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

void TreeTraverseLevelByLevelWithQUEUE(Tree* root,   void (*function)(ItemType* p)) {
  if (root == NULL) {
    return;
  }

  // Not checking for queue errors !!
  // Create the QUEUE for storing POINTERS

  Queue* queue = QueueCreate();

  QueueEnqueue(queue, root);

  while (QueueIsEmpty(queue) == 0) {
    Tree* p = QueueDequeue(queue);

    function(&(p->item));

    if (p->left != NULL) {
      QueueEnqueue(queue, p->left);
    }
    if (p->right != NULL) {
      QueueEnqueue(queue, p->right);
    }
  }

  QueueDestroy(&queue);
}

void TreeTraverseInPREOrderWithSTACK(Tree *root, void (*function)(ItemType *p)) {
    if (root == NULL)
      {
        return;
      }

  // Not checking for queue errors !!
  // Create the STACK for storing POINTERS

  Stack *stack = StackCreate();

  StackPush(stack, root);

  while (StackIsEmpty(stack) == 0)
  {
    Tree* p = StackPop(stack);

    function(&(p->item));

    //Pay attention to the push order
    if (p->right != NULL)
    {
      StackPush(stack, p->right);
    }
    if (p->left != NULL)
    {
      StackPush(stack, p->left);
    }
    
    
  }
}

void TreeTraverseINOrderWithSTACK(Tree* root, void (*function)(ItemType* p)) {

    if (root == NULL)
      {
        return;
      }

  // Not checking for queue errors !!
  // Create the STACK for storing POINTERS

  Stack *stack = StackCreate();

  StackPush(stack, root);

  while (StackIsEmpty(stack) == 0)
  {
    Tree* p = StackPop(stack);

    //Pay attention to the push order
    if (p->right != NULL)
    {
      StackPush(stack, p->right);
    }

    function(&(p->item));

    if (p->left != NULL)
    {
      StackPush(stack, p->left);
    }
    
    
  }
}

// ...

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

// Storing and reading from a FILE

struct _fileNode {
  ItemType item;
  int emptyLeftSubTree;
  int emptyRightSubTree;
};

static void _storeInFile(const Tree* root, FILE* f, int fileType) {
  if (root == NULL) {
    return;
  }

  struct _fileNode r;
  r.item = root->item;
  r.emptyLeftSubTree = (root->left == NULL);
  r.emptyRightSubTree = (root->right == NULL);

  if (fileType == 1) {
    fprintf(f, "%d %d %d ", r.item, r.emptyLeftSubTree, r.emptyRightSubTree);
  } else {
    fwrite(&r, sizeof(struct _fileNode), 1, f);
  }

  _storeInFile(root->left, f, fileType);
  _storeInFile(root->right, f, fileType);
}

static void _getFromFile(Tree** pRoot, FILE* f, int fileType) {
  struct _fileNode r;

  if (fileType == 1) {
    fscanf(f, "%d", &r.item);
    fscanf(f, "%d", &r.emptyLeftSubTree);
    fscanf(f, "%d", &r.emptyRightSubTree);
  } else {
    fread(&r, sizeof(struct _fileNode), 1, f);
  }

  Tree* newNode = (Tree*)malloc(sizeof(struct _TreeNode));

  newNode->item = r.item;

  if (r.emptyLeftSubTree) {
    newNode->left = NULL;
  } else {
    _getFromFile(&(newNode->left), f, fileType);
  }

  if (r.emptyRightSubTree) {
    newNode->right = NULL;
  } else {
    _getFromFile(&(newNode->right), f, fileType);
  }

  *pRoot = newNode;
}

int TreeStoreInFile(const Tree* root, char* fileName, int fileType) {
  FILE* f = fopen(fileName, "w");
  if (f == NULL) {
    return 0;
  }

  _storeInFile(root, f, fileType);

  fclose(f);
  return 1;
}

Tree* TreeGetFromFile(char* fileName, int fileType) {
  FILE* f = fopen(fileName, "r");
  if (f == NULL) {
    return NULL;
  }

  Tree* root;
  _getFromFile(&root, f, fileType);

  fclose(f);
  return root;
}

// JUST FOR RUNNING EXAMPLES - REMOVE FROM THE INTERFACE

Tree* createExampleTree(void) {
  // SHOULD NEVER BE DONE LIKE THIS !!!???!!!

  int numNodes = 8;

  Tree* nodes[numNodes];

  for (int i = 0; i < numNodes; i++) {
    nodes[i] = (Tree*)malloc(sizeof(Tree));
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
