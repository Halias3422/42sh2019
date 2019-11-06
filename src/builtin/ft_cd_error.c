/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/26 12:58:07 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/26 13:05:32 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char		*error_in_new_path(char *new_path)
{
	int		i;
	int		error;

	error = 0;
	i = 0;
	while (new_path && new_path[i] && error == 0)
	{
		if (ft_strncmp(new_path + i, "./", 2) == 0 ||
			ft_strncmp(new_path + i, "../", 3) == 0)
			error = 1;
		i++;
	}
	if (error == 1)
	{
		free(new_path);
		new_path = longpwd(NULL, 1000);
	}
	return (new_path);
}
