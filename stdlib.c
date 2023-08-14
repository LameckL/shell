#include <stdio.h>
#include "main.h"

/**
 * get_len - func that gets the lenght of a number
 * @n:  int number
 * Return: lenght
 */
int get_len(int n)
{
	unsigned int n1;
	int lenn = 1;

	if (n < 0)
	{
		lenn++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenn++;
		n1 = n1 / 10;
	}

	return (lenn);
}
/**
 * aux_itoa - a function that converts int to string
 * @n: int number
 * Return: string
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int lenn = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenn + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenn) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenn--;
	do {
		*(buffer + lenn) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenn--;
	}
	while (n1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - a func that converts a string to an integer
 * @s: string input
 * Return: integer
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
