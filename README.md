![CI](https://github.com/h3l333/sorting-algorithms/actions/workflows/ci.yml/badge.svg)

# Sorting Algorithms Benchmark

A C project that implements and compares five classic sorting algorithms under best-case, average-case, and worst-case input arrangements.

The goal is to connect algorithmic complexity with measured runtime behaviour. The project includes a technical report written in Spanish with methodology, timing tables for a single series of executions, charts, and conclusions.

## Algorithms

| Algorithm                      |               Best case |            Average case |              Worst case | Stable | In-place |
| ------------------------------ | ----------------------: | ----------------------: | ----------------------: | :----: | :------: |
| Bubble sort                    |                  O(n^2) |                  O(n^2) |                  O(n^2) |  Yes   |   Yes    |
| Selection sort                 |                  O(n^2) |                  O(n^2) |                  O(n^2) |   No   |   Yes    |
| Insertion sort                 |                    O(n) |                  O(n^2) |                  O(n^2) |  Yes   |   Yes    |
| Shell sort\*                   | Depends on gap sequence | Depends on gap sequence | Depends on gap sequence |   No   |   Yes    |
| QuickSort (last-element pivot) |              O(n log n) |              O(n log n) |                  O(n^2) |   No   |   Yes    |

\* This implementation uses a halving gap sequence. Shell sort complexity depends on both the sequence of gaps and the input, so the report treats its worst-case input as an experimental approximation.

## Project layout

```text
include/    Public function declarations
src/        Sorting algorithms, utilities, and benchmark program
tests/      Utility-generator check and sorting correctness tests
.github/    GitHub Actions CI workflow
bin/        Build output (generated; ignored by Git)
Dockerfile  Multi-stage build for running the benchmark in a container, no local toolchain needed
.dockerignore
            Excludes bin/, .git/, tests/, and docs from the Docker build context
Análisis de algoritmos de ordenamiento.pdf
            Full report: methodology, results, charts, and conclusions
Análisis de algoritmos de ordenamiento.md
            Markdown transcription of the report (charts omitted; see the PDF for those)
```

## Requirements

- A C compiler with C11 support, such as GCC or Clang
- GNU Make

The commands below are written for Linux, macOS, or WSL. On Windows, WSL is the simplest way to use the provided Makefile. Alternatively, use [Docker](#running-with-docker) and skip installing a toolchain entirely.

## Build and run

```bash
make
./bin/main 1  # best case
./bin/main 2  # average/random case
./bin/main 3  # worst case
```

Example output (times vary by computer):

```text
Caso para n = 2500
Burbujeo: 0.016082 segundos
Seleccion: 0.006066 segundos
Insercion: 0.002986 segundos
Shell: 0.000280 segundos
QuickSort: 0.000220 segundos
```

Run the test suite (utility-generator check plus sorting correctness tests covering all five algorithms):

```bash
make test
```

Remove generated executables:

```bash
make clean
```

## Running with Docker

No local compiler needed. The included `Dockerfile` is a multi-stage build: it compiles with `gcc:13-bookworm`, then copies only the resulting binary into a `debian:bookworm-slim` runtime image (~114 MB, no compiler included).

```bash
docker build -t sorting-algorithms .
docker run --rm sorting-algorithms 1   # best case
docker run --rm sorting-algorithms 2   # average/random case (default if no argument is given)
docker run --rm sorting-algorithms 3   # worst case
```

## Results at a glance

The complete measurement tables and charts are available in [the Markdown transcription of the original report](<Análisis de algoritmos de ordenamiento.md>) (charts omitted). The table below highlights the random-input run at `n = 150,000`.

| Algorithm      | Time (seconds) |
| -------------- | -------------: |
| Bubble sort    |      88.994592 |
| Selection sort |      23.829920 |
| Insertion sort |      13.448955 |
| Shell sort     |       0.037259 |
| QuickSort      |       0.020236 |

## Key findings

- Bubble and Selection sort exhibit the expected quadratic growth and become impractical for large arrays.
- Insertion sort is extremely effective on already sorted input, but degrades on random or reverse-ordered arrays.
- QuickSort is fastest on average with balanced partitions, but choosing the final element as the pivot exposes its quadratic worst case on ordered input.
- Shell sort was consistently fast in these experiments, while its theoretical worst-case behaviour remains dependent on the selected gap sequence.

## Known limitations

**QuickSort recursion depth on the worst-case input.** This is separate from the O(n^2) _time_ growth documented above and in the report- it's about _stack memory_, not CPU time.

With the last element as pivot, an already-sorted or reverse-sorted array (exactly the worst-case construction used for `caso 3`) produces maximally unbalanced partitions at every step. Instead of the O(log n) recursion depth QuickSort normally achieves, this implementation recurses n levels deep, using stack space linearly in n.

In practice this means the amount of stack space available matters:

| Stack size                                                                   | `./bin/main 3` at n = 150,000                      |
| ---------------------------------------------------------------------------- | -------------------------------------------------- |
| 8 MB (typical Linux/WSL default- what this project's report was measured on) | Completes normally                                 |
| 1 MB (Windows' default thread stack)                                         | Crashes with a stack overflow (segmentation fault) |

So the timings in the report and README are unaffected- they were produced on WSL, comfortably within the 8 MB default. But the 8 MB case isn't a large margin either, and the same worst-case input would reliably crash a build run natively on Windows (outside WSL) rather than merely running slower.

The standard fix is to recurse into the smaller partition and loop over the larger one, which bounds the recursion depth to O(log n) regardless of input order- left as a possible follow-up rather than applied here, since it would change the implementation being measured.

## Reproducing the original compilation command

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c -o bin/main
```

## License

Released under the [MIT License](LICENSE).
