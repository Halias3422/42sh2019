/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 08:05:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 15:33:46 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int				regular_env_process_cmd(t_process *p, t_var *var, int i)
{
	char		*new_cmd;
	t_var		*head;

	head = var;
	new_cmd = ft_strnew(0);
	if (!p->cmd[i])
		print_env(&var);
	while (p->cmd[i])
	{
		new_cmd = ft_strjoinf(new_cmd, p->cmd[i], 1);
		new_cmd = ft_strjoinf(new_cmd, " ", 1);
		i++;
	}
	if (check_error(new_cmd) != -1)
	{
		start_exec(start_lex(var, new_cmd), var);
		free_new_env(head);
		return (0);
	}
	free(new_cmd);
	free_new_env(head);
	return (-1);
}

t_var			*place_new_entry_in_tmp_env(char **new_env_entry,
		t_var *var)
{
	t_var		*head;
	int			name_len;

	name_len = ft_strlen(new_env_entry[0]);
	if (var == NULL)
	{
		var = add_list_back_env(NULL);
		var->name = ft_strdup(new_env_entry[0]);
		var->data = ft_strdup(new_env_entry[1]);
		var->type = ENVIRONEMENT;
		var->next = NULL;
	}
	head = var;
	while (var && var->next && ft_strcmp(new_env_entry[0], var->name) != 0)
		var = var->next;
	if (var->name != NULL && ft_strncmp(new_env_entry[0], var->name, 
				name_len) == 0)
	{
		var->data = ft_secure_free(var->data);
		var->data = ft_strdup(new_env_entry[1]);
		var = head;
	}
	else
	{
		var->next = add_list_back_env(var);
		var = var->next;
		var->name = ft_strdup(new_env_entry[0]);
		var->data = ft_strdup(new_env_entry[1]);
		var->type = ENVIRONEMENT;
	}
	return (head);
}

t_var			*copy_env(t_var *var)
{
	t_var		*new_var;
	t_var		*head;

	new_var = NULL;
	head = NULL;
	while (var)
	{
		if (var->type == ENVIRONEMENT)
		{
			new_var = add_list_back_env(new_var);
			if (head == NULL)
				head = new_var;
			new_var->name = ft_strdup(var->name);
			new_var->data = ft_strdup(var->data);
			new_var->type = var->type;
		}
		var = var->next;
	}
	return (head);
}

int				normal_env_behavior(t_process *p, t_var **var)
{
	int			i;
	char		**new_env_entry;
	t_var		*new_var;

	new_var = copy_env(*var);
	i = 1;
	if (ft_strchr(p->cmd[i], '=') != NULL)
	{
		while (p->cmd[i])
		{
			if (ft_strchr(p->cmd[i], '=') != NULL)
			{
				new_env_entry = ft_strsplit(p->cmd[i], '=');
				if (new_env_entry[1] == NULL && p->cmd[i][0] == '=')
				{
					ft_printf_err("%s: env: invalid argument", TERM);
					free_new_env(new_var);
					ft_free_tab(new_env_entry);
					return (-1);
				}
				new_var = place_new_entry_in_tmp_env(new_env_entry, new_var);
				ft_free_tab(new_env_entry);
			}
			else
				return (regular_env_process_cmd(p, new_var, i));
			i++;
		}
	}
	return (regular_env_process_cmd(p, new_var, i));
}

int				ft_env(t_process *p, t_var **var)
{
	t_var		*new_env;
	t_var		*head;
	int			err;

	err = 1;
	head = NULL;
	new_env = NULL;
	if (!p->cmd[1])
		print_env(var);
	else if (p->cmd[1] && (ft_strcmp(p->cmd[1], "-") == 0 ||
				ft_strcmp(p->cmd[1], "-i") == 0 ||
				ft_strcmp(p->cmd[1], "--ignore-environment") == 0))
	{
		err = go_through_process_cmd(p, &new_env, &head, 0);
		free_new_env(head);
	}
	else
		err = normal_env_behavior(p, var);
	return (err);
}
