/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_alias.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/29 09:16:52 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:42:22 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	write_alias(t_var *var, t_pos *pos)
{
	while (var && var->next)
	{
		if (var->type == ALIAS)
		{
			write(pos->alias, var->name, ft_strlen(var->name));
			write(pos->alias, "=", 1);
			write(pos->alias, var->data, ft_strlen(var->data));
			write(pos->alias, "\n", 1);
		}
		var = var->next;
	}
}

void	init_alias(t_var *var, t_pos *pos)
{
	char	*pwd;
	int		ret;
	char	*line;

	// ret = 1;
	line = NULL;
	pwd = getcwd(NULL, 255);
	pwd = ft_strjoinf(pwd, "/.aliases", 1);
	pos->alias = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	free(pwd);
	while (var->next)
		var = var->next;
	while ((ret = get_next_line(pos->alias, &line)) > 0)
	{
		if (ft_strlen(line) > 0)
		{
			var->next = malloc(sizeof(t_var));
			var = var->next;
			var->name = init_name(line);
			var->data = init_data(line);
			var->type = ALIAS;
			var->next = NULL;
		}
		if (line != NULL)
			ft_strdel(&line);
	}
}
