#include <iostream>
#include "final.hpp"
using namespace std;
#define COUNT 10
/**
Create a node with key as data
**/

Node* BST:: createNode(int data)
{
    Node* newNode = new Node;
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BST::BST()
{
}

/**
parameterized constructor. It will create the root and put the data in the root.
**/

BST::BST(int data)
{
    root = createNode(data);
    cout<< "New tree created with "<<data<<endl;
}

/**
Destructor
**/

BST::~BST(){
     destroyNode(root);
}


Node* BST::getRoot(){
    return root;
}

 /**
 This function will destroy the subtree rooted at currNode.
 Think about in what order should you destroy. POSTORDER. or right-left-root
 **/
void BST:: destroyNode(Node *currNode){
     if(currNode!=NULL)
     {
         destroyNode(currNode->left);
         destroyNode(currNode->right);

         delete currNode;
         currNode = NULL;
     }
 }

/*
Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void BST::print2DUtilHelper(Node *currNode, int space)
{
    // Base case
    if (currNode == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtilHelper(currNode->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", currNode->key);

    // Process left child
    print2DUtilHelper(currNode->left, space);
}

void BST::print2DUtil( int space)
{
  print2DUtilHelper(root, space);
}



//---------------------------- INSERT NODE IN THE TREE --------------------------------------

/**
This function will add the data in the tree rooted at currNode.
We will call this function from addNode.
**/

Node* BST:: addNodeHelper(Node* currNode, int data)
{
    if(currNode == NULL){
        return createNode(data);
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;

}


void BST:: addNode(int data)
{
    root = addNodeHelper(root, data);
    cout<<data<<" has been added"<<endl;
}

//-----------------------------------------PRINT TREE (INORDER TRAVERSAL)--------------------------------

/** This function will traverse the tree in-order and print out the node elements.
printTree() function will call this function.
**/

void BST:: printTreeHelper(Node* currNode){
     if(currNode)
     {
        printTreeHelper( currNode->left);
        cout << " "<< currNode->key;
        printTreeHelper( currNode->right);
     }
 }

void BST:: printTree(){
     printTreeHelper(root);
     cout<<endl;
}

 //------------------------------------------------SEARCH A KEY------------------------------------------
 /** This function will search the data in a tree
     We will call this function from searchKey.
 **/

Node* BST::searchKeyHelper(Node* currNode, int data){
    if(currNode == NULL)
        return NULL;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

// This function will return whether a key is in the tree
bool BST::searchKey(int key){
    Node* tree = searchKeyHelper(root, key);
    if(tree != NULL) {
        return true;
    }
    cout<<"Key not present in the tree"<<endl;
    return false;
}

//--------------------------- Get Max and Min value Node ------------------------------------------------

Node* BST::getMaxValueNode(Node* currNode){
    if(currNode->right == NULL){
        return currNode;
    }
    return getMaxValueNode(currNode->right);
}

Node* BST::getMinValueNode(Node* currNode){

    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}


//--------------------------- Delete a Node ------------------------------------------------

// This function deletes the Node with 'value' as it's key. This is to be called inside removeRange() function
// SILVER TODO Complete the implementation of this function
Node* BST::deleteNode(Node *currNode, int value)
{

  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->key)
  {
    currNode->left = deleteNode(currNode->left, value);
  }
  else if(value > currNode->key)
  {
    currNode->right = deleteNode(currNode->right, value);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode->left == NULL && currNode->right == NULL)
    {
        delete(currNode);
        return NULL;
    }
    //TODO Case : Only right child
    else if(currNode->left == NULL)
    {
        struct Node *temp = currNode -> right;
        delete(currNode);
        return temp;
    }
    //TODO Case : Only left child
    else if(currNode->right == NULL)
    {
        struct Node *temp = currNode -> left;
        delete(currNode);
        return temp;
    }
    //TODO Case: Both left and right child
    else
    {
      ///Replace with Minimum from right subtree
        Node* sp = root-> right;
        Node* s = root -> right;//find successor
        while(s->left != NULL)
        {
            sp = s;
            s = s ->left;
        }
        sp->left = s->right;//delte s since its always left child of its parent
        currNode->key = s->key;//copy s data to currNode
        delete s;//delete s and return currNode
        return currNode;
    }

  }
return currNode;
}

// This function removes nodes with values in the range low and high.
// You need to call deleteNode() function inside this function

void BST::removeRange(int low, int high)
{
  for(int i=low; i<=high; i++){
    root=deleteNode(root,i);
  }
}

// ------------------------------------ Check for a Valid BST ------------------------------------------------

// GOLD TODO

bool BST::valid(Node*root, int min, int max)
{
    if(root == NULL)
    {
     return true;
    }
    if(root->key < min || root ->key > max)//like if outside range?
    {
        return false;
    }
    int minL = getMinValueNode(root->left) -> key;
    int maxL = getMaxValueNode(root->left) -> key;
    int minR = getMinValueNode(root->right) -> key;
    int maxR = getMaxValueNode(root->right) -> key;
    return valid(root->left,minL,maxL) && valid(root->right,minR,maxR);
}
bool BST::isValidBST()
{
  //TODO Uncomment below and Complete this function, you can use any logic (add a helper function if you want)
  //everything in left subtree should be smaller than nodes value
  //nodes value should be < than everything in the right subtree
  int a = getMinValueNode(root) -> key;
  int b = getMinValueNode(root) -> key;
  bool returnVal = valid(root, a, b);
  return returnVal; //huh?
}



//hi ok starting here is the stuff for linked list? 

void LinkedList::insert(LLNode* prev, int newKey){

  //Check if head is Null i.e list is empty
  if(head == NULL){
    head = new LLNode;
    head->key = newKey;
    head->next = NULL;
  }

  // if list is not empty, look for prev and append our LLnode there
  else if(prev == NULL)
  {
      LLNode* newNode = new LLNode;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }

  else{

      LLNode* newNode = new LLNode;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
  }

// Print the keys in your list
void LinkedList::printList(){
  LLNode* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
LLNode* LinkedList::searchList(int key) {

    LLNode* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}

 bool HashTavle::insertItem(int key)//tbh not sure exactly what the boolean is for
 {
     //uh im just saying if i could add it then it returns true?
     bool return_Val = false;
     int index = hashFunction(key);
     if(HashTable[index]->key == NULL)//if its empty
     {
         HashTable[index]->key = key;//overwrite with key given
        //i do believe the next function should be done in the constructor?
        //bc the array should just have a bunch of nulls in it??
        //wait maybe nvm bc its for the ll duh
        return_Val = true;
     }
     else//meaning there is already a value in its spot
     {
         hashNode* ptr = HashTable[index];// first item in bucket
         hashNode* n = new hashNode;//new item
         n->key = key; //initializing key
         n->next = NULL; // initializing next to nothing
         //next need to add to end of linked list in the bucket
         while(ptr->!= NULL)//while next element != NULL
         {
             ptr = ptr->next;//go through to next
         }
         //ptr is now pointing to last item in list
         ptr->next = n; // linking the last item in list to newly created item
        return_Val = true;

     }
     
 }

int HashTable::NumberOfItemsInIndex(int index)
{
    int count = 0;
    if(HashTable[index]->key == NULL)
    {
        return count;//return zero bc nothing in it
    }
    else
    {
        count++;//count first item
        hashNode* ptr = HashTable[index];//points to being of list thats in tht bucket
        while(ptr->next != NULL) //as long as next ptr is not nothing
        {
            count++; //increment counter
            ptr=ptr->next; // move ptr to next item
        }
    }
    return count;//by now we have all items accounted for in that list
}
void HashTable:: printTable()
{
    int num; //num of elements in each buckets
    for(int i = 0; i < tableSize; i++)//remember tableSize is the no. of buckets (linked lists)
    {
        num = NumberOfItemsInIndex(i);//assign number to num
        cout << "------------------\n";
        cout << "index = " << i << endl;
        cout << HashTable[i]->key << endl;
        cout << "# of items = " << number << endl;
        cout << "------------------\n";
    }
}

hashNode* HashTable:: searchItem(int key)
{
    int bucket = hashFunction(key);//unsigned a problem? ... this is where we find the bucket its stored in
    bool foundKey = false;
    hashNode* ptr = HashTable[bucket]; pointer that points to first item in the bucket
    while(ptr != NULL) //scan entire list (as long as ptr points to something)
    {
        if(ptr->key == key)//seeing if the keys match
        {
            foundKey = true;//mark that we found a match
        }
        ptr = ptr->next;
    }
    if(foundKey == true)//if we kow we found the value then return the ptr val
    {
        return ptr;//ptr should be pointng to the right one
    }
    else
    {
        //should I return null? 
        return NULL; //i decided to but we will have to check for it when we use this function...
        //possibly w an if statement... if (returnVal != NULL)... blah blah blah
    }
}
