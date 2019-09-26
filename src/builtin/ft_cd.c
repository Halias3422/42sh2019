/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 13:18:39 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/26 19:49:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int		get_cd_option(char **cmd, int *i, int ret)
{
	int		j;

	while (cmd[*i])
	{
		j = 1;
		if (ft_strcmp(cmd[*i], "--") == 0)
			return (0);
		else if (cmd[*i][0] == '-' && cmd[*i][1])
		{
			while (cmd[*i][j])
			{
				if (cmd[*i][j] == 'L' || cmd[*i][j] == 'P')
					ret = cmd[*i][j];
				else
				{
					ft_printf_err("42sh: cd: %c: invalid option\n", cmd[*i][j]);
					return (-1);
				}
				j++;
			}
		}
		++(*i);
	}
	return (ret);
}

char	*fill_new_path(char ***tmp, char *new_path, char *cmd, t_var **var)
{
	if (cmd[0] != '/')
		new_path = go_to_absolute_path(cmd, var);
	else
		new_path = ft_strdup(cmd);
	*tmp = ft_strsplit(new_path, '/');
	new_path = ft_secure_free(new_path);
	new_path = ft_strdup("/");
	return (new_path);
}

char	*get_path(char *cmd, t_var **var, char *new_path, int option)
{
	if (cmd == NULL || (cmd && cmd[0] == '~') || ft_strcmp(cmd, "cd") == 0)
		new_path = move_to_home_dir(var);
	else if (ft_strcmp(cmd, "-") == 0)
		new_path = move_to_oldpwd(var);
	else
	{
		if (option == 'P')
		{
			new_path = ft_strdup(cmd);
			new_path = verif_p_option_path(new_path);
		}
		else
			new_path = move_to_new_dir(cmd, var, new_path);
	}
	return (new_path);
}

void	replace_pwd_vars_in_env(t_var **var, char *new_path, int option)
{
	char	*tmp;
	char	*tmp_pwd;

	if (option == 'P')
	{
		tmp = ft_strnew(1000);
		tmp = getcwd(tmp, 1000);
	}
	else
		tmp = ft_strdup(new_path);
	if (ft_get_val("PWD", *var, ENVIRONEMENT) != NULL)
	{
		tmp_pwd = ft_strdup(ft_get_val("PWD", *var, ENVIRONEMENT));
		add_list_env(var, ENVIRONEMENT, "OLDPWD", tmp_pwd);
	}
	else
		add_list_env(var, ENVIRONEMENT, "OLDPWD", tmp);
	add_list_env(var, ENVIRONEMENT, "PWD", tmp);
}

int		ft_cd(t_process *p, t_var **var)
{
	int		option;
	int		i;
	char	*new_path;

	new_path = NULL;
	(void)var;
	i = 1;
	if ((option = get_cd_option(p->cmd, &i, 0)) == -1)
	{
		ft_printf_err("cd: usage: cd [-L|-P] [dir]\n");
		return (1);
	}
	if ((new_path = get_path(p->cmd[i - 1], var, new_path, option)) == NULL)
		return (1);
	if (verif_path(new_path) == 0)
		return (1);
	chdir(new_path);
	replace_pwd_vars_in_env(var, new_path, option);
	new_path = ft_secure_free(new_path);
	return (0);
}
