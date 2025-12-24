# get_next_line

_This project has been created as part of the 42 curriculum by egaziogl._

## Description

Reading input line-by-line, from a file descriptor, implemented in C.

### Requirements

Function signature:  
`char *get_next_line(int fd)`

External functions allowed:
- Memory allocation functions (`malloc, free`),
- I/O (`read`).

Restrictions:
- Libft,
- `lseek()`,
- Global variables.

Bonus requirements:
- Use only one static variable,
- Handle multiple file descriptors (and keep track of each one separately).

### The challenge

_(More on this later.)_

### Implementation

Here's the initial algorithm I drafted in pseudocode:

(init)
- malloc a string named `buffer` with `size=buf_size * sizeof(char)`. Don't ever re-malloc this one. (static for sure)
- malloc another string named `result` with `size=buf_size * sizeof(char)`. This will be the return value.
- define another temp string without any malloc. This is to be able to free the previous result.
- define int `bytes_read`, self-explanatory (static?)
- define int `lb_pos`. lb refers to "line break" position (in buffer).

(first read)
- read `buf_size` into `buffer`, store retval in `bytes_read`.
- lb_pos = `ft_strchr(buffer, '\n')`

(while `bytes_read == buffer && lb_pos == -1`)
- `temp = ft_strnjoin(result, buffer, -1)`, `free(result)`, `result=temp`
- read `buf_size` into `buffer`, store retval in `bytes_read`.
- lb_pos = `ft_strchr(buffer, '\n')`

(if `lb_pos != -1`)
- `temp = ft_strnjoin(result, buffer, lb_pos)`, `free(result)`, `result=temp`
- `ft_strpull(buffer, lb_pos)` (copies buffer + lb_pos to buffer, then fills the rest with zero)
- otherwise: temp = `ft_strnjoin(result, )`, `free(result)`, result = temp.



## Instructions

### Compilation

_(More on this later.)_

### Integration

_(More on this later.)_

### Testing

_(More on this later.)_

## Resources
