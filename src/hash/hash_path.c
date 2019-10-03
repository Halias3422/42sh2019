/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 09:43:55 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/25 09:10:51 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

char                *path_not_found(char **paths, char **arg)
{
    ft_printf("42sh: %s: command not found\n", arg[0]);
    ft_free_tab(paths);
    return (NULL);
}

char				*absolute_path(char *path)
{
	char	*tmp;
	DIR		*file;

	tmp = path;
	if (path[0] == '.')
		path = ft_strjoin(getcwd(NULL, 1000), path + 1);
	if ((file = opendir(path)) != NULL)
	{
		ft_printf("42sh: %s: is a directory\n", tmp);
		closedir(file);
	}
	if (access(path, F_OK) == -1)
		ft_printf("42sh: %s: No such file or directory", tmp);
		//ft_printf("42sh: %s: command not found\n", tmp);
	else if (access(path, X_OK) == -1)
		ft_printf("42sh: %s: permission denied\n", tmp);
	else
		return (path);
	return (NULL);
}

char				*path_found(char **paths, int i, char *ans, char **arg)
{
	ans = fill_hash_table(paths[i], arg);
	ft_free_tab(paths);
	return (ans);
}

char				*path_denied(char **paths, char **arg)
{
	ft_printf("42sh: %s: permission denied\n", arg[0]);
	ft_free_tab(paths);
	return (NULL);
}

int					scan_name_for_undesired_symbols(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (((ft_isalpha(str[i]) == 0) || (str[i] < '0' && str[i] > '9')) &&
				(str[i] != 45 && str[i] != 95))
			return (-1);
		i++;
	}
	return (0);
}