#ifndef _GET_NEXT_LINE_H_
# define _GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (30 * 1024)
# endif /* !READ_SIZE */

char	*get_next_line(const int fd);
char	*my_strncat(char *, const char *, int);
char	*my_strndup(const char *, int);
char	*concatenate(char *, char *);

#endif /* !_GET_NEXT_LINE_H_ */
