#pragma once
/*
* Author: Ahmed Ashraf
*/
class Node
{
public:
	Node(const char symbol, const unsigned long long freq);
	char &getSymbol();

	Node* getLeftNode();
	Node* getRightNode();
	void setNodes(Node *left, Node *right);

	unsigned long long &getFreq();
	void setFreq(const unsigned long long freq);

	virtual ~Node();

private:
	char symbol;
	Node *left, *right;
	unsigned long long frequency;
};

