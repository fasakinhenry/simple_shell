#include "main.h"
void execute(char **argv)
{
    char *cmd = NULL, *actual_cmd = NULL;

    if (argv && argv[0])
	{
        /* get the command */
        cmd = argv[0];

        /* generate the path to this command before passing it to execve */
        actual_cmd = locate_cmd(cmd);
		/* get environment variables */
		extern char **environ;

        /* execute the actual command with execve */
        if (actual_cmd != NULL && execve(actual_cmd, argv, environ) == -1)
		{
            perror("Error:");
        }
		free(actual_cmd);
    }

}
