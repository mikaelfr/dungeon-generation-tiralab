# Weekly report for week 5
## This week's progress
Approx. time spent: 15h

Our hero's journey has come to an end. From humble beginnings of simple Travis testing system and basic data structures with poor memory management, all the way to full on CI/CD pipeline with multiplatform deployment and workable data structures with less mediocre memory management, our hero has stood fast against procrastination and shoddy time management. The final boss has been slain. CI/CD pipeline is finally done for real this time. The actual objective of the course has been completed, dungeon generation is functional.

TLDR: Added a deployment script for linux and windows for the fun of it and finished up the generation algorithm.

## What I learned this week
I learned about setting up automatic deployment to Github with Travis on Windows and Linux. Fortunately, I had the utmost pleasure of learning the joys of working with Windows' fine \\\\\\\\\\\\\\ filled file system in deployment scripts. 

I also learned a bit about how friend functions work in C++ and some practical things about overloading the stream operator in C++.

## Problems?
I had really no issues with code after finishing the triangulation part last week. After that, this week has been mostly straight forward finishing up the last few generation steps. 

I obviously ran into problems while messing around with Travis, that's unavoidable. Most of the problems there were just due to the fact that the trifecta of Windows' file system, configuration scripts and my brain don't mesh well together. At the end of the day though, I got the whole pipeline working with a dopamine rush to boot.

## Next up?
Next week I'll probably start off by cleaning up the project. Finishing up test coverage, adding performance tests and maaaaybe, just maybe, adding some tweaks like broadphasing and removing some of the smaller, ugly and useless, rooms (for a potentially nicer visual look).

I'll also need to make sure that the project scope is large enough. If it is, I might add some fun things like generating spawn points and different room environment types over the last few weeks.