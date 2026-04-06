#ifndef BRANCHMANAGER_H
#define BRANCHMANAGER_H

#include <iostream>
#include <string>
#include "VersionManager.h"

using namespace std;

struct VersionNode; // forward

/* BranchNode structure for Singly Linked List */
struct BranchNode {
    string branchName;
    VersionNode* versionHead;
    BranchNode* next;

    BranchNode(string name) {
        branchName = name;
        versionHead = NULL;
        next = NULL;
    }
};

class BranchManager {
private:
    BranchNode* head;
    BranchNode* currentBranch;

public:
    // Constructor:default main 
    BranchManager() {
        head = new BranchNode("main");
        currentBranch = head;
    }

    /* Create Branch */
    void createBranch(string name) {

        // Checking for duplicate
        BranchNode* temp = head;
        while (temp != NULL) {
            if (temp->branchName == name) {
                cout << "Error: Branch '" << name << "' already exists."<<endl;
                return;
            }
            temp = temp->next;
        }

        BranchNode* newBranch = new BranchNode(name);

        // Insert at beginning 
        newBranch->next = head;
        head = newBranch;
    }

    /* Switch Branch */
    void switchBranch(string name) {
        BranchNode* temp = head;

        while (temp != NULL) {
            if (temp->branchName == name) {
                currentBranch = temp;
                return;
            }
            temp = temp->next;
        }

        cout << "Error : Branch '" << name << "' not found."<<endl;
    }

    /* List Branches */
    void listBranches() {

        if (head == NULL) {
            cout << "No branches available."<<endl;
            return;
        }

        BranchNode* temp = head;

        while (temp != NULL) {

            cout << temp->branchName;
            if (temp == currentBranch)
                cout << " (Active)\n";
            else
                cout << endl;

            temp = temp->next;
        }
    }
    //  get active branch 
    BranchNode* getActiveBranch() {
        return currentBranch;
    }
};

#endif // BRANCHMANAGER_H
