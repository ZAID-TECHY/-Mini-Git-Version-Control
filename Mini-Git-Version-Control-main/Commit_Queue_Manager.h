#ifndef COMMIT_QUEUE_MANAGER_H
#define COMMIT_QUEUE_MANAGER_H

#include <string>
#include "VersionManager.h"

using namespace std;

struct CommitNode {
    string filename;
    string content;
    int commitID;
    string timestamp;
    CommitNode* next;
    CommitNode(string fname, string cont, int id, string time);
};

class CommitQueue {
private:
    CommitNode* front;
    CommitNode* rear;

public:
    CommitQueue();
    void enqueueCommit(string filename, string content, int commitID, string timestamp);
    CommitNode* dequeueCommit();
    // processCommit applies the next commit to the provided VersionManager
    bool processCommit(VersionManager &vm);
    bool isQueueEmpty();
    void displayQueue();
};

#endif // COMMIT_QUEUE_MANAGER_H
