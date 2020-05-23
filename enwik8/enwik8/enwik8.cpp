#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "Huffman.h"
using namespace std;
void huffmanTest() {
	string encoded = "";
	char ch;
	ifstream inp;
	inp.open("encoded");
	while (inp.get(ch)) encoded += ch;
	int sz = encoded.size() / 8;
	cout << sz << endl;

	//string inputFile = "enwik8";
	//ifstream inputStream;
	//inputStream.open(inputFile);
	//if (!inputStream) exit(1);

	//string line, text;
	//map<char, unsigned long long> frequency;
	//bool start = true;

	//while (getline(inputStream, line)) {
	//	if (start) start = false;
	//	else frequency['\n']++;

	//	for (auto ch : line) frequency[ch]++;
	//	/*text += line;*/
	//}
	//inputStream.close();

	//if (frequency.size() == 0) {
	//	cout << "Empty Input" << endl;
	//	exit(1);
	//}

	//frequency['\0']++;

	//Huffman *huffman = new Huffman();
	//huffman->compress(frequency);
	//map<char, string> codes = huffman->getCodes();
	///*string encoded = "";*/
	//inputStream.open(inputFile);
	//if (!inputStream) exit(1);
	//text = "";
	//
	//while (getline(inputStream, line)) {
	//	text += line;
	//}
	//inputStream.close();
	//ofstream encoded("encoded", std::ios_base::binary | std::ios_base::out);
	//for (auto ch : text) encoded << codes[ch];

	///*cout << encoded << endl;*/
	//huffman->decompress(codes, encoded);
	//string decoded = huffman->getDecodedString();
	///*cout << decoded << endl;*/

	//decompressedFile.open("myenwik8");
	//decompressedFile << decoded;
	//decompressedFile.close();
}
int main() {

	system("PAUSE");
	return 0;
}