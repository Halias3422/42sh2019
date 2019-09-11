/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_expansion_free.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 12:41:43 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 13:34:12 by vde-sain    ###    #+. /#+    ###.fr     */
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

char			*filling_ans_with_new_ans(t_pos *pos, char *new_ans, char **ans,
				int end_exp)
{
	pos->replace_hist += 1;
	new_ans = ft_strjoinf(new_ans, *ans + end_exp, 1);
	*ans = ft_secure_free(*ans);
	*ans = new_ans;
	return (new_ans);
}

char			*new_ans_not_valid(char **ans, char *new_ans, int *i)
{
	*ans = ft_secure_free(*ans);
	new_ans = ft_secure_free(new_ans);
	*i += 1;
	return (new_ans);
}

t_hist			*no_expansion_found(char **expansion, char **new_ans,
				t_hist *hist)
{
	*expansion = ft_secure_free(*expansion);
	*new_ans = ft_secure_free(*new_ans);
	return (hist);
}
