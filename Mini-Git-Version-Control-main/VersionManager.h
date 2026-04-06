// VersionManager.h
#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <iostream>
#include <string>
using namespace std;

// Version Node Doubly Linked List

struct VersionNode
{
    int commitID;
    string content;
    string timestamp;
    string commitMessage;
    VersionNode *prev;
    VersionNode *next;

    VersionNode(int id, string data, string msg = "")
    {
        commitID = id;
        content = data;
        commitMessage = msg;
        prev = nullptr;
        next = nullptr;

        timestamp = "2026-04-01 21:30:12";
    }
};

// Version Manager Class

class VersionManager
{
private:
    VersionNode *head;
    VersionNode *tail;
    int versionCount;

public:

    // Constructor
    VersionManager()
    {
        head = nullptr;
        tail = nullptr;
        versionCount = 0;
    }

    // Destructor
    ~VersionManager()
    {
        VersionNode *current = head;

        while (current != nullptr)
        {
            VersionNode *temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Function 1: createVersion()

    void createVersion(string content, string msg = "")
    {
        if (head != nullptr)
        {
            cout << "Version history already exists! Use addVersion()." << endl;
            return;
        }

        versionCount++;

        VersionNode *newNode = new VersionNode(versionCount, content, msg);

        head = newNode;
        tail = newNode;

        cout << "✓ Version 1 created successfully!" << endl;
        cout << "  Content: " << content << endl;
        cout << "  Time: " << newNode->timestamp << endl;
    }

    // Function 2: addVersion()

    void addVersion(string newContent, string msg = "")
    {
        if (head == nullptr)
        {
            createVersion(newContent, msg);
            return;
        }

        versionCount++;

        VersionNode *newNode = new VersionNode(versionCount, newContent, msg);

        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;

        cout << "✓ Version " << versionCount << " added!" << endl;
        cout << "  Content: " << newContent << endl;
        cout << "  Time: " << newNode->timestamp << endl;
    }

    // Function 3: displayHistory()

    void displayHistory()
    {
        if (head == nullptr)
        {
            cout << "No version history found!" << endl;
            return;
        }

        VersionNode *current = head;

        while (current != nullptr)
        {
            cout << "Commit " << current->commitID
                 << " → " << current->content << endl;

            cout << "Message: " << current->commitMessage << endl;

            current = current->next;
        }
    }

    // Function 4: getLatestVersion()

    string getLatestVersion()
    {
        if (tail == nullptr)
            return "No versions exist!";

        return tail->content;
    }

    // Get Version by ID

    string getVersionByID(int id)
    {
        if (head == nullptr)
            return "No versions exist!";

        VersionNode *current = head;

        while (current != nullptr)
        {
            if (current->commitID == id)
                return current->content;

            current = current->next;
        }

        return "Version " + to_string(id) + " not found!";
    }

    // Total Versions

    int getTotalVersions()
    {
        return versionCount;
    }

    // Get Latest Node

    VersionNode* getLatestNode()
    {
        return tail;
    }

    // Remove Latest

    void removeLatest()
    {
        if (tail == nullptr) return;
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            VersionNode* temp = tail;
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            delete temp;
        }
        versionCount--;
    }
};

#endif