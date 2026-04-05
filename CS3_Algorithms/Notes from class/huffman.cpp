#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class Node{
    private:
        char _ch;
        int _freq;
        Node* _left;
        Node* _right;
    public:
        Node(char ch = '\0', int freq = 0, Node* left = nullptr, Node* right = nullptr) : _ch(ch), _freq(freq), _left(left), _right(right){}

    char getCh() { return _ch; }
    int getFreq() { return _freq; }
    Node* getLeft() { return _left; }
    Node* getRight() { return _right; }

};

// comparitor
class Compare{
    public:
        bool operator() (Node* left, Node* right){
            return left->getFreq() > right->getFreq();
        }
};

Node* buildHuffmanTree(string text);
void printHuffman(Node* root, string str, unordered_map<char, string>& huffmanCode);
string encodeStr(string text, unordered_map<char, string> huffmanCode);
void decode(string str, Node* root);


int main(int argc, char* argv[]){
    string inputStr = "aaaaaabbbbcccd";
    Node* root;
    unordered_map<char, string> huffmanCode;
    root = buildHuffmanTree(inputStr);
    printHuffman(root, "", huffmanCode);

    string huffmanEncoded = encodeStr(inputStr, huffmanCode);
    cout << huffmanEncoded << endl;

    cout << "Decoded string: " << endl;
    decode(huffmanEncoded, root);
    cout << endl;

    cout << "Saved space = " << (float)(inputStr.length()*8)/huffmanEncoded.length() << " times smaller!" << endl;
    return 0;
}


Node* buildHuffmanTree(string text){
    // take in node, add to vector in order
    priority_queue<Node*, vector<Node*>, Compare> pq;
    unordered_map<char, int> charFreq;
    // charFreq = {}
    // use dictionary in python ^
    // priority queue is called heap queue in python
    // key is a char
    
    
    // count frequency of each letter
    for(char ch : text){
        charFreq[ch]++;
    }
    // push values onto queue based on the unordered map
    for(auto it = charFreq.begin(); it != charFreq.end(); it++){
        pq.push(new Node(it->first, it->second));
    }

    // makes node that has left and right based on the top 2 items in the priority queue
    while(pq.size() > 1){
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        // '\0' is a null character
        Node* newNode = new Node('\0', left->getFreq() + right->getFreq(), left, right);
        pq.push(newNode);
    }
    // last node in the queue is the root of the tree
    Node* root = pq.top();
    return root;
}

// prints tree in increasing order using inorder print
void printHuffman(Node* root, string str, unordered_map<char, string>& huffmanCode){
    if(root == nullptr) return;
    
    // adds 0 or 1 for the binary expression of the thing based on where in the tree the value is
    printHuffman(root->getLeft(), str + "0", huffmanCode);
    // prints the frequency of each character
    if(root->getCh() != '\0') cout << root->getCh() << ":" << root->getFreq() << " ";
    printHuffman(root->getRight(), str + "1", huffmanCode);
    
    // prints out the binary value of each character
    if(!root->getLeft() && !root->getRight()){ // if roots are nullptrs
        cout << root->getCh() << ": " << str << endl;
        huffmanCode[root->getCh()] = str;
    }
}

string encodeStr(string text, unordered_map<char, string> huffmanCode){
    string toReturn = "";
    for(auto ch : text){
        toReturn += huffmanCode[ch];
    }
    return toReturn;
}

void decode(string str, Node* root){
    // input example: 1010100010010

    Node* curNode = root;
    for(auto ch : str){
        if(ch == '0'){
            // traverse left side
            curNode = curNode->getLeft();
        }
        else{
            // traverse right side
            curNode = curNode->getRight();
        }
        if(curNode->getLeft() == curNode->getRight()){
            // if at the end of the tree
            cout << curNode->getCh();
            curNode = root;
        }
    }
}