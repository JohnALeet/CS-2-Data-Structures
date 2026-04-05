#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;
class Node
{
private:
    char _ch;
    int _freq;
    Node* _left;
    Node* _right;


public:
    Node( char ch = '\0', int freq = 0, Node* left = nullptr, Node* right = nullptr) : _ch(ch), _freq(freq)
    
    char getch() {return _ch;}
    int getFreq() {return _freq;}
    Node* getLeft() {return _left;}
    Node* getRight() {return _right;}
    
};


class Compare
{
    public:
    bool operator() (Node* left, Node* right)
    {
        return left->getFreq() > right->getFreq();
    }


};

Node* buildHuffmanTree(string text);
void printHuffman(Node* root, unordered_map<char, string> & huffmanCode);
string encodeStr(string text, unordered_map<char, string> huffmanCode );
void decode(string str, Node* root);

int main(int argc, char* argv[])
{
    string inputStr = "aaaaaaahhhhhhhh123"
    Node* root;
    unordered_map<char, string> huffmanCode;

    root = buildHuffmanTree(inputStr);
    print(huffmanroot)
    string encodeStr = encodeStr(inputStr, )
    cout << huffmanCode << endl;

    cout << "Decode string: " << endl;
    decode(huffmanCode, root);
    cout << endl;

    //cout << "Saved space = " << (inputStr.length()*8)

    return 0;
}

Node* buildHuffmanTree(string text)
{
    unordered_map<char, int> charFreq;
    priority_queue <Node*, vector<Node*>, Compare > pq; //You can use Heapify in Python to sort elements in a list.
    for (char ch : text)
    {
        charFreq[ch]++; //Now that we've counted the frequencies of all characters, how do we weight them? Priority que!
    }

    for (auto it = charFreq.begin(); it != charFreq.end(); it++)
    {
        pq.push(new Node(it->first, it->second));
    }//Now we need to pop two off the tree, compare them and push them together.

    while(pq.size() > 1)
    {//This compares the two nodes and compares them. The priority que is filled with null nodes.
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node ('\0', left->getFreq() + right->getFreq(), left, right);
        pq.push(newNode);
    }
    Node* root = pq.top();
    return root;
}

void printHuffman(Node* root, unordered_map<char, string>&huffmanCode)
{

    if (root == nullptr) return;
    if(!root-> getLeft()&& !root->getRight())
    {
        cout << root->getCh() << ":" << str << endl;
        huffmanCode[root->getCh()] = str;
    }
    printHuffman(root->getLeft());
    if (root -> getCh != '\0') cout << root -> getCh() << :


}

void decode(string str, Node* root)
{
    //input: something 
    Node* curNode = root;

    for (auto ch : str)
    {
        if(ch == '0')
        {
            curNode = curNode->getLeft();
        }
        else
        {
            curNode = curNode -> getRight();

        }
        if (curNode->getleft() == curNode->getRight
        {
            cout << currNode -> getCh();
            curNode = root;
        }
    }
}