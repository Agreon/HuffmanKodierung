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
}

Node::~Node()
{
}

