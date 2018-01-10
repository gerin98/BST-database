#include "TreeNode.h"
#include "DBentry.h"
#include <string>
#include <iostream>

//WORKS
TreeNode::TreeNode()
{
  entryPtr = NULL;
  left = NULL;
  right = NULL;
}

TreeNode::TreeNode(DBentry* _entryPtr)
{
  entryPtr = _entryPtr;
  left = NULL;
  right = NULL;
}
//WORKS
TreeNode::~TreeNode()
{
  //not sure if this WORKS
  //test out other functions without this first to make sure it doesnt uneccessarily delete
  delete entryPtr;
}
//WORKS
//only call this function if valueExists returns false
void TreeNode::insertTN(DBentry* v)
{
  //check if tree is empty first
  if(entryPtr == NULL){
    entryPtr = v;
    return;
  }

  if(entryPtr->getName() == v->getName()){
    return;
  }

  //assume that v does not already exist in the tree and is able to be inserted
  if(v->getName() < entryPtr->getName()){
    //insert to the left
    if(left == NULL){
      //nothing to the left, lowest value
      left = new TreeNode(v);
    }
    else{
      //recursion: call this function again repeatedly, moving down the tree
      //until you find the right place to insert
      left->insertTN(v);
    }
  }
  else{
    //insert to the right
    if(right == NULL){
      //nothing to the right
      right = new TreeNode(v);
    }
    else{
      //recursion: call this function again repeatedly, moving down the tree
      //until you find the right place to insert
      right->insertTN(v);
    }
  }
}
//WORKS
//prints the whole tree
/*
void TreeNode::print_inorder()
{
    if(entryPtr != NULL){
        if(left != NULL)
          left->print_inorder();
        
        if(entryPtr->getActive() == 1){
            cout << entryPtr->getName() << " : " << entryPtr->getIPaddress() << " : " << "active" << endl;
        }
        else
            cout << entryPtr->getName() << " : " << entryPtr->getIPaddress() << " : " << "inactive" << endl;
        
        if(right != NULL)
          right->print_inorder();
    }
}*/
/*
//only call this function if valueExists returns false
void TreeNode::print_one(string key)
{
  if(key == entryPtr->getName()){
    //found
    if(entryPtr->getActive() == 1){
        cout << entryPtr->getName() << " : " << entryPtr->getIPaddress() << " : " << "active" << endl;
    }
    else
        cout << entryPtr->getName() << " : " << entryPtr->getIPaddress() << " : " << "inactive" << endl;
  }
  //use recursion to traverse the whole binary tree
  if(left != NULL)
    left->print_one(key);
  if(right != NULL)
    right->print_one(key);
}*/
/*
//returns name of lowest node in the tree
string TreeNode::minimum()
{
  string key = "";

  if(left != NULL)
    key = left->minimum();
  else
    key = entryPtr->getName();
  return key;
}
*/
string TreeNode::maximum_Name()
{
  string key = "";

  if(right != NULL)
    key = right->maximum_Name();
  else
    key = entryPtr->getName();
  return key;
}

unsigned int TreeNode::maximum_IPaddress()
{
  unsigned int key = 0;

  if(right != NULL)
    key = right->maximum_IPaddress();
  else
    key = entryPtr->getIPaddress();
  return key;
}

bool TreeNode::maximum_Active()
{
  bool key = false;

  if(right != NULL)
    key = right->maximum_Active();
  else
    key = entryPtr->getActive();
  return key;
}
/*
//valueExists and checkValue assumes the input is a pointer to DBentry
//may have to change input to string later on
bool TreeNode::valueExists(string v)
{
  bool check = false;

  if(entryPtr->getName() == v){
    return true;
  }
  if(v < entryPtr->getName()){
    //search left
    if(left == NULL){
      //nothing to the left
      return false;
    }
    else{
      //recursion
      check = left->valueExists(v);
      return check;
    }
  }
  else{
    //search right
    if(right == NULL){
      //nothing to the right
      return false;
    }
    else{
      check = right->valueExists(v);
      return check;
    }
  }
}
*/


////////////////////////////////////////////////////////////////////////////////
TreeNode* TreeNode::valueExists(string v, TreeNode* pp)
{
  TreeNode* check = NULL;
  
  //list is empty or no entry
  if(entryPtr == NULL){
    return NULL;
  }
  
  //match found at node 
  if(entryPtr->getName() == v){
    //return pointer to node
    return pp;
  }
  
  if(v < entryPtr->getName()){
    //search left
    if(left == NULL){
      //nothing to the left
      return NULL;
    }
    else{
      //recursion
      check = left->valueExists(v, left);
      return check;
    }
  }
  else{
    //search right
    if(right == NULL){
      //nothing to the right
      return NULL;
    }
    else{
      check = right->valueExists(v,right);
      return check;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////


/*
//implement a find value function in treeDB that traverses the tree and calls
//this function at every node to determine if the value is found
bool TreeNode::checkValue(DBentry* v)
{
  if(entryPtr->getName() == v->getName())
    return true;
  else
    return false;
}
*/
//first check if node exists before performing this delete function
void TreeNode::del(string s, TreeNode *& pp)
{
  if(s < entryPtr->getName()){
    //if value is less, go to left branch
    if(left != NULL)      //recursion
      left->del(s, left);
    return;
  }
  if(s > entryPtr->getName()){
    //if value is greater, go to right branch
    if(right != NULL)      //recursion
      right->del(s,right);
      return; //break after deleting so program doesnt keep deleting as it recursively goes back up the list
  }
  //otherwise: if program reaches this point, node is found
  /*********************************** case 1 **********************************
                                  NODE IS A LEAF
  *****************************************************************************/
  if((left == NULL) && (right == NULL)){
    pp = NULL;
    delete this;
  }

  /*********************************** case 2 **********************************
                              NODE HAS ONE BRANCH
  *****************************************************************************/
  else if((left == NULL) && (right != NULL)){
    pp = right;
    right = NULL;
    delete this;
  }
  else if((left != NULL) && (right == NULL)){
    pp = left;
    left = NULL;
    delete this;
  }

  /*********************************** case 3 **********************************
                             NODE HAS TWO BRANCHES
  *****************************************************************************/
  else{
    //delete the node and replace it with the maximum node in the left subtree
    //this can be done by determining the maximum node, replacing the node to be
    //deleted with this value, and then deleting the maximum node
    string temp1 = left->maximum_Name();
    unsigned int temp2 = left->maximum_IPaddress();
    bool temp3 = left->maximum_Active();

    entryPtr->setName(temp1);
    entryPtr->setIPaddress(temp2);
    entryPtr->setActive(temp3);

    left->del(temp1,left);
  }
  return;
}

//this function deletes TreeNodes properly but need to make it also delete
//DBentry as well. Maybe use a destructor

void TreeNode::delete_all(TreeNode*& pp)
{
  if(pp == NULL)
    return;

  left->delete_all(left);
  right->delete_all(right);
  pp = NULL;
  delete this;

}


//THESE ALL WORK
void TreeNode::setLeft(TreeNode* newLeft)
{
  left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight)
{
  right = newRight;
}

TreeNode* TreeNode::getLeft() const
{
  return left;
}

TreeNode* TreeNode::getRight() const
{
  return right;
}

DBentry* TreeNode::getEntry() const
{
  return entryPtr;
}


void TreeNode::activeCount(int &counter)
{
     
    //if(entryPtr != NULL){
        if(left != NULL)
          left->activeCount(counter);
        
        if(entryPtr->getActive() == 1)
            counter++;
               
        if(right != NULL)
          right->activeCount(counter);
    //}
    
}
//counter = 0
void TreeNode::probeCount(string name, int &counter, int &flag){

    
    if(entryPtr->getName() == name){
        flag = 1;
        counter++;
        return;
    }
    
    if(left != NULL){
        left->probeCount(name, counter, flag);
        
        
    }
    
    if(right != NULL){
        if(flag == 1){
            counter++;
            return;
        }
        right->probeCount(name, counter, flag);
    }
    
    if(flag == 1)
        counter++;
}

