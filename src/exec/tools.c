/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 10:55:32 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 14:17:11 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"
/*
char	*ft_join_env(char *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!(s1 && s2))
		return (0);
	i = 0;
	j = 0;
	if (!(dest = (char*)malloc(sizeof(char) *
					(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 2))))
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = '=';
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
*/
char	**split_env(t_var *var)
{
//	char	*tmp;
	char	**array;
	t_var	*save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	save = var;
	while (save)
	{
		save = save->next;
		i++;
	}
	save = var;
	array = malloc(sizeof(char*) * (i + 1));
	array[i] = 0;
	while (i--)
	{
//		tmp = ft_strdup(save->name);
//		array[j++] = ft_join_env(tmp, save->data);
//		ft_strdel(&tmp);
		array[j] = ft_strjoinf(save->name, "=", 0);
		array[j] = ft_strjoinf(array[j], save->data, 1);
//		array[j] = ft_strjoinf(array[j], "P", 1);
		j++;
		save = save->next;
	}
	return (array);
}

char	*strjoin_path(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	ft_strjoin_free(&tmp, s2);
	return (tmp);
}

void	cnf_print_error(char *str)
{
	ft_putstr("42sh: \033[1;31merror: \033[0mcommand not found: ");
	ft_putstr(str);
	ft_putstr("\n");
}

void	ft_tabfree(char **res)
{
	int i;

	i = -1;
	while (res[++i])
		ft_strdel(&res[i]);
	free(res);
}
