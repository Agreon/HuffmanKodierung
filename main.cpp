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
    Huffman huffman;
        
    codeTable table = huffman.GenerateCodeTable("hallo");
    
    std::string enc = huffman.EncodeString("hallo",table);
    std::cout << enc << std::endl;
    
    std::cout << huffman.DecodeString(enc,table);
    
    return 0;
}

