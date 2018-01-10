#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    //DECLARE A TREE IN THE VERY BEGINNING
    //THE DEFAULT CONSTRUCTOR WILL CREATE A ROOT POINTER FOR THIS TREE
    TreeDB* tree = new TreeDB;
    
    //declare a dummy variable for DBentry and a dummy boolean variable
    //DBentry* dummy = new DBentry;
    DBentry* dummy = NULL;
    bool temp = false;
     
    string line = "", command = "", key = "", status2 = "";
    unsigned int address = 0;
    bool status = false;
    
    
    cout << "> ";
    getline(cin,line);
    
    while(!cin.eof()){
        
        stringstream lineStream (line);
        lineStream >> command;
        
        if(command == "insert"){
            lineStream >> key >> address >> status2;            
            if(status2 == "active")
                status = 1;
            else
                status = 0;
            
            dummy = tree->find(key);
            if(dummy == NULL){
                //key wasn't found so insert
                //dynamically create an entry
                DBentry* entry = new DBentry(key, address, status);
                //insert entry
                temp = tree->insert(entry);
                cout << "Success" << endl;
            }
            else{
                //key already exists
                cout << "Error: entry already exists" << endl;
            }
        }
        else if(command == "find"){
            lineStream >> key;
            
            dummy = tree->find(key);
            if(dummy == NULL){
                cout << "Error: entry does not exist" << endl;
            }
            else{
                tree->printOne(key);
            }

        }
        else if(command == "remove"){
            lineStream >> key;
            
            dummy = tree->find(key);
            if(dummy == NULL){
                cout << "Error: entry does not exist" << endl;
            }
            else{
                tree->remove(key);
                cout << "Success" << endl;
            }
            
        }
        else if(command == "printall"){
            
            tree->printAll();
            
        }
        else if(command == "printprobes"){  //to do
            lineStream >> key;
            
            dummy = tree->find(key);
            if(dummy == NULL){
                cout << "Error: entry does not exist" << endl;
            }
            else{
                tree->find(key);
                tree->printProbes();
            }
            
        }
        else if(command == "removeall"){
            
            tree->clear();
            cout << "Success" << endl;

            
        }
        else if(command == "countactive"){  //to do
            
            tree->countActive();
            
        }
        else if(command == "updatestatus"){
            lineStream >> key >> status2;            
            
            if(status2 == "active")
                status = 1;
            else
                status = 0;
            
            dummy = tree->find(key);
            if(dummy == NULL){
                cout << "Error: entry does not exist" << endl;
            }
            else{
                dummy->setActive(status);
                cout << "Success" << endl;
            }
        }
        
        
        line = "", command = "", key = "", status2 = "";
        address = 0;
        status = false;
        dummy = NULL;
        
        cout << "> ";
        getline(cin,line);
    }
    
    
    delete tree;
    
    return 0;
}

