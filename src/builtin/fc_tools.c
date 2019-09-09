/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_tools.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 13:14:57 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 11:06:53 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void			remove_cmd_from_hist(t_hist *hist)
{
	while (hist && hist->next && hist->next->next)
		hist = hist->next;
	hist->cmd = NULL;
	hist->next = NULL;
}

char			*get_program_pwd(char *pwd, int i)
{
	t_var		*var;
	char		**env;

	var = stock(NULL, 6);
	env = split_env(var);
	while (env[i] && ft_strncmp(env[i], "_=", 2) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	pwd = ft_strnew(0);
	pwd = ft_strjoinf(pwd, env[i] + 2, 1);
	i = ft_strlen(pwd) - 1;
	while (pwd[i] && pwd[i] != '/')
		i--;
	pwd[i] = '\0';
	pwd = ft_strjoinf(pwd, "history", 1);
	ft_free_tab(env);
	return (pwd);
}

void			overwrite_history_file(t_hist *hist)
{
	char		*pwd;
	int			i;
	int			fd;

	i = 0;
	pwd = NULL;
	pwd = get_program_pwd(pwd, i);
	if (pwd == NULL)
		return ;
	fd = open(pwd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(pwd);
	while (hist->prev)
		hist = hist->prev;
	while (hist->next)
	{
		write(fd, hist->cmd, ft_strlen(hist->cmd));
		hist = hist->next;
		write(fd, "\n", 1);
	}
}

void			place_new_cmds_in_history(char **new_cmds, t_hist *hist)
{
	int			i;

	while (hist && hist->next && hist->next->next)
		hist = hist->next;
	hist->cmd = NULL;
	hist->next = NULL;
	i = 0;
	while (new_cmds[i])
	{
		if (ft_strlen(new_cmds[i]) > 0 && (!hist->prev || ft_strcmp(new_cmds[i],
					hist->prev->cmd) != 0))
		{
			hist->cmd = ft_strdup(new_cmds[i]);
			hist = add_list_back_hist(hist);
		}
		i++;
	}
	hist->next = NULL;
	ft_free_tab(new_cmds);
	overwrite_history_file(hist);
}

void			print_fc_usage(void)
{
	write(2, "fc: usage: fc [-e ename] [-nlr] [first] [last]", 46);
	write(2, " or fc -s [pat=rep] [cmd]\n", 26);
}
