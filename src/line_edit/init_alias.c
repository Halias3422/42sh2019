/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_alias.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/29 09:16:52 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 17:37:08 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	write_alias(t_var *var, t_pos *p)
{
	chdir(p->path);
	if ((p->alias = (open("./.aliases", O_WRONLY | O_TRUNC | O_CREAT, 0664))) != -1)
		while (var)
		{
			if (var->type == 2)
			{
				write(p->alias, var->name, ft_strlen(var->name));
				write(p->alias, "=", 1);
				write(p->alias, var->data, ft_strlen(var->data));
				write(p->alias, "\n", 1);
			}
			var = var->next;
		}
}

void	init_alias(t_var *var, t_pos *pos, char *line)
{
	char	*pwd;
	int		ret;

	pos->path = getcwd(NULL, 255);
	pwd = ft_strjoin(pos->path, "/.aliases");
	if ((pos->alias = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666)) == -1)
	{
		ft_strdel(&pwd);
		return ;
	}
	ft_strdel(&pwd);
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
			var->type = 2;
			var->next = NULL;
		}
		if (line != NULL)
			ft_strdel(&line);
	}
	close(pos->alias);
}
