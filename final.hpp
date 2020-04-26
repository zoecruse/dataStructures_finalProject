#ifndef final_HPP
#define final_HPP
#include <string>
//hellooooooooo
using namespace std;

struct Node{
    int key;
    Node* left ;
    Node* right;
};

struct LLNode 
{
    int key;
    LLNode* next;
};



class LinkedList
{
  private:
    LLNode *head;

  public:
    LinkedList(){
    	head = nullptr;
    }
    void insert(LLNode *prev, int newKey);
    LLNode* searchList(int key);
    void printList();
};

class BST{
    private:
        Node* root;
        Node* createNode(int data);//done
        /** since root is a private member we need helper functions
         to access root for insertion, searching and printing.
         These helper functions is used for performing recursion **/
        Node* addNodeHelper(Node*, int);//DONE
        void printTreeHelper(Node*); //DONE
        void print2DUtilHelper(Node *, int); //DONE

        Node* searchKeyHelper(Node*, int); //done

        Node* getMinValueNode(Node*); //DONE
        Node* getMaxValueNode(Node*); //DONE

        void destroyNode(Node *root); //DONE

        Node* deleteNode(Node*, int);//DONE


    public:
        Node* getRoot();                // Returns the root of the tree; DONE
        void addNode(int);              // function to insert a node in the tree. DONE
        bool searchKey(int);            // function to search a data in the tree DONE
        void printTree();               //function to print the tree DONE
        BST();                          // default constructor DONE
        BST(int data);                  // parameterized constructor DONE
        ~BST();                         // destructor DONE
        //after this idk if any of it is necessary? like fr
        void removeRange(int, int); //DONE but unnecessary 
        void print2DUtil(int); //DONE
        bool isValidBST(); //DOne
        bool valid(Node*, int, int); //DONE

};
#endif//this might be an issue...



struct hashNode
{
    int key;
    struct hashNode* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    hashNode* *table;
    int numOfcolision =0;
    hashNode* createNode(int key, hashNode* next);
public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertItem(int key);

    // hash function to map values to key
    unsigned int hashFunction(int key);

    void printTable();
    int getNumOfCollision();
    //hi im adding in the next one
    int NumberOfItemsInIndex(int index);
    //^^ I dont know if I can like actually put it here but id have to send in the hashtable if i dont

    hashNode* searchItem(int key);
};

#endif
