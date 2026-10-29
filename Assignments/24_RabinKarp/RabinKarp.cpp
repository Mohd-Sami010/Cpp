#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    const long long base = 256;
    const long long modulus = 1000000007;

    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    vector<size_t> matches;
    if (pattern.empty())
    {
        for (size_t start = 0; start <= text.size(); ++start)
            matches.push_back(start);
    }
    else if (pattern.size() <= text.size())
    {
        long long patternHash = 0;
        long long windowHash = 0;
        long long highestPower = 1;

        for (size_t i = 0; i < pattern.size(); ++i)
        {
            patternHash = (patternHash * base +
                           static_cast<unsigned char>(pattern[i])) %
                          modulus;
            windowHash = (windowHash * base +
                          static_cast<unsigned char>(text[i])) %
                         modulus;
            if (i + 1 < pattern.size())
                highestPower = highestPower * base % modulus;
        }

        for (size_t start = 0; start <= text.size() - pattern.size(); ++start)
        {
            if (patternHash == windowHash &&
                text.compare(start, pattern.size(), pattern) == 0)
                matches.push_back(start);

            if (start < text.size() - pattern.size())
            {
                long long outgoing =
                    static_cast<unsigned char>(text[start]) * highestPower % modulus;
                windowHash = (windowHash - outgoing + modulus) % modulus;
                windowHash =
                    (windowHash * base +
                     static_cast<unsigned char>(text[start + pattern.size()])) %
                    modulus;
            }
        }
    }

    if (matches.empty())
    {
        cout << "Pattern not found.\n";
        return 0;
    }

    cout << "Pattern found at starting indices: ";
    for (size_t i = 0; i < matches.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        cout << matches[i];
    }
    cout << '\n';

    return 0;
}
