#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include "FileManager.h"
#include "VersionManager.h"
#include "Commit_Queue_Manager.h"
#include "BranchManager.h"
#include "UndoRedo.h"

using namespace std;

void displayDashboard(string currentBranch, int totalFiles, int totalVersions, int totalBranches, int undoSteps, int redoSteps, string latestFile, string latestVersion, vector<string> recentFiles) {
    cout << "================ Mini Git 2.0 Dashboard ================" << endl;
    cout << "Current Branch: " << currentBranch << endl;
    cout << "Total Files: " << totalFiles << endl;
    cout << "Total Versions (active branch): " << totalVersions << endl;
    cout << "Total Branches: " << totalBranches << endl;
    cout << "Undo Steps Left: " << undoSteps << " | Redo Steps Available: " << redoSteps << endl;
    cout << "-- Latest File --" << endl;
    cout << "Latest file: " << latestFile << endl;
    if (latestFile != "(none selected)") {
        cout << "Latest version: " << latestVersion << endl;
    }
    cout << "-- Recent Files --" << endl;
    if (recentFiles.empty()) {
        cout << "(none)" << endl;
    } else {
        cout << "Most recent -> oldest: ";
        for (size_t i = 0; i < recentFiles.size(); ++i) {
            cout << recentFiles[i];
            if (i < recentFiles.size() - 1) cout << " ";
        }
        cout << endl;
    }
    cout << "=================== Menu ====================" << endl;
    cout << " [C] Create File" << endl;
    cout << " [E] Edit File";
    if (totalFiles == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [M] Commit Version";
    if (totalFiles == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [U] Undo";
    if (undoSteps == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [R] Redo";
    if (redoSteps == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [V] View Version History";
    if (totalFiles == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [B] Create Branch" << endl;
    cout << " [S] Switch Branch" << endl;
    cout << " [H] List Branches" << endl;
    cout << " [F] Search File";
    if (totalFiles == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [L] Display All Files";
    if (totalFiles == 0) cout << " (disabled)" << endl;
    else cout << endl;
    cout << " [X] Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    FileManager fm;
    BranchManager bm;
    undo_redo ur;
    VersionManager vm;
    CommitQueue cq;

    string currentBranch = "main";
    int totalFiles = 0;
    int totalVersions = 0;
    int totalBranches = 1;
    int undoSteps = 0;
    int redoSteps = 0;
    string latestFile = "(none selected)";
    string latestVersion = "(none yet)";
    vector<string> recentFiles;
    map<string, string> staged;
    string lastUndoneContent = "";
    string lastUndoneMessage = "";

    while (true) {
        displayDashboard(currentBranch, totalFiles, totalVersions, totalBranches, undoSteps, redoSteps, latestFile, latestVersion, recentFiles);
        string choice;
        getline(cin, choice);
        if (choice.empty()) continue;
        char ch = toupper(choice[0]);
        switch (ch) {
            case 'C': {
                cout << "Enter new filename: ";
                string fname;
                getline(cin, fname);
                fm.createFile(fname);
                cout << "Enter initial staged content (optional, press Enter for empty): ";
                string content;
                getline(cin, content);
                staged[fname] = content;
                totalFiles++;
                recentFiles.insert(recentFiles.begin(), fname);
                latestFile = fname;
                cout << "Opening file '" << fname << "' (branch '" << currentBranch << "')... (No committed version yet)" << endl;
                break;
            }
            case 'E': {
                if (totalFiles == 0) {
                    cout << "This option is disabled. (No files created yet)" << endl;
                    continue;
                }
                cout << "Enter filename to edit: ";
                string fname;
                getline(cin, fname);
                FileNode* f = fm.findFile(fname);
                if (!f) {
                    cout << "File not found" << endl;
                    continue;
                }
                cout << "Opening file '" << fname << "' (branch '" << currentBranch << "')... ";
                if (f->versions.getTotalVersions() == 0) cout << "(No committed version yet)" << endl;
                else cout << endl;
                cout << "Enter new content to stage (not committed yet): ";
                string content;
                getline(cin, content);
                staged[fname] = content;
                cout << "Staged content updated for '" << fname << "' in branch '" << currentBranch << "'." << endl;
                break;
            }
            case 'M': {
                if (totalFiles == 0) {
                    cout << "This option is disabled. (No files created yet)" << endl;
                    continue;
                }
                string fname = latestFile;
                FileNode* f = fm.findFile(fname);
                if (!f || staged.find(fname) == staged.end()) {
                    cout << "No staged content" << endl;
                    continue;
                }
                cout << "Enter short commit message: ";
                string message;
                getline(cin, message);
                f->versions.addVersion(staged[fname], message);
                staged.erase(fname);
                totalVersions++;
                undoSteps++;
                VersionNode* vn = f->versions.getLatestNode();
                latestVersion = "CommitID " + to_string(vn->commitID);
                cout << "Opening file '" << fname << "' (branch '" << currentBranch << "')..." << endl;
                cout << "Latest version: CommitID " << vn->commitID<<endl;
                cout << " Timestamp: " << vn->timestamp<<endl;
                cout << " Commit Message: " << vn->commitMessage<<endl;
                cout << " Content: " << vn->content << endl;
                cout << "Commit successful. CommitID " << vn->commitID << "." << endl;
                break;
            }
            case 'U': {
                if (undoSteps == 0) {
                    cout << "This option is disabled. (No undo steps available)" << endl;
                    continue;
                }
                string fname = latestFile;
                FileNode* f = fm.findFile(fname);
                if (!f) continue;
                VersionNode* vn = f->versions.getLatestNode();
                lastUndoneContent = vn->content;
                lastUndoneMessage = vn->commitMessage;
                f->versions.removeLatest();
                totalVersions--;
                undoSteps--;
                redoSteps++;
                cout << "Undo successful. Current content restored to previous version." << endl;
                break;
            }
            case 'R': {
                if (redoSteps == 0) {
                    cout << "This option is disabled. (No redo steps available)" << endl;
                    continue;
                }
                string fname = latestFile;
                FileNode* f = fm.findFile(fname);
                f->versions.addVersion(lastUndoneContent, lastUndoneMessage);
                totalVersions++;
                undoSteps++;
                redoSteps--;
                cout << "Redo successful. Current content restored." << endl;
                break;
            }
            case 'V': {
                if (totalFiles == 0) {
                    cout << "This option is disabled. (No files created yet)" << endl;
                    continue;
                }
                string fname = latestFile;
                FileNode* f = fm.findFile(fname);
                if (!f) continue;
                cout << "Version History for " << fname << ":" << endl;
                f->versions.displayHistory();
                break;
            }
            case 'B': {
                cout << "Enter new branch name: ";
                string b;
                getline(cin, b);
                bm.createBranch(b);
                totalBranches++;
                break;
            }
            case 'S': {
                cout << "Enter branch to switch to: ";
                string b;
                getline(cin, b);
                bm.switchBranch(b);
                currentBranch = b;
                break;
            }
            case 'H': {
                bm.listBranches();
                break;
            }
            case 'F': {
                if (totalFiles == 0) {
                    cout << "This option is disabled. (No files created yet)" << endl;
                    continue;
                }
                cout << "Enter filename: ";
                string fname;
                getline(cin, fname);
                FileNode* f = fm.findFile(fname);
                if (f) cout << "File Found!" << endl;
                else cout << "File not found." << endl;
                break;
            }
            case 'L': {
                if (totalFiles == 0) {
                    cout << "This option is disabled. (No files created yet)" << endl;
                    continue;
                }
                fm.showFiles();
                break;
            }
            case 'X': {
                return 0;
            }
            default:
                continue;
        }
    }
    return 0;
}
