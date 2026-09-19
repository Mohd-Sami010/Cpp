#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f, Node *l = NULL, Node *r = NULL)
    {
        ch = c;
        freq = f;
        left = l;
        right = r;
    }
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq; // min-heap
    }
};

void printCodes(Node *root, string code)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        cout << root->ch << " : " << code << endl;
        return;
    }
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main()
{
    vector<char> chars = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (int i = 0; i < chars.size(); i++)
        pq.push(new Node(chars[i], freq[i]));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node *combined = new Node('$', left->freq + right->freq, left, right);
        pq.push(combined);
    }

    Node *root = pq.top();
    cout << "Huffman Codes:\n";
    printCodes(root, "");
    return 0;
}