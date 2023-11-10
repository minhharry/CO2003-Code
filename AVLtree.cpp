#include<iostream>
#include<string>
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
template<class T>
class AVLTree
{
private:
    class Node
    {
    public:
        T key = 0;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node() {};
        Node(const T& key): key(key) {};
        Node(const T& key, Node* left, Node* right): key(key), left(left), right(right) {};

    };
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
        root->height = max(height(root->left), height(root->right)) + 1;
        root = temp;
        root->height = max(height(root->left), height(root->right)) + 1;
    }
    static void rotateLeft(Node* &root)
    {
        Node* temp = root->right;
        Node* temp2 = root->right->left;
        temp->left = root;
        root->right = temp2;
        root->height = max(height(root->left), height(root->right)) + 1;
        root = temp;
        root->height = max(height(root->left), height(root->right)) + 1;
    }
    static void balanceTree(Node* &root)
    {
        int balanceFactor = getBalance(root);
        if (balanceFactor > 1 && getBalance(root->left) >= 0)
        {
            rotateRight(root);
            return;
        }
        if (balanceFactor > 1 && getBalance(root->left) <= -1)
        {
            rotateLeft(root->left);
            rotateRight(root);
            return;
        }
        if (balanceFactor < -1 && getBalance(root->right) <= 0)
        {
            rotateLeft(root);
            return;
        }
        if (balanceFactor < -1 && getBalance(root->right) >= 1)
        {
            rotateRight(root->right);
            rotateLeft(root);
            return;
        }
    }
    static Node* insertNode(Node* root, const T& key)
    {
        if (root == nullptr)
        {
            root = new Node(key);
            root->height = 1;
            return root;
        }
        if (key < root->key)
        {
            root->left = insertNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = insertNode(root->right, key);
        }
        else
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;
        balanceTree(root);
        return root;
    }
    static Node* minKeyNode(Node* x)
    {
        Node* current = x;
        while (current->left)
            current = current->left;
        return current;
    }
    static Node* deleteNode(Node* root, const T& key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (key == root->key)
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
                Node* temp = minKeyNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        else if (key < root->key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = deleteNode(root->right, key);
        }
        if (root)
        {
            root->height = max(height(root->left), height(root->right)) + 1;
            balanceTree(root);
        }
        return root;
    }
    static void printTreePreorder(Node* x, int space = 0)
    {
        for (int i = 0; i < space; ++i) cout << " ";
        if (x) cout << x->key << endl;
        else cout << "N" << endl;
        if (x == nullptr) return;
        printTreePreorder(x->left, space + 4);
        printTreePreorder(x->right, space + 4);
    }
    static void printTreeInorder(Node* x, int space = 0)
    {
        if (x == nullptr)
        {
            for (int i = 0; i < space; ++i) cout << " ";
            cout << "N" << endl;
            return;
        }
        printTreeInorder(x->left, space + 4);
        for (int i = 0; i < space; ++i) cout << " ";
        cout << x->key << endl;
        printTreeInorder(x->right, space + 4);
    }
    static T findKey(Node* x, const T& key)
    {
        if (x == nullptr) return T();
        if (x->key == key) return x->key;
        if (x->key > key) return findKey(x->left, key);
        return findKey(x->right, key);
    }
    static bool isExist(Node* x, const T& key)
    {
        if (x == nullptr) return false;
        if (x->key == key) return true;
        if (x->key > key) return isExist(x->left, key);
        return isExist(x->right, key);
    }
public:
    AVLTree()
    {
        root = nullptr;
    }
    ~AVLTree()
    {
        while (root) deleteNode(root->key);
    }
    void insertNode(const T& key)
    {
        root = insertNode(root, key);
    }
    void deleteNode(const T& key)
    {
        root = deleteNode(root, key);
    }
    void printTree(string type = "LNR")
    {
        if (type == "LNR") printTreeInorder(root);
        if (type == "NLR") printTreePreorder(root);
    }
    T findKey(const T& key) const
    {
        return findKey(root, key);
    }
    bool isExist(const T& key) const
    {
        return isExist(root, key);
    }
};
struct Point2D
{
    int x, y;

};
bool operator<(const Point2D &a, const Point2D &b)
{
    return a.x < b.x;
}
bool operator>(const Point2D &a, const Point2D &b)
{
    return a.x > b.x;
}
bool operator==(const Point2D &a, const Point2D &b)
{
    return a.x == b.x;
}
ostream& operator<<(ostream &os, const Point2D &a)
{
    os << "(" << a.x << "," << a.y << ")";
}
int main()
{
    //freopen("debug.out", "w", stdout);
    {
        AVLTree<int> a;
        for (int i = 20; i >= 0; --i) a.insertNode(rand()%100);
        a.printTree();
        cout << a.isExist(68) << endl;
    }

    deb(totalAllocated);
    deb(totalFreed);
    return 0;
}














