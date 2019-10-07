/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_i_flag.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:50:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 14:39:20 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			fill_new_link_in_env(t_var *new_env, char **new_env_var)
{
	new_env->name = new_env_var[0];
	new_env->data = new_env_var[1];
	new_env->type = ENVIRONEMENT;
}

static int		fill_new_env(t_process *p, int i, t_var **new_env,
		t_var **head)
{
	char		**new_env_var;

	if (ft_strchr(p->cmd[i], '=') != NULL)
	{
		new_env_var = ft_strsplit(p->cmd[i], '=');
		if ((new_env_var[0] == NULL && new_env_var[1] == NULL) ||
				p->cmd[i][0] == '=')
		{
			ft_free_tab(new_env_var);
			ft_printf("42sh: env: invalid argument");
			return (-2);
		}
		if (*new_env == NULL)
		{
			*head = add_list_back_env(*new_env);
			*new_env = *head;
		}
		else
			*new_env = add_list_back_env(*new_env);
		fill_new_link_in_env(*new_env, new_env_var);
		free(new_env_var);
		if (!p->cmd[i + 1])
			return (-1);
	}
	return (0);
}

static void		interpret_env_cmd(t_process *p, int i, char *new_cmd,
				t_var *head)
{
	new_cmd = ft_strnew(0);
	while (p->cmd[i])
	{
		new_cmd = ft_strjoinf(new_cmd, p->cmd[i], 1);
		new_cmd = ft_strjoinf(new_cmd, " ", 1);
		i++;
	}
	if (check_error(new_cmd) != -1)
		start_exec(start_lex(head, new_cmd), head);
	free(new_cmd);
}

void			print_new_env(t_var **new_env, t_var **head)
{
	*new_env = *head;
	print_env(*new_env);
}

int				go_through_process_cmd(t_process *p, t_var **new_env,
				t_var **head, int ret)
{
	char		*new_cmd;
	int			i;

	new_cmd = NULL;
	i = 1;
	while (p->cmd[++i])
	{
		if (ft_strchr(p->cmd[i], '=') != NULL)
		{
			if ((ret = fill_new_env(p, i, new_env, head)) <= -1)
			{
				if (ret == -2)
					return (-1);
				print_new_env(new_env, head);
				break ;
			}
		}
		else if (p->cmd[i])
		{
			*new_env = *head;
			interpret_env_cmd(p, i, new_cmd, *new_env);
			break ;
		}
	}
	return (0);
}
