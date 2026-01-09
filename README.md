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

From an educational point of view, the main takeaway concerns **static variables.** It's an exercise in managing memory over multiple calls of the same function, allocating and freeing memory as needed.

### Implementation

Initially, I'd interpreted the instructions differently— since multiple calls of the function were to read subsequent lines, I assumed the result would be freed only at the end and not at every iteration. That's why my initial approach was _to return the static variable "stash" at the end of each function call, which would be freed by the user when it's no longer needed._ To that end, I'd devised some functional acrobacy and string manipulation methods, where the program would add a `\0` after the next `\n` character, so that the `stash` returned would represent a string up to that line break, but still contain the information beyond it.

Needless to say, the final version looks wildly different, but is still built on the same architecture designed to support that idea:
- An `init` function that 
    - takes the address of all the relevant variables,
    - handles leftover data on the static `stash` variable,
    - allocates necessary memory,
    - returns `true` on success, or frees everything and returns `false` on failure;
- A loop that reads the file into the buffer & searches for a newline character;
- At the end of the loop, handles one of two scenarios:
    - `handle_lb` in case of a line break,
    - `handle_eof` in case of reaching the end of the file (without finding a newline). 

Some of the helper functions in `get_next_line_utils.c` are a little "hacky" in nature, to support the initial idea explained in the first paragraph. Notably these two:
- `ft_strnjoin(char *s1, char *s2, ssize_t n, bool free_s1)` that accepts
    - a `ssize_t` value which limits the number of characters joined (-1 for no limit),
    - and a `bool` that determines whether the first string should be freed or not (to support operations such as `*stash = ft_strnjoin(*stash, buffer, bytes_read, true);`);
- `ft_strcpy_lb(char *dst, char *src, char delim, bool lb)` that was designed originally to build the `stash` string as explained in the first paragraph. It's no longer used for that purpose but I decided to keep it in there for future reference.


## Instructions

### Compilation

`cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c <your file here>` where `<your file here>` is a file with a main function where you'll be using the `get_next_line` function.  
Alternatively, write a main function directly inside `get_next_line.c`.

### Integration

Once compiled, open a file and call `get_next_line` with the file descriptor (fd) obtained. Here's an example (from my personal tests):
```c
#include <fcntl.h>

int suite_read_multi(int n, char *fn)
{
	char	*result;
	int		i;
	int		fd;
	
	i = n;
	fd = open(fn, O_RDONLY);
	printf("\n--- Reading %s (%d times) ---\n", fn, n);
	while (i--)
	{
		result = get_next_line(fd);
		if (!result)
			printf("READ | (NULL)\n");
		else
		{
			printf("READ | %s", result);
			free(result);
		}
	}
	close(fd);
	return (0);
}
```

### Testing

`francinette` works, but I like to write my own tests as a way to visualize what's going on.  
Feel free to check out the repo: [erengazioglu/42-get_next_line/tests](https://github.com/erengazioglu/42-get_next_line-tests).

## Resources

- **Manual entries:** `man 2 read`, `man 2 open`
- **Fellow 42 students:** As always, conversations with peers were the most valuable resource.
- **Google & Forums:** Heavy use of Google searches, often leading to Stack Overflow and similar forums.
- **AI:** I turned to AI to make sense of some valgrind error logs, and other minor questions (e.g. _"is there a point to writing sizeof(char) instead of just 1?"_).