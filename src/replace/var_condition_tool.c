/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_condition_tool.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 10:20:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 10:21:44 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

void			condition_simple_quote(char *str, int *i)
{
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	else
		(*i)++;
}
