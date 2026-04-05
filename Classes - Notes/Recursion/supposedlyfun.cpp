    Node* insert(Node* newRoot, int data);
    void print(Node* root);
    Node* remove(Node* root, int data);
        Node* maxVal(Node* root);

    public:
    Tree() { _root = nullptr; }
    @@ -48,26 +49,32 @@ int main(int argc, char* argv[])
    myTree.insert(15);
    myTree.insert(23);
    myTree.insert(-2);
        myTree.insert(8);
        // myTree.insert(8);
    myTree.insert(9000);
    myTree.insert(69);
        myTree.insert(100);
        myTree.insert(10000);

    myTree.print();
    cout << endl;

    cout << "Enter number to delete: ";
    cin >> toBeDeleted;
    myTree.remove(toBeDeleted);
        // cout << "after remove" << endl;

        myTree.print();
        cout << endl;

    return 0;
    }

    void Tree::remove(int data)
    {
        remove(_root, data);
        _root = remove(_root, data);
    }

    Node* remove(Node* root, int data)
    Node* Tree::remove(Node* root, int data)
    {
    if(root == nullptr) return root;
    if(data < root->getData())
    @@ -78,10 +85,54 @@ Node* remove(Node* root, int data)
    {
    root->setRight(remove(root->getRight(), data));
    }
        else
        {
            //The data exists at this "root"
            if(root->getLeft() == nullptr)
            {
                Node* toReturn = root->getRight();
                delete root;
                return toReturn;
            }
            else if(root->getRight() == nullptr)
            {
                Node* toReturn = root->getLeft();
                delete root;
                return toReturn;
            }
            else
            {
                //Both left and right has a node
                // cout << "DEBUG: " << root << endl;
                Node* largestNode = maxVal(root->getLeft());
                
                root->setData(largest->getData());
                remove(root->getleft(),)

            // largestNode->setRight(root->getRight());
                //largestNode->setLeft(root->getLeft());
                // if(root == _root) _root = largestNode; THE WRONG WAY!!!!
                //delete root;
                // cout << "After updating node" << endl;
                //return largestNode;
            }
        }
        return root;
    }

    Node* Tree::maxVal(Node* root)
    {
        Node* curNode = root;
        Node* parent = root;
        while(curNode->getRight() != nullptr)
        {
            parent = curNode;
            curNode = curNode->getRight();
        }
        parent->setRight(nullptr);
        return curNode;
    }

    void Tree::print()
    {
        // cout << "_root: " << _root << endl;
    print(_root);
    }

    @@ -99,6 +150,7 @@ void Tree::insert(int data)
    {
    // cout << "Inserting " << data << endl;
    _root = insert(_root, data);
        // cout << "_root: " << _root << endl;
    }

    Node* Tree::insert(Node* newRoot, int data)