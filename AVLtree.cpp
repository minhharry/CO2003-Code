#include<iostream>
#include<memory>
#define MOD 1000000007

#ifdef cbaaabc
#define deb(x) cerr << "[DEBUG] "<< #x << '=' << x << endl
#else
#define deb(x) 0
#endif

using namespace std;
int totalAllocated = 0;
int totalFreed = 0;
void* operator new(size_t size)
{
    //cout << "Allocating " << size << " bytes" << endl;
    totalAllocated += size;
    return malloc(size);
}
void operator delete(void* memory, size_t size)
{
    //cout << "Deallocating "  << size << " bytes" << endl;
    totalFreed += size;
    free(memory);
}
class Node
{
public:
    int value = 0;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(){};
    Node(int value): value(value) {};
    Node(int value, Node* left, Node* right): value(value), left(left), right(right){};

};
class AVLTree
{
private:
    Node* root;
    static int height(Node* x)
    {
        if (x) return x->height;
        return 0;
    }
    static int getBalance(Node* x)
    {
        return height(x->left) - height(x->right);
    }
    static void rotateRight(Node* &root)
    {
        Node* temp = root->left;
        Node* temp2 = root->left->right;
        temp->right = root;
        root->left = temp2;
        root->height = max(height(root->left), height(root->right))+1;
        root = temp;
        root->height = max(height(root->left), height(root->right))+1;
    }
    static void rotateLeft(Node* &root)
    {
        Node* temp = root->right;
        Node* temp2 = root->right->left;
        temp->left = root;
        root->right = temp2;
        root->height = max(height(root->left), height(root->right))+1;
        root = temp;
        root->height = max(height(root->left), height(root->right))+1;
    }
    static void balanceTree(Node* &root)
    {
        int balanceFactor = getBalance(root);
        if (balanceFactor > 1 && getBalance(root->left)>=0)
        {
            rotateRight(root);
            return;
        }
        if (balanceFactor > 1 && getBalance(root->left)<=-1)
        {
            rotateLeft(root->left);
            rotateRight(root);
            return;
        }
        if (balanceFactor < -1 && getBalance(root->right)<=0)
        {
            rotateLeft(root);
            return;
        }
        if (balanceFactor < -1 && getBalance(root->right)>=1)
        {
            rotateRight(root->right);
            rotateLeft(root);
            return;
        }
    }
    static Node* insertNode(Node* root, int value)
    {
        if (root==nullptr)
        {
            root = new Node(value);
            root->height = 1;
            return root;
        }
        if (value < root->value)
        {
            root->left = insertNode(root->left, value);
        } else if (value > root->value)
        {
            root->right = insertNode(root->right, value);
        } else
            return root;

        root->height = max(height(root->left), height(root->right))+1;
        balanceTree(root);
        return root;
    }
    static Node* minValueNode(Node* x)
    {
        Node* current = x;
        while (current->left)
            current = current->left;
        return current;
    }
    static Node* deleteNode(Node* root, int value)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (value == root->value)
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                Node* temp = root;
                root = nullptr;
                delete temp;
            }
            else if (root->left != nullptr && root->right == nullptr)
            {
                Node* temp = root;
                root = root->left;
                delete temp;
            }
            else if (root->left == nullptr && root->right != nullptr)
            {
                Node* temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->left != nullptr && root->right != nullptr)
            {
                Node* temp = minValueNode(root->right);
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->value);
            }
        } else if (value < root->value)
        {
            root->left = deleteNode(root->left, value);
        } else if (value > root->value)
        {
            root->right = deleteNode(root->right, value);
        }
        if (root)
        {
            root->height = max(height(root->left), height(root->right))+1;
            balanceTree(root);
        }
        return root;
    }
    static void printTreePreorder(Node* x, int space=0)
    {
        for (int i = 0; i<space; ++i) cout << " ";
        if (x) cout << x->value << endl; else cout << "N" << endl;
        if (x==nullptr) return;
        printTreePreorder(x->left, space+4);
        printTreePreorder(x->right, space+4);
    }
    static void printTreeInorder(Node* x, int space=0)
    {
        if (x==nullptr)
        {
            for (int i = 0; i<space; ++i) cout << " ";
            cout << "N" << endl;
            return;
        }
        printTreeInorder(x->left, space+4);
        for (int i = 0; i<space; ++i) cout << " ";
        cout << x->value << endl;
        printTreeInorder(x->right, space+4);
    }
    static bool isExist(Node* x, int value)
    {
        if (x==nullptr) return false;
        if (x->value==value) return true;
        if (x->value > value) return isExist(x->left, value);
        return isExist(x->right, value);
    }
public:
    AVLTree()
    {
        root = nullptr;
    }
    ~AVLTree()
    {
        while (root) deleteNode(root->value);
    }
    void insertNode(int value)
    {
        root = insertNode(root, value);
    }
    void deleteNode(int value)
    {
        root = deleteNode(root, value);
    }
    void printTree(string type="LNR")
    {
        if (type=="LNR") printTreeInorder(root);
        if (type=="NLR") printTreePreorder(root);
    }
    bool isExist(int value)
    {
        isExist(root, value);
    }
};

int main()
{
    // freopen("debug.out", "w", stdout);
    {
        AVLTree a;
        for (int i = 0; i<20; ++i) a.insertNode(i);
        a.printTree();
    }

    deb(totalAllocated);
    deb(totalFreed);
    return 0;
}














