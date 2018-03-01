#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "archive.h"

char		*pathconcatenate(char *str1, char *str2)
{
  char  *concatenated;

  if (str1 == NULL || str2 == NULL)
    return (NULL);
  if ((concatenated = malloc((strlen(str1) + strlen(str2) + 2) *
			     sizeof(char))) == NULL)
    return (NULL);
  concatenated[0] = '\0';
  strcat(concatenated, str1);
  if (concatenated[strlen(concatenated) - 1] != '/')
    strcat(concatenated, "/");
  strcat(concatenated, str2);
  return (concatenated);
}

void		add_linked(t_linked **head, t_linked *new)
{
  t_linked	*copy;

  if (new != NULL && *head != NULL)
    {
      copy = *head;
      while (copy->next != NULL)
	copy = copy->next;
      new->next = copy->next;
      copy->next = new;
    }
  else if (*head == NULL && new != NULL)
    {
      new->next = *head;
      *head = new;
    }
}

void	create_metadata(t_linked **list, char *file, t_flags *flags);

void		create_metadata_directory(t_linked **list, char *directory,
					  t_flags *flags)
{
  DIR		*dir;
  struct dirent	*file;
  char		*file_name;

  if ((dir = opendir(directory)) == NULL)
    return;
  while ((file = readdir(dir)) != NULL)
    {
      if (file->d_name[0] != '.')
	{
	  file_name = pathconcatenate(directory, file->d_name);
	  if (flags->verbose)
	    printf("-> %s\n", file_name);
	  create_metadata(list, file_name, flags);
	  free(file_name);
	}
    }
  closedir(dir);
}

void		create_metadata(t_linked **list, char *file, t_flags *flags)
{
  t_linked	*metadata;
  struct stat	buf;

  if ((metadata = malloc(sizeof(*metadata))) == NULL)
    return;
  if ((metadata->fd = open(file, O_RDONLY)) == -1)
    {
      printf("Can't open file %s\n", file);
      return;
    }
  if ((metadata->header = malloc(sizeof(*metadata->header))) == NULL)
    return;
  fstat(metadata->fd, &buf);
  sprintf(metadata->header->name, "%s%c", file,
	  S_ISDIR(buf.st_mode) ? '/' : '\0');
  sprintf(metadata->header->size, "%d", (int)buf.st_size);
  sprintf(metadata->header->mode, "%u", (unsigned int)buf.st_mode);
  sprintf(metadata->header->time, "%u", (unsigned int)buf.st_mtime);
  add_linked(list, metadata);
  if (S_ISDIR(buf.st_mode))
    create_metadata_directory(list, file, flags);
}

void	create_linked(t_linked **list, int argc, char **argv, t_flags *flags)
{
  int	i;

  i = 3;
  while (i < argc)
    {
      if (flags->verbose)
	printf("-> %s\n", argv[i]);
      create_metadata(list, argv[i], flags);
      i += 1;
    }
}
