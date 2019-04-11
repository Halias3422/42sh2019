/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnjoinnf.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bjuarez <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 08:59:30 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 10:48:10 by bjuarez     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		splitjoin2(char *str, int mode)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (str[i] != '\0')
	{
		if (str[i] && str[i] == '|')
			check++;
		if (check < mode && str[i] == '\0')
			return (-1);
		if (check == mode && str[i] && str[i] == '|' && str[i + 1] == '|')
			return (-1);
		if (check == mode && str[i] && str[i] != '|')
			return (ft_atoi(&str[i]));
		i++;
	}
	return (-1);
}

int		splitjoin(char *str, int mode)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp(str, "0") == 0)
		return (0);
	if (mode == 1 && str[0] != '\0' && str[0] != '|')
		return (ft_atoi(str));
	else if (mode == 1 && str[0] != '\0' && str[0] == '|')
		return (-1);
	if (mode == 2)
		return (splitjoin2(str, 1));
	if (mode == 3)
		return (splitjoin2(str, 2));
	return (-1);
}

char	*ft_strnjoinn(char const *s1, char const *s2, int n1, int n2)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = 0;
	while ((s1[i] && i != n1) || (s2[j] && j != n2))
	{
		while (s1[i] && i != n1)
		{
			str[i] = s1[i];
			i++;
		}
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strnjoinnf(char *s1, char *s2, char *str)
{
	char	*tmp;
	int		n1;
	int		n2;
	int		mode;

	n1 = splitjoin(str, 1);
	if (n1 == 0)
		n1 = ft_strlen(s1);
	n2 = splitjoin(str, 2);
	if (n2 == 0)
		n2 = ft_strlen(s2);
	mode = splitjoin(str, 3);
	tmp = ft_strnjoinn(s1, s2, n1, n2);
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (tmp);
}
