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
#include <string.h>

int     size(char *str)             // вроде работает6 но выглядит пипец подозрительно
{
    int i;

    if (!str)
        return (0);
    //    return (-1);                // мы вообще этот выход используем? Почему -1 то?
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

char    *str_join(char *out, char *buf, int k)         // копирует до определённого числа!!
{
    char    *output;
    int     i;
    int     j;

    if (!buf && !out)
        return (0);
    if (!out && buf)
    {
        output = malloc(size(buf) + 1);          // вроде так
        str_cpy(output, buf);
        return (output);
    }
    output = malloc(size(out) + k + 1);
    i = 0;
    while (out[i] != 0)
    {
        output[i] = out[i];
        i++;
    }
    output[i] = 0;                               // по идее если баф не 0, он переобозначится
    if (!buf)
        return (output);
    j = 0;
    while (j < k)
    {
        output[j + i] = buf[j];
        j++;
    }
    output[j + i] = 0;
    return (output);
}

int     check_buf(char *buf)    // Итак, у нас может быть 2 вида информации: размер буфера и вывод                                   этой функции. Если выход меньше размера, то там есть \n, если                                     размер меньше, чем баф сайз, там конец файла. Всё просто
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

void    save_str(char *save, char *str)  // спасает ваши стринги (точнее одни стринги)
{
    int i;

    i = 0;
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
    int     bufsize = 2;                     // проверить  на 1
	char	*buf = NULL;
    static char    *save_buf = NULL;
    char    *out = NULL, *temp = NULL, *temp_buf = NULL;

	buf = calloc(bufsize + 1, 1);               // каллок, потому что нулевой размер в начале
    //printf("save_buf = %s\n", save_buf);
	while (read(fd, buf, bufsize))              // она должна тоже входить если есть буфер
	{
        if (save_buf)
        {
            //printf("save_buf = %s, buf = %s\n", save_buf, buf);
            buf = str_join(save_buf, buf, size(buf));
        }
        //printf("buf = %s, out = %s, temp = %s\n", buf, out, temp);
        if (temp)
            free(temp);
        if (out)                                // не первый проход
		    temp = malloc(size(out) + 1);
		str_cpy(temp, out);                     // сохраняем аут
        check = size(buf);
        k = check_buf(buf);
        out = str_join(temp, buf, k);
        if (k < bufsize)
        {
            out[size(temp) + k] = 0;
            save_buf = malloc(size(buf + k + 1));
            save_str(save_buf, buf + k + 1);
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

	for (int i = 1; i <= 20; i++)
		printf("out%d = %s\n", i, get_next_line(fd));
	//char    *temp = NULL;
	close(fd);
	//printf("\n%d\n", BUFFER_SIZE);
	return 0;
}
