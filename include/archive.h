#ifndef _ARCHIVE_H_
# define _ARCHIVE_H_

typedef struct	s_flags
{
  int		extract;
  int		create;
  int		verbose;
  int		takefiles;
  int		tarinfo;
  int		permission;
}		t_flags;

typedef struct	s_header
{
  char		name[255];
  char		size[12];
  char		mode[8];
  char		time[12];
}		t_header;

typedef struct		s_linked
{
  int			fd;
  t_header		*header;
  struct s_linked	*next;
}			t_linked;

int	strclen(char *, int);
void	create_linked(t_linked **, int, char **, t_flags *);
void	create_metadta(t_linked **, char *, t_flags *);
void	create_archive(t_linked *, char *);
void	create_files(char *, t_flags *);
void	archive_info(char *, t_flags *);

#endif /* !_ARCHIVE_H_ */
