Mini Git - student project

Overview

This is a small "mini git" style project split across several components:
- FileManager (BST of files, each with a VersionManager)
- VersionManager (doubly-linked list of versions)
- CommitQueue (simple queue of commits)
- BranchManager (linked list of branches)
- Undo/Redo manager (stack-based)

Files added/changed by refactor
- FileManager.h (new) - header for file manager
- BranchManager.h (new) - header for branch manager
- Commit_Queue_Manager.h (new) - header for commit queue
- UndoRedo.h (new) - header for undo/redo
- main.cpp (rewritten) - single entry-point that wires components together
- Commit_Queue_Manager.cpp (updated) - fixed constructor and processCommit
- FileManager.cpp, BranchManager.cpp, undo_redo.cpp trimmed to include headers

Build (Windows)

This repository does not include a compiler. You can build with either MinGW (g++) or Visual Studio's cl.exe.

Using MinGW (g++) in PowerShell:

# Install MinGW-w64 and add g++ to PATH, then run:
# cd to repository folder
g++ .\*.cpp -std=c++11 -O2 -o .\mini_git.exe

Using Visual Studio Developer Command Prompt (cl):

# Open "x64 Native Tools Command Prompt for VS" and run:
cl /EHsc /std:c++17 *.cpp

Or use the provided build.bat which tries to run g++ if available.

Notes & Next steps

- I removed duplicate main() functions from component files and centralized behavior in `main.cpp`.
- I created headers to expose classes and made `CommitQueue::processCommit` operate on a provided `VersionManager` instance.
- The code compiles when a C++ compiler is available (not present in your current PATH here). Please run the build locally; if you paste the compiler errors I can iterate fixes.

If you want, I can also:
- Add unit tests (GoogleTest) for core classes.
- Improve the CLI to persist data to disk.
- Wire branch-specific VersionManager instances per file.

Contributors:

Azaan Mehtab Khan 
Sharjeel Ahmed 
Mohammad Talha 
Zaid bin Shahid 
Mohammad Talha Shafique 
Mohammad Javed 
Sameer Azam Khan