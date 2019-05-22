/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_expansion.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/22 07:05:34 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/22 15:16:48 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static int		get_expansion_length(char *ans, int i)
{
	int			j;

	j = i;
	while (ans[j] && (ans[j] < 9 || ans[j] > 13) && ans[j] != 32)
		j++;
	return (j);
}

static char		*get_expansion_content(char *ans, int i)
{
	char		*new_ans;
	int			j;
	int			k;

	k = 0;
	j = get_expansion_length(ans, i);
	new_ans = ft_strnew(j - i);
	while (i < j)
		new_ans[k++] = ans[i++];
	new_ans[k] = '\0';
	return (new_ans);
}

t_hist			*number_expansion(char **new_ans, t_hist *hist, char *expansion)
{
	int			index;

	while (hist->prev)
		hist = hist->prev;
	index = ft_atoi(expansion + 1);
	if (index > 0)
	{
		while (--index > 0 && hist->next)
			hist = hist->next;
	}
	if (hist->cmd == NULL || index > 0 || hist->next == NULL)
	{
		ft_printf("\n42sh: %s: event not found", expansion);
		*new_ans = ft_secure_free(*new_ans);
	}
	else
		*new_ans = ft_strjoinf(*new_ans, hist->cmd, 1);
	return (hist);
}

t_hist			*negative_number_expansion(char **new_ans, t_hist *hist, char *expansion)
{
	int			index;
	index = ft_atoi(expansion + 2);
	while (index > 0 && hist->prev)
	{
		hist = hist->prev;
		index--;
	}
	if (index > 0 || hist->cmd == NULL)
	{
		ft_printf("\n42sh: %s: event not found", expansion);
		*new_ans = ft_secure_free(*new_ans);
	}
	else
		*new_ans = ft_strjoinf(*new_ans, hist->cmd, 1);
	return (hist);
}

t_hist			*word_finding_expansion(char **new_ans, t_hist *hist, char *expansion)
{
	int			check;

	check = 0;
	while (hist->prev)
	{
		hist = hist->prev;
		if (ft_strncmp(hist->cmd, expansion + 1, ft_strlen(expansion) - 1) == 0)
		{
			*new_ans = ft_strjoinf(*new_ans, hist->cmd, 1);
			check += 1;
			break ;
		}
	}
	if (check == 0)
	{
		ft_printf("\n42sh: %s: event not found", expansion);
		*new_ans = ft_secure_free(*new_ans);
	}
	return (hist);
}

t_hist			*double_exclamation_expansion(char **new_ans, t_hist *hist, char *expansion)
{
	if (hist && hist->prev)
		*new_ans = ft_strjoinf(*new_ans, hist->prev->cmd, 1);
	else
	{
		ft_printf("\n42sh: %s: event not found", expansion);
		*new_ans = ft_secure_free(*new_ans);
	}
	return (hist);
}

t_hist			*replace_expansion_by_value(t_pos *pos, char **ans, t_hist *hist, int *i)
{
	char		*new_ans;
	int			end_exp;
	int			j;
	char		*expansion;

	expansion = get_expansion_content(*ans, *i);
	j = 0;
	end_exp = get_expansion_length(*ans, *i);
	new_ans = ft_strnew(*i);
	while (j < *i)
	{
		new_ans[j] = ans[0][j];
		j++;
	}
	new_ans[j] = '\0';
	if (expansion[1] == '!')
		hist = double_exclamation_expansion(&new_ans, hist, expansion);
	else if (expansion[1] >= 48 && expansion[1] <= 57)
		hist = number_expansion(&new_ans, hist, expansion);
	else if (expansion[1] == '-')
		hist = negative_number_expansion(&new_ans, hist, expansion);
	else if (expansion[1] && expansion[1] != '!' && expansion[1] != '-' &&
			(expansion[1] < 9 || expansion[1] > 13) && expansion[1] != 32)
		hist = word_finding_expansion(&new_ans, hist, expansion);
	else
		return (hist);
	if (new_ans != NULL && ans != NULL)
	{
		pos->replace_hist += 1;
		new_ans = ft_strjoinf(new_ans, *ans + end_exp, 1);
		*ans = ft_secure_free(*ans);
		*ans = new_ans;
	}
	else
		*ans = ft_secure_free(*ans);
	expansion = ft_secure_free(expansion);
	return (hist);
}



t_hist			*check_history_expansion(t_pos *pos, char *ans, t_hist *hist)
{
	int			i;
	int			check;
	
	check = 0;
	i = 0;
	if (ft_strchr(ans, '!') == NULL)
		return (hist);
	while (ans && ans[i])
	{
		if (ans[i] == '!')
		{
			hist = replace_expansion_by_value(pos, &ans, hist, &i);
			check += 1;
		}
			i += 1;
	}
	while (hist->next)
		hist = hist->next;
	if (ans != NULL && pos->replace_hist > 0)
	{
		pos->ans = ans;
		i = 0;
		clean_at_start(pos);
		write(1, ans, ft_strlen(ans));
		pos->let_nb = ft_strlen(ans);
		update_position(pos);
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
		pos->history_mode = 0;
	}
	else
	{
		pos->ans = ans;
	}
	return (hist);
}
