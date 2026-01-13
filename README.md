*This project has been created as part of the 42 curriculum by yelallam*
Description :
    GET_NEXT_LINE :The goal of this project is to create a function that returns a single line read from a file descriptor. A "line" is defined as a string ending with a newline character (\n) or the end of the file (EOF). This implementation is built to handle multiple file descriptors (in the bonus) and varying buffer sizes efficiently, providing a reliable tool for sequential text processing in C.

Instructions :
 1.Compilation :
    To use get_next_line, include the header in your source code and compile the .c files. You must define a BUFFER_SIZE during compilation:
        cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
    Usage :
        The function prototype is: char *get_next_line(int fd);
        It returns the line read, including the \n if present. It returns NULL if there is nothing left to read or if an error occurs.
Resources :
    So in my long journey while working on this project i faced several hurdles especially form lack of knowledge so in general here is the best resources that helped through completing this project ;
        For :Local, Global , Static Variables (in C) - Types of variables : https://www.youtube.com/watch?v=K9s1EuzMmYI
        Other important resources for main concepts and planning :
            file descriptors : https://www.youtube.com/watch?v=dDwXnB6XeiA
            https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/
            a general guide that helped me to better know how to correctly plan my solution: https://medium.com/@ayogun/master-file-i-o-operations-with-42s-get-next-line-project-5fb001d1fff5
            And  without forgetting the use of the gemini llm in making the concpets easier to understand and also making quizes with it to test my understanding and it helped me discovering new tools and ways to helo treating memory leaks in and by saving time for me for automating the process of the norminette check of the indentation tabs and syntaxing so that i can focus more on the algo.

Algorithm Explanation and Justification :
    My approach moved through three distinct phases:
    Initial Plan: I originally intended to use a single, large function that handled reading, joining, and searching for newlines in one go.
    Identifying Flaws: During the pseudo-code phase, I realized this would lead to a "spaghetti code" mess that violated the 42 Norm (the 25-line limit per function) and made error handling (like malloc failures) extremely difficult to track.
    he Re-planned Modular Approach: I broke the logic into specialized helpers. This allowed me to "section off" specific responsibilities, making the code easier to debug and compliant with the line-count constraints.
    Sectioning the Logic: Function Breakdown
    1.get_next_line (The Orchestrator): Manages the high-level loop. It handles the "handover" by moving the static left_overs to a local line pointer immediately to prevent dangling pointers.
    2.read_and_join (The Fetcher): Tailored to handle the read() system call and append new data to our current string using ft_strjoin.
    3.process_line & handle_extraction (The Sculptors): Once a \n is found, these functions "carve" the returnable line out of the accumulated data and save the remainder back into the static variable.
    4.handle_error (The Cleaner):
         A centralized way to free memory and return NULL whenever a read fails or an invalid file descriptor is detected.
    Elaborated Leak Prevention :
        Memory safety was a primary requirement. I handled it through:
            Handover Strategy: By setting left_overs = NULL at the start, I ensure that the function "owns" the memory locally. If the function crashes or returns early, the static variable isn't pointing to freed memory.
            Heap-Based Buffering: Using malloc for the read buffer (instead of a stack array) ensures we can handle a BUFFER_SIZE of 10,000,000 without a stack overflow.
            Systematic Freeing: Every ft_strjoin or ft_extract_str result replaces an old pointer, which is immediately freed to prevent accumulation...
