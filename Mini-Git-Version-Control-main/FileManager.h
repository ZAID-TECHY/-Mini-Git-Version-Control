#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <iostream>
#include "VersionManager.h"

using namespace std;

/* File Node for BST */
struct FileNode
{
    string filename;
    VersionManager versions;

    FileNode* left;
    FileNode* right;

    FileNode(string name)
    {
        filename = name;
        left = NULL;
        right = NULL;
    }
};

class FileManager
{
private:
    FileNode* root;

public:

    FileManager()
    {
        root = NULL;
    }

    /* Insert File used by createfile */
    FileNode* insertFile(FileNode* node, string name)
    {
        if(node == NULL)
        {
            return new FileNode(name);
        }

        if(name < node->filename)
        {
            node->left = insertFile(node->left, name);
        }
        else if(name > node->filename)
        {
            node->right = insertFile(node->right, name);
        }
        else
        {
            cout << "File already exists.\n";
        }

        return node;
    }
    /* Create File will be call in main*/
    void createFile(string name)
    {
        root = insertFile(root, name);
    }

    /* Search File used by showfile*/
    FileNode* searchFile(FileNode* node, string name)
    {
        if(node == NULL)
            return NULL;

        if(node->filename == name)
            return node;

        if(name < node->filename)
            return searchFile(node->left, name);

        return searchFile(node->right, name);
    }
    /* Find File will be call in main*/
    FileNode* findFile(string name)
    {
        return searchFile(root, name);
    }

    /* Find minimum node (used in delete) */
    FileNode* findMin(FileNode* node)
    {
        while(node && node->left != NULL)
            node = node->left;

        return node;
    }

    /* Delete File used by removed file */
    FileNode* deleteFile(FileNode* node, string name)
    {
        if(node == NULL)
            return NULL;

        if(name < node->filename)
        {
            node->left = deleteFile(node->left, name);
        }
        else if(name > node->filename)
        {
            node->right = deleteFile(node->right, name);
        }
        else
        {
            /* Case 1: No child */
            if(node->left == NULL && node->right == NULL)
            {
                delete node;
                cout << "File deleted\n";
                return NULL;
            }

            /* Case 2: One child */
            else if(node->left == NULL)
            {
                FileNode* temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right == NULL)
            {
                FileNode* temp = node->left;
                delete node;
                return temp;
            }

            /* Case 3: Two children */
            FileNode* temp = findMin(node->right);
            node->filename = temp->filename;
            node->right = deleteFile(node->right, temp->filename);
        }

        return node;
    }

    /* Remove File  will be call in function*/
    void removeFile(string name)
    {
        root = deleteFile(root, name);
    }

    /* Display files (Inorder Traversal) */
    void displayFiles(FileNode* node)
    {
        if(node == NULL)
            return;

        displayFiles(node->left);

        cout << node->filename << endl;

        displayFiles(node->right);
    }

    void showFiles()
    {
        if(root == NULL)
        {
            cout << "No files available\n";
            return;
        }

        cout << "Files in system:" << endl;
        displayFiles(root);
    }
};

#endif // FILEMANAGER_H
