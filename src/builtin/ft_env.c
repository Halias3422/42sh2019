/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 08:05:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 10:36:07 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static int		fill_new_env(t_process *p, int i, t_var **new_env,
				t_var **head)
{
	char		**new_env_var;

	if (ft_strchr(p->cmd[i], '=') != NULL)
	{
		new_env_var = ft_strsplit(p->cmd[i], '=');
		if (*new_env == NULL)
		{
			*head = add_list_back_env(*new_env);
			*new_env = *head;
		}
		else
			*new_env = add_list_back_env(*new_env);
		(*new_env)->name = new_env_var[0];
		(*new_env)->data = new_env_var[1];
		(*new_env)->type = ENVIRONEMENT;
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
}

static void		go_through_process_cmd(t_process *p, t_var **new_env,
				t_var **head)
{
	char		*new_cmd;
	int			i;

	new_cmd = NULL;
	i = 2;
	while (p->cmd[i])
	{
		if (ft_strchr(p->cmd[i], '=') != NULL)
		{
			if (fill_new_env(p, i, new_env, head) == -1)
			{
				*new_env = *head;
				print_env(new_env);
				break ;
			}
		}
		else if (p->cmd[i])
		{
			*new_env = *head;
			interpret_env_cmd(p, i, new_cmd, *new_env);
			break ;
		}
		i++;
	}
}

int				ft_env(t_process *p, t_var **var)
{
	t_var		*new_env;
	t_var		*head;

	head = NULL;
	new_env = NULL;
	if (!p->cmd[1])
		print_env(var);
	else if (p->cmd[1] && (ft_strcmp(p->cmd[1], "-") == 0 ||
				ft_strcmp(p->cmd[1], "-i") == 0 ||
				ft_strcmp(p->cmd[1], "--ignore-environment") == 0))
		go_through_process_cmd(p, &new_env, &head);
	free_new_env(head);
	return (1);
}
