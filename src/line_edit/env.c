/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/08 10:53:46 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 09:16:13 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/lexeur.h"

char	*init_data(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	i++;
	dest = ft_strsub(src, i, ft_strlen(src) - i);
	return (dest);
}

char	*init_name(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	dest = ft_strsub(src, 0, i);
	return (dest);
}

t_var	*init_env(char **env, t_pos *pos)
{
	t_var	*new;
	t_var	*save;
	int		i;

	i = 0;
	new = malloc(sizeof(t_var));
	save = new;
	while (env[i])
	{
		new->name = init_name(env[i]);
		new->data = init_data(env[i]);
		new->type = ENVIRONEMENT;
		i++;
		if (env[i])
		{
			new->next = malloc(sizeof(t_var));
			new = new->next;
		}
	}
	new->next = malloc(sizeof(t_var));
	new = new->next;
	new->name = ft_strdup("?");
	new->data = ft_strdup("0");
	new->next = NULL;
	init_alias(save, pos, NULL);
	return (save);
}

void	free_env(t_var *env)
{
	t_var *buf;

	while (env)
	{
		buf = env->next;
		free(env->name);
		free(env->data);
		free(env);
		env = buf;
	}
}
