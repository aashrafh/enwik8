#include "Node.h"



Node::Node()
{
}

Node::Node(const char symbol, const unsigned long long freq)
{
	this->symbol = symbol;
	this->frequency = freq;
	this->left = nullptr;
	this->right = nullptr;

}

char Node::getSymbol()
{
	return this->symbol;
}

Node * Node::getLeftNode()
{
	return this->left;
}

Node * Node::getRightNode()
{
	return this->right;
}

void Node::setNodes(Node * left, Node * right)
{
	this->left = left;
	this->right = right;
}

unsigned long long Node::getFreq()
{
	return this->frequency;
}

void Node::setFreq(const unsigned long long freq)
{
	this->frequency = freq;
}

Node::~Node()
{
	/*if (this->left != nullptr) delete this->left;
	if (this->right != nullptr) delete this->right;*/
}

bool Node::operator<(const Node & node)
{
	return this->frequency > node.frequency;
}
