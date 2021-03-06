#include "TreeType.h"

struct TreeNode
{
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};

TreeType::TreeType()
{
  root = NULL;
  length = 0;
}

TreeType::~TreeType()
// Calls recursive function destroy to destroy the tree.
{
  destroy(root);
}

void TreeType::makeEmpty()
{
  destroy(root);
  root = NULL;
  length = 0;
}

void TreeType::destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    destroy(tree->left);
    destroy(tree->right);
    delete tree;
  }
}

bool TreeType::isEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int TreeType::getLength() const
{
  return length;
}

void TreeType::putItem(ItemType item)
// Calls recursive function insert to insert item into tree.
{
  insert(root, item);
  length++;
}

// helper Function for putItem
void TreeType::insert(TreeNode *&tree, ItemType item)
// inserts item into tree.
// Post:  item is in tree; binary search property is maintained.
{
  if (tree == NULL)
  { // insertion place found.
    tree = new TreeNode;
    tree->left = NULL;
    tree->right = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    insert(tree->left, item); // insert in left subtree.
  else
    insert(tree->right, item); // insert in right subtree.
}

void TreeType::deleteItem(ItemType item, ofstream &outFile)
// Calls recursive function remove to delete item from tree.
{
  remove(root, item, outFile);
  length--;
}

void TreeType::remove(TreeNode *&tree, ItemType item, ofstream &outFile)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (tree == NULL) {
    outFile << item << " is not in tree." << endl;
    length++;	// if item not found, then this length++ offsets the length-- in deleteItem()
  }
  else if (item < tree->info)
    remove(tree->left, item, outFile); // Look in left subtree.
  else if (item > tree->info)
    remove(tree->right, item, outFile); // Look in right subtree.
  else
    deleteNode(tree, outFile); // Node found; call deleteNode
}

void TreeType::deleteNode(TreeNode *&tree, ofstream &outFile)
// Modify this function to call the getSuccessor function instead of getPredecessor
{
TreeNode *tempPtr;
  tempPtr = tree;

  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    TreeNode *sucNode = getSuccessor(tree->right);
    tree->info = sucNode->info;
    remove(tree->right, sucNode->info, outFile); // Delete predecessor node.
  }}

//Helper function for deleteNode
TreeNode *TreeType::getPredecessor(TreeNode *tree) const
{
  while (tree->right != NULL)
    tree = tree->right;
  return tree;
}

TreeNode *TreeType::getSuccessor(TreeNode *tree) const
// Precondition: Node must be initialized.
// Input Parameter: a TreeNode pointer
// Post Condition: A a pointer to the successor of the TreeNode Parameter is returned; helper function for deleteNode.
{
  while (tree -> left != NULL) {
    tree = tree -> left;
  } //while
  return tree;
}

void TreeType::print(ofstream &outFile) const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root, outFile);
  outFile << endl;
}

// Helper function for print
void TreeType::inOrderTraverse(TreeNode *tree, ofstream &outFile) const
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left, outFile); // Print left subtree.
    outFile << tree->info << " ";
    inOrderTraverse(tree->right, outFile); // Print right subtree.
  }
}

void TreeType::preOrderPrint(ofstream &outFile) const
// Precondtion: Tree has been initialized.
// Parameters: A file to which the output will be printed to.
// Post Condition: Returns void; prints the tree contents in specified order.
  
{
  preOrderTraverse(root, outFile);
  outFile << endl;
}

void TreeType::postOrderPrint(ofstream &outFile) const {
  // Precondtion: Tree has been initialized. 
  // Parameters: A file to which the output will be printed to.  
  // Post Condition: Returns void; prints the tree contents in specified order.
  postOrderTraverse(root, outFile);
  outFile << endl;
}

void TreeType::levelOrderPrint(ofstream &outFile) const
// Precondtion: Tree has been initialized.                                                                                                                                                            
// Parameters: A file to which the output will be printed to.                                                                                                                                            
// Post Condition: Returns void; prints the tree contents in specified order.
{
  int h = treeHeight(root);
  for (int i = 1; i <= h; i++) {
    levelOrderTraverse(root, outFile,  i);
    } //for
  outFile << endl;
}

void TreeType::printAncestors(ItemType value, ofstream &outFile) const
// Precondition: Tree has been initialized.
// Parameters: The value to which you would like to print it's ancestors and the file to which you wish to print result.
// Post Condition: Returns void; prints the ancestors of node holding specified value to outFile.
{
  if (findNode(root, value) == true) {
    traverseAncestors(root, outFile, value);
    outFile << endl;
  } //if
  else {
    outFile << value << " is not in the tree." << endl;
  } //else
}

void TreeType::mirrorImage(TreeType &t) const
// calls the helper function mirror
{
  mirror(t.root, root);
}

// helper function for mirrorImage
void TreeType::mirror(TreeNode *&copy, const TreeNode *originalTree) const
// implement this function
// Post: copy is the root of a tree that is a mirror Image of originalTree.
// HINT: this function can be implemented in a very similar way as the copyTree() function in the slides
// Preconditions: Tree structure has been instantiated.
// Input Parameters: a TreeNode pointer address and a TreeNode pointer
// Post Condition: Returns void; a helper function for the mirrorImage function and helps arrange output in specified order.
{
  if (originalTree == NULL) {
    copy = NULL;
  } //if
  else {
    copy = new TreeNode;
    copy -> info = originalTree -> info;
    mirror(copy -> left, originalTree -> right);
    mirror(copy -> right, originalTree -> left);
  } //else
} // mirror

void TreeType::preOrderTraverse(TreeNode *tree, ofstream &outFile) const {
  // Preconditions: Tree structure has been instantiated 
  // Input Parameters: a TreeNode pointer and a file
  // Post Condition: Returns void; a helper function for preOrderPrint that prints output in specified order.
  if (tree != NULL) {
    outFile << tree -> info << " ";
    preOrderTraverse(tree -> left, outFile);
    preOrderTraverse(tree -> right, outFile);
  } //if
} // preOrder

void TreeType::postOrderTraverse(TreeNode *tree, ofstream &outFile) const { 
  // Preconditions: Tree structure has been instantiated  
  // Input Parameters: a TreeNode pointer and a file                                                                                     
  // Post Condition: Returns void; a helper function for postOrderPrint that prints output in specified order.
  if (tree != NULL) {
    postOrderTraverse(tree -> left, outFile);
    postOrderTraverse(tree -> right, outFile);
    outFile << tree -> info << " ";
  } //if                                                                                        
} // postOrder

void TreeType::levelOrderTraverse(TreeNode *tree, ofstream &outFile, int level) const {
  // Preconditions: Tree structure has been instantiated
  // Input Parameters: a TreeNode pointer, a file, and an integer object
  // Post Condition: Returns void; a helper function for levelOrderPrint that prints output in specified order.
  if (tree == NULL) {
    return;
  } //if
  if (level == 1) {
    outFile << tree -> info << " ";
  } //if
  else if (level > 1)
    {
      levelOrderTraverse(tree -> left, outFile, level - 1);
      levelOrderTraverse(tree -> right, outFile, level - 1);
    } //else if
} //levelOrderTraverse

bool TreeType::traverseAncestors(TreeNode *tree, ofstream &outFile, ItemType value) const {
  // Preconditions: Tree structure has been instantiated.
  // Input Parameters: A TreeNode pointer, a file, and an ItemType object
  // Post Condition: Returns a boolean dependant on whether a node has ancestors or not; a helper function for printAncestors
  if (tree == NULL) {
    return false;
  } //if
  if (root -> info == value) {
    outFile << value << " has no ancestors.";
    return false;
  } //if
  if (tree -> info == value) {
    return true;
  } //if
  if (traverseAncestors(tree -> left, outFile, value) || traverseAncestors(tree -> right, outFile, value)) {
      outFile << tree -> info << " ";
      return true;
  } //if
  else {
  outFile << value << " is not in the tree" << endl; 
  }
  return false;
  
} //traverseAncestors

int TreeType::treeHeight(TreeNode *tree) const {
  // Precondition: Tree structure has been instantiated.
  // Input Parameters: A TreeNode pointer
  // Post Condition: Returns an integer onbject that indicated a level on a TreeNode object; a helper function for levelOrderTraverse.
  if (tree == NULL) {
    return 0;
  } //if
  else {
    int leftHeight = treeHeight(tree -> left);
    int rightHeight = treeHeight(tree -> right);
    return max(leftHeight, rightHeight) + 1;
  } //else
} //treeHeight

bool TreeType::findNode(TreeNode* tree, ItemType item) const {
  // Precondtion: Tree structure has been instantiated.
  // Input Parameters: A TreeNode pointer and an ItemType object.
  // Post Condition: Returns true if a node is found containing item. Returns false otherwise.
  TreeNode* nodePtr = tree;
  TreeNode* parentPtr = NULL;
  bool found = false;
  while (nodePtr != NULL && !found) {
    if (item < nodePtr -> info) {
      parentPtr = nodePtr;
      nodePtr = nodePtr -> left;
    }
    else if (item > nodePtr -> info) {
      parentPtr = nodePtr;
      nodePtr = nodePtr->right;
    } else
      found = true;
  }
  return found;
} //findNode
 
