/* 
 * File:   Node.cpp
 * Author: daniel
 * 
 * Created on February 26, 2015, 3:50 PM
 */

#include "Node.h"


Node::Node(char character, int value)
{
    m_Character = character;
    m_Value = value;
    m_BinValue = 0;
    m_IsConnected = false;
    m_NextNode = 0;
    /*m_Node1 = 0;
    m_Node2 = 0;*/
  //  m_BinKey = "";
}

Node::Node(char character, int value, Node *nextNode)
{
    m_Character = character;
    m_Value = value;
    m_BinValue = 0;
    m_IsConnected = false;
    m_NextNode = nextNode;
  //  m_BinKey = "";
}

Node::~Node()
{
}

