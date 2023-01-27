/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 15:54:09 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/01/25 17:49:18 by dkocob        ########   odam.nl         */
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
#include <string.h>

int     str_len(char *str, char c)             // вроде работает6 но выглядит пипец подозрительно
{
    int i;

    i = 0;
    while (str && str[i] != c && str[i])
        i++;
    return (i);
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

char    *str_join(char *out, char *buf, int k)         // копирует до определённого числа!!
{
    char    *output;
    int     i;
    int     j;

    if (!buf && !out)
        return (0);
    if (!out && buf)
    {
        output = malloc(str_len(buf, '\0') + 1);
        str_cpy(output, buf);
        return (output);
    }
    output = malloc(str_len(out, '\0') + k + 1);
    i = 0;
    while (out[i] != 0)
    {
        output[i] = out[i];
        i++;
    }
    j = 0;
    while (buf && buf[j] && j < k)
    {
        output[j + i] = buf[j];
        j++;
    }
    output[j + i] = 0;
    return (output);
}

char	*get_next_line(int fd)
{
    int     k, check;
    int     bufsize = 2000;
	char	*buf = NULL;
    static char    *save_buf = NULL;
    char    *out = NULL, *temp = NULL, *temp_buf = NULL;

	buf = calloc(bufsize + 1, 1);               // каллок, потому что нулевой размер в начале
    printf("save_buf = %s\n", save_buf);
	while (read(fd, buf, bufsize))              // она должна тоже входить если есть буфер
	{
        if (save_buf)
        {
            //printf("save_buf = %s, buf = %s\n", save_buf, buf);
            buf = str_join(save_buf, buf, str_len(buf, '\0'));
            printf("buf = %s\n", buf);
        }
        if (temp)
            free(temp);
        if (out)                                // не первый проход
		    temp = malloc(str_len(out, '\0') + 1);
		str_cpy(temp, out);                     // сохраняем аут
        check = str_len(buf, '\0');
        k = str_len(buf, '\n');
        out = str_join(temp, buf, k);
        if (k < bufsize)
        {
            out[str_len(temp, '\0') + k] = 0;
            save_buf = malloc(str_len(buf + k + 1, '\0'));
            str_cpy(save_buf, buf + k + 1);
            break ;
        }
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

    //printf("%d\n", str_len("", 'a'));
    //printf("%s\n", str_join("abcdef", "0123", str_len("\n01\n23", '\n')));
	for (int i = 1; i <= 11; i++)
		printf("out%d = %s\n", i, get_next_line(fd));
	//char    *temp = NULL;
	close(fd);
	//printf("\n%d\n", BUFFER_SIZE);
	return 0;
}
