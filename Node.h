/* 
 * File:   Node.h
 * Author: daniel
 *
 * Created on February 26, 2015, 3:50 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <string>

class Node {
public:
    Node(char character, int value);
    Node(char character, int value, Node *nextNode);
    ~Node();
    
    char GetCharacter(){ return m_Character; }
    int GetValue(){ return m_Value; }
    int GetBinValue(){ return m_BinValue; }
    bool IsConnected(){ return m_IsConnected; }
    Node* GetNextNode(){ return m_NextNode; }
    //std::string GetBinKey(){ return m_BinKey; } 
    
    void SetCharacter( char character ){ m_Character = character; }
    void SetValue( int value ){ m_Value = value; }
    void SetBinValue( int binValue ){ m_BinValue = binValue; }
    void SetConnected(bool connected){ m_IsConnected = connected; }
    void SetNextNode( Node *node ){ m_NextNode = node; }
    //void SetBinKey(const std::string& binKey){ m_BinKey = binKey; }
private:
    char m_Character;
    int m_Value;
    int m_BinValue;
    bool m_IsConnected;
    //std::string m_BinKey;
    
    Node *m_NextNode;
};

/*
class Node {
public:
    Node(char character, int value);
    Node(char character, int value, Node *node1, Node *node2);
    ~Node();
    
    char GetCharacter(){ return m_Character; }
    int GetValue(){ return m_Value; }
    int GetBinValue(){ return m_Value; }
    bool IsConnected(){ return m_IsConnected; }
    Node* GetNode1(){ return m_Node1; }
    Node* GetNode2(){ return m_Node2; }
    std::string GetBinKey(){ return m_BinKey; } 
    
    void SetCharacter( char character ){ m_Character = character; }
    void SetValue( int value ){ m_Value = value; }
    void SetBinValue( int binValue ){ m_BinValue = binValue; }
    void SetConnected(bool connected){ m_IsConnected = connected; }
    void SetNode1( Node *node ){ m_Node1 = node; }
    void SetNode2( Node *node ){ m_Node2 = node; }
    void SetBinKey(const std::string& binKey){ m_BinKey = binKey; }
private:
    char m_Character;
    int m_Value;
    int m_BinValue;
    bool m_IsConnected;
    std::string m_BinKey;
    
    Node *m_Node1;
    Node *m_Node2;
};*/

#endif	/* NODE_H */

