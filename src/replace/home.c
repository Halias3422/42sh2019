/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   home.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 16:34:57 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 17:17:02 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
	
#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"
#include "../../includes/alias.h"

char		*get_home(t_var *var)
{
	while (var)
	{
		if (ft_strcmp(var->name, "HOME") == 0)
			return (var->data);
		var = var->next;
	}
	return (ft_strdup(var->data));
}

char		*replace_home(char *str, t_var *var)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] != '~')
		i++;
	if ((tmp = get_home(var)) == NULL)
		return (str);
    printf("tmp = %s\n", tmp);
	res = ft_strsub(str, 0, i - 1);
	ft_strjoin_free(&res, tmp);
	ft_strdel(&tmp);
	tmp = ft_strsub(str, i + 1, ft_strlen(str));
	ft_strjoin_free(&res, tmp);
	// ft_strdel(&tmp);
    // ft_strdel(&str);
	return (res);
}