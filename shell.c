#include "shell.h"

ssize_t my_getline(char **linee, size_t *n, FILE *stream)
{
	if (linee == NULL || n == NULL || stream == NULL)
	{
		return -1;
	}

	int character;
	size_t o = 0;

	if (*linee == NULL || *n = 0)
	{
		*n = 128;
                *linee = malloc(*n);
		if (*linee = NULL)
		{
			return -1;
		}
	}

	while ((character = fgetc(stream)) != EOF)
	{
		(*linee)[o++] = character;

		if (o == *n - 1)
		{
			*n *= 2;
			char *temp = realloc(*linee, *n);
			if (temp == NULL)
			{
				return -1;
			}
			*linee = temp;
		}

		if (character == '\n')
		{
			break;
		}
	}

	(*linee)[o] = '\0';

	if (o > 0)
	{
		return 0;
	}

	if (feof(stream))
	{
		return -1;
	}

	return -1;
}


int main()
{
	char *line = NULL;
	size_t bufsize = 0;

	while (1)
	{
		write(STDOUT_FILENO, "Shell ~# ", 9);
		ssize_t chars_read = my_getline(&line, &bufsize, stdin);

		if (chars_read == -1)
		{
			break;
         	}
		else if (chars_read != -1)
		{
			if (strcmp(line, "exit") == 0)
			{
				break;
			}

			char *args[bufsize];
			char *token = strtok(line, " \t\n");
			int i = 0;

			while (token != NULL)
			{
				token = strtok(NULL, " \t\n");
				args[i++] = token;
			}

			args[i] = NULL;

			char *path = getenv("PATH");
			char *command = args[0];
			
			int command_exists = 0;
                          if (path != NULL)
			  {
				  char *path_token = strtok(path, ":");
				  while (path_token != NULL)
				  {
					  char *executable_path = malloc(strlen(path_token) + strlen(command) +2);
					  if (executable_path != NULL)
					  {
						  sprintf(executable_path, "%s/%s", path_command, command);
						  if (access(executable_path, X_OK) == 0)
						  {
							  command_exists = 1;
							  args[0] = executable_path;
							  break;
						  }
						  free(executable_path);
					  }
					  path_token = strtok(NULL, ":");
				  }
			  }


			  if (!command_exists)
			  {
				  write(STDOUT_FILENO, "Command not found: ", 19);
				  write(STDOUT_FILENO, command, strlen(command));
				  write(STDOUT_FILENO, "\n", 1);
				  continue;
			  }

			  pid_t child_pid = fork();
			  if (child_pid == -1)
			  {
				  write(STDOUT_FILENO, "Failed to fork a child process.\n", 32);
				  continue;
			  }
			  else if (child_pid == 0)
			  {
				  if (execvp(args[0], args) == -1)
				  {
					  write(STDOUT_FILENO, "Command execution failed.\n", 26);
					  exit(1);
				  }

			  }
			  else
			  {
				  int status;
				  waitpid(child_pid, &status, 0);
			  }
		}
	}

	free(line);
	return 0;
}
