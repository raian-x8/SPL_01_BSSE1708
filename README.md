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

**Development Phase:** Basic Source Preprocessing Implemented and Tested

### Implemented Features

- C++17 command-line application.
- Local C/C++ source-file and folder input.
- Non-recursive directory scanning using `std::filesystem`.
- Filtering of regular `.c` and `.cpp` files.
- Complete source-file reading using `std::ifstream` and `std::ostringstream`.
- Basic source preprocessing using a five-state lexical scanner.
- Single-line (`//`) and block (`/* ... */`) comment removal.
- Preservation of ordinary string and character literals.
- Basic support for escaped quotation marks.
- Preservation of newlines during supported comment removal.
- Preprocessing integrated with single-file and folder input.
- Five passing preprocessing unit tests.

### Testing

The basic preprocessing module has passed five focused unit tests:

1. Single-line comment removal.
2. Block-comment removal.
3. String-literal preservation.
4. Escaped quotation mark preservation.
5. Character-literal preservation.

Single-file and folder-input preprocessing have also been manually tested using sample source files.

### Current Limitations

- Directory scanning is non-recursive.
- File filtering currently supports lowercase `.c` and `.cpp` extensions.
- The scanner does not fully support raw string literals, line splicing, or all C++ lexical edge cases.
- The implementation is not a complete C++ lexer or compiler preprocessor.
- Tokenization and function/block representation are not yet implemented.
- Clone detection and stylometric analysis are not yet implemented.

### Learning Documentation

Detailed preprocessing concepts, implementation explanations, testing notes, and supervisor viva questions are available in:

[Source Preprocessing Learning Manual](docs/learning-notes/CloneScope_Source_Preprocessing_Learning_Manual.pdf)

### Next Development Milestone

Implement source-code tokenization, followed by function/block-level representation and initial Type-1 and Type-2 clone candidate tagging.
