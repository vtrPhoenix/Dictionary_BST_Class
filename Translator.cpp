/*
 * Translator.cpp
 * 
 * Description: Drives the testing of the Dictionary class. 
 *
 * Author: (vtr) Vansh Thakur Rana and aja121 (Agrim Joshi)
 * Last Modification Date: Mar. 2024
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "Dictionary.h"
#include "BST.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using namespace std;

void display(WordPair& anElement) {
  cout << anElement;
}

int main(int argc, char *argv[])
{

    Dictionary testDictionary; // Test object

    string aLine = "";
    string aWord = "";
    string englishW = "";
    string translationW = "";
    string filename = "";
    string delimiter = ":";
    size_t pos = 0;
    WordPair translated;

    if ((argc > 1))
    {
        filename = argv[1]; // Reading filename from input

        ifstream myfile(filename);
        if (myfile.is_open())
        {
            // cout << "Reading from a file:" << endl;  // For debugging purposes
            while (getline(myfile, aLine))
            {
                pos = aLine.find(delimiter);
                englishW = aLine.substr(0, pos);
                aLine.erase(0, pos + delimiter.length());
                translationW = aLine;
                WordPair aWordPair(englishW, translationW);

                try
                {
                    testDictionary.put(aWordPair);
                }
                catch (ElementAlreadyExistsException &anException)
                {
                    cout << anException.what() << " - " << aWordPair.getEnglish() << ":" << aWordPair.getTranslation() << endl;
                }
            }
            myfile.close();

            if (argc > 2)               // To display the elements if asked by user
            {
                string test = argv[2];
                string test1 = "display";

                if (test.length() == test1.length())
                {
                    testDictionary.displayContent(display);
                }
            }

            ifstream myFile(argv[1]);
            while (!myFile.eof())             // Translation happening
            {
                getline(myFile, aLine);
                string inputWord;
                cout << "Enter an English word to translate: ";              //Taking user input to find the translation
                cin >> inputWord;

                WordPair tranlateWord(inputWord);
                try                               //Exception Handling
                {
                    testDictionary.get(tranlateWord);
                    cout << inputWord << ":" << testDictionary.get(tranlateWord).getTranslation() << endl;
                }
                catch (ElementDoesNotExistException &anException)                
                {
                    cout << "***Not Found!***" << endl;
                }
            }
        }
        else
            cout << "Unable to open file" << endl;
    }
    else
        cout << "Missing the data filename!" << endl;

    testDictionary.~Dictionary();

    return 0;
}
