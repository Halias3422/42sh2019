/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 08:43:18 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 11:18:12 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

// char	*get_line(char *str, char **line)
// {
// 	char		*temp;
// 	int			i;
// 	int			newl;

// 	i = 0;
// 	newl = 0;
// 	if (!(*str))
// 		return (NULL);
// 	while (str[i] != '\n' && str[i] != '\0')
// 		i++;
// 	if (str[i] == '\n')
// 		newl = 1;
// 	*line = ft_strsub(str, 0, i);
// 	temp = ft_strsub(str, i + newl, (ft_strlen(str) - (i + newl)));
// 	str = ft_strcpy(str, temp);
// 	free(temp);
// 	return (*line);
// }

// int		get_next_line(const int fd, char **line)
// {
// 	static char	*str[255];
// 	char		buf[BUFF_SIZE + 1];
// 	char		*temp;
// 	int			ret;

// 	ret = 1;
// 	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
// 		return (-1);
// 	if (!(str[fd]))
// 		str[fd] = ft_strnew(1);
// 	while (!ft_strchr(str[fd], '\n') && ret > 0)
// 	{
// 		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
// 		{
// 			buf[ret] = '\0';
// 			temp = ft_strjoin(str[fd], buf);
// 			free(str[fd]);
// 			str[fd] = ft_strdup(temp);
// 			free(temp);
// 		}
// 	}
// 	buf[ret] = '\0';
// 	if (ret < 0)
// 		return (-1);
// 	if ((*line = get_line(str[fd], line)) == NULL)
// 		return (0);
// 	return (1);
// }
char	*get_line(char *str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[i])
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (str[i] == '\n')
		{
			*line = ft_strsub(str, 0, i);
			tmp = ft_strdup(str + i + 1);
			str = ft_strcpy(str, tmp);
			free(tmp);
			return (*line);
		}
		else
		{
			*line = ft_strsub(str, 0, i);
			str[0] = '\0';
			return (*line);
		}
	}
	return (NULL);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[256];
	char		*tmp;
	char		buff[BUFF_SIZE + 1];
	int			i;
	int			rd;

	i = 0;
	rd = 0;
	while ((rd = read(fd, buff, BUFF_SIZE)) != 0)
	{
		if (rd < 0)
			return (-1);
		buff[rd] = '\0';
		if (!(str[fd]))
			str[fd] = ft_strnew(1);
		tmp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = tmp;
	}
	*line = get_line(str[fd], line);
	if (*line == NULL)
		return (0);
	else
		return (1);
}
