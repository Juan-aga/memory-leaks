# memory_leaks

memory_leaks is a library to check for memory leaks in C programs.

## Usage

1. Include the `memory_leaks.h` header file in all your header files that contain calls to `malloc`, `calloc`, or `free` functions. Make sure to include this header file in all relevant files to ensure accurate tracing of memory allocations.

2. At the exit of the program, memory_leaks will generate a report with any detected memory leaks. By default, the report is displayed in the standard output.

3. Optional: If you want to save the report to a file, you can compile the program with the `make LOG` command. This will create a report file named `PID_PROCESS.log`, where `PID` is the process ID of the program.

## Platform-specific Notes

### MAC

No special attention is required when using MemoryLeaks on MAC systems.

### LINUX

If you encounter compilation issues, make sure that you have the `build-essential` package installed. You can install it by running the following command:

```
sudo apt install build-essential
```
This package provides essential tools for building software on LINUX systems.
