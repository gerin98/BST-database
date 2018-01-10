#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"

#include <iostream>

TreeDB::TreeDB()
{
  root = new TreeNode;
}
TreeDB::~TreeDB()
{
  //this should call the delete_all function and then delete TreeDB
  root->delete_all(root);
}

// inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry)
{
  //if(root->getEntry() == NULL)
    //tree is empty

  root->insertTN(newEntry);
  return true;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name)
{

  TreeNode* check = NULL;
  int counter = 0;
  int flag = 0;
  
  check = root->valueExists(name,root);
  if(check == NULL){
    //root->probeCount(name, counter, flag);
    //probesCount = counter;
    return NULL;
  }
  else{
    root->probeCount(name, counter, flag);
    probesCount = counter;
    return check->getEntry();
  }
    
    
  
}



// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name)
{
  //check that value exists in main before calling delete
  root->del(name, root);
  
  //if the root now points to NULL, create a new tree node for it to point to
  if(root == NULL){
      root = new TreeNode;
  }
  
  return true;
}

// deletes all the entries in the database.
void TreeDB::clear()
{
    //may have to pass root by reference
  root->delete_all(root);
  //root = NULL;
  if(root == NULL){
      root = new TreeNode;
  }
  
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const
{
    //int counter = 0;
    //int flag = 0;
    //root->probeCount(name, counter, flag);
    cout << probesCount << endl;
    
}


// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const
{
    int d;
    int counter = 0;
    root->activeCount(counter);
    //probesCount = counter;
    cout << counter << endl;
    return;
}

void TreeDB::printOne(string name)
{
    TreeNode* temp = root;
    print_one(temp,name);
}

void TreeDB::printAll()
{
    print_inorder(root);
}

void TreeDB::print_inorder(TreeNode* node)
{
    //node = root;
    if(node->getEntry() != NULL){
        if(node->getLeft() != NULL)
          print_inorder(node->getLeft());
        
        if(node->getEntry()->getActive() == 1){
            cout << node->getEntry()->getName() << " : " << node->getEntry()->getIPaddress() << " : " << "active" << endl;
        }
        else
            cout << node->getEntry()->getName() << " : " << node->getEntry()->getIPaddress() << " : " << "inactive" << endl;
        
        if(node->getRight() != NULL)
          print_inorder(node->getRight());
    }
}

void TreeDB::print_one(TreeNode* node, string key)
{
  if(key == node->getEntry()->getName()){
    //found
    if(node->getEntry()->getActive() == 1){
        cout << node->getEntry()->getName() << " : " << node->getEntry()->getIPaddress() << " : " << "active" << endl;
    }
    else
        cout << node->getEntry()->getName() << " : " << node->getEntry()->getIPaddress() << " : " << "inactive" << endl;
  }
  //use recursion to traverse the whole binary tree
  if(node->getLeft() != NULL)
    print_one(node->getLeft(),key);
  if(node->getRight() != NULL)
    print_one(node->getRight(),key);
}

