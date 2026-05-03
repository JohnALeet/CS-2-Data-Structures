#include <iostream>
#include <vector>
#include <list>
#include <sstream> //string stream
#include <fstream>

using namespace std;

int hashFunction(string, int);
int nextPrime(int);
bool isPrime(int);
void cleanWord(string&);

int main(int argc, char* argv[]){
    string inStr;
    // string inLine = "";
    vector<list<string>> hashTable;
    int collisions = 0;
    

    // for manual input to hash:

    // cout << "enter string to hash: ";
    // getline(cin, inStr);


    // to hash text from some file: (uncomment inLine declaration)

    // ifstream fin;
    // fin.open("filename");
    // while(getline(fin, inLine)){
    //     inStr += inLine;
    // }

    int inStrSize = inStr.length();

    hashTable.resize(nextPrime(inStrSize*2));

    istringstream iss;
    iss.str(inStr);
    string token;

    while(iss >> token){
        cleanWord(token);
        // hashTable.at(hashFunction(token, hashTable.size())).push_back(token);
        int hashIdx = hashFunction(token, hashTable.size());
        if(!hashTable.at(hashIdx).empty()){
            for(string word : hashTable.at(hashIdx)){
                if(word != token){
                    collisions++;
                    break;
                }
            }
        }
        hashTable.at(hashIdx).push_back(token);
    }
    
    for(int i = 0; i < hashTable.size(); i++){
        if(hashTable.at(i).empty()) continue;
        // exclude empty lines when printing
        
        cout << "hash[" << i << "]: ";
        for(string word : hashTable.at(i)){
            cout << word << ", ";
        }
        cout << endl;
    }
    cout << "collisions: " << collisions << endl;
    cout << "tablesize: " << hashTable.size() << endl;
    return 0;
}


int hashFunction(string str, int tblSize)
{
     //SDMB Hash
    unsigned long hash = 0;
    for (auto ch : str)
    {
        hash = ch + (hash << 6)+ (hash << 16) - hash;
    }
    return (hash^tblSize);

    //Takes the number, * by 32 and adds the original character value, and does that for each character, adding them to the hash value.
    // unsigned long hash = 5381;
    // for (auto ch : str)
    // {
    //     hash = ch + (hash << 5) + hash;
    // }
    // return (hash % tblSize);

    // int p = 31;
    // int hashval = 0;
    // int p_pow = 1;

    // for(char ch : str){
    //     hashval = (hashval + (ch - 'a' + 1) * p_pow);
    //     p_pow = (p_pow * p)  % tblSize;
    // }
    // return hashval % tblSize;


    
    // lose-lose algorithm

    // int hash = 0;
    // for(char ch : str){
    //     hash += ch;
    // }
    // return hash%tblSize;
}

int nextPrime(int n){
    while(!isPrime(n)) n++;
    return n;
}
bool isPrime(int n){
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n%2 == 0 || n%3 == 0) return false;
    for(int i = 5; i*i <= n; i+= 6){

    }
    // more stuff

    // filler
    return false;
}

void cleanWord(string& str){
    string cleanedWord = "";
    for(char ch : str){
        if(isalpha(ch)) cleanedWord += tolower(ch);
    }
    str = cleanedWord;
}