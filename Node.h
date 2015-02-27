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
    ~Node();
    
    char GetCharacter(){ return m_Character; }
    int GetValue(){ return m_Value; }
    int GetBinValue(){ return m_BinValue; }
    bool IsConnected(){ return m_IsConnected; }
    Node* GetNextNode(){ return m_NextNode; }
    
    void SetCharacter( char character ){ m_Character = character; }
    void SetValue( int value ){ m_Value = value; }
    void SetBinValue( int binValue ){ m_BinValue = binValue; }
    void SetConnected(bool connected){ m_IsConnected = connected; }
    void SetNextNode( Node *node ){ m_NextNode = node; }
private:
    char m_Character;
    int m_Value;
    int m_BinValue;
    bool m_IsConnected;
    
    Node *m_NextNode;
};

#endif	/* NODE_H */

