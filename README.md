# OPESY-MP1
Group Members:
- Chua, Edric Jarvis
- Cruz, Renz Ezekiel
- Li, Wai Kei
- Yu, Cedric Leopold

## Dependencies
### Required
- [gcc](https://gcc.gnu.org/install/download.html)
- [GNU Make](https://www.gnu.org/software/make/#download)
### Optional
- [diff](https://www.man7.org/linux/man-pages/man1/diff.1.html)
- [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html)

## Build
1. Install the required dependencies `gcc` and `make`.
2. `cd` into project root.
3. Run `make release` to compile executable.
4. Executable is located at `build/a.out`.
5. After usage, run `make clean` to remove executable and build artifacts.

# Usage
- Program reads input from `stdin`.
- Input redirection is preferred method for passing inputs (i.e. `build/a.out < input_txt_file_here`).
- All inputs are expected to conform to the specifications.

## Extras
- Other compilation targets: `all` `debug` `bench` `bench-prof`
- `bench` prints output together with CPU execution time.
- `bench-prof` is the same as `bench` but with extra compilation flags for profiling with [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html).
- Run `./testscript.sh` for info on how to run test cases. *(requires optional dependencies)*
