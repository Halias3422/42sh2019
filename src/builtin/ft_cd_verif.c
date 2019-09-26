/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_verif.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 19:11:29 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/26 19:33:00 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char	*verif_p_option_path(char *new_path)
{
	int		i;
	char	**split_path;
	char	*test;

	i = 0;
	test = ft_strnew(0);
	split_path = ft_strsplit(new_path, '/');
	while (split_path[i])
	{
		test = ft_strjoinf(test, split_path[i], 1);
		test = ft_strjoinf(test, "/", 1);
		if (verif_path(test) == 0)
		{
			ft_free_tab(split_path);
			free(test);
			return (NULL);
		}
		i++;
	}
	ft_free_tab(split_path);
	free(test);
	return (new_path);
}

int		verif_path(char *path)
{
	DIR		*file;
	int		i;

	i = ft_strlen(path) - 2;
	while (i > 0 && path[i] != '/')
		i--;
	if ((file = opendir(path)) == NULL)
	{
		ft_printf_err("42sh: cd: %s: is not a directory\n", path + i + 1);
		return (0);
	}
	else
		closedir(file);
	if (access(path, F_OK) == -1)
		ft_printf_err("42sh: cd: %s: No such file or directory", path + i + 1);
	else if (access(path, X_OK) == -1)
		ft_printf_err("42sh: cd: %s: permission denied\n", path + i + 1);
	else
		return (1);
	return (0);
}
