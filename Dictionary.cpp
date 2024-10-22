/*
 * Dictionary.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: vtr(Vansh Thakur Rana)
 *         aja121(Agrim Joshi)
 *
 * Date of last modification: March 15, 2024
 */

#include "Dictionary.h"
#include "BST.h"
#include "WordPair.h"
#include "BSTNode.h"
#include <iostream>
#include "ElementAlreadyExistsException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"
#include "ElementDoesNotExistException.h"


using namespace std;

// Default constructor
Dictionary::Dictionary() {
    //Creates a new binary search tree to store key-value pairs
    keyValuePairs = new BST();
}
// Destructor
Dictionary::~Dictionary() {
     //Deletes the binary search tree to release memory
    keyValuePairs->~BST();
}

//Returns the number of elements currently stored in the Dictionary
unsigned int Dictionary::getElementCount() const {
    return keyValuePairs->getElementCount();
}
// Description: Puts "newElement" (association of key-value) into the Dictionary.
   // Precondition: "newElement" does not already exist in the Dictionary.
   //               This is to say: no duplication allowed.
   // Exception: Throws the exception "UnableToInsertException" 
   //            when newElement cannot be inserted in the Dictionary.  
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the Dictionary.  
    void Dictionary::put(WordPair & newElement) {
    try {
        //Inserts the new element into the binary search tree
        keyValuePairs->insert(newElement);
    } catch (UnableToInsertException& e) {
        // If insertion fails due to memory issues, rethrow the exception
        throw UnableToInsertException("Could not insert the element in Dictionary");
    } catch (ElementAlreadyExistsException& e) {
        // If the element already exists, rethrow the exception
        throw ElementAlreadyExistsException("Element already exists in Dictionary");
    }
   }

// Description: Gets "newElement" (i.e., the associated value of a given key) 
   //              from the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception ElementDoesNotExistException
   //            if the key is not found in the Dictionary.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
  WordPair & Dictionary::get(WordPair & targetElement) const {
    try {
        // Retrieves the element associated with the given key from the binary search tree
        return keyValuePairs->retrieve(targetElement);
    } catch (ElementDoesNotExistException& e) {
        // If the element does not exist, rethrow the exception
        throw ElementDoesNotExistException("Element does not exist in Dictionary");
    } catch (EmptyDataCollectionException& e) {
        // If the Dictionary is empty, rethrow the exception
        throw EmptyDataCollectionException("Dictionary is empty");
    }
   }

   // Description: Prints the content of the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
    void Dictionary::displayContent(void visit(WordPair &)) const {
    try {
        // Traverses the binary search tree in order and calls the visit function on each element
        keyValuePairs->traverseInOrder(visit);
    } catch (EmptyDataCollectionException& e) {
        // If the Dictionary is empty, rethrow the exception
        throw EmptyDataCollectionException("Dictionary is empty");
    }
   }