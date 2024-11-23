# get_next_line

The `get_next_line` project is a foundational task at 42 that challenges students to write a function capable of reading a file, one line at a time. This function must work efficiently and handle edge cases such as varying buffer sizes, file descriptors, and memory management.

This document explains the structure, implementation, and key concepts of the project, including the use of static variables.

## Status

Finished: 17/11/2024. Grade: 125/100.

## Function Prototype
```c
char *get_next_line(int fd);
```
### Parameters:
- `fd`: The file descriptor to read from.

### Return Value:
- Returns the next line from the file descriptor, including the newline character (if present).
- Returns `NULL` if an error occurs, the end of the file is reached, or the buffer size is invalid.

## Key Concepts

### Static Variables
A critical part of this project is the use of static variables. Static variables retain their value between function calls, making them ideal for storing data that persists across multiple invocations of `get_next_line`. In this project:

- The static variable `buffer` is used to store leftover data from the previous read operation.
- This allows the function to continue processing from where it left off, ensuring efficient reading without redundant operations.

### Memory Management
Careful memory management is crucial in `get_next_line`. Functions like `ft_calloc`, `ft_strjoin`, and `free` ensure that dynamically allocated memory is properly managed to avoid memory leaks.

## File Structure

### `get_next_line.c`
Contains the main logic:
- **`get_next_line`**: Orchestrates the reading process, using helper functions to fill the buffer, extract the next line, and update the buffer.
- **`fill_buffer`**: Reads from the file descriptor into the buffer until a newline is encountered or the end of the file is reached.
- **`get_the_line`**: Extracts a single line from the buffer.
- **`erase_from_buffer`**: Updates the buffer by removing the extracted line.

### `get_next_line_utils.c`
Contains utility functions:
- **`ft_calloc`**: Allocates memory and initializes it to zero.
- **`ft_strchr`**: Searches for a character in a string.
- **`ft_strjoin`**: Concatenates two strings, freeing the first string.
- **`ft_strlen`**: Computes the length of a string.

### `get_next_line.h`
Defines the function prototypes and includes necessary headers. It also defines the default `BUFFER_SIZE` if not specified during compilation.

## Buffer Size
The `BUFFER_SIZE` macro determines the number of bytes read at a time from the file descriptor. You can set this value at compile time using the `-D` flag, e.g.,

```bash
gcc -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c -o get_next_line
```

### Choosing the Buffer Size
- A larger `BUFFER_SIZE` reduces the number of read calls but increases memory usage.
- A smaller `BUFFER_SIZE` increases the number of read calls but decreases memory usage.

## Usage
Compile the files with a test program and run:

```bash
gcc get_next_line.c get_next_line_utils.c -o gnl
./gnl
```

## Important Notes
- **Static variables**: Their persistent nature makes them powerful but also requires careful handling to avoid unexpected behavior, especially in multi-threaded contexts or recursive calls.
- **Memory leaks**: Always free allocated memory after use.
- **Edge cases**: Ensure your implementation handles edge cases like invalid file descriptors, empty files, or non-standard input correctly.

## Example Output
Given a file `test.txt` containing:
```
Hello, World!
42 is amazing.
EOF
```
Calling `get_next_line` repeatedly will produce:
1. `"Hello, World!\n"`
2. `"42 is amazing.\n"`
3. `NULL` (end of file).

## Bonus Part: Handling Multiple File Descriptors
The bonus part extends `get_next_line` to support reading from multiple file descriptors simultaneously, while still adhering to the requirement of using only one static variable.

### Implementation Details
- **Static Array:**
  A static array is used to maintain separate buffers for each FD:

  ```c
  static char *buffer[4096];
  ```

- **Indexed by FD:**
  Each index in the `buffer` array corresponds to a specific FD. This allows each FD to retain its own buffer state independently.

### Key Features
1. **Multiple FD Support:**
   - The function can handle simultaneous reads from different FDs without interference.

2. **Efficient Memory Management:**
   - Each FD's buffer is dynamically allocated and freed as necessary.

### Improvement Suggestion
The current implementation uses a fixed-size static array (`buffer[4096]`), which reserves memory for a large number of FDs even if most are unused. An improvement would be to use a dynamic data structure, such as a hash table or linked list, to allocate buffers only for active FDs. This would optimize memory usage and make the implementation more scalable.

### Example Usage
```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);

printf("From file1: %s", line1);
printf("From file2: %s", line2);

free(line1);
free(line2);
close(fd1);
close(fd2);
```

## Conclusion
The `get_next_line` project is an excellent exercise in memory management, file handling, and efficient reading strategies. By mastering this project, you develop foundational skills essential for more advanced programming tasks.
