/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_alias.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/29 09:16:52 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/31 16:00:24 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	init_alias(t_var *var, t_pos *pos)
{
	char	*pwd;
	int		ret;
	char	*line;

	line = NULL;
	pos->path = getcwd(NULL, 255);
	pwd = ft_strjoin(pos->path, "/.aliases");
	pos->alias = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
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
