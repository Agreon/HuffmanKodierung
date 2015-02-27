/* 
 * File:   Huffman.cpp
 * Author: daniel
 * 
 * Created on February 26, 2015, 3:56 PM
 */

#include <fstream>

#include "Huffman.h"

/**
 * Generates a code table that you can use to en- and decode a string.
 * @param text Your text
 * @return a code table
 */
codeTable Huffman::GenerateCodeTable(const std::string& text)
{
    std::vector<Node*> nodes = CreateNodes(text);
        
    SortNodes(nodes);
    
    ConnectNodes(nodes);
   
    return CreateCodeTable(nodes);
}


/**
 * Encodes a string with a previously generated code table.
 * @param text
 * @param table
 * @return the encoded string.
 */
std::string Huffman::EncodeString(const std::string& text, codeTable &table)
{
    std::string encoded = "";
    
    for(int i = 0; i < text.size(); i++)
    {
        encoded += table[text[i]];
    }
    
    return encoded;
}

/**
 * Decodes a string with a previously generated code table.
 * @param _text
 * @param table
 * @return the decoded string.
 */
std::string Huffman::DecodeString(const std::string& _text, codeTable &table)
{   
    std::string decoded = "";
    
    std::string text = _text;
    std::vector<std::string> codes;
    
    // Save all codes in a iteratable vector.
    for(auto const &it : table) 
    {
        codes.push_back(it.second);
    }
    
    int cIndex = 0;
    
    std::string check = "";
    check += _text[0];
    
    bool alreadyFound = false;
       
    while(cIndex < text.size())
    {
        // Got through all codes an check if the current piece of the encoded string matches a code.
        for(int i = 0; i < codes.size(); i++)
        {
            if(check == codes[i])
            {                
                // If so, delete the code from the encoded string.
                text = text.substr(check.size());
                // Add a character from the code table to the decoded string.
                for(auto const &it : table) 
                {
                    if(check == it.second)
                    {
                        decoded += it.first;
                    }
                }   
                cIndex = 0;
                check = "";
                check += text[0];
                alreadyFound = true;
                break;
            }
        }
        // If theres a character found, begin from new with a single char.
        if(alreadyFound)
        {
            alreadyFound = false;
            continue;
        }
        
        // Add a character from the encoded string to the check variable.
        cIndex++;
        check += text[cIndex];  
    }
    
    return decoded;
}

/**
 * Creates nodes for every char depending on its frequency.
 * @param text
 * @return 
 */
std::vector<Node*> Huffman::CreateNodes(const std::string& text)
{
    std::vector<Node*> nodes;
    int frequency;
    
    for(int i = 0; i < 255; i++)
    {
        frequency = GetFrequency((char)i,text);
        if(frequency > 0)
        {
            nodes.push_back(new Node((char)i,frequency));
            
            std::cout << "Added new Node(" << nodes.back()->GetCharacter() << "," << nodes.back()->GetValue() << ")" << std::endl;
        }
    }    
    return nodes;
}

/**
 * A simple frequency Analysis.
 * @param character
 * @param text
 * @return the frequency of a character in the string.
 */
int Huffman::GetFrequency(char character, const std::string& text)
{
    int frequency = 0;
    
    for(int i = 0; i < text.size(); i++)
    {
        if(character == text[i]) frequency++;
    }
    
    return frequency;
}

/**
 * Basically a SelectionSort. Sorts nodes by their values.
 * @param nodes
 */
void Huffman::SortNodes(std::vector<Node*> &nodes)
{
    int min;
    for (int i = 0; i < nodes.size()-1; i++) 
    {
        min = i;
        for (int j = i + 1; j < nodes.size(); j++) 
        {
            if (nodes[j]->GetValue() < nodes[min]->GetValue()) 
            {
                min = j;
            }
        }  
        
        if (min != i) 
        {
            Node *tmp = nodes[min];
            nodes[min] = nodes[i];
            nodes[i] = tmp;
        }
    }
}

void Huffman::ConnectNodes(std::vector<Node*> &nodes)
{
    int notConnected = 0;
    int newValue = 0;
    
    /*
     As long as there are unconnected nodes, connect them.
     */
    while(true)
    {
        Node *first;
        Node *second;
        
        notConnected = 0;
        // Check if only one is left.
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false)
            {
                notConnected++;
            }
        }
        if(notConnected < 2) break;
        
        // Search for first not connected..
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false) 
            {
                first = nodes[i];
                break;
            }
        }
        
        // Search for second not connected.
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false && nodes[i] != first) 
            {
                second = nodes[i];
                break;
            }
        }
        
        // Set the new node to the correct position in the list.
        newValue = first->GetValue() + second->GetValue();
        for(int i = 0; i < nodes.size(); i++)
        {
            if(newValue <= nodes[i]->GetValue())
            {
                Node *newNode = new Node(0, newValue);
                nodes.insert(nodes.begin()+i, newNode);

                first->SetNextNode(newNode);
                first->SetConnected(true);
                first->SetBinValue(0);

                second->SetNextNode(newNode);
                second->SetConnected(true);
                second->SetBinValue(1);
                break;
            }
            // If the new value is greate than every other value.
            if(i == nodes.size()-1)
            {
                nodes.push_back(new Node(0, newValue));
                
                first->SetNextNode(nodes.back());
                first->SetConnected(true);
                first->SetBinValue(0);

                second->SetNextNode(nodes.back());
                second->SetConnected(true);
                second->SetBinValue(1);
                break;
            }
        }
    }
}

/**
 * Creates a code table based on a binary tree.
 * @param nodes
 * @return 
 */
codeTable Huffman::CreateCodeTable(std::vector<Node*>& nodes)
{
    Node *currentNode = 0;
    std::string text;
    codeTable table;
    
    std::cout << "Binary-Keys" << std::endl;
    
    for(int i = 0; i < nodes.size(); i++)
    {
        // Only create keys for nodes with characters.
        if(nodes[i]->GetCharacter() != 0)
        {                       
            text = "";
            currentNode = nodes[i];
            while(true)
            {
                // If the last node was reached, you got the key and can escape the loop..
                if(currentNode->GetNextNode() == 0)
                {
                    break;
                }
                if(currentNode->GetBinValue() == 0) text += "0";
                else text += "1";
                currentNode = currentNode->GetNextNode();
            }
            // Save key in the map.
            text =  ReverseString(text);
            table[nodes[i]->GetCharacter()] = text;
            std::cout << nodes[i]->GetCharacter() << ": " << text << std::endl;
        }
    }
    return table;
}

/**
 * Reverses a string.
 * @param str
 * @return the reversed string.
 */
std::string Huffman::ReverseString(const std::string& str)
{
    std::string newString = "";
    
    for(int i = str.size(); i >= 0; i--)
    {
        newString += str[i];
    }
    return newString;    
}
