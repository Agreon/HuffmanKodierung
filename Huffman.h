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
    Huffman();
    ~Huffman();
    
    codeTable GenerateCodeTable(const std::string& text);
    std::string EncodeString(const std::string& text, codeTable& table);
    std::string DecodeString(const std::string& text, codeTable& table);
private:
    std::vector<Node*> CreateNodes(const std::string& text);
    int GetAppearance(char character, const std::string& text);
    void SortNodes(std::vector<Node*> &nodes);
    void ConnectNodes(std::vector<Node*> &nodes);
    codeTable CreateCodeTable(std::vector<Node*> &nodes);
private:
    
};

#endif	/* HUFFMAN_H */

