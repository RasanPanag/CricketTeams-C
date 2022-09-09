# Creator: Rasandeep Singh Panag

## General Concept;
There are two files in this repository. One file will show you how a program can enter into deadlocks and other file will break the deadlock

## CricketTeams.c
- This file based on scenario that there are five cricket teams numbered zero to four and there are 4 sets of three wickets.   
- Each team needs two set to practice for their upcoming matches but, on the  ground each team has one set to use. So, for them, in order to practice they must share set of wickets. The set on their right hand side has the same number as the team has. So, each team will reach their own set.  
- When they have their assigned set of wickets. Then the team will reach wickets that is assigned to their neighbor.    
- After one team has both sets of wickets then they will practice. After practice then that team can return the set of wickets to their original position on the ground. The process is repeated until there is no more team left to practice.

**This program use POSIX threads and can exhibit both potential and actual deadlocks**

## Deadlocks.c
This file is based on the same scenario but, it has four teams will attempt to practice at the same time. The new implementation uses the semaphore "num_can_practice" to limit the number of teams who can practice at same time. This semaphore is initialized to four, one less than the number of philosophers.   
**Also, this file is created to solve the problem of actual or potential deadlocks.**
