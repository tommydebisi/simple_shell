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

/**
 * _isdigit - prints the return value is digit or not
 * @str: string to check
 * Return: 1 if it's digit and 0 otherwise
 */
int _isdigit(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
	}
	return (1);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}

/**
 * itoa - changes integer to string
 *
 * @num: number to be changed to string
 * @str: buffer to add the string
 * @base: base to be changed to
 * Return: number converted to string
 */
char *itoa(int num, char *str, int base)
{
	int i = 0, isNegative = 0;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}

	/* In standard itoa(), negative numbers are handled only with */
	/* base 10. Otherwise numbers are considered unsigned. */
	if (num < 0 && base == 10)
	{
		isNegative = 1;
		num = -num;
	}

	/* Process individual digits */
	while (num != 0)
	{
		int rem = num % base;

		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	/* If number is negative, append '-' */
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; /* Append string terminator */

	/* Reverse the string */
	rev_string(str, i);

	return (str);
}
