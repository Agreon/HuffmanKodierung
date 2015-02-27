/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on February 26, 2015, 3:50 PM
 */

#include <iostream>
#include "Huffman.h"

using namespace std;



int main(int argc, char** argv)
{   
    string toEncode = "ACHT ALTE AMEISEN ASSEN AM ABEND ANANAS";
    codeTable table = Huffman::GenerateCodeTable(toEncode);
       
    string encoded = Huffman::EncodeString(toEncode,table);
    string decoded = Huffman::DecodeString(encoded, table);
    
    cout << "Encoded string: " << encoded << endl;
    cout << "Size: " << encoded.size() << " Bit" << endl;
    
    cout << "The normal text would have a size of " << toEncode.size()*8 << " Bit" << endl;
    
    return 0;
}

