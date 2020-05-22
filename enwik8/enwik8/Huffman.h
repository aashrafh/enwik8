#pragma once
#include "Node.h"
#include <queue>
#include <map>
#include <string>
class Huffman
{
public:
	Huffman();

	void compress(const std::map<char, unsigned long long> freq);
	void decompress(const std::map<char, std::string> codes, std::string encoded);

	std::map<char, std::string> getCodes();
	std::string getDecodedString();
	virtual ~Huffman();
private:
	std::map<char, std::string> codes;
	std::string decoded = "";

	void constructCodes(Node *node, std::string code = "0");
	struct PriorityQueueCompareUtility {
		bool operator()(Node &a, Node &b) {
			return a.getFreq() > b.getFreq();
		}
	};
};

