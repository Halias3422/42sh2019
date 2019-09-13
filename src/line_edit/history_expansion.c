/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_expansion.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/22 07:05:34 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 07:31:44 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int				check_if_inside_symbols(char *ans, int i)
{
	int			j;
	int			check_anti;
	int			check_single;
	int			check_double;

	check_anti = 0;
	check_single = 0;
	check_double = 0;
	j = 0;
	while (ans && ans[j] && j < i)
	{
		if (ans[j] == 39)
			check_single += 1;
		j++;
	}
	if ((check_single % 2) == 1)
		return (-1);
	return (0);
}

int				replace_expansion_by_value(t_pos *pos, t_hist *hist, int i,
				int error)
{
	char		*expansion;
	int			end_exp;
	char		*new_ans;

	expansion = get_expansion_content(pos->ans, i);
	end_exp = get_expansion_length(pos->ans, i);
	new_ans = ft_copy_part_str(pos->ans, i - 1, 0);
	error = get_expansion_value(expansion, hist, &new_ans);
	new_ans = ft_strjoinf(new_ans, pos->ans + i + ft_strlen(expansion), 1);
	pos->ans = ft_secure_free(pos->ans);
	pos->ans = ft_strdup(new_ans);
	new_ans = ft_secure_free(new_ans);
	expansion = ft_secure_free(expansion);
	return (error);
}

t_hist			*check_history_expansion(t_pos *pos, t_hist *hist, int i,
				int error)
{
	char		*original_ans;

	if (ft_strchr(pos->ans, '!') == NULL)
		return (hist);
	original_ans = ft_strdup(pos->ans);
	while (pos->ans && pos->ans[i])
	{
		if (pos->ans[i] == '!' && (i == 0 || (i > 0 && pos->ans[i - 1] != '!'))
			&& check_if_inside_symbols(pos->ans, i) == 0)
			error = replace_expansion_by_value(pos, hist, i, error);
		if (error == -1)
		{
			ft_printf("\n42sh: %s: event not found", original_ans);
			pos->error = 1;
			pos->ans = ft_secure_free(pos->ans);
			pos->ans = ft_strdup(original_ans);
			pos->ans = ft_strnew(0);
			break ;
		}
		i++;
	}
	free(original_ans);
	return (hist);
}
