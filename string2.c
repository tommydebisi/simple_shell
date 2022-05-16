#include "shell.h"

/**
 * _strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}

/**
 * _strcat2 - adding  of three strings
 *
 * @dest: first string to be added
 * @src: second string to be added
 * @s: third string to be added
 * Return: concatenated string or NULL if it fails
 */
char *_strcat2(char *dest, char *src, char *s)
{
	int len1 = _strlen(dest), len2 = _strlen(src), sum, comp;
	int len3 = _strlen(s);
	char *charLen = NULL;

	sum = len1 + len2 + len3;
	charLen = malloc(sizeof(char) * (sum + 1));
	if (!charLen)
	{
		free(charLen);
		return (NULL);
	}

	for (len1 = len2 = len3 = comp = 0; comp < sum; comp++)
	{
		if (dest[len1] != '\0')
		{
			charLen[comp] = dest[len1];
			len1++;
		}
		else if (src[len2] != '\0' && dest[len1] == '\0')
		{
			charLen[comp] = src[len2];
			len2++;
		}
		else if (s[len3] != '\0' && src[len2] == '\0' && dest[len1] == '\0')
		{
			charLen[comp] = s[len3];
			len3++;
		}
	}
	/* to seal off the string */
	charLen[comp] = '\0';

return (charLen);
}
