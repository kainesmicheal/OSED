we refer to the memory visible only to the kernel as kernel land memory

the memory of the user process sees as user land memory

userrs are indentified by a unique value usually a number, userid

administrator and root userid has the higher privileges than other users

they are also called as super users

super users can modify the kernel itself

reaching super user access is the goal of an kernal exploit

execution context is the state of process at a given time

if the we switch it, we call it a context switching

Sheduler does this job, by switch diferent processes concurrently

being able to influence the scheduler's desicion is of great importance when exploiting race conditions

the kernel also keeps track of other process details, such as what files it opened, its security credentials and what memory range it is usiing

