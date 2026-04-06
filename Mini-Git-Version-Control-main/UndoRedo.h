#ifndef UNDOREDO_H
#define UNDOREDO_H

#include <iostream>
#include <string>
using namespace std;

class undo_redo
{
private:
    struct Node
    {
        string value;
        Node *previous;
    };
    Node*undo_top = nullptr;
    Node *redo_top = nullptr;
    string old_content;
    string current_content;

public:
    void Edit(string new_con, string old_con)
    {
        old_content=old_con;
        current_content=new_con;
        pushUndo();
    }
    void pushUndo(){
        Node*newnode=new Node();
        newnode->value=old_content;
        newnode->previous=nullptr;
        if (undo_top==nullptr)
        {
            undo_top=newnode;
        }else{
            newnode->previous=undo_top;
            undo_top=newnode;
        }
    }
    void popUndo(){
        if (undo_top==nullptr)
        {
            cout<<"Undo Stack is Empty"<<endl;
            return;
        }
        Node*temp=undo_top;
        current_content=undo_top->value;
        if (undo_top->previous==nullptr)
        {
            undo_top=nullptr;
        }else
        {
            undo_top=undo_top->previous;
        }
        delete temp;
    }
    void pushRedo(){
        Node*newnode=new Node();
        newnode->value=current_content;
        newnode->previous=nullptr;
        if (redo_top==nullptr)
        {
            redo_top=newnode;
        }else{
            newnode->previous=redo_top;
            redo_top=newnode;
        }
    }
    void popRedo(){
        if (redo_top==nullptr)
        {
            cout<<"Redo Stack is Empty"<<endl;
            return;
        }
        Node*temp=redo_top;
        old_content=current_content;
        current_content=redo_top->value;
        if (redo_top->previous==nullptr)
        {
            redo_top=nullptr;
        }else
        {
            redo_top=redo_top->previous;
        }
        delete temp;
    }
    string getCurrentContent(){
        return current_content;
    }
};

#endif // UNDOREDO_H
