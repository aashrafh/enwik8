#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <chrono>
#include "List.cpp"

typedef long long ll;
typedef unsigned int ui;
typedef unsigned char uc;

std::queue<char> buffer;
std::string enwik8Line;

void mtf(std::string &str)
{
    // std::cout << "MTF...\n";
    // std::cout.flush();
    List list;
    for (int i = 0; i < 256; i++)
        list.push_back((unsigned char)i);

    for (unsigned int i = 0; i < str.size(); i++)
    {
        int j = 0;
        for (ListNode *it = list.head; it != NULL; j++, it = it->next)
        {
            if ((unsigned char)str[i] == it->data)
            {
                list.swap_to_front((unsigned char)str[i]);
                str[i] = j;
                break;
            }
        }
    }
}
int bwtCompare(const void *x, const void *y)
{
    int a = *(int *)x, b = *(int *)y, cmp;
    for (ui i = 0; i < enwik8Line.size(); i++)
        if (cmp = (int)enwik8Line[(a + i) % enwik8Line.size()] - (int)enwik8Line[(b + i) % enwik8Line.size()])
            return cmp;
    return 0;
}

std::string bwt()
{
    int *shifts = new int[enwik8Line.size()];
    for (ui i = 0; i < enwik8Line.size(); i++)
        shifts[i] = i;
    std::qsort(shifts, enwik8Line.size(), sizeof(int), &bwtCompare);
    std::string bwtLine = "";
    ui rev = 0;
    for (ui i = 0; i < enwik8Line.size(); i++)
        bwtLine += (shifts[i] != 0 ? enwik8Line[shifts[i] - 1] : (rev = i, enwik8Line[enwik8Line.size() - 1]));
    return bwtLine;
}

std::string clistBits(const ll &data, const ll &numberOfBits)
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
    std::unordered_map<std::string, ll> dct;
    for (int i = 0; i < 256; i++)
        dct[std::string(1, (char)(i))] = i;

    char symbol;
    ll n = 0, numberOfBits = 8, lastCode = 256;
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
            std::string bits = clistBits(code, numberOfBits);
            n += bits.size();

            writeToFile(bits, enwik8Enco);

            dct[tMatch] = lastCode++;
            if (dct.size() > ((1 << numberOfBits) - 1))
                numberOfBits++;
            match = symbol;
        }
    }

    ll code = dct[match];
    std::string bits = clistBits(code, numberOfBits);
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
int min(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    std::ifstream enwik8Src("enwik8", std::ios::binary);
    int cnt = 0;
    std::string tot = "";
    while (std::getline(enwik8Src, enwik8Line))
    {
        tot += enwik8Line;
    }

    std::chrono::high_resolution_clock::time_point st = std::chrono::high_resolution_clock::now();
    enwik8Line = tot; //tot.substr(i, min(10000000, (tot.size() - i)));
    std::string bwtLine = bwt();
    mtf(bwtLine);
    std::ofstream enwik8MTF("mtf");
    enwik8MTF << bwtLine;
    enwik8MTF.close();
    std::ifstream inMTF("mtf", std::ios::binary);
    std::ofstream out("bwtMtfLzwVlc", std::ios_base::app);
    encode(inMTF, out);
    std::chrono::high_resolution_clock::time_point ed = std::chrono::high_resolution_clock::now();
    std::cout << "Encoding time in seconds: " << std::chrono::duration_cast<std::chrono::duration<double>>(ed - st).count() << "\n";
    enwik8Src.close();
    remove("mtf");

    std::ifstream bitsBeforeCompression("enwik8", std::ifstream::ate | std::ifstream::binary);
    int sizeBefore = bitsBeforeCompression.tellg();
    std::ifstream bitsAfterCompression("bwtMtfLzwVlc", std::ifstream::ate | std::ifstream::binary);
    int sizeAfter = bitsAfterCompression.tellg();
    bitsBeforeCompression.close();
    bitsAfterCompression.close();
    double compressionRatio = 1.0 * sizeBefore / sizeAfter;
    std::cout << "Compression Ratio: " << compressionRatio << "\n";
    return 0;
}