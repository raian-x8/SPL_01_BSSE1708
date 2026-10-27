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

**Development Phase:** Source Preprocessing and Basic Tokenization Implemented and Tested

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
- Rule-based C/C++ tokenization using C++17.
- Token classification with lexeme, line, and column information.
- String and character literal recognition with basic error recovery.
- Tokenization integrated with single-file and folder processing.
- Minimal main function with separate application coordination.

### Testing

The basic preprocessing module has passed five focused unit tests:

1. Single-line comment removal.
2. Block-comment removal.
3. String-literal preservation.
4. Escaped quotation mark preservation.
5. Character-literal preservation.

Single-file and folder-input preprocessing have also been manually tested using sample source files.

The tokenization module has passed focused regression tests
covering keywords, identifiers, numeric literals, quoted literals,
operators, punctuation, unknown tokens, and source positions.

Automated pipeline tests also verify file reading, preprocessing,
tokenization, and recovery from malformed ordinary literals.

### Current Limitations

- Directory scanning is non-recursive.
- File filtering currently supports lowercase `.c` and `.cpp` extensions.
- The scanner does not fully support raw string literals, line splicing, or all C++ lexical edge cases.
- The implementation is not a complete C++ lexer or compiler preprocessor.
- Basic tokenization is implemented, but function/block-level representation is not yet implemented.
- Clone detection and stylometric analysis are not yet implemented.

### Learning Documentation

Detailed preprocessing concepts, implementation explanations, testing notes, and supervisor viva questions are available in:

[Source Preprocessing Learning Manual](docs/learning-notes/CloneScope_Source_Preprocessing_Learning_Manual.pdf)

[Tokenization Learning Manual](docs/learning-notes/CloneScope_Tokenization_Learning_Manual.pdf)

### Next Development Milestone

Complete tokenization documentation and merge the tested tokenization feature into main. Then proceed to function/block-level representation and initial Type-1 and Type-2 clone candidate tagging.

## Tokenization Module

CloneScope includes a lightweight, rule-based C/C++ tokenizer
implemented in C++17.

### Current Processing Pipeline

1. Read a source file from a user-provided path.
2. Remove supported comments while preserving source positions.
3. Convert the preprocessed source into tokens.
4. Store each token's type, lexeme, line, and column.
5. Display the total number of generated tokens.

The application supports individual source-file input and
nonrecursive folder scanning for .c and .cpp files.

### Supported Token Categories

- Selected C/C++ keywords
- Identifiers
- Basic decimal integer and floating-point literals
- Double-quoted string literals
- Single-quoted character literals
- Structural punctuation
- Selected single- and two-character operators
- Unknown tokens for unsupported non-whitespace characters

### Error Handling

The tokenizer preserves unsupported non-whitespace characters
as Unknown tokens instead of silently discarding them.

The preprocessor and tokenizer also implement basic recovery
for unterminated ordinary string and character literals
encountering a physical newline.

### Current Limitations

- The tokenizer does not implement the complete C/C++ grammar.
- Preprocessor directives and macro expansion are not fully supported.
- Raw string literals and full C++ line-splicing rules are unsupported.
- Advanced numeric literal forms are not fully supported.
- Some C/C++ operators and lexical constructs remain unsupported.
- Folder scanning is nonrecursive.
- Tokenization alone does not detect plagiarism or code clones.

### Verification

The following test programs have been used:

- tests/preprocessor_smoke.cpp
- tests/tokenizer_smoke.cpp
- tests/pipeline_smoke.cpp

The file-processing pipeline has also been manually verified
using actual C/C++ files in the samples directory.

### Next Development Stage

The generated token sequences will serve as input for
subsequent code-clone analysis and explainable reporting.
