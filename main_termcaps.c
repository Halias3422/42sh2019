/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_termcaps.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 15:07:10 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int		main(void)
{
	char	*test;

	while (1)
	{
		test = termcaps42sh("$ ", 0);
		if (test == NULL)
			break ;
		ft_printf("reponse -> /%s/\n", test);
		free(test);
		test = NULL;
	}
}
