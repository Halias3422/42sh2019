/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hach.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/07 10:05:58 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 09:56:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hach.h"

typedef struct		s_hash
{
		int				hits;
		char			*path;
		struct s_hach	*next;
}						t_hash;


unsigned short	hash_str(char *str)
{
	int		i;
	unsigned short	sum;

	sum = 0;
	i = 0;
	while (str[i])
	{
		sum += str[i] * 3;
		i++;
	}
	return (sum);
}

int		hach_function(char *str)
{
	int		size;
	int		nb;
	int		i;

//	t_hash *hash[1000];

	i = hash_str(str);
	ft_printf("i = %d\n", i);
	nb = 0;
	size = ft_strlen(str);
	return (nb);
}
