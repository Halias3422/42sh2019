/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/26 13:29:35 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 10:48:01 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_fill_line(char **line, t_gnlist *list, char *str)
{
	int				i;
	char			*tmp;
	int				new_line;

	new_line = 0;
	i = 0;
	if (!(list->str))
		return (0);
	while (list->str[i] != '\n' && list->str[i])
		i++;
	if (list->str[i] == '\n')
		new_line = 1;
	*line = ft_strsub(list->str, 0, i);
	tmp = ft_strsub(list->str, i + new_line, (ft_strlen(str) - (i + new_line)));
	list->str = ft_strcpy(list->str, tmp);
	free(tmp);
	if (!(**line) && new_line != 1)
		return (0);
	return (1);
}

static int			ft_fill_str(t_gnlist *list)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;

	ret = 1;
	while (!ft_strchr(list->str, '\n') && ret > 0)
	{
		if ((ret = read(list->fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			tmp = ft_strjoin(list->str, buf);
			free(list->str);
			list->str = tmp;
		}
	}
	if (ret < 0)
		return (-1);
	return (0);
}

static t_gnlist		*ft_lst_new(t_gnlist *list, int fd, t_gnlist *head)
{
	while (list && list->fd != fd)
		list = list->next;
	if (list == NULL)
	{
		if (!(list = (t_gnlist*)malloc(sizeof(t_gnlist))))
			return (NULL);
		list->fd = fd;
		list->str = ft_strnew(0);
	}
	list->next = head;
	return (list);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnlist	*list;
	t_gnlist		*head;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	if (!list)
	{
		if (!(list = (t_gnlist*)malloc(sizeof(t_gnlist))))
			return (-1);
		list->fd = fd;
		list->str = ft_strnew(0);
		list->next = NULL;
	}
	head = list;
	if (list && list->fd != fd)
	{
		if (!(list = ft_lst_new(list, fd, head)))
			return (-1);
	}
	if (ft_fill_str(list) == -1)
		return (-1);
	if ((ft_fill_line(line, list, list->str)) == 1)
		return (1);
	return (0);
}
