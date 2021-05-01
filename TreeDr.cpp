
// Test driver
#include "TreeType.h"

TreeType *makeTree(int arr[], int size);
TreeType* arrayToBST(TreeType* tree, int arr[], int start, int end);
  
int main()
{
	string command; // operation to be executed

	int item;
	TreeType tree;
	bool found;
	ifstream inFile;
	inFile.open("input.txt");
	ofstream outFile;
	outFile.open("output.txt");
	inFile >> command;

	while (command != "Quit")
	{
		//1
		if (command == "PutItem")
		{
			inFile >> item;
			tree.putItem(item);
			outFile << item;
			outFile << " is inserted" << endl;
		}
		//2
		else if (command == "DeleteItem")
		{
			inFile >> item;
			tree.deleteItem(item, outFile);
		}
		//3
		else if (command == "GetLength")
		{
			outFile << "Number of nodes is " << tree.getLength() << endl;
		}
		//4
		else if (command == "IsEmpty")
			if (tree.isEmpty())
				outFile << "Tree is empty." << endl;
			else
				outFile << "Tree is not empty." << endl;
		//5
		else if (command == "Print")
		{
			outFile << "Printing the tree...InOrder Traversal\n";
			tree.print(outFile);
		}
		//6
		else if (command == "PreOrderPrint")
		{
			outFile << "PreOrder Print:\n";
			tree.preOrderPrint(outFile);
		}
		//7
		else if (command == "PostOrderPrint")
		{
			outFile << "PostOrder Print:\n";
			tree.postOrderPrint(outFile);
		}
		//8
		else if (command == "LevelOrderPrint")
		{
			outFile << "LevelOrder Print:\n";
			tree.levelOrderPrint(outFile);
		}
		//9
		else if (command == "MakeEmpty")
		{
			tree.makeEmpty();
			outFile << "Tree has been made empty." << endl;
		}
		//10
		else if (command == "PrintAncestorsOf")
		{
			inFile >> item;
			outFile << "testing Ancestors of " << item << endl;
			tree.printAncestors(item, outFile);
		}
		//11
		else if (command == "MirrorImage")
		{
			outFile << "Testing Mirror Image\n";
			tree.makeEmpty();
			tree.putItem(10);
			tree.putItem(13);
			tree.putItem(5);
			tree.putItem(4);
			tree.putItem(7);
			tree.putItem(12);
			tree.putItem(20);
			outFile << "Original Tree before mirroring:\n";
			tree.levelOrderPrint(outFile);
			TreeType mirrorOftree;
			tree.mirrorImage(mirrorOftree);
			outFile << "Original Tree After Mirroring:\n";
			tree.levelOrderPrint(outFile);
			outFile << "Mirror Image:\n";
			mirrorOftree.levelOrderPrint(outFile);
		}
		//12
		else if (command == "MakeTree")
		{

			int array[100], length;
			inFile >> length;
			for (int i = 0; i < length; i++)
			{
				inFile >> array[i];
			}

			TreeType *balancedTree = makeTree(array, length);
			outFile << "balancedTree.LevelOrderPrint()\n";
			balancedTree->levelOrderPrint(outFile);
			outFile << "balancedTree.InOrderPrint()\n";
			balancedTree->print(outFile);
			delete balancedTree;
		}
		else
			outFile << "Undefined Command!" << command << endl;
		inFile >> command;
	}
	cout << "Testing completed." << endl;

	return 0;
}


TreeType *makeTree(int arr[], int size)
// implement this function
// you may define and call helper functions.
// Precondition: None.
// Parameters: An integer array and integer object.
// Post Condition: A TreeType object is returned filled with the array contents.
{
  TreeType *balancedTree = new TreeType;
  balancedTree = arrayToBST(balancedTree, arr, 0, size - 1);
  return balancedTree;
}

TreeType* arrayToBST(TreeType* tree, int arr[], int start, int end) {
  // Precondition: All parameters must be initialized.
  // Parameters: a Treetype pointer, an integer array, and two integer objects.
  // Post Condition: a TreeType object is returned filled with the array contents.
  if (start > end)
    return NULL;
  int mid = (start + end)/2;
  tree -> putItem(arr[mid]);
  arrayToBST(tree, arr, start, mid - 1);
  arrayToBST(tree, arr, mid + 1, end);
  return tree;
} //arrayToBST