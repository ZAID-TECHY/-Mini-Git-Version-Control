

#include <iostream>
#include <string>
#include "Commit_Queue_Manager.h"

using namespace std;

CommitNode::CommitNode(string fname, string cont, int id, string time)
    : filename(fname), content(cont), commitID(id), timestamp(time), next(nullptr) {}

CommitQueue::CommitQueue() : front(nullptr), rear(nullptr) {}

void CommitQueue::enqueueCommit(string filename, string content, int commitID, string timestamp)
{
    CommitNode *new_node = new CommitNode(filename,content,commitID,timestamp);
    new_node->next=nullptr;
    if(front==nullptr){
        front=rear=new_node;
    }else{
        rear->next=new_node;
        rear = new_node;
    }
}

CommitNode *CommitQueue::dequeueCommit()
{
    if(isQueueEmpty()){
        return nullptr;
    }
    CommitNode* temp = front;
    front = front->next;
    if(front==nullptr){
        rear=nullptr;
    }
    return temp;
}

bool CommitQueue::processCommit(VersionManager &vm)
{
    if(isQueueEmpty()){
        return false;
    }
    CommitNode* first = front;
    // For now, we'll append commit content as a new version to the VersionManager
    vm.addVersion(first->content);
    dequeueCommit();
    return true;
}

bool CommitQueue::isQueueEmpty()
{
    return front == nullptr;
}

void CommitQueue::displayQueue()
{
    if(isQueueEmpty()){
        return;
    }else{
        CommitNode* temp = front;
        cout<<"Pending Commits:"<<endl;

        while(temp!=nullptr){
            cout<<"File: "<<temp->filename<<endl;
            cout<<"CommitId "<<temp->commitID<<endl;
            cout<<"Time "<<temp->timestamp<<endl;
            temp = temp->next;

        }
    }
}
