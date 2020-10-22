# Testing Documentation
## Manual testing
The program has been extensively tested manually in various ways. 

First of all, every step of the generation has been manually checked to produce correct results.

Secondly, the result of the entire generation is checked and parameters have been adjusted to produce a visually pleasing dungeon.


## Automated testing
All of the program, excluding the UI, is verified with automated tests. These tests are automatically ran in Travis for every commit in all branches. The automated tests are split into 4 different parts. Each part requires the previous one to pass. The tests are ran locally on Windows 10 with MSVC 19.16 and in a CI environment on Ubuntu 20.04 with GCC 10.

1. Static checks  
The project uses a slightly customized coding style derived from WebKit and enforces that using `clang-format`. Static checks are ran for every file in `src/dungeon_generation` (incl. UI) using [a python script](https://github.com/Sarcasm/run-clang-format).

2. Unit/Integration testing   
The project uses [doctest](https://github.com/onqtam/doctest) for automated unit and integration tests. After running tests, code coverage from gcov is automatically uploaded to [codecov](https://codecov.io/).

3. Runtime and memory leaks  
On this step, the program is ran using the `--headless` flag through [valgrind](https://valgrind.org/) to check for memory leaks. It also verifies that the program is able to be ran.

4. Windows build  
The final check is building the project on Windows. The tests aren't ran again, since that is done locally. This step exists mostly for enabling automated deployment of both Windows and Linux binaries to GitHub for commits specifically tagged for release.

## Performance testing
Performance testing is not as important for a project of this type. The generation is usually done during a loading screen, so the difference between a 10 second and 1 second loading screen is negligible at best.
