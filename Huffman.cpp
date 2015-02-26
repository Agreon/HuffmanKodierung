/* 
 * File:   Huffman.cpp
 * Author: daniel
 * 
 * Created on February 26, 2015, 3:56 PM
 */

#include "Huffman.h"

Huffman::Huffman()
{
}

Huffman::~Huffman()
{
}


codeTable Huffman::GenerateCodeTable(const std::string& text)
{
    std::vector<Node*> nodes = CreateNodes(text);
        
    SortNodes(nodes);
    
    ConnectNodes(nodes);
   
    return CreateCodeTable(nodes);
}


std::string Huffman::EncodeString(const std::string& text, codeTable& table)
{
    std::string encoded = "";
    
    for(int i = 0; i < text.size(); i++)
    {
        encoded += table[text[i]];
    }
    
    return encoded;
}

std::string Huffman::DecodeString(const std::string& text, codeTable& table)
{
    std::string decoded = "";
    int cIndex = 0;
    std::string tmp = ""+text[0];
    /*
    while(cIndex < text.size() -1)
    {
        for(auto const &it : table) 
        {
            if(tmp == it.second)
            {
                decoded += it.first;
                tmp = "";
            }
            else
            {
                cIndex++;
                tmp += text[cIndex];
            }
        }      
    }*/
            
    
    return decoded;
}

/*
 TODO: All characters
 */
std::vector<Node*> Huffman::CreateNodes(const std::string& text)
{
    std::vector<Node*> nodes;
    for(int i = 97; i < 97+26; i++)
    {
        int appearance = GetAppearance((char)i,text);
        if(appearance > 0)
        {
            nodes.push_back(new Node((char)i,appearance));
            
            std::cout << "Added new Node(" << nodes.back()->GetCharacter() << "," << nodes.back()->GetValue() << ")" << std::endl;
        }
    }
    
    return nodes;
}

int Huffman::GetAppearance(char character, const std::string& text)
{
    int appearance = 0;
    
    for(int i = 0; i < text.size(); i++)
    {
        if(character == text[i]) appearance++;
    }
    
    return appearance;
}

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
        /*
         Search for 2 not connected nodes
         */
        Node *first;
        Node *second;
        
        notConnected = 0;
        // Check if only one is left
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false)
            {
                notConnected++;
            }
        }
        if(notConnected < 2) break;
        
        // Search for first
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false) 
            {
                first = nodes[i];
                break;
            }
        }
        
        // Search for second
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false && nodes[i] != first) 
            {
                second = nodes[i];
                break;
            }
        }
        
        // Set the new node to the correct position
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
            if(i == nodes.size()-1)
            {
                nodes.push_back(new Node(0, newValue));
                
                first->SetConnected(true);
                first->SetBinValue(0);
                first->SetNextNode(nodes.back());

                second->SetConnected(true);
                second->SetBinValue(1);
                second->SetNextNode(nodes.back());
                break;
            }
        }
    }
}

codeTable Huffman::CreateCodeTable(std::vector<Node*>& nodes)
{
    Node *currentNode = 0;
    std::string text;
    codeTable table;
    std::cout << "Bin-Keys" << std::endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->GetCharacter() != 0)
        {                       
            text = "";
            currentNode = nodes[i];
            while(true)
            {
                if(currentNode->GetNextNode() == 0)
                {
                    break;
                }
                if(currentNode->GetBinValue() == 0) text += "0";
                else text += "1";
                currentNode = currentNode->GetNextNode();
            }
            //nodes[i]->SetBinKey(text);
            table[nodes[i]->GetCharacter()] = text;
            std::cout << nodes[i]->GetCharacter() << ": " << text << std::endl;
        }
    }
    return table;
}


/*
 * void Huffman::ConnectNodes(std::vector<Node*> &nodes)
{
    int notConnected = 0;
    int newValue = 0;
    /*
     As long as there are unconnected nodes, connect them.
     
    while(true)
    {
        /*
         Search for 2 not connected nodes
         
        Node *first;
        Node *second;
        
        notConnected = 0;
        // Check if only one is left
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false)
            {
                notConnected++;
            }
        }
        if(notConnected < 2) break;
        
        // Search for first
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false) 
            {
                first = nodes[i];
                break;
            }
        }
        
        // Search for second
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->IsConnected() == false && nodes[i] != first) 
            {
                second = nodes[i];
                break;
            }
        }
        
        // Set the new node to the correct position
        newValue = first->GetValue() + second->GetValue();
        for(int i = 0; i < nodes.size(); i++)
        {
            if(newValue <= nodes[i]->GetValue())
            {
                first->SetConnected(true);
                second->SetConnected(true);
                first->SetBinValue(0);
                second->SetBinValue(1);
                nodes.insert(nodes.begin()+i, new Node(0, newValue, first, second));
                break;
            }
            if(i == nodes.size()-1)
            {
                first->SetConnected(true);
                second->SetConnected(true);
                first->SetBinValue(0);
                second->SetBinValue(1);
                nodes.push_back(new Node(0, newValue, first, second));
                break;
            }
        }
    }
}


void Huffman::CreateCodeTable(std::vector<Node*>& nodes)
{
    std::string text = GetNextBinKey(nodes, nodes.back(), "");
    std::cout << text << std::endl;
}

std::string Huffman::GetNextBinKey(Node *nextNode, std::string txt)
{
    if(nextNode->GetBinValue() == 0) txt += "0";
    if(nextNode->GetBinValue() == 1) txt += "1";
    
    if(nextNode->GetNode1() == 0)
    {
        if(nextNode->GetNode2() == 0)
        {
            return txt;
        }
        else
        {
            return GetNextBinKey(nextNode->GetNode2(), txt);
        }
    }
    else
    {
        return GetNextBinKey(nextNode->GetNode1(), txt);
    }
}*/