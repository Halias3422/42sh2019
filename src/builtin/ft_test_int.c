/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_test_int.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 10:10:59 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 19:22:24 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int			verif_int(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if ((i == 0 && name[i] == '-') ||
			(name[i] >= '0' && name[i] <= '9'))
			i++;
		else
		{
			ft_printf("test: integer expression expected: %s\n", name);
			return (-1);
		}
	}
	return (0);
}

int			comp_num_operator(char *name1, char *type, char *name2)
{
	if (verif_int(name1) == -1 || verif_int(name2) == -1)
		return (2);
	if (ft_strcmp(type, "-eq") == 0)
		return (ft_atoi(name1) == ft_atoi(name2)) ? 0 : 1;
	else if (ft_strcmp(type, "-ne") == 0)
		return (ft_atoi(name1) != ft_atoi(name2)) ? 0 : 1;
	else if (ft_strcmp(type, "-ge") == 0)
		return (ft_atoi(name1) >= ft_atoi(name2)) ? 0 : 1;
	else if (ft_strcmp(type, "-lt") == 0)
		return (ft_atoi(name1) < ft_atoi(name2)) ? 0 : 1;
	else if (ft_strcmp(type, "-le") == 0)
		return (ft_atoi(name1) <= ft_atoi(name2)) ? 0 : 1;
	else
	{
		ft_printf("test: unknown condition: %s\n", type);
		return (2);
	}
}

int			comp_operator(char *name1, char *type, char *name2)
{
	if (ft_strcmp(type, "=") == 0)
		return (ft_strcmp(name1, name2) == 0) ? 1 : 0;
	else if (ft_strcmp(type, "!=") == 0)
		return (ft_strcmp(name1, name2) != 0) ? 1 : 0;
	else if (type[0] != '-')
	{
		ft_printf("test: condition expected: %s\n", type);
		return (1);
	}
	else
		return (comp_num_operator(name1, type, name2));
	return (2);
}
