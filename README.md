# memory_leaks

This is a library to check the memory leaks.

At the exit of the program, it returns a report with the leaks.

# Use

You have to include memory_leaks.h in all your headers files that calls malloc, calloc or free.
It only can trace the memory allocations if it's included in all the header. Otherwise it could be information that can't trace.

It shows the final report, by default, in the standar output.
If you need the report go to a file, you can compile with "make LOG".
It creates a report file named "PID_PROCESS.log".

# MAC

No need special attention to use.

# LINUX

If you have problems to compile, make sure that you have build-essential installed.

You can install it using "sudo apt install build-essential"
