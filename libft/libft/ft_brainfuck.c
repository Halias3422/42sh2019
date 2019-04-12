/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   brainfuck.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 09:22:09 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/22 14:18:13 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	b_to_b(char *input, unsigned char *ptr, size_t *i, size_t *brace)
{
	if (input[*i] == '[' && *ptr == 0)
	{
		while (input[++*i])
		{
			if (input[*i] == '[')
				++*brace;
			if (input[*i] == ']' && *brace == 0)
				break ;
			else if (input[*i] == ']')
				--*brace;
		}
	}
	else if (input[*i] == ']' && *ptr != 0)
	{
		while (input[--*i])
		{
			if (input[*i] == ']')
				++*brace;
			if (input[*i] == '[' && *brace == 0)
				break ;
			else if (input[*i] == '[')
				--*brace;
		}
	}
}

void	brainfuck1(char *input, unsigned char *ptr, size_t i, size_t brace)
{
	while (input[++i])
	{
		if (input[i] == '>')
			++ptr;
		else if (input[i] == '<')
			--ptr;
		else if (input[i] == '+')
			++*ptr;
		else if (input[i] == '-')
			--*ptr;
		else if (input[i] == '.')
			write(1, ptr, 1);
		else if (input[i] == '[' || input[i] == ']')
			b_to_b(input, ptr, &i, &brace);
	}
}

void	ft_brainfuck(char *input)
{
	unsigned char	save[2048];
	unsigned char	*ptr;
	size_t			i;
	size_t			brace;

	i = -1;
	brace = 0;
	ptr = save;
	while (++i < 2048)
		save[i] = 0;
	i = -1;
	return (brainfuck1(input, ptr, i, brace));
}
