#include "main.h"

/**
 * display_prompt - a function that prompts the user
 */

void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
