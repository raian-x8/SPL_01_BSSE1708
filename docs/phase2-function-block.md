# CloneScope — Phase 2: Function and Block Representation

## 1. Overview

Phase 2 introduces token-based brace-region identification, restricted function-body recognition, and Type-1 body-level clone candidate detection.

The implementation uses C++17 and does not depend on machine learning or a full C++ parser.

The purpose of this phase is to identify matching function bodies between source files and produce explainable evidence for human review.

## 2. Processing Pipeline

1. Read supported C/C++ source files.
2. Remove supported single-line and block comments.
3. Convert source code into lexical tokens.
4. Identify matching brace regions.
5. Recognize supported function-body regions.
6. Store each file's path, tokens, and function regions.
7. Generate unique pairs of source files.
8. Compare function-body token sequences.
9. Report Type-1 body-level candidates with source locations.

## 3. Main Components

### 3.1 Preprocessor

Files: `preprocessor.hpp` and `preprocessor.cpp`

- Removes supported comments.
- Preserves string and character literals.
- Maintains source positions needed for location reporting.

### 3.2 Tokenizer

Files: `tokenizer.hpp` and `tokenizer.cpp`

- Converts preprocessed source code into tokens.
- Records token types, lexemes, line numbers, and column numbers.
- Provides token sequences for subsequent analysis.

### 3.3 Code Region Detection

Files: `code_region.hpp` and `code_region.cpp`

- Identifies matched brace-delimited regions.
- Supports nested brace regions.
- Represents regions using token-index boundaries.

### 3.4 Function Region Detection

Files: `function_region.hpp` and `function_region.cpp`

- Recognizes supported function bodies using restricted token-based rules.
- Distinguishes supported function bodies from certain nonfunction brace regions.
- Does not attempt to recognize every valid C++ function syntax.

### 3.5 Type-1 Clone Detection

Files: `type1_clone.hpp` and `type1_clone.cpp`

- Compares recognized function-body regions.
- Requires identical token types and lexemes.
- Collects matching regions as Type-1 body-level candidates.

### 3.6 Explainable Reporting

Files: `type1_report.hpp` and `type1_report.cpp`

- Generates human-readable candidate reports.
- Displays source filenames and matching line ranges.
- Explains the lexical evidence supporting the reported match.
- Includes a warning that human review is required.

### 3.7 Application Integration

Files: `application.hpp` and `application.cpp`

- Coordinates input handling and source analysis.
- Supports individual source-file processing.
- Supports processing multiple directly contained `.c` and `.cpp` files in a selected directory.
- Stores analyzed source information in memory.
- Generates unique source-file pairs.
- Performs automatic Type-1 body-level comparison between file pairs.
- Displays candidate counts and explainable reports.

## 4. Type-1 Body-Level Matching

Two recognized function bodies are considered Type-1 candidates when their corresponding token sequences contain identical token types and lexemes.

Whitespace and supported comment differences do not affect the comparison after preprocessing and tokenization.

Changes to identifiers, operators, or numeric literals generally prevent an exact Type-1 match.

Function signatures are not included in the body comparison.

A matching function body does not imply that two entire programs are identical.

## 5. Multiple Source-File Comparison

CloneScope stores analyzed source files using an `AnalyzedSourceFile` structure.

Each stored record contains:

- Source-file path.
- Token sequence.
- Recognized function-body regions.

The application generates unique unordered file pairs using nested loops.

For `n` successfully analyzed files, the number of distinct file pairs is:

**P = n(n - 1) / 2**

For example:

- 2 files produce 1 pair.
- 4 files produce 6 pairs.
- 10 files produce 45 pairs.
- 20 files produce 190 pairs.
- 40 files produce 780 pairs.

This avoids self-comparisons and repeated reversed comparisons.

The pair-generation mechanism supports multiple submissions, but classroom-scale performance has not yet been established through benchmarking.

## 6. Verified Test Results

### 6.1 Regression Tests

All seven existing smoke-test executables passed:

1. Preprocessor smoke test.
2. Tokenizer smoke test.
3. Basic file pipeline smoke test.
4. Code-region smoke test.
5. Function-region smoke test.
6. Type-1 clone smoke test.
7. Type-1 file pipeline smoke test.

### 6.2 Positive Dataset

- Source files: 4
- Unique file pairs: 6
- Type-1 body-level candidates: 6

All four files contained an identical `add()` function body.

### 6.3 Negative Dataset

- Source files: 2
- Unique file pairs: 1
- Type-1 body-level candidates: 0

The function bodies differed in their arithmetic operators (`+` and `-`).

### 6.4 Mixed Dataset

- Source files: 3
- Unique file pairs: 3
- Type-1 body-level candidates: 1

The application identified the matching pair and rejected the two nonmatching pairs.

### 6.5 Source-Location Verification

The realistic positive dataset correctly reported:

- `realistic_student_a.cpp`: lines 7 to 9.
- `realistic_student_b.cpp`: lines 10 to 13.

Reports included filenames, matching source-line ranges, lexical evidence, and a human-review warning.

## 7. Current Limitations

- Function recognition relies on restricted token-based heuristics.
- The implementation is not a complete C++ parser.
- Not every valid C++ function syntax is supported.
- Type-1 comparison operates on function bodies rather than complete function definitions or entire programs.
- Function names and signatures are outside the current body-level comparison.
- Short common function bodies may generate similarity candidates.
- Directory scanning currently checks only directly contained files, not nested directories.
- Directory-based comparison currently supports `.c` and `.cpp` file extensions.
- Single-file input performs analysis but does not independently perform cross-file clone comparison.
- Type-2, Type-3, restricted Type-4, and stylometric analysis are not implemented in this phase.
- The current tests do not establish comprehensive C++ syntax coverage.
- Large classroom-scale performance has not yet been benchmarked.

## 8. Interpretation of Results

CloneScope is designed to identify potential code similarities and present evidence for human review.

An identical function body is not proof of plagiarism.

The instructor must consider assignment requirements, common algorithms, programming conventions, and other relevant evidence before making a judgment.

CloneScope does not automatically accuse students of plagiarism.

## 9. Phase 2 Outcome

Phase 2 establishes a working foundation for explainable function-body-level clone candidate detection.

The application can now read multiple supported source files, preprocess and tokenize their contents, identify supported function bodies, compare unique file pairs, and generate Type-1 candidate reports with source locations.

The implementation has been verified through seven smoke-test executables and positive, negative, and mixed application-level test datasets.

More advanced clone categories, stylometric analysis, and additional reporting capabilities belong to future development phases.
