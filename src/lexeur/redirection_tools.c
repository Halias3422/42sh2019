/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_tools.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/17 01:19:20 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/17 01:21:43 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void			free_ar_lexeur(t_lexeur ***array)
{
	int		i;

	i = 0;
	while ((*array)[i])
	{
		ft_strdel(&(*array)[i]->word);
		ft_strdel(&(*array)[i]->redirection);
		i++;
	}
	free((*array));
}
