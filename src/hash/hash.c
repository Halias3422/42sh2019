/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 13:32:51 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 15:56:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

char	*cut_last_slash(char *path)
{
	int		i;

	i = ft_strlen(path);
	while (i > 0 && path[i] != '/')
		i--;
	if (i != 0)
		path[i + 1] = '\0';
	return (path);
}

void	check_path_hash(char **tab_var, char *path, char **arg)
{
	DIR				*dirp;
	struct dirent	*read;
	char			*tmp_path;

	tmp_path = ft_strdup(path);
	tmp_path = cut_last_slash(tmp_path);
	dirp = opendir(tmp_path);
	if (dirp == NULL)
		return ;
	while ((read = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(arg[0], read->d_name) == 0)
		{
			closedir(dirp);
			fill_hash_table(tab_var, tmp_path, arg);
			free(tmp_path);
			return ;
		}
	}
	free(tmp_path);
	closedir(dirp);
	return ;
}

unsigned short    hash_str(char *str)
{
	int        i;
	unsigned short    sum;

	sum = 0;
	i = 0;
	while (str[i])
	{
		sum += str[i] * (3 + i);
		i++;
	}
	return (sum % 100);
}

t_hash		**stock_hash(t_hash **to_stock, int usage)
{
	static t_hash	**stock_t_hash = NULL;

	if (usage == 0)
		stock_t_hash = to_stock;
	else if (usage == 1)
		return (stock_t_hash);
	return (NULL);
}

void		fill_hash_table(char **tab_var, char *path, char **arg)
{
	t_hash **hash;
	int		key;

	hash = NULL;
	hash = stock_hash(hash, 1);
	if (hash == NULL)
	{
		ft_printf("cest NULLL\n");
		hash = (t_hash**)malloc(sizeof(t_hash*) * 100);
		stock_hash(hash, 0);
	}
	else
		ft_printf("cest plus NLUL\n");
	(void)tab_var;
	(void)path;
	(void)arg;
	ft_printf("contenu de arg %T\npath = %s\n", arg, path);
	key = hash_str(arg[0]);
	ft_printf("cle = %d\n", key);

}
