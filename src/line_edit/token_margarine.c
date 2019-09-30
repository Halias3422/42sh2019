/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_margarine.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:04:30 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 23:24:25 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"


int		double_quote(char *ans, int i)
{
	while (ans[i])
	{
		if (ans[i] == '"' && ans[i - 1] != 92)
			return (i);
		i++;
	}
	return (-1);
}

int		simple_quote(char *ans, int i)
{
	while (ans[i])
	{
		if (ans[i] == 39 && ans[i - 1] != 92)
			return (i);
		i++;
	}
	return (-1);
}

int		brace_param(char *ans, int i)
{
	while (ans[i])
	{
		if (ans[i] == '}' && ans[i - 1] != 92)
			return (i);
		i++;
	}
	return (-1);
}

int		double_token(char *ans, int i)
{
	int	j;

	j = i - 1;
	if (i - 2 == 0)
		return (ft_strlen(ans));
	while (ans[i] && (ans[i] == 32 || (ans[i] >= 9 && ans[i] <= 13)))
	{
		if (ans[i] != 92 && (ans[i + 1] == '&' || ans[i + 1] == '|'))
			return (ft_strlen(ans));
		i++;
	}
	if (!ans[i])
		return (-1);
	else
		return (j);
}

int		simple_pipe(char *ans, int i)
{
	int	j;


	j = i;
	if (i - 1 == 0)
		return (ft_strlen(ans));
	if (ans[i + 1] == '\0')
		return (-1);
	while (ans[i] && (ans[i] == 32 || (ans[i] >= 9 && ans[i] <= 13)))
	{
		if (ans[i] != 92 && (ans[i + 1] == '&' || ans[i] == '|'))
			return (ft_strlen(ans));
		i++;
	}
	if (i == j)
		return (ft_strlen(ans));
	else if (!ans[i])
		return (-1);
	else
		return (j);
}

int		token_margarine(char *ans)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (ans[i])
	{
		if (ans[i] == '"' && (i == 0 || (i > 0 && ans[i - 1] != 92)))
			i = double_quote(ans, i + 1);
		else if (ans[i] == 39  && (i == 0 || (i > 0 && ans[i - 1] != 92)))
			i = simple_quote(ans, i + 1);
		else if (ans[i] == '$' && ans[i + 1] == '{'  && (i == 0 || (i > 0 &&
						ans[i - 1] != 92)))
			i = brace_param(ans, i + 2);
		else if (ans[i] == '&' && ans[i + 1] == '&'  && (i == 0 || (i > 0 &&
						ans[i - 1] != 92)))
			i = double_token(ans, i + 2);
		else if (ans[i] == '|' && ans[i + 1] == '|'  && (i == 0 || (i > 0 &&
						ans[i - 1] != 92)))
			i = double_token(ans, i + 2);
		else if (ans[i] == '|' && (i == 0 || (i > 0 && ans[i - 1] != 92)))
			i = simple_pipe(ans, i + 1);
		if (i <= -1)
			return (0);
		if (i < ft_strlen(ans))
			i++;
	}
	return (1);
}
