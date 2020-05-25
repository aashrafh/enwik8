#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::unordered_map;
class LZW
{
private:
public:
	std::vector<int> encode(string s)
	{
		unordered_map<string, int> dct;
		for (int i = 0; i < 256; i++)
		{
			string ch = "";
			ch += char(i);
			dct[ch] = i;
		}

		string current = "", ch = "";
		current += s[0];
		int code = 256;
		std::vector<int> codes;
		for (int i = 0; i < s.size(); i++)
		{
			if (i != s.size() - 1)
				ch += s[i + 1];
			if (dct.count(current + ch) > 0)
				current = current + ch;
			else
			{
				codes.push_back(dct[current]);
				dct[current + ch] = code;
				code++;
				current = ch;
			}
			ch = "";
		}
		codes.push_back(dct[current]);
		return codes;
	}
	string decode(std::vector<int> decoded)
	{
		string text = "";
		unordered_map<int, string> dct;
		for (int i = 0; i < 256; i++)
		{
			string ch = "";
			ch += char(i);
			dct[i] = ch;
		}

		int old = decoded[0], n;
		string s = dct[old];
		text += s;
		string ch = "";
		int count = 256;
		for (int i = 0; i < decoded.size() - 1; i++)
		{
			n = decoded[i + 1];
			if (dct.count(n) == 0)
			{
				s = dct[old];
				s = s + ch;
			}
			else
				s = dct[n];
			text += s;
			ch = "";
			ch += s[0];
			dct[count] = dct[old] + ch;
			count++;
			old = n;
		}
		return text;
	}
};