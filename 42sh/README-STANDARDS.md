# Project Standards Documentation

This document describes the standards and best practices to follow during the **42SH** project.

## Coding Style

### 1. File Organization

- Header files (`.h`) contain only declarations, and source files (`.c`) contain implementations.
- Follow the Epita Standard

```
// Example of include guards in io.h
#ifndef IO_H
#define IO_H

// ... (contents of the header file)

#endif /* ! IO_H */
```

### 2. Naming Conventions

- Use `snake_case` for variable and function.

### 3. Indentation and Formatting

- Follow the Epita coding-style.

### 4. Comments

- Add comments in the header file to explain each function.
- For static functions, comment must be in source file, on top of the implementation
- Use Doxygen-style comments.

```
/**
 
@brief Get the size of the FILE.*
@param file Pointer to the FILE.
@return The size of the file.
*/
static long get_file_size(FILE *file);
```

## Memory Management

### 1. Memory Allocation

- Always check the return value of memory allocation to check if it worked.
- In the case of an allocation error, use this define function to handle it.
```
#define handle_error(msg)                                                 
    do                                                                    
    {                                                                     
        perror(msg);                                                      
        exit(EXIT_FAILURE);                                               
    } while (0)
```

## Git

- Commit messages should follow the git convetional commit : https://www.conventionalcommits.org/en/v1.0.0/.
- Always worked on the dedicated branch for each module named as follow : `modulename_branch`.

```
git commit -m "feat(io): io function implemented"
```
