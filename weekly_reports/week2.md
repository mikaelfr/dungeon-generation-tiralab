# Weekly report for week 2
## This week's progress
Approx. time spent: 30h

I spent the early part of this week coding basic data structures and helper classes and started working a bit on the base structure of the generation.

The largest chunk of the approximately 30h spent on the project this week was just setting up automatic testing and code coverage. I am very happy with the end result. Static checks (style checking) and testing are ran in Travis CI automatically after each push to any branch and test coverage report is automatically uploaded to Codecov. Since I'm using a Windows machine to develop the project, using a CI solution also has the added benefit of making sure that the code is compatible with Linux systems as well. The work done this week should make sure that the time I have to spend on maintaining testing and code coverage should be minimal.

## What I learned
This week my objective was to get some hands-on experience with CI solutions. I learned to use CI to automatically run tests and static checks.

I also learned a lot about CMake, especially about the developer side of things. I had previously only used CMake to build premade projects and never made scripts myself. Now I would say I'm quite comfortable with the basics and wouldn't mind using it in other projects as well.

Unfortunately, I also learned about more C++ compiler optimization quirks. I had not previously encountered problems with dead code optimization since I very rarely, if ever, make my own libraries. As it turns out, if you have some unused boilerplate code in your library that you would like to test anyway for the future, tough luck, the symbols are optimized away and not retrievable even from the object files. But then again, does it really make sense to test code that is never used?

## Problems?
I had a multitude of problems this week, most of which just had to do with me wanting to dive head first into new and interesting challenges (like learning how to use CMake, testing and coverage in C++ and CI; all in one week). All of the problems were solved, though, and I learned a ton of very useful things. I regret nothing.

## Next up
Now that I've set up automatic testing and all that, next week I should be able to progress quite quickly and hopefully get some sort of generation finished. I will probably also look at integrating a UI library to help with debugging how the rooms are separated after generation.