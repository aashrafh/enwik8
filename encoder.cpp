#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <chrono>
typedef long long ll;

std::queue<char> buffer;

std::string calBits(const ll &data, const ll &numberOfBits)
{
    std::string res = "";
    ll i = 0;
    for (ll i = 0; i < numberOfBits; i++)
        res += (((data >> (numberOfBits - i - 1)) & 0x01) + '0');
    return res;
}

void writeToFile(std::string bits, std::ofstream &enwik8Enco)
{
    //write to file
    for (int i = 0; i < bits.size(); i++)
        buffer.push(bits[i]);
    while (buffer.size() > 8)
    {
        char deco = 0;
        for (int i = 0; i < 8; i++)
            if (!buffer.empty())
            {
                bool bit = buffer.front() - '0';
                buffer.pop();
                deco = deco | (bit << (7 - i));
            }
        enwik8Enco.put(deco);
    }
}

//LZW Encoding
void encode(std::ifstream &enwik8, std::ofstream &enwik8Enco)
{
    std::cout << "LZW and Variable-Length-Coding Encoding...\n";
    std::cout.flush();
    std::unordered_map<std::string, ll> dct;
    for (int i = 0; i < 256; i++)
        dct[std::string(1, (char)(i))] = i;

    char symbol;
    ll n, numberOfBits = 8, lastCode = 256;
    //can be replaced with 8 !!
    // while ((1 << (numberOfBits - 1)) < dct.size())
    //     numberOfBits++;
    std::string match = "";

    enwik8Enco.put(0xff);
    while (enwik8.get(symbol))
    {
        std::string tMatch = match + symbol;
        if (dct.find(tMatch) != dct.end())
            match = tMatch;
        else
        {
            ll code = dct[match];
            std::string bits = calBits(code, numberOfBits);
            n += bits.size();

            writeToFile(bits, enwik8Enco);

            dct[tMatch] = lastCode++;
            if (dct.size() > ((1 << numberOfBits) - 1))
                numberOfBits++;
            match = symbol;
        }
    }

    ll code = dct[match];
    std::string bits = calBits(code, numberOfBits);
    n += bits.size();

    writeToFile(bits, enwik8Enco);
    char deco = 0;
    for (int i = 0; !buffer.empty(); i++)
    {
        bool bit = buffer.front() - '0';
        buffer.pop();
        deco = deco | (bit << (7 - i));
    }
    enwik8Enco.put(deco);

    int paddingBits = (8 - (n % 8) % 8);
    char numberOfPadding = 0;
    for (int i = 0; i < 3; i++)
    {
        numberOfPadding <<= 1;
        numberOfPadding |= (paddingBits >> (2 - i));
    }
    enwik8Enco.seekp(0, std::ios::beg);
    enwik8Enco.put(numberOfPadding);
    enwik8Enco.close();
    enwik8.close();
}

int main()
{
    std::ifstream enwik8("enwik8", std::ios::binary);
    std::ofstream enwik8Enco("enwik8Enco", std::ios::binary);
    std::chrono::high_resolution_clock::time_point st = std::chrono::high_resolution_clock::now();
    encode(enwik8, enwik8Enco);
    std::chrono::high_resolution_clock::time_point ed = std::chrono::high_resolution_clock::now();
    std::cout << "Encoding time in seconds: " << std::chrono::duration_cast<std::chrono::duration<double>>(ed - st).count() << "\n";
}