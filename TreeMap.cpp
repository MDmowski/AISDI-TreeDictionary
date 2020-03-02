#include <utility>
#include <iostream>

template <typename KeyType, typename ValueType>
class TreeMap
{
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;

    struct BSTNode
    {
        BSTNode(mapped_type data) : father(nullptr), left(nullptr), right(nullptr), data(data){};

        BSTNode *father, *left, *right;
        key_type key;
        mapped_type data;
    };

    BSTNode *root;
    int treeSize;

    void insertElement(key_type key, mapped_type data)
    {
        BSTNode *newNode;

        if (root == nullptr)
        {
            root = new BSTNode(data);
            root->key = key;
            treeSize++;
            return;
        }
        splay(key);
        if (key > root->key) // Going left side
        {
            newNode = new BSTNode(data);
            newNode->key = key;
            newNode->left = root;
            root->father = newNode;
            newNode->right = root->right;
            if(root->right)
                root->right->father = newNode;
            root->right = nullptr;
            treeSize++;
            root = newNode;
        }
        else if (key < root->key) //Going right
        {
            newNode = new BSTNode(data);
            newNode->key = key;
            newNode->right = root;
            root->father = newNode;
            newNode->left = root->left;
            if(root->left)
                root->left->father = newNode;
            root->left = nullptr;
            treeSize++;
            root = newNode;
        }
        else{
            root->data = data;
        }
    }

    void leftRotation(BSTNode *a)
    {
        BSTNode *b = a->right, *parent = a->father;

        if (b) //Checking is there anything to rotate
        {
            a->right = b->left;
            if (a->right)
            {
                a->right->father = a; //Setting father of right son of a
            }

            b->left = a;
            b->father = parent;
            a->father = b;

            if (parent) //Checking if a wasn't root
            {
                if (parent->left == a)
                    parent->left = b; //setting b as new left child of old parent of a
                else
                    parent->right = b; //setting b as new right child of old parent of a
            }
            else
                root = b;
        }
    }

    void rightRotation(BSTNode *a)
    {
        BSTNode *b = a->left, *parent = a->father;

        if (b) //is there anything to rotate
        {
            a->left = b->right;
            if (a->left)
            {
                a->left->father = a; //setting new father of new left son
            }

            b->right = a;
            b->father = parent;
            a->father = b;

            if (parent) //Checking if a wasnt root
            {
                if (parent->left == a)
                    parent->left = b; //setting b as new left child of parent of a
                else
                    parent->right = b; //setting b as new left child of parent of a
            }
            else
                root = b;
        }
    }

    void deleteRecursive(BSTNode *node)
    {
        if (node)
        {
            deleteRecursive(node->left);  // recursive left side delete
            deleteRecursive(node->right); // recursive right side delete
            delete node;                  //delete Node
        }
    }

    void splay(key_type key)
    {
        BSTNode *x, *y;

        x = root; //Going from root to the wanted node
        if (x)    //is BST empty?
        {
            do
            {
                if (x->key == key){
                    break;
                }
                y = x; //Remembering the node in case there's no node with selected key
                x = key < x->key ? x->left : x->right;
            } while (x);
            // Closest element as root
            if (!x)
                x = y;
            while (true) //going with selected node x to the root
            {
                if (!x->father)
                {
                    root = x;
                    break; //no father = root -> end
                }

                if (!x->father->father)
                { //father of x is root then needs rotation
                    if (x->father->left == x)
                    {
                        rightRotation(x->father); //ZIG
                    }
                    else
                    {
                        leftRotation(x->father); //ZAG
                    }
                    root = x;
                    break; //x is root now -> end
                }

                if ((x->father->father->left == x->father) && (x->father->left == x))
                { //ZIG-ZIG
                    rightRotation(x->father->father);
                    rightRotation(x->father);
                    continue;
                }

                if ((x->father->father->right == x->father) && (x->father->right == x))
                { //ZAG-ZAG
                    leftRotation(x->father->father);
                    leftRotation(x->father);
                    continue;
                }

                if (x->father->right == x)
                { //ZAG-ZIG
                    leftRotation(x->father);
                    rightRotation(x->father);
                }
                else
                { //ZIG-ZAG
                    rightRotation(x->father);
                    leftRotation(x->father);
                }
            }
        }
    }

    void displayRecursive(BSTNode *n, int spacing)
    {
        if (!n)
        {
            return;
        }

        spacing += 10;
        displayRecursive(n->right, spacing);
        for (int i = 10; i < spacing; ++i)
        {
            std::cout << " ";
        }
        std::cout << n->key << ":" << n->data << "\n";
        displayRecursive(n->left, spacing);
    }

public:
    TreeMap() : root(nullptr), treeSize(0) {}
    ~TreeMap()
    {
        deleteRecursive(root);
        treeSize = 0;
    }

    void display() { displayRecursive(root, 0); }

    bool isEmpty() const
    {
        return root == nullptr ? true : false;
    }

    void insert(const key_type &key, const mapped_type &value)
    {
        insertElement(key, value);
    }

    void insert(const value_type &key_value)
    {
        insertElement(key_value.first, key_value.second);
    }

    mapped_type &operator[](const key_type &key)
    {
        splay(key);
        if (root != nullptr && root->key == key)
            return root->data;
        else
            throw std::runtime_error("No such element.");
    }

    const mapped_type &value(const key_type &key)
    {
        splay(key);
        if (root != nullptr && root->key == key)
            return root->data;
        else
            throw std::runtime_error("No such element.");
    }

    bool contains(const key_type &key)
    {
        splay(key);
        if (root != nullptr && root->key == key)
            return true;
        else
        {
            return false;
        }
    }

    int size() const
    {
        return treeSize;
    }
};
