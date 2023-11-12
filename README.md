# OPESY-MP1

## Dependencies
---
### Required
- [gcc](https://gcc.gnu.org/install/download.html)
- [GNU Make](https://www.gnu.org/software/make/#download)
### Optional
- [diff](https://www.man7.org/linux/man-pages/man1/diff.1.html)
- [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html)

## Build Instructions
---
1. Install (required)[#Required] dependencies.
2. `cd` into project root.
3. Run `make release` to compile executable.
4. Executable will be located at `build/a.out`.
5. Program will read input from `stdin`. Input redirection is preferred method for passing inputs.
6. Run `make clean` to remove executable and build artifacts.

## Extras
---
- Other compilation targets: `all` `debug` `bench` `bench-prof`
- Running `testscript.sh` requires (optional)[#Optional] dependencies.
- `bench` suppresses printing of processes and only outputs elapsed CPU time.
- `bench-prof` is the same as `bench` but requires [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html) for profiling.
