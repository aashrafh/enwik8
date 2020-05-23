#include "Huffman.h"
#include <iostream>
#include <map>
#include <string>


Huffman::Huffman()
{
}

void Huffman::compress(const std::map<char, unsigned long long> freq)
{
	std::priority_queue<Node, std::vector<Node>, PriorityQueueCompareUtility> nodes;
	
	for (auto symbol : freq) if (symbol.second != 0) {
		Node node((char)symbol.first, symbol.second);
		nodes.push(node);
	}

	while (nodes.size() > 1) {
		Node *n1 = new Node();
		*n1 = nodes.top();
		nodes.pop();

		Node *n2 = new Node();
		*n2 = nodes.top();
		nodes.pop();

		Node node('\0', (*n1).getFreq() + (*n2).getFreq());
		node.setNodes(n1, n2);
		nodes.push(node);
	}
	
	Node root = nodes.top();
	nodes.pop();

	this->constructCodes(&root);
}

void Huffman::decompress(const std::map<char, std::string> codes, std::string encoded)
{
	std::map<std::string, char> decodedCodes;

	for (auto code : codes) decodedCodes[code.second] = code.first;

	std::string code = "";
	for (unsigned int i = 0; i < (unsigned int)encoded.size(); i++) {
		code += encoded[i];
		if (decodedCodes.count(code) > 0) {
			if (decodedCodes[code] == '\0') break;
			this->decoded += decodedCodes[code];
			code = "";
		}
	}
}


std::map<char, std::string> Huffman::getCodes()
{
	return this->codes;
}

std::string Huffman::getDecodedString()
{
	return this->decoded;
}

Huffman::~Huffman()
{
}

void Huffman::constructCodes(Node * node, std::string code)
{
	if (node->getLeftNode() != nullptr) constructCodes(node->getLeftNode(), code + "1");

	if (node->getRightNode() != nullptr) constructCodes(node->getRightNode(), code + "0");

	if (node->getSymbol() != '\0') this->codes[node->getSymbol()] = code;

	return;
}
