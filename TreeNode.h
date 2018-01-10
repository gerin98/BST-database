#ifndef _TREENODE_H
#define _TREENODE_H

#include "DBentry.h"
#include <string.h>

class TreeNode {
  private:
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right;
  public:

    // A useful constructor
    TreeNode(DBentry* _entryPtr);
    TreeNode();
    ~TreeNode();

    //set functions
    void setLeft(TreeNode* newLeft);
    void setRight(TreeNode* newRight);

    //get functions
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    DBentry* getEntry() const;

    //additional functions: may have to make these private functions in TreeDB.h later
    void insertTN(DBentry* v);
        
    string maximum_Name();
    unsigned int maximum_IPaddress();
    bool maximum_Active();
    
    TreeNode* valueExists(string v, TreeNode* pp);
    
    void del(string s, TreeNode *& pp);
    void delete_all(TreeNode*& pp);
    
    void update(string name, bool status);
    void activeCount(int &counter);
    void probeCount(string name, int &counter, int &flag);

};

#endif
