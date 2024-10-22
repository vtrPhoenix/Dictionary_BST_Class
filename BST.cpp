/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: vtr(Vansh thakur Rana)
 *         aja121(Agrim Joshi)
 *          
 * Date of last modification: March 15, 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { 
      //Initializes root to null and elementCount to 0
      root = nullptr;
      elementCount = 0;
   }            

   // Copy constructor
   BST::BST(const BST & aBST) {
     
	     // Initialize root to null and elementCount to 0
     root = nullptr;
     elementCount = 0;
      // If the source tree is not empty, perform deep copy
     if(aBST.root != nullptr) {
      copyR(aBST.root);
     }
     else
     // If the source tree is empty, indicate the end of copy process
      cout << "Root nullptr, copy ends here" << endl;
   }
 void BST::copyR(BSTNode* current) {
      // Insert the current node's element into the new tree
      insert(current->element);
      // Recursively copy left subtree if it exists
      if(current->hasLeft())
         copyR(current->left);
      // Recursively copy right subtree if it exists
      else if (current->hasRight())
         copyR(current->right);
   }

// Destructor 
   BST::~BST() {

      // Perform recursive deletion starting from the root
      if (root != nullptr)
         deleteR(root);
   }
    // Recursive deletion function
   void BST::deleteR(BSTNode *&current)
   {
      // Recursively delete left subtree
      if (current->hasLeft())
      {
         deleteR(current->left);
      }
      // Recursively delete right subtree
      if (current->hasRight())
      {
         deleteR(current->right);
      }
      // Delete current node and set it to null
      delete current;
      current = nullptr;
   }                    
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     

     return this->elementCount;
	 
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
   // If the binary search tree is empty, create a new root node
     if (root == nullptr) {
      root = new BSTNode(newElement);
      // Check if root node creation failed
      if (root == nullptr)
         throw UnableToInsertException("Could not insert the element in BST");
      elementCount++;
     }
     // If the binary search tree is not empty, call insertR to insert the element
     else {
      BSTNode* newEle = new BSTNode(newElement);
      // If insertion fails, throw an exception
      if (!insertR(newEle, root)) {
            throw ElementAlreadyExistsException("Element already exists in BST");
         }
      elementCount++;
     }
   } 
   
   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
    
	
      if (current->element == newBSTNode->element)
      {
      // If the element to be inserted already exists, delete the new node and return false.
         delete newBSTNode;
         return false;
      }
      else if (newBSTNode->element < current->element)
      {
         if (current->hasLeft())
         // If there's a left child, recursively call insertR with the left child as the current node.
            return insertR(newBSTNode, current->left);
         else
         {
            // If there's no left child, set the left child of the current node to the new node and return true.
            current->left = newBSTNode;
            //delete newBSTNode;
            return true;
         }
      }
      else if (newBSTNode->element > current->element)
      {
         if (current->hasRight())
         // If there's a right child, recursively call insertR with the right child as the current node.
            return insertR(newBSTNode, current->right);
         else
         {
            // If there's no right child, set the right child of the current node to the new node and return true.
            current->right = newBSTNode;
            //delete newBSTNode;
            return true;
         }
      }
      return false; 
   }

   
   // Description: Retrieves "targetElement" from the binary search tree.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(log2 n)
    WordPair& BST::retrieve(WordPair & targetElement) const {
      // Check if the binary search tree is empty
      if (elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");

      // Call the recursive retrieval method to find and return the target element
      WordPair& translated = retrieveR(targetElement, root);
	 
      return translated;
   }
   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {
    // Base case: If the current node matches the target element, return a reference to its element
    if (current == nullptr)
        throw ElementDoesNotExistException("Element not found in the BST");

    if (current->element == targetElement)
        return current->element;
    // If the target element is less than the current node's element, search in the left subtree
    else if (targetElement < current->element)
        return retrieveR(targetElement, current->left);
    // If the target element is greater than the current node's element, search in the right subtree
    else if (targetElement > current->element)
        return retrieveR(targetElement, current->right);
    // If the target element is not found in the tree, throw an ElementDoesNotExistException
    else
        throw ElementDoesNotExistException("Element not found in the BST");
}
         
   
   // Description: Traverses the binary search tree in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
      // Check if the binary search tree is empty
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");

      // Call the recursive method to traverse the tree in order
     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   // Postcondition: This method does not change the binary search tree. 
    void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
   
	  // Base case: If the current node is null, return
	  if (current == nullptr)
         return;
      //Traverse left subtree
      traverseInOrderR(visit, current->left);

      visit(current->element);
      //Traverse right subtree
      traverseInOrderR(visit, current->right);
   }