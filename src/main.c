#include <stdlib.h>
#include <stdio.h>
#include "archive.h"

void	error(void)
{
  printf("Usage: ./my_tar -x|c|v|f|t|p files..\n");
  exit(1);
}

void	flags_reset(t_flags *flags)
{
  flags->extract = 0;
  flags->create = 0;
  flags->verbose = 0;
  flags->takefiles = 0;
  flags->tarinfo = 0;
  flags->permission = 0;
}

t_flags		*fetch_flags(char *str)
{
  t_flags	*flags;
  int		i;

  if (str[0] != '-' || (flags = malloc(sizeof(*flags))) == NULL)
    return (NULL);
  flags_reset(flags);
  i = 1;
  while (str[i] != '\0')
    {
      if (str[i] == 'x')
	flags->extract = 1;
      if (str[i] == 'c')
	flags->create = 1;
      if (str[i] == 'v')
	flags->verbose = 1;
      if (str[i] == 'f')
	flags->takefiles = 1;
      if (str[i] == 't')
	flags->tarinfo = 1;
      if (str[i] == 'p')
	flags->permission = 1;
      i += 1;
    }
  return (flags);
}

void	free_list(t_linked *list)
{
  if (list != NULL)
    {
      free_list(list->next);
      free(list->header);
      free(list);
    }
}

int		main(int argc, char **argv)
{
  t_flags	*flags;
  t_linked	*list;

  if (argc <= 2 || (flags = fetch_flags(argv[1])) == NULL)
    error();
  if (!flags->takefiles)
    printf("Missing -f option\n");
  else if (flags->create)
    {
      if (argc < 4)
	error();
      list = NULL;
      create_linked(&list, argc, argv, flags);
      create_archive(list, argv[2]);
      free_list(list);
    }
  else if (flags->extract)
    create_files(argv[2], flags);
  else if (flags->tarinfo)
    archive_info(argv[2], flags);
  free(flags);
  return (0);
}
