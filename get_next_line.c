/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 15:54:09 by mikhalil      #+#    #+#                 */
/*   Updated: 2022/12/06 19:42:24 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int	check_buf(char* buf, int k)
{
	int	i;

	i = 0;
	while (i <= k)
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (k);
}

void	cpy(char *src, char *dst, int len)
{
	if (!src || !dst || !len)
		return ;
	while (len--)
		dst[len] = src[len];
}

int	join(char *src, char *dst, int i, int len)
{
	if (!len || !src || !dst)
		return (0);
	while (len--)
		dst[i + len] = src[len];
	return (i + len);
}

char	*get_next_line(int fd)
{
	static int	a = 0;                                    // should be 0, but I am experimenting..
	char*		buf, *out, *beg;
	int			k, j, i;

	printf("a = %d\n", a);
	i = 0;
	if (a)
	{
		beg = calloc((a + 1), sizeof(void));
		j = read(fd, beg, a + 1);
		printf("beg = %s\n", beg);
		free(beg);
		if (j == -1)
			return ("");
	}
	//printf("aaaaaaaaaaaa");
	while (1)
	{
		buf = calloc(BUFFER_SIZE, sizeof(void));
		beg = calloc(BUFFER_SIZE * i, sizeof(void));
		cpy(out, beg, BUFFER_SIZE * i);
		/*if (out)
			free(out);*/
		out = calloc(BUFFER_SIZE * (i + 1), sizeof(void));
		cpy(beg, out, BUFFER_SIZE * i);
	/*	if (!buf || !beg || !out)
		{
			free(buf);
			free(beg);
			free(out);
			return ("");
		}*/
		k = read(fd, buf, BUFFER_SIZE);
		if (k == -1)
			return ("");
		j = check_buf(buf, k);
		printf("buf = %s\n", buf);
		if (k < BUFFER_SIZE || j < k)
		{
			printf("j = %d\n", j);
			a += BUFFER_SIZE * i + j + 1;
			join(buf, out, BUFFER_SIZE * i, j);
			free(buf);
			free(beg);
			//printf("out = %s\n", out);
			return (out);
		}
		free(buf);
		free(beg);
		i++;
	}
	return ("");
}

int main()
{
	FILE* ptr;
	int fd;
	char ch;                                                                     // there should be a defolt value
	char *str1, *str2;
	int k;

	fd = open("test_file", O_RDONLY);
	
	printf("out1 = %s\n", get_next_line(fd));
	printf("out2 = %s\n", get_next_line(fd));
	printf("out3 = %s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	
	close(fd);
	//printf("\n%d\n", BUFFER_SIZE);
	return 0;
}
