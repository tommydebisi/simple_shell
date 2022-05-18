#include "shell.h"

/**
 * rev_string - funtion that prints the reverse of
 * string
 * @s: string passed in
 * @len: length of string
 */
void rev_string(char *s, int len)
{
	int max, half;
	char first, last;

	max = len - 1;
	half = max / 2;
	while (half >= 0)
	{
		first = s[max - half];
		last = s[half];
		s[half] = first;
		s[max - half] = last;
		half--;
	}
}
