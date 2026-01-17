# GET_NEXT_LINE

*This project has been created as part of the 42 curriculum by yelallam*

## Description

The goal of this project is to create a function that returns a single line read from a file descriptor. A "line" is defined as a string ending with a newline character (`\n`) or the end of the file (EOF). This implementation is built to handle multiple file descriptors (in the bonus) and varying buffer sizes efficiently, providing a reliable tool for sequential text processing in C.

## Compilation

To use `get_next_line`, include the header in your source code and compile the `.c` files. You must define a `BUFFER_SIZE` during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

## Usage

The function prototype is:

```c
char *get_next_line(int fd);
```

It returns the line read, including the `\n` if present. It returns `NULL` if there is nothing left to read or if an error occurs.

## Resources

In my journey while working on this project, I faced several hurdles, especially from lack of knowledge. Here are the best resources that helped me complete this project:

### Understanding Variables in C
- [Local, Global, Static Variables - Types of variables](https://www.youtube.com/watch?v=K9s1EuzMmYI)

### Core Concepts and Planning
- [File descriptors](https://www.youtube.com/watch?v=dDwXnB6XeiA)
- [Handling a file by its descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
- [Master File I/O Operations with 42's get_next_line project](https://medium.com/@ayogun/master-file-i-o-operations-with-42s-get-next-line-project-5fb001d1fff5)

### Additional Tools
I also used the Gemini LLM to make concepts easier to understand, create quizzes to test my understanding, discover new debugging tools for treating memory leaks, and automate the norminette check process for indentation, tabs, and syntax. This allowed me to focus more on the algorithm itself.

## Algorithm Explanation and Justification

My approach evolved through three distinct phases:

### Phase 1: Initial Plan
I originally intended to use a single, large function that handled reading, joining, and searching for newlines in one go.

### Phase 2: Identifying Flaws
During the pseudo-code phase, I realized this would lead to "spaghetti code" that violated the 42 Norm (the 25-line limit per function) and made error handling (like malloc failures) extremely difficult to track.

### Phase 3: Re-planned Modular Approach
I broke the logic into specialized helpers. This allowed me to section off specific responsibilities, making the code easier to debug and compliant with the line-count constraints.

## Function Breakdown

### 1. `get_next_line` (The Orchestrator)
Manages the high-level loop. It handles the "handover" by moving the static `left_overs` to a local line pointer immediately to prevent dangling pointers.

### 2. `read_and_join` (The Fetcher)
Tailored to handle the `read()` system call and append new data to our current string using `ft_strjoin`.

### 3. `process_line` & `handle_extraction` (The Sculptors)
Once a `\n` is found, these functions "carve" the returnable line out of the accumulated data and save the remainder back into the static variable.

### 4. `handle_error` (The Cleaner)
A centralized way to free memory and return `NULL` whenever a read fails or an invalid file descriptor is detected.

## Memory Safety and Leak Prevention

Memory safety was a primary requirement. I handled it through:

- **Handover Strategy**: By setting `left_overs = NULL` at the start, I ensure that the function "owns" the memory locally. If the function crashes or returns early, the static variable isn't pointing to freed memory.

- **Heap-Based Buffering**: Using `malloc` for the read buffer (instead of a stack array) ensures we can handle a `BUFFER_SIZE` of 10,000,000 without a stack overflow.

- **Systematic Freeing**: Every `ft_strjoin` or `ft_extract_str` result replaces an old pointer, which is immediately freed to prevent accumulation.
