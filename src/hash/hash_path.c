/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 09:43:55 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 11:11:52 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

char				*absolute_path(char *path)
{
	char			*tmp;
	DIR				*doss;

	tmp = path;
	if (path[0] == '.')
		path = ft_strjoin(getcwd(NULL, 1000), path + 1);
	if ((doss = opendir(path)) != NULL)
	{
		ft_printf("42sh: %s: is a directory\n", tmp);
		closedir(doss);
	}
	if (access(path, F_OK) == -1)
		ft_printf("42sh: %s: command not found\n", tmp);
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
