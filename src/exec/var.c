/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/07 04:12:58 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/07 04:41:42 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

// Pour les variables temporaires ex:(toto=tata echo $toto) on peut creer un type pour elles 
// et ensuite avant de refaire un tour de boucle on fait un tout dans la liste chainé pour supprimer
// ces types la ??

char		*get_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	res = ft_strsub(str, 0, i);
	return (res);
}

char		*get_data(char *str)
{
	char	*res;
	int		i;
	int		s;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	s = i;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	res = ft_strsub(str, s, i - s);
	return (res);
}

void		add_var(char *str, t_var *var)
{
	t_var	*start;
	t_var	*new;

	start = var;
	while (var->next)
		var = var->next;
	new = malloc(sizeof(t_var));
	new->name = get_name(str);
	printf("new->name: _%s_\n", new->name);
	new->data = get_data(str);
	printf("new->data: _%s_\n", new->data);
	var->next = new;
	new->next = NULL;
	new->type = LOCAL;
	var = start;
}