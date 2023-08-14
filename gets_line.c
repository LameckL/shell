#include <stdio.h>
#include "main.h"

/**
 * input_buf - this func handles buffers chained commands
 * @info: struct param
 * @buf: buffer address
 * @len: len var address
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		q = getline(buf, &len_p, stdin);
#else
		q = _getline(info, buf, &len_p);
#endif
		if (q > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[q - 1] = '\0';
				q--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = q;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - func that gets a line without a newline
 * @info: struct param
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
	if (q == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* passing back pointer to current position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (q); /* return length of buffer from _getline() */
}

/**
 * read_buf - this function reads a buffer
 * @info: struct param
 * @buf: buffer
 * @i: size
 * Return: q
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t q = 0;

	if (*i)
		return (0);
	q = read(info->readfd, buf, READ_BUF_SIZE);
	if (q >= 0)
		*i = q;
	return (q);
}

/**
 * _getline - this func gets the next line of input from STDIN
 * @info: struct parameter
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr buffer
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t q = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	q = read_buf(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
