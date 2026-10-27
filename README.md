# CloneScope

**An Explainable Code Clone Tagging and Stylometric Analysis Tool**

**Student:** Raian Huq (BSSE1708)  
**Institute:** IIT, University of Dhaka  
**Supervisor:** Dr. Kazi Muheymin-Us-Sakib

## Project Overview

CloneScope is a C++17-based software engineering project designed to detect and classify code clones in student programming submissions.

The project aims to provide explainable similarity evidence for instructors rather than automatically declaring plagiarism.

CloneScope is being developed incrementally, beginning with source-file processing, preprocessing, tokenization, structural code representation, and restricted Type-1 clone candidate detection.

## Planned Features

- Type-1, Type-2, and Type-3 code clone detection.
- Restricted Type-4 clone candidate screening.
- Clone tagging with source locations and evidence.
- Stylometric analysis of coding habits.
- Student-wise and pairwise statistical analysis.
- CSV/JSON dataset export.
- Explainable reports for human review.

These represent the approved project direction. Not all planned features have been implemented.

## Midterm Development Target

- Local source-file and folder processing.
- Code preprocessing and tokenization.
- Type-1 and Type-2 clone detection.
- Initial stylometry and pairwise statistics.
- Basic CSV/JSON export.

These are development targets, not a statement that every feature is already complete.

## Current Status

**Development Phase:** Phase 2 — Function and Block Representation, Implemented and Tested Locally

**Git Branch:** `feat/function-block-representation`

**Current Milestone:** Restricted Type-1 function-body clone candidate detection and explainable reporting integrated into the application.

### Implemented Features

**Application and File Handling**

- C++17 command-line application.
- Local C/C++ source-file and folder input.
- Non-recursive directory scanning using `std::filesystem`.
- Filtering of regular `.c` and `.cpp` files.
- Complete source-file reading using `std::ifstream` and `std::ostringstream`.
- Minimal `main()` function with separate application coordination.

**Source Preprocessing**

- Basic source preprocessing using a five-state lexical scanner.
- Single-line (`//`) and block (`/* ... */`) comment removal.
- Preservation of ordinary string and character literals.
- Basic support for escaped quotation marks.
- Preservation of newlines during supported comment removal.
- Preprocessing integrated with single-file and folder input.

**Tokenization**

- Rule-based C/C++ tokenization using C++17.
- Token classification with lexeme, line, and column information.
- Basic string and character literal recognition with error recovery.
- Tokenization integrated with single-file and folder processing.

**Function and Block Representation**

- Token-based matching of brace-delimited code regions.
- Support for nested brace-region identification.
- Region representation using token-index boundaries.
- Restricted function-body recognition.
- Function-body identification integrated into source-file processing.

**Type-1 Body-Level Clone Detection**

- Exact comparison of recognized function-body token sequences.
- Comparison using token types and lexemes.
- Detection of identical function bodies despite supported whitespace and comment differences.
- Rejection of changed operators, identifiers, or literal values in exact Type-1 matching.
- In-memory storage of analyzed source-file information.
- Automatic generation of unique source-file pairs.
- Automatic Type-1 body-level comparison across files in a selected directory.

**Explainable Reporting**

- Candidate reporting with source filenames.
- Matching source-line ranges.
- Token-based evidence explanation.
- Human-review warning.
- Candidate counts for compared file pairs.

### Testing

The preprocessing module passed five focused tests:

1. Single-line comment removal.
2. Block-comment removal.
3. String-literal preservation.
4. Escaped quotation mark preservation.
5. Character-literal preservation.

Tokenization has been tested for supported token categories, source positions, and selected malformed-literal recovery cases.

**Phase 2 Regression Testing**

All seven existing smoke-test executables passed:

1. `tests/preprocessor_smoke.cpp`
2. `tests/tokenizer_smoke.cpp`
3. `tests/pipeline_smoke.cpp`
4. `tests/code_region_smoke.cpp`
5. `tests/function_region_smoke.cpp`
6. `tests/type1_clone_smoke.cpp`
7. `tests/type1_file_pipeline_smoke.cpp`

**Application-Level Dataset Verification**

| Dataset  | Files | File Pairs | Type-1 Candidates | Result |
| -------- | ----: | ---------: | ----------------: | ------ |
| Positive |     4 |          6 |                 6 | Passed |
| Negative |     2 |          1 |                 0 | Passed |
| Mixed    |     3 |          3 |                 1 | Passed |

These tests verify selected supported behaviors. They do not establish comprehensive C++ syntax coverage or plagiarism-detection accuracy.

### Current Limitations

- Directory scanning is non-recursive.
- File filtering currently supports lowercase `.c` and `.cpp` extensions.
- Preprocessing and tokenization do not fully support all C/C++ lexical constructs.
- Raw string literals, full line-splicing behavior, and advanced numeric literal forms are not fully supported.
- Function-body recognition uses restricted token-based heuristics rather than a complete C++ parser.
- Type-1 comparison operates on function bodies, not complete functions or programs.
- Function signatures are excluded from the current body comparison.
- Short commonly occurring function bodies can produce matching candidates.
- Single-file input does not independently perform cross-file comparison.
- Type-2, Type-3, restricted Type-4, and stylometric analysis remain future development work.
- Large classroom-scale performance has not yet been benchmarked.
- Reported similarity is not proof of plagiarism.

### Learning Documentation

Existing learning manuals:

- [Source Preprocessing Learning Manual](docs/learning-notes/CloneScope_Source_Preprocessing_Learning_Manual.pdf)
- [Tokenization Learning Manual](docs/learning-notes/CloneScope_Tokenization_Learning_Manual.pdf)

Phase 2 technical documentation:

- [Phase 2 — Function and Block Representation](docs/phase2-function-block.md)

- [Phase 2 Function, Block and Type-1 Learning Manual](docs/learning-notes/CloneScope_Phase2_Function_Block_Type1_Learning_Manual.pdf)

The Phase 2 learning manual provides detailed code explanations, worked examples, testing guidance, and supervisor-viva preparation.

## Tokenization Module

CloneScope includes a lightweight, rule-based C/C++ tokenizer implemented in C++17.

### Tokenization Processing Pipeline

1. Read a source file from a user-provided path.
2. Remove supported comments while preserving source positions.
3. Convert the preprocessed source into tokens.
4. Store each token's type, lexeme, line, and column.
5. Display the total number of generated tokens.

The application supports individual source-file input and non-recursive folder scanning for `.c` and `.cpp` files.

### Supported Token Categories

- Selected C/C++ keywords.
- Identifiers.
- Basic decimal integer and floating-point literals.
- Double-quoted string literals.
- Single-quoted character literals.
- Structural punctuation.
- Selected single- and two-character operators.
- Unknown tokens for unsupported non-whitespace characters.

### Error Handling

The tokenizer preserves unsupported non-whitespace characters as `Unknown` tokens instead of silently discarding them.

The preprocessor and tokenizer also implement basic recovery for unterminated ordinary string and character literals encountering a physical newline.

### Tokenization Limitations

- The tokenizer does not implement the complete C/C++ grammar.
- Preprocessor directives and macro expansion are not fully supported.
- Raw string literals and full C++ line-splicing rules are unsupported.
- Advanced numeric literal forms are not fully supported.
- Some C/C++ operators and lexical constructs remain unsupported.
- Tokenization alone does not identify code clones or establish plagiarism.

### Verification

The following test programs verify preprocessing and tokenization behavior:

- `tests/preprocessor_smoke.cpp`
- `tests/tokenizer_smoke.cpp`
- `tests/pipeline_smoke.cpp`

The file-processing pipeline has also been manually verified using actual C/C++ source files.

## Phase 2 — Function and Block Representation

### Overview

Phase 2 extends the tokenization foundation by introducing structural code-region identification and restricted Type-1 function-body clone candidate detection.

The system uses rule-based algorithms written in C++17. It does not use machine-learning models or a complete C++ parser.

### Phase 2 Processing Pipeline

1. Read source files from the selected directory.
2. Remove supported comments.
3. Tokenize each source file.
4. Identify matched brace regions.
5. Recognize supported function bodies.
6. Store each file's path, tokens, and function regions.
7. Generate unique unordered source-file pairs.
8. Compare all recognized function-body combinations for each file pair.
9. Produce explainable Type-1 body-level candidate reports.

### Main Phase 2 Components

| Component         | Responsibility                                           |
| ----------------- | -------------------------------------------------------- |
| `code_region`     | Identifies matching brace regions                        |
| `function_region` | Recognizes supported function-body regions               |
| `type1_clone`     | Compares function bodies and collects Type-1 matches     |
| `type1_report`    | Produces source-location and evidence reports            |
| `application`     | Coordinates directory analysis and file-pair comparisons |

### Type-1 Comparison Rules

Two recognized function bodies are Type-1 candidates when their token sequences have identical token types and lexemes.

Supported whitespace and comment differences do not affect the result.

For example:

`return a + b;`

and

`return a - b;`

are not exact Type-1 body matches because the operator lexemes differ.

Function names and signatures are outside the current body-level comparison.

### Multi-File Comparison

The application stores each processed source file using an `AnalyzedSourceFile` structure containing:

- Source-file path.
- Token vector.
- Recognized function-body regions.

Each pair of distinct source files is compared only once.

For `n` analyzed files, the number of unique unordered file pairs is:

**n(n - 1) / 2**

For example, four files generate six distinct file pairs.

### Example Explainable Report

```text
CloneScope Type-1 body-level candidate report

Candidate #1
realistic_student_a.cpp: lines 7 to 9
realistic_student_b.cpp: lines 10 to 13
Evidence: identical body token types and lexemes.
Human review required; similarity is not proof of plagiarism.

Reported candidates: 1
```

This report identifies a matching function-body region, not necessarily an identical complete program.

### Build and Run

From the repository root, compile using a C++17-compatible `g++` compiler:

```powershell
g++ -std=c++17 -Wall -Wextra src/main.cpp src/application.cpp src/preprocessor.cpp src/tokenizer.cpp src/code_region.cpp src/function_region.cpp src/type1_clone.cpp src/type1_report.cpp -o clonescope.exe
```

Run the application:

```powershell
.\clonescope.exe
```

Example directory input:

```text
tests/fixtures/type1
```

Other available test directories:

```text
tests/fixtures/type1/negative
tests/fixtures/type1/mixed
```

### Phase 2 Outcome

CloneScope can now compare supported function-body regions across multiple C/C++ source files and report restricted Type-1 body-level clone candidates with explainable source locations.

Its output is intended to support instructor review, not automatically determine plagiarism.

## Next Development Stage

After Phase 2 documentation review, the feature branch will be prepared for a GitHub Pull Request and merge into `main`.

Subsequent development will follow the approved CloneScope roadmap, including additional clone categories, stylometric analysis, statistical evidence, and structured reporting.

These future capabilities are not claimed as implemented in Phase 2.
