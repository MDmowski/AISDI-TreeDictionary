#include <iostream>
#include <algorithm>

class AVL
{

private:

    // 
    struct node
    {
        node(int data) : left(NULL), right(NULL), height(0), data(data) {}
        node* left;
        node* right;
        int height;
        int data;
    };

    // Pointer to root
    node* root;

    // Recursive delete method
    void deleteRecursive(node* n)
    {
        if(n == NULL)
            return;
        deleteRecursive(n->left);
        deleteRecursive(n->right);
        delete n;
    }

    // Get height of a node taking into account NULL pointer
    int height(node* n)
    {
        return (n == NULL ? 0 : n->height);
    }

    int getBalance(node* n)
    {
        if(n == NULL)
            return 0;
        else
            return height(n->left) - height(n->right);
    }

    // Rotates
    // Functions receive refs to pointers
    node* singleRightRotate(node* &n)
    {
        // Rotation
        node* u = n->left;
        n->left = u->right;
        u->right = n;

        // Update heights
        n->height = std::max(height(n->left), height(n->right)) + 1;
        u->height = std::max(height(u->left), height(u->right)) + 1;
        return u;
    }

    node* singleLeftRotate(node* &n)
    {
        // Rotation
        node* u = n->right;
        n->right = u->left;
        u->left = n;

        // Update heights
        n->height = std::max(height(n->left), height(n->right)) + 1;
        u->height = std::max(height(u->left), height(u->right)) + 1;

        return u;
    }

    node* doubleLeftRotate(node* &n)
    {
        n->right = singleRightRotate(n->right);
        return singleLeftRotate(n);
    }

    node* doubleRightRotate(node* &n)
    {
        n->left = singleLeftRotate(n->left);
        return singleRightRotate(n);
    }
    

    // Recursive insertion of a key, returns new root of the tree
    node* insertRecursive(node* n, int data)  
    {  
        // Normal insertions
        if (n == NULL)  
            return(new node(data));  
    
        // Standard insertion
        if (data < n->data)  
            n->left = insertRecursive(n->left, data);  
        else if (data > n->data)  
            n->right = insertRecursive(n->right, data);  
        else // Equal datas are not allowed in BST  
            return n;  
    
        // Update height of current node
        n->height = std::max(height(n->left), height(n->right)) + 1;  
    
        // Get balance
        int balance = getBalance(n);  
    
    
        // Unbalanced node
        // LL case  
        if (balance > 1 && data < n->left->data)  
            return singleRightRotate(n);  
    
        // RR case  
        if (balance < -1 && data > n->right->data)  
            return singleLeftRotate(n);  
    
        // LR case  
        if (balance > 1 && data > n->left->data)  
        {  
            return doubleRightRotate(n);  
        }  
    
        // RL case  
        if (balance < -1 && data < n->right->data)  
        {  
            return doubleLeftRotate(n);  
        }  
    
        return n;  
    }  


public:
    AVL(): root(NULL) {}
    ~AVL(){ deleteRecursive(root); }

    void display(){ displayRecursive(this->root, 0); }
    void insert(int data){ root = insertRecursive(this->root, data); }
};


int main()
{
    AVL tree = AVL();
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.display();

}
