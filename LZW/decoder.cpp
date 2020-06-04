#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <chrono>
typedef long long ll;

ll calMatch(std::string &data, const ll &numberOfBits)
{
    ll match = 0;
    ll i = 0;
    for (ll i = 0; i < numberOfBits; i++)
    {
        match <<= 0x01;
        match |= (data[i] - '0');
    }
    return match;
}
void decode(std::ifstream &enwik8Enoc, std::ofstream &enwik8Deco)
{
    std::cout << "LZW and Variable-Length-Coding Decoding...\n";
    std::cout.flush();

    int paddingBits = 0;
    char numberOfPadding;
    enwik8Enoc.get(numberOfPadding);
    for (int i = 0; i < 3; i++)
    {
        paddingBits <<= 1;
        paddingBits |= ((numberOfPadding >> (2 - i)) & 0x01);
    }

    std::unordered_map<ll, std::string> dct;
    for (int i = 0; i < 256; i++)
        dct[i] = std::string(1, (char)(i));

    char symbol;
    ll numberOfBits = 8, lastCode = 0x100;
    std::string buffer = "";
    bool change = false;

    while (!enwik8Enoc.eof() || !buffer.empty())
    {
        while (buffer.size() < numberOfBits)
        {
            enwik8Enoc.get(symbol);
            int sz = enwik8Enoc.peek() == EOF ? 8 - paddingBits : 8;
            for (int i = 0; i < sz; i++)
                buffer += ((symbol >> (7 - i)) & 0x01) + '0';
        }

        ll tMatch = calMatch(buffer, numberOfBits);
        buffer.erase(0, numberOfBits);

        if (change)
        {
            std::string t = dct[dct.size() - 1];
            t[t.size() - 1] = dct[tMatch][0];
            dct[dct.size() - 1] = t;
        }
        else
            change = true;

        std::string code = dct[tMatch];
        for (int i = 0; i < code.size(); i++)
            enwik8Deco.put(code[i]);
        dct[lastCode++] = dct[tMatch] + "$";
        if (dct.size() > ((0x01 << numberOfBits) - 1))
            numberOfBits++;
    }
    enwik8Deco.close();
    enwik8Enoc.close();
}

int main()
{
    std::ifstream enwik8("enwik8Enco", std::ios::binary);
    std::ofstream enwik8Enco("enwik8Deco", std::ios::binary);
    std::chrono::high_resolution_clock::time_point st = std::chrono::high_resolution_clock::now();
    decode(enwik8, enwik8Enco);
    std::chrono::high_resolution_clock::time_point ed = std::chrono::high_resolution_clock::now();
    std::cout << "Decoding time in seconds: " << std::chrono::duration_cast<std::chrono::duration<double>>(ed - st).count() << "\n";
}