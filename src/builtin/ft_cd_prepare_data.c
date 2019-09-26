/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_prepare_data.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 19:10:28 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/26 19:49:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char	*move_to_home_dir(t_var **var)
{
	char	*path;

	path = ft_get_val("HOME", *var, ENVIRONEMENT);
	if (path == NULL)
		ft_printf_err("42sh: cd: HOME not set\n");
	return (ft_strdup(path));
}

char	*move_to_oldpwd(t_var **var)
{
	char	*path;

	path = ft_get_val("OLDPWD", *var, ENVIRONEMENT);
	if (path == NULL)
		ft_printf_err("42sh: cd: OLDPWD not set\n");
	return (ft_strdup(path));
}

char	*go_to_absolute_path(char *cmd, t_var **var)
{
	char	pwd[1000];
	char	*ret;

	ret = NULL;
	if ((ret = ft_get_val("PWD", *var, ENVIRONEMENT)) != NULL)
	{
		if (cmd[0] != '/')
			ret = ft_strjoin(ret, "/");
		return (ft_strjoinf(ret, cmd, 1));
	}
	getcwd(pwd, 1000);
	if (cmd[0] != '/')
		ret = ft_strjoin(pwd, "/");
	return (ft_strjoinf(ret, cmd, 1));
}

char	*replace_double_dot_by_real_path(char *path)
{
	int		i;

	if ((i = ft_strlen(path) - 2) == -1)
		return (path);
	while (i > 0 && path[i] != '/')
		i--;
	if (i == 0)
		return (path);
	path[i + 1] = '\0';
	return (path);
}

char	*move_to_new_dir(char *cmd, t_var **var, char *new_path)
{
	int			i;
	char		**tmp;

	i = 0;
	new_path = fill_new_path(&tmp, new_path, cmd, var);
	while (tmp[i])
	{
		if (ft_strcmp(tmp[i], "..") == 0)
			new_path = replace_double_dot_by_real_path(new_path);
		else if (ft_strcmp(tmp[i], ".") != 0)
		{
			new_path = ft_strjoinf(new_path, tmp[i], 1);
			if (verif_path(new_path) == 0)
			{
				ft_free_tab(tmp);
				free(new_path);
				return (NULL);
			}
			new_path = ft_strjoinf(new_path, "/", 1);
		}
		i++;
	}
	ft_free_tab(tmp);
	return (new_path);
}
