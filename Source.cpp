#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "LZW.cpp"
using namespace std;
struct suffix
{
	int idx;
	int rank[2];
};

int suffixCompare(suffix a, suffix b)
{
	return a.rank[0] == b.rank[0] ? a.rank[1] < b.rank[1] ? 1 : 0 : a.rank[0] < b.rank[0] ? 1 : 0;
}
suffix * firstStep(int n, char *s) {
	suffix *suffixes = new suffix[n];
	for (int i = 0; i < n; i++)
	{
		suffixes[i].idx = i;
		suffixes[i].rank[0] = s[i] - 'a';
		suffixes[i].rank[1] = ((i + 1) < n) ? (s[i + 1] - 'a') : -1;
	}
	cout << "first loop\n";
	return suffixes;
}
int *suffixArray(char *s, int n)
{
	/*int n = strlen(s);*/
	/*suffix *suffixes = firstStep(n, s);*/
	/*vector<suffix> suffixes(n, s);*/
	/*struct suffix suffixes[n];*/

	/*for (int i = 0; i < n; i++)
	{
		suffixes[i].idx = i;
		suffixes[i].rank[0] = s[i] - 'a';
		suffixes[i].rank[1] = ((i + 1) < n) ? (s[i + 1] - 'a') : -1;
	}
	cout << "first loop\n";*/
	suffix *suffixes = new suffix[n];
	for (int i = 0; i < n; i++)
	{
		suffixes[i].idx = i;
		suffixes[i].rank[0] = s[i] - 'a';
		suffixes[i].rank[1] = ((i + 1) < n) ? (s[i + 1] - 'a') : -1;
	}
	/*cout << "first loop\n";*/
	 sort(suffixes, suffixes+n, suffixCompare);
	 /*cout << "first sort\n";*/

	 int *indices = new int[n];
	 for (int i = 4; i < 2 * n; i *= 2)
	 {
	     int rank = 0, prevRank = suffixes[0].rank[0];
	     suffixes[0].rank[0] = rank;
	     indices[suffixes[0].idx] = 0;

	     for (int j = 1; j < n; j++)
	     {
	         if (suffixes[j].rank[0] == prevRank && suffixes[j].rank[1] == suffixes[j - 1].rank[1])
	         {
	             prevRank = suffixes[j].rank[0];
	             suffixes[j].rank[0] = rank;
	         }
	         else
	         {
	             prevRank = suffixes[j].rank[0];
	             suffixes[j].rank[0] = ++rank;
	         }
	         indices[suffixes[j].idx] = j;
	     }

	     for (int j = 0; j < n; j++)
	     {
	         int nextIdx = suffixes[j].idx + i / 2;
	         suffixes[j].rank[1] = nextIdx < n ? suffixes[indices[nextIdx]].rank[0] : -1;
	     }

	     sort(suffixes, suffixes+n, suffixCompare);
	 }
	 delete[] indices;
	 /*cout << "the fucking loop\n";*/
	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].idx;
	delete[] suffixes;
	return suffixArr;
}
//struct suffix
//{
//	int index; // To store original index 
//	int rank[2]; // To store ranks and next rank pair 
//};
//
//// A comparison function used by sort() to compare two suffixes 
//// Compares two pairs, returns 1 if first pair is smaller 
//int cmp(struct suffix a, struct suffix b)
//{
//	return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
//		(a.rank[0] < b.rank[0] ? 1 : 0);
//}
//
//// This is the main function that takes a string 'txt' of size n as an 
//// argument, builds and return the suffix array for the given string 
//int *buildSuffixArray(char *txt, int n)
//{
//	// A structure to store suffixes and their indexes 
//	struct suffix suffixes[n];
//
//	// Store suffixes and their indexes in an array of structures. 
//	// The structure is needed to sort the suffixes alphabatically 
//	// and maintain their old indexes while sorting 
//	for (int i = 0; i < n; i++)
//	{
//		suffixes[i].index = i;
//		suffixes[i].rank[0] = txt[i] - 'a';
//		suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
//	}
//
//	// Sort the suffixes using the comparison function 
//	// defined above. 
//	sort(suffixes, suffixes + n, cmp);
//
//	// At this point, all suffixes are sorted according to first 
//	// 2 characters.  Let us sort suffixes according to first 4 
//	// characters, then first 8 and so on 
//	int ind[n];  // This array is needed to get the index in suffixes[] 
//				 // from original index.  This mapping is needed to get 
//				 // next suffix. 
//	for (int k = 4; k < 2 * n; k = k * 2)
//	{
//		// Assigning rank and index values to first suffix 
//		int rank = 0;
//		int prev_rank = suffixes[0].rank[0];
//		suffixes[0].rank[0] = rank;
//		ind[suffixes[0].index] = 0;
//
//		// Assigning rank to suffixes 
//		for (int i = 1; i < n; i++)
//		{
//			// If first rank and next ranks are same as that of previous 
//			// suffix in array, assign the same new rank to this suffix 
//			if (suffixes[i].rank[0] == prev_rank &&
//				suffixes[i].rank[1] == suffixes[i - 1].rank[1])
//			{
//				prev_rank = suffixes[i].rank[0];
//				suffixes[i].rank[0] = rank;
//			}
//			else // Otherwise increment rank and assign 
//			{
//				prev_rank = suffixes[i].rank[0];
//				suffixes[i].rank[0] = ++rank;
//			}
//			ind[suffixes[i].index] = i;
//		}
//
//		// Assign next rank to every suffix 
//		for (int i = 0; i < n; i++)
//		{
//			int nextindex = suffixes[i].index + k / 2;
//			suffixes[i].rank[1] = (nextindex < n) ?
//				suffixes[ind[nextindex]].rank[0] : -1;
//		}
//
//		// Sort the suffixes according to first k characters 
//		sort(suffixes, suffixes + n, cmp);
//	}
//
//	// Store indexes of all sorted suffixes in the suffix array 
//	int *suffixArr = new int[n];
//	for (int i = 0; i < n; i++)
//		suffixArr[i] = suffixes[i].index;
//
//	// Return the suffix array 
//	return  suffixArr;
//}
char *findLastChar(char *s, int *suffixArr)
{
	int n = strlen(s);
	char *bwtArr = (char *)malloc(n * sizeof(char));
	int i;
	for (i = 0; i < n; i++)
	{
		int j = suffixArr[i] - 1;
		if (j < 0)
			j += n;
		bwtArr[i] = s[j];
	}
	bwtArr[i] = '\0';

	return bwtArr;
}

char *BWT()
{
	string inputFile = "enwik8";
	ifstream inputStream;
	inputStream.open(inputFile);
	if (!inputStream)
		exit(1);

	string line, text = "";
	vector<int> suff;
	int cnt  = 0;
	while (getline(inputStream, line))
	{
		cout << ++cnt << endl;
		text += line;
		/*if (cnt == 1128024) {
			int x;
			cin >> x;
		}*/
		char *enwik8 = new char[(int)line.size()];
		for (int i = 0; i < line.size(); i++) enwik8[i] = line[i];
		int *suffixArr = suffixArray(enwik8, strlen(enwik8));
		for (int i = 0; i < line.size(); i++) suff.push_back(suffixArr[i]);
		delete[] enwik8;
		delete[] suffixArr;
	}
	inputStream.close();
	int n = text.size();
	cout << "Reading the text is DONE\n";
	char *enwik8 = (char *)malloc(n * sizeof(char));
	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++) enwik8[i] = text[i];
	for (int i = 0; i < n; i++) suffixArr[i] = suff[i];
	 char *bwtArr = findLastChar(enwik8, suffixArr);
	 cout << "BWT is DONE\n";

	return bwtArr;
}
int main()
{
	char *text = BWT();
	 string str(text, text + strlen(text));
	 LZW lzw;
	 vector<int> enco = lzw.encode(str);
	 cout << "LZW: DONE!\n";
	 unsigned sz = enco.size();
	 std::ofstream outfile("bwtLZW", std::ofstream::binary);
	 outfile.write(reinterpret_cast<char *>(&sz), sizeof(unsigned));
	 outfile.write(reinterpret_cast<const char *>(&enco[0]), sizeof(uint8_t) * enco.size());
	/*system("PAUSE");*/
	return 0;
}