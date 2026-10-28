# CloneScope

**An Explainable Code Clone Tagging and Stylometric Analysis Tool**

**Student:** Raian Huq (BSSE1708)  
**Institute:** Institute of Information Technology (IIT), University of Dhaka\
**Supervisor:** Dr. Kazi Muheymin-Us-Sakib\
**Language:** C++17\
**Development environment:** Windows, VS Code, PowerShell, Git and GitHub

## Project Overview

CloneScope is a rule-based C++17 application being developed to identify and explain code-similarity candidates in student programming submissions. It currently analyzes supported C/C++ function bodies and reports:

- **Type-1 body-level candidates:** identical token types and lexemes after supported comment removal and whitespace-insensitive tokenization.
- **Type-2-only body-level candidates:** the same supported token structure with consistent one-to-one identifier renaming and otherwise identical token lexemes.

Reports contain source-file paths, relevant line ranges, the matching rule and an explicit human-review warning.

**CloneScope does not determine plagiarism.** Similarity findings are evidence for instructors to examine in context; they are not accusations or automatic judgments. The project does not use machine-learning training.

The current implementation is an explainable **prototype**, not a full C/C++ parser or comprehensive clone-detection engine.

## Approved Project Scope

The supervisor-approved direction includes:

- Type-1, Type-2 and Type-3 code clone detection.
- Restricted Type-4 clone candidate screening.
- Stylometric analysis of programming habits.
- Student-wise and pairwise statistical analysis.
- Explainable source-location evidence and human-review reports.
- CSV/JSON data export.

**Only the features identified as implemented below are currently available.** Type-3, restricted Type-4, stylometry, statistical summaries and CSV/JSON export are not yet implemented.

## Current Development Status

| Item                                                                 | Status                                                                 |
| -------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| Application foundation, preprocessing and tokenization               | Implemented and locally tested                                         |
| Function/block representation and initial Type-1 detection (Phase 2) | Completed and merged into `main`                                       |
| Initial Type-2 detection, integration and reporting (Phase 3)        | Implemented and locally tested; documentation/final review in progress |
| Current local development branch                                     | `feat/type2-clone-detection`                                           |
| Phase 3 GitHub publication / Pull Request                            | Not yet published or merged                                            |
| Initial stylometric and statistical analysis                         | Planned for a subsequent pre-midterm phase                             |
| Enhanced Type-1/Type-2 coverage, CSV/JSON and larger datasets        | Planned before the midterm                                             |
| Type-3 and restricted Type-4                                         | Planned after the midterm                                              |

**Verified local Phase 3 commits:**

- `e4b156d` — `feat: implement Type-2 identifier mapping and region matching`
- `9a658e9` — `feat: integrate Type-2 reporting and recursive source discovery`
- `2c6e033` — `test: add Type-2 reporting and invalid-region regression checks`

These commits are local milestones; a feature branch is not considered merged until its Pull Request has been reviewed and merged.

## Implemented Features

### 1. Input and File Handling

- C++17 command-line application with a minimal `src/main.cpp` and coordination in `src/application.cpp`.
- Read an individual source file or select a source directory.
- Scan a directory **non-recursively (`n`)** or **recursively (`y`)** using `std::filesystem`.
- Filter regular files with lowercase `.c` and `.cpp` extensions.
- Read complete source files with `std::ifstream` and `std::ostringstream`.
- Store each analyzed file's path, tokens and recognized function-body regions.
- Compare every distinct unordered pair of discovered source files.
- Display paths relative to the selected directory in comparison messages and reports.

For a single source-file input, CloneScope currently preprocesses, tokenizes and recognizes function-body regions; cross-file clone comparison is performed through the directory-analysis path.

### 2. Source Preprocessing

- Remove supported `//` and `/* ... */` comments using a state-based scanner.
- Preserve ordinary string and character literals, including basic escaped quotations.
- Preserve physical line breaks while removing supported comments to retain useful source-line locations.
- Pass the cleaned source text to tokenization.

Comment stripping is a **matching-stage operation**. Future stylometric analysis of comments or formatting must use the original source text rather than only the cleaned representation.

### 3. Tokenization and Code Regions

- Recognize supported C/C++ keywords, identifiers, numbers, string/character literals, operators and punctuation.
- Store each token's type, lexeme, line and column.
- Retain unsupported non-whitespace characters as `Unknown` tokens.
- Identify matched brace regions and selected function bodies with token-based heuristics.
- Represent a region by `beginTokenIndex` and **exclusive** `endTokenIndex`.

Function-body recognition is deliberately restricted and is **not** a complete parser.

### 4. Type-1 Function-Body Candidate Detection

Two valid supported function-body regions qualify when their token sequences have:

1. The same number of tokens.
2. Identical token types at corresponding positions.
3. Identical token lexemes at corresponding positions.

Supported differences in comments and whitespace do not prevent matching. A changed identifier, operator or literal normally prevents an exact Type-1 body match.

The current comparison examines recognized **bodies**, not complete function definitions or signatures. For example, a function-name change outside the body is not itself examined by this matcher.

### 5. Type-2-Only Function-Body Candidate Detection

The initial Type-2 comparator (`src/type2_clone.cpp`) requires:

1. Valid, nonempty regions with equal token counts.
2. Equal token types at corresponding positions.
3. Exact lexeme equality for all **non-identifier** tokens, including currently supported keywords, operators, punctuation and literals.
4. A consistent **one-to-one** correspondence between identifier lexemes in the two bodies.
5. At least one identifier lexeme difference, so an exact Type-1 match is not reported again as a Type-2-only finding.

The implementation uses two `std::unordered_map<std::string, std::string>` objects:

- A forward map checks that each identifier in the first body always maps to the same identifier in the second.
- A reverse map prevents two different identifiers in the first body from mapping to one identifier in the second.

**Example — accepted Type-2-only candidate:**

```c
/* First body */
int sum = a + b;
return sum;
```

```c
/* Second body */
int total = x + y;
return total;
```

The mapping `sum -> total`, `a -> x`, `b -> y` is consistent.

**Example — rejected under the current rules:**

```c
return a + a;
```

```c
return x + y;
```

The same identifier `a` would have to map to both `x` and `y`.

Classic Type-2 definitions may include other permitted changes, such as literal or type variations. **Those are not currently supported by this initial implementation.** The term _Type-2-only_ in the output describes a candidate beyond the exact Type-1 category, not full coverage of every conventional Type-2 case.

### 6. Explainable Candidate Reporting

The `type1_report` and `type2_report` modules produce:

- Candidate counts and classification.
- Relative source-file paths, including student subfolders.
- Starting and ending source-line numbers for each reported body.
- A description of the matching rule.
- The statement: **"Human review required; similarity is not proof of plagiarism."**

The Type-2 report currently explains the **rule** (consistent identifier renaming) but does **not** yet print the actual identifier-to-identifier mapping for each candidate.

## Processing Pipeline

```text
User-supplied file or directory
        |
        v
Optional recursive or non-recursive source discovery
        |
        v
Source reading -> supported comment removal -> tokenization
        |
        v
Supported function-body recognition
        |
        v
Distinct unordered source-file pairs
        |
        +--> Type-1 body comparison --> Type-1 report
        |
        +--> Type-2-only body comparison --> Type-2 report
        |
        v
Candidate counts, source locations and human-review warning
```

For `n` successfully analyzed source files, the directory pipeline generates:

`n * (n - 1) / 2`

distinct unordered file pairs. For example, six files produce 15 pairs; 60 files would produce 1,770 pairs **if all 60 files are successfully analyzed**.

Within each file pair, the system compares combinations of recognized function-body regions. It does not yet automatically group files by student or assignment.

## Main Source Components

| File/module             | Responsibility                                                           |
| ----------------------- | ------------------------------------------------------------------------ |
| `src/main.cpp`          | Minimal entry point                                                      |
| `src/application.cpp`   | Input, discovery, pipeline coordination, file-pair comparison and output |
| `src/preprocessor.*`    | Supported comment removal                                                |
| `src/tokenizer.*`       | Token construction and source positions                                  |
| `src/code_region.*`     | Matched brace-region identification                                      |
| `src/function_region.*` | Restricted function-body recognition                                     |
| `src/type1_clone.*`     | Exact Type-1 body comparison and discovery                               |
| `src/type1_report.*`    | Explainable Type-1 candidate reporting                                   |
| `src/type2_clone.*`     | Consistent identifier mapping and Type-2-only discovery                  |
| `src/type2_report.*`    | Explainable Type-2-only candidate reporting                              |

## Phase 3 — Detailed Technical Explanation

This section integrates the Phase 3 implementation details directly into the main README. The earlier sections provide the quick-start project overview, build commands, verified tests, and known limitations.

### Public Type-2 module interface

Files: `src/type2_clone.hpp` and `src/type2_clone.cpp`.

The public interface defines a result record and two functions:

```cpp
struct Type2BodyMatch
{
    CodeRegion firstRegion;
    CodeRegion secondRegion;
};

bool areType2BodyCandidates(
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion);

std::vector<Type2BodyMatch> findType2BodyMatches(
    const std::vector<Token> &firstTokens,
    const std::vector<CodeRegion> &firstRegions,
    const std::vector<Token> &secondTokens,
    const std::vector<CodeRegion> &secondRegions);
```

The first function decides whether **one specified pair of regions** qualifies. The second visits combinations of recognized regions and collects all qualifying pairs. This separation avoids duplicating the matching rules inside the discovery loop.

### Explainable reporting implementation

Files: `src/type2_report.hpp` and `src/type2_report.cpp`.

`printType2BodyMatches()` accepts an `std::ostream &`, two relative source paths, the two token vectors, and the detected `Type2BodyMatch` vector. It:

1. Validates each reported region before indexing token vectors.
2. Reads the first and last included tokens for the line range (`endTokenIndex - 1` is the last included index).
3. Prints candidate numbers, relative paths, line ranges, and a textual explanation of consistent identifier renaming.
4. Labels the classification as a _Type-2-only body candidate_.
5. Prints **“Human review required; similarity is not proof of plagiarism.”**
6. Excludes invalid match records from the reported count and issues a warning.

The current report states the **rule** that was satisfied; it does **not** yet list each identifier mapping, calculate a similarity score, or produce CSV/JSON.

### Application integration

File: `src/application.cpp`.

`AnalyzedSourceFile` stores each source path, token vector, and recognized function-body regions. In the nested source-file comparison loops, the application calls both `findType1BodyMatches()` and `findType2BodyMatches()` independently and prints their counts. When a match collection is nonempty, it calls the matching reporter.

A file pair is counted whether or not either detector finds a candidate. The single-file input path still performs source reading, preprocessing, tokenization, and region recognition without cross-file detection.

### Recursive scanning and student-relative paths

The directory-analysis path asks:

```text
Scan subfolders recursively? (y/n):
```

- `n` (and currently any choice other than `y` or `Y`) uses `std::filesystem::directory_iterator` to visit direct entries only.
- `y` or `Y` uses `std::filesystem::recursive_directory_iterator` to visit entries in subdirectories too.
- Both modes accumulate discovered entries and process regular files whose extension is exactly `.c` or `.cpp` (lowercase).

For a source path within a student directory, the expression below produces a readable path relative to the selected root:

```cpp
first.path.lexically_relative(sourcePath).generic_string()
```

For instance, `student1/fibonacci.c` can be distinguished from `student2/fibonacci.c` in both comparison messages and reports. `generic_string()` gives `/` separators regardless of Windows path presentation.

### Matching Rules, Bidirectional Maps and Worked Examples

#### Required checks

For each proposed region pair, the comparator proceeds in this order:

1. **Bounds:** Reject a region if it is empty (`begin >= end`) or its exclusive end exceeds the corresponding token-vector size.
2. **Length:** Reject if the two regions have different numbers of tokens.
3. **Type:** For each aligned token position, reject if token types differ.
4. **Identifiers:** If both aligned tokens are identifiers, enforce a consistent **bidirectional**, one-to-one lexeme mapping.
5. **Other tokens:** If the token is not an identifier, require exact lexeme equality.
6. **Type-2-only distinction:** Return true only if a valid comparison included at least one renamed identifier; otherwise leave an exact Type-1 match in the Type-1 category.

These checks operate on token lexemes; the code does not perform scope-aware binding resolution or check that two algorithms have the same meaning.

#### Why two hash maps are necessary

The comparator uses:

```cpp
std::unordered_map<std::string, std::string> forwardMap;
std::unordered_map<std::string, std::string> reverseMap;
bool hasRenamedIdentifier = false;
```

- `forwardMap`: first-body identifier → second-body identifier. A repeated identifier must keep the same target.
- `reverseMap`: second-body identifier → first-body identifier. Two different first-body identifiers must not collapse onto the same target.
- `hasRenamedIdentifier`: distinguishes renamed candidates from exact matches.

For supported input sizes, hash-map lookup is typically average-case constant time; worst-case hashing costs can be higher.

#### Worked example: accepted rename

```c
/* Body A */
int sum = a + b;
return sum;
```

```c
/* Body B */
int total = x + y;
return total;
```

A valid one-to-one correspondence is:

| First body | Second body |
| ---------- | ----------- |
| `sum`      | `total`     |
| `a`        | `x`         |
| `b`        | `y`         |

The repeated `sum` must continue mapping to `total`; keywords, operators, and punctuation remain identical. At least one identifier differs, so the pair can qualify as Type-2-only.

#### Worked example: forward conflict

```c
return a + a;
```

```c
return x + y;
```

The first appearance suggests `a -> x`, but the next requires `a -> y`. The comparator rejects this inconsistent mapping.

#### Worked example: reverse conflict

```c
return a + b;
```

```c
return x + x;
```

Here `a -> x` and `b -> x` would violate the reverse-map uniqueness requirement. The comparator rejects the pair.

#### Type-1 versus Type-2-only classification

| Bodies being compared                                     | Type-1    | Restricted Type-2-only |
| --------------------------------------------------------- | --------- | ---------------------- |
| Same body-token types and lexemes                         | Candidate | Excluded               |
| Identifiers consistently renamed; other lexemes unchanged | Rejected  | Candidate              |
| Operator changed (`+` to `-`)                             | Rejected  | Rejected               |
| Number literal changed (`1` to `2`)                       | Rejected  | Rejected               |
| Inconsistent identifier mapping                           | Rejected  | Rejected               |

**Terminology note:** The restricted implementation does not cover every variation sometimes included in conventional Type-2 definitions.

#### Region discovery and complexity

`findType2BodyMatches()` uses nested loops over two vectors of recognized regions and calls the single-pair comparator for each combination.

- If the two files have `r` and `s` recognized function bodies, then **`r × s` region pairs** are examined for Type-2-only matches.
- If the aligned regions contain `L` tokens, a comparison typically takes **O(L)** time under average hash-map operations, with early exits when constraints fail.
- The per-comparison identifier maps use memory proportional to the number of distinct identifiers seen in that comparison.

### Comparing Files and Nested Student Submissions

#### Pair enumeration

The application processes every distinct unordered pair of analyzed source files using `i` and `j = i + 1` loops. For `n` successfully analyzed source files:

```text
source-file pairs = n * (n - 1) / 2
```

Examples: four files yield six pairs; six files yield 15 pairs; 60 files would yield 1,770 pairs **if all 60 were successfully analyzed**. The 60-file scenario has not yet been benchmarked.

File-pair enumeration includes comparisons of files for different assignments and comparisons between files belonging to the same student. The current pipeline does not infer or use student identity or assignment identity to constrain comparisons.

#### Nested student-submission layout

The verified recursive fixture uses:

```text
tests/fixtures/type2/three_students/
├── student1/
│   ├── fibonacci.c
│   └── prime.c
├── student2/
│   ├── fibonacci.c
│   └── prime.c
└── student3/
    ├── fibonacci.c
    └── prime.c
```

The intended controlled relationships are one exact Fibonacci body between Students 1 and 2 and five identifier-renaming relationships across corresponding Fibonacci and prime-code pairs. The system analyzes all six files rather than assuming these pairings.

### Three-Student Experimental Evidence (Detailed)

For `tests/fixtures/type2/three_students` with recursive scanning (`y`):

| Metric                              |                       Actual |
| ----------------------------------- | ---------------------------: |
| Analyzed `.c` files                 |                            6 |
| Recognized function bodies          |                   1 per file |
| Distinct source-file pairs          |                           15 |
| Type-1 candidates                   |                            1 |
| Type-2-only candidates              |                            5 |
| Unintended positive candidate pairs | 0 in this controlled fixture |

**Detailed observed candidate relationships:**

| Source pair                                      | Classification |
| ------------------------------------------------ | -------------- |
| `student1/fibonacci.c` vs `student2/fibonacci.c` | Type-1         |
| `student1/fibonacci.c` vs `student3/fibonacci.c` | Type-2-only    |
| `student2/fibonacci.c` vs `student3/fibonacci.c` | Type-2-only    |
| `student1/prime.c` vs `student2/prime.c`         | Type-2-only    |
| `student1/prime.c` vs `student3/prime.c`         | Type-2-only    |
| `student2/prime.c` vs `student3/prime.c`         | Type-2-only    |

The remaining nine file pairs produced zero candidates. Reports preserved relative paths such as `student1/fibonacci.c` and `student3/fibonacci.c`.

### Interpreting Matching Evidence Responsibly

A CloneScope result is a **candidate for human review**. It means that two recognized function-body token sequences satisfied a specified rule. It **does not** mean the students collaborated improperly or that either student plagiarized.

- A **Type-1** finding provides evidence of identical body-token types and lexemes after supported preprocessing.
- A **Type-2-only** finding provides evidence of matching non-identifier tokens and consistent one-to-one identifier renaming.
- A zero candidate count means no qualifying region pair was found **under the current detection rules**; it does not prove the submissions are unrelated or semantically different.
- Candidate counts depend on the number of files, recognized regions, and assignment structure. They are **not** a measured plagiarism probability or a calibrated similarity percentage.

Any academic interpretation must account for assignment requirements, reference solutions, standard patterns, and independent development.

## Build and Run (Windows PowerShell)

From the repository root, compile the full application with a C++17-compatible `g++`:

```powershell
g++ -std=c++17 -Wall -Wextra src/main.cpp src/application.cpp src/preprocessor.cpp src/tokenizer.cpp src/code_region.cpp src/function_region.cpp src/type1_clone.cpp src/type1_report.cpp src/type2_clone.cpp src/type2_report.cpp -o clonescope.exe
```

Run it:

```powershell
.\clonescope.exe
```

**Example A — Non-recursive Type-1 regression dataset**

```text
Enter source file path: tests/fixtures/type1
Scan subfolders recursively? (y/n): n
```

**Example B — Type-2 positive fixture**

```text
Enter source file path: tests/fixtures/type2
Scan subfolders recursively? (y/n): n
```

**Example C — Nested student folders (recursive scan)**

```text
Enter source file path: tests/fixtures/type2/three_students
Scan subfolders recursively? (y/n): y
```

`n` considers only directly contained source files; `y` also considers source files in nested subdirectories. In the current implementation, entries other than `y`/`Y` use non-recursive scanning.

## Verification and Testing

Tests described here are **local checks** and controlled fixtures, not automated GitHub CI or measurements of general plagiarism-detection accuracy.

### Existing Phase 2 Regression Programs

These seven smoke-test programs were previously executed successfully:

1. `tests/preprocessor_smoke.cpp`
2. `tests/tokenizer_smoke.cpp`
3. `tests/pipeline_smoke.cpp`
4. `tests/code_region_smoke.cpp`
5. `tests/function_region_smoke.cpp`
6. `tests/type1_clone_smoke.cpp`
7. `tests/type1_file_pipeline_smoke.cpp`

Previously verified Type-1 fixture results:

| Dataset                                          | Source files | File pairs | Type-1 candidates |
| ------------------------------------------------ | -----------: | ---------: | ----------------: |
| Positive (`tests/fixtures/type1`, non-recursive) |            4 |          6 |                 6 |
| Negative (`tests/fixtures/type1/negative`)       |            2 |          1 |                 0 |
| Mixed (`tests/fixtures/type1/mixed`)             |            3 |          3 |                 1 |

### Phase 3 Type-2 Comparator Tests

Build and execute:

```powershell
g++ -std=c++17 -Wall -Wextra tests/type2_clone_smoke.cpp src/type2_clone.cpp src/tokenizer.cpp -o type2_clone_smoke.exe
.\type2_clone_smoke.exe
```

**10/10 checks passed** in the latest verified local run, covering:

- Consistent identifier renaming.
- Inconsistent forward mapping rejection.
- Reverse-map collision rejection.
- Exclusion of exact Type-1 matches.
- Changed-operator rejection.
- Changed-literal rejection.
- Valid-region acceptance.
- Empty-region rejection.
- Out-of-bounds-region rejection.
- Multi-region match discovery.

### Phase 3 Type-2 Reporting Tests

Build and execute:

```powershell
g++ -std=c++17 -Wall -Wextra tests/type2_report_smoke.cpp src/type2_report.cpp src/tokenizer.cpp -o type2_report_smoke.exe
.\type2_report_smoke.exe
```

**5/5 checks passed** in the latest verified local run, covering:

- Relative source-path text.
- Type-2-only classification text.
- Human-review warning.
- Reported candidate count.
- Safe skipping of an invalid match region.

### Application-Level Datasets

| Dataset and mode                            | Files | File pairs | Type-1 | Type-2-only |
| ------------------------------------------- | ----: | ---------: | -----: | ----------: |
| `tests/fixtures/type1` (`n`)                |     4 |          6 |      6 |           0 |
| `tests/fixtures/type2` (`n`)                |     2 |          1 |      0 |           1 |
| `tests/fixtures/type2/three_students` (`y`) |     6 |         15 |      1 |           5 |

The three-student recursive fixture contains separate `student1`, `student2` and `student3` directories with `fibonacci.c` and `prime.c` files in each. Its controlled results included one Type-1 Fibonacci-body match and five Type-2-only matches across the same assignments, with no unexpected matches in the other nine file pairs.

Additional manually exercised fixtures include:

- `tests/fixtures/type2/factorial/` — factorial programs with identifier renaming.
- `tests/fixtures/type2/classroom_six/` — six mixed student submissions covering `for` loops, `while` loops, prime checking, comment differences and identifier renaming.

These tests support the behavior observed on the selected fixtures. They do **not** establish measured precision, recall, or broad-language coverage.

### Example Report

```text
Comparing files: student1/fibonacci.c vs student3/fibonacci.c
Type-1 body-level candidates: 0
Type-2 body-level candidates: 1
CloneScope Type-2 body-level candidate report

Candidate #1
student1/fibonacci.c: lines 4 to 19
student3/fibonacci.c: lines 4 to 19
Evidence: consistent one-to-one identifier renaming with matching non-identifier token lexemes.
Classification: Type-2-only body candidate.
Human review required; similarity is not proof of plagiarism.

Reported candidates: 1
```

## Current Limitations

- **Restricted language handling:** preprocessing, tokenization and function recognition do not cover all C/C++ syntax.
- **Restricted Type-1/Type-2 coverage:** comparisons are performed on recognized function bodies, not whole-program semantics; signatures are excluded.
- **Identifier-only Type-2 variation:** changed number/string/character literals, operators and non-identifier lexemes are not permitted by the current Type-2 matcher.
- **Lexeme-based identifier mapping:** the current comparator is not scope-aware and does not resolve identifier binding or shadowing like a full parser.
- **Supported file extensions:** only lowercase `.c` and `.cpp` are selected by the folder filter.
- **Filesystem behavior:** recursive traversal is optional; sophisticated error handling, deterministic discovery ordering and assignment-aware grouping are not yet implemented.
- **Input encoding:** the pipeline has not yet been made robust for all BOM-encoded source files. Test fixtures were saved as UTF-8 without BOM.
- **Lexical limits:** full macro expansion, raw string literals, line splicing, advanced numeric forms and some other C/C++ constructs remain unsupported.
- **Output volume:** the program currently prints preprocessed source code and pairwise results to the terminal, which can be unwieldy for large datasets.
- **Reporting detail:** the Type-2 reporter describes consistent renaming but does not list the actual identifier mapping.
- **No automatic student/assignment grouping:** all discovered distinct file pairs are compared, including different assignments and files from the same student.
- **No statistical or stylometric assessment yet:** candidate counts are not plagiarism scores, and the tool does not calculate verified authorship probabilities.
- **No CSV/JSON export yet:** structured export is planned, not implemented.
- **Scalability unmeasured:** 30–40-student / 60–80-file experiments have not yet been benchmarked.
- **No automated CI configured:** the recorded tests were run locally.

Short or common solutions, assignment templates and independently written code can legitimately produce candidate matches. **All findings require human interpretation.**

## Learning and Technical Documentation

Existing materials:

- [Source Preprocessing Learning Manual](docs/learning-notes/CloneScope_Source_Preprocessing_Learning_Manual.pdf)
- [Tokenization Learning Manual](docs/learning-notes/CloneScope_Tokenization_Learning_Manual.pdf)
- [Phase 2 — Function and Block Representation](docs/phase2-function-block.md)
- [Phase 2 Function, Block and Type-1 Learning Manual](docs/learning-notes/CloneScope_Phase2_Function_Block_Type1_Learning_Manual.pdf)

Phase 3 implementation details, algorithms, verified experiments, and limitations are documented in this README.

For detailed C++17 explanations, identifier-mapping walkthroughs, recursive scanning, testing procedures, and supervisor-viva preparation, see the [CloneScope Phase 3 Type-2 Learning Manual](docs/learning-notes/CloneScope_Phase3_Type2_Learning_Manual.pdf).

## Midterm-First Development Roadmap

The remaining pre-midterm work is planned in this order:

1. **Close Phase 3:** complete Type-2 documentation, final tests, branch publication, Pull Request review and merge.
2. **Initial stylometric and statistical analysis:** collect suitable coding-style features and explainable student-wise/pairwise summaries; preserve access to original source text for formatting/comment evidence.
3. **Enhance Type-1 and Type-2:** improve supported cases, reliability, validation and false-positive control based on documented limitations.
4. **Structured reporting:** introduce basic CSV/JSON export and less verbose terminal summaries.
5. **Larger classroom-style evaluation:** exercise approximately 30–40 students / 60–80 source files with labeled examples, performance measurement and examination of false positives and false negatives. If genuine student submissions are used, obtain appropriate permission and anonymize them.
6. **Midterm demonstration and viva:** prepare reproducible examples, documented limitations, performance observations and human-review-oriented findings.

**After the midterm**, planned work includes restricted Type-3 detection, restricted Type-4 candidate screening, Type-3 enhancements and remaining approved final-project refinements.

This roadmap is a development plan, not a claim that later features are already implemented.

## Academic and Ethical Use

CloneScope presents explainable code-similarity **candidates** for review. Identical or structurally similar student solutions may arise legitimately, especially on short or standardized programming tasks. Source locations, clone types, stylometric observations and future statistics must be interpreted by a human reviewer together with assignment context.

**CloneScope must not be used to automatically declare that a student committed plagiarism.**
