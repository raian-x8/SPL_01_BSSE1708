# CloneScope

**An Explainable Code Clone Tagging and Stylometric Analysis Tool**

**Student:** Raian Huq (BSSE1708)  
**Institute:** IIT, University of Dhaka  
**Supervisor:** Dr. Kazi Muheymin-Us-Sakib

## Project Overview

CloneScope is a C++17-based software engineering project designed to detect and classify code clones in student programming submissions.

It aims to provide explainable evidence for instructors rather than automatically declaring plagiarism.

## Planned Features

- Type-1, Type-2 and Type-3 code clone detection
- Restricted Type-4 clone candidate screening
- Clone tagging with source locations and evidence
- Stylometric analysis of coding habits
- Student-wise and pairwise statistical analysis
- CSV/JSON dataset export
- Explainable reports for human review

## Midterm Development Target

- Local source file and folder processing
- Code preprocessing and tokenization
- Type-1 and Type-2 clone detection
- Initial stylometry and pairwise statistics
- Basic CSV/JSON export

## Current Status

**Development Phase:** Source Input Module Completed (Basic Version)

### Implemented Features

- C++17 command-line application.
- User-selected C/C++ source-file input.
- Local folder input using `std::filesystem`.
- Directory scanning using `directory_iterator`.
- Filtering of regular `.c` and `.cpp` files.
- Opening and reading multiple source files using `ifstream` and `getline()`.
- Basic file-opening error handling.
- Manual testing of valid and invalid inputs.

### Current Limitations

- Directory scanning is non-recursive.
- File-extension filtering supports lowercase `.c` and `.cpp`.
- Source code is read and displayed but not yet analyzed.
- Clone detection and stylometric analysis are not yet implemented.

### Next Development Milestone

Source code preprocessing, tokenization, function/block representation, and initial Type-1 and Type-2 clone candidate tagging.
