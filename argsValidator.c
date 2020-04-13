#include "shell.h"

/**
 * argsValidator - validates if the command typed exists
 * @grind: array of strings of args
 * @path: string, env-variable $PATH
 *
 * Return: 0 if found, -1 otherwise
 */

int argsValidator(char **grind, char *path)

{
	pid_t child_pid;
	int status;
	paths *head = NULL;
	paths *temp;
	char *command;
	struct stat stt;

	if (grind[0] == '\0')
		return (0);
	if (stat(grind[0], &stt) == 0)
	{	child_pid = fork();
		if (child_pid == 0)
			if (execve(grind[0], grind, environ) == -1)
				perror("Error:");
		if (child_pid > 0)
			wait(&status);
		return (0);
	}
	temp = head;
	head = c_pathList(&temp, path);
	while (temp != NULL)
	{	command = _strcat(temp->miniPath, grind[0]);
		if (stat(command, &stt) == 0)
		{	child_pid = fork();
			if (child_pid == 0)
				if (execve(command, grind, environ) == -1)
					perror("Error:");
			if (child_pid > 0)
				wait(&status);
			free(command);
			freeList(head);
			return (0);
		}
		free(command);
		temp = temp->next;
	}
	if (stat(grind[0], &stt) == -1)
		printf("%s\n", grind[0]);
	freeList(head);
	return (0);
}
