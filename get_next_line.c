/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 15:54:09 by mikhalil      #+#    #+#                 */
/*   Updated: 2022/12/16 18:33:12 by mikhalil      ########   odam.nl         */
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

/*int	check_buf(char* buf, int k)
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
		beg = calloc((a + 1), sizeof(void));             // calloc is not aloud (i think)
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
		//if (out)
		//	free(out);
		out = calloc(BUFFER_SIZE * (i + 1), sizeof(void));
		cpy(beg, out, BUFFER_SIZE * i);
		//if (!buf || !beg || !out)
		//{
		//	free(buf);
		//	free(beg);
		//	free(out);
		//	return ("");
		//}
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
}*/

#include <string.h>

int     size(char *str)
{
    int i;

    if (!str)
        return (-1);
    i = 0;
    while (str[i++]);
    return (i - 1);
}

void    str_cpy(char *dest, char *sour)
{
    int i;

    i = 0;
    if (!dest || !sour)
        return ;
    while (sour[i] != 0)
    {
        dest[i] = sour[i];
        i++;
    }
    dest[i] = 0;
}

char    *str_join(char *out, char *buf)
{
    char    *output;
    int     i;
    int     j;

    if (!buf && !out)
        return (0);
    if (!out && buf)
    {
        output = malloc(size(buf));
        str_cpy(output, buf);
        return (output);
    }
    output = malloc(size(out) + size(buf) + 1);
    i = 0;
    while (out[i] != 0)
    {
        output[i] = out[i];
        i++;
    }
    if (!buf)
        return (output);
    j = 0;
    while (buf[j] != 0)
    {
        output[j + i] = buf[j];
        j++;
    }
    output[j + i] = 0;
    return (output);
}

int     check_buf(char *buf)
{
    int i;

    i = 0;
    while (buf[i] != 0)
    {
        if (buf[i] == '\n')
            break ;
        i++;
    }
    return (i);
}

void    save_str(char *save, char *str)
{
    int i;

    i = 0;
    //save = malloc(size(str));
    while (str[i] != 0)
    {
        *(save + i) = str[i];
        i++;
    }
    *(save + i) = 0;
}

char	*get_next_line(int fd)
{
    int     k, check;
	static int  a = 0;
    int     bufsize = 4;
	char	*buf = NULL;
    static char    *save_buf = NULL;
    char    *out = NULL, *temp = NULL;

	buf = calloc(bufsize + 1, 1);              // потом уберём
	while (read(fd, buf, bufsize))              // она должна тоже входить если есть буфер
	{
        //printf("buf = %s, out = %s, temp = %s\n", buf, out, temp);
        printf("save_buf = %s\n", save_buf);
        if (out)
		    temp = malloc(size(out));
		str_cpy(temp, out);
        check = size(buf);
        buf[check] = 0;
        out = str_join(temp, buf);
        k = check_buf(buf);
        if (k < bufsize)
        {
            if (temp)
                out[size(temp) + k] = 0;
            else
                out[k] = 0;
            save_buf = malloc(size(buf + k + 1));
            save_str(save_buf, buf + k + 1);
            break ;
        }
        //printf("buf = %s, out = %s, temp = %s\n", buf, out, temp);
	}
    if (!out)
        return ("");
	return (out);
}

int main()
{
	int fd;
	int k;

	fd = open("test_file", O_RDONLY);

	for (int i = 1; i <= 10; i++)
		printf("out%d = %s\n", i, get_next_line(fd));
	char    *temp = NULL;
    //printf("sj1 = %s\n", str_join(str_join(temp, "a"), "b"));

	close(fd);
	//printf("\n%d\n", BUFFER_SIZE);
	return 0;
}
