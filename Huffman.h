/* 
 * File:   Huffman.h
 * Author: daniel
 *
 * Created on February 26, 2015, 3:56 PM
 */

#ifndef HUFFMAN_H
#define	HUFFMAN_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "Node.h"

typedef std::map<char, std::string> codeTable;

class Huffman 
{
public:  
    static codeTable GenerateCodeTable(const std::string& text);
    static void ExtractCodeTable(const std::string& filePath);
    static std::string EncodeString(const std::string& text, codeTable &table);
    static std::string DecodeString(const std::string& _text, codeTable &table);
private:
    Huffman();
    ~Huffman();
    static int GetFrequency(char character, const std::string& text);
    static void SortNodes(std::vector<Node*> &nodes);
    static void ConnectNodes(std::vector<Node*> &nodes);
    static codeTable CreateCodeTable(std::vector<Node*> &nodes);
    static std::vector<Node*> CreateNodes(const std::string& text);
    
    static std::string ReverseString(const std::string& str);
private:
    
};

#endif	/* HUFFMAN_H */

