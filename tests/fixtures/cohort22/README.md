# CloneScope controlled classroom corpus — 22 students

**Synthetic educational fixture only.** These are not collected student submissions.
Matching code and style deviations do **not** prove academic misconduct.

## Shared assignment briefs

Every student receives exactly the same three assignment briefs:

1. **Number Theory Lab:** implement bounded factorial, Euclidean GCD,
   and integer palindrome checking; accept four integer inputs.
2. **Array Processing Lab:** read six integers and a target, perform
   selection sort, then search the sorted array with binary search.
3. **Math Toolkit Lab:** read a primality candidate, Fibonacci term index,
   and four integer complex-number components. Report prime status,
   Fibonacci value, and the complex sum.

Each `studentNN/assignmentN.cpp` has its own `main()` and is buildable
with C++17. For controlled fixtures, students select slightly different
input-bound constants. The common example inputs are inside the documented
bounds. Different source bodies for similar assignments are **not** presumed
clones; only exact/consistent-renaming matches are relevant to this prototype.

## Injected clone ground truth

- Group **T1-A**: student01, student02, student17, student18, student19,
  each on `assignment3.cpp`, sharing the *prime-checking function body*.
- Group **T2-B**: student05, student11, student12, student13, student14,
  each on `assignment3.cpp`, sharing *Fibonacci function structure* with
  consistent one-to-one identifier renaming.
- Each group has 5 members and therefore 10 unordered pairs.
- `expected_clone_pairs.csv` contains all 20 injected expected file pairs.
- **Other algorithm functions in the same files are not intentionally clones.**

## Stylometry controls

- student01 and student05: camelCase on assignments 1–2, snake_case on 3.
- student09: PascalCase on assignments 1–2, snake_case on 3; no injected clone.
- student15: historically mixed naming/commenting, so a firm baseline is
  intentionally unavailable.
- student05 and student09: high comment rate in the history, then zero on 3.
- student20: zero historical comments, then high current comment rate.
- student16: zero comments consistently (negative control).
- student21: stable camelCase; student22: stable snake_case (negative controls).

## Expected execution and verification

- 22 student folders; 66 C++ source files; 2,145 source-file pairs.
- Expected injected *body-level* matches: 10 Type-1 + 10 Type-2-only.
- Use `manifest.csv` for the file-level map, `expected_clone_pairs.csv` for
  clone ground truth, `expected_student_findings.csv` for intended style
  controls, and `sample_inputs.csv` for input demonstrations.
- Actual CloneScope output must be checked; do not assume it matches these
  expectations before running integration tests. If not, investigate and
  report false positives and misses instead of changing ground truth.

These authored fixtures are useful for controlled regression tests but are
not representative data and cannot establish real-world precision/recall.
