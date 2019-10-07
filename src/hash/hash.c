/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 13:32:51 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 14:56:51 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

static char			*complete_hash_table(t_hash *tmp, char *arg, char *path)
{
	while (tmp->next != NULL && tmp->exec != NULL && ft_strcmp(arg, tmp->exec)
			!= 0)
		tmp = tmp->next;
	if (tmp->exec != NULL && ft_strcmp(arg, tmp->exec) == 0)
		tmp->hit += 1;
	else
		init_single_link(tmp, arg, path);
	return (tmp->path);
}

void				read_hash_table(t_hash **hash)
{
	int				i;
	t_hash			*tmp;

	i = 0;
	while (i < NB_KEY)
	{
		tmp = hash[i];
		while (tmp != NULL)
		{
			if (tmp->path != NULL)
				ft_printf("key[%d] -- path = %s -- cmd = %s -- hit = %d\n",
						i, tmp->path, tmp->exec, tmp->hit);
			tmp = tmp->next;
		}
		i++;
	}
}

static char			*search_exec_in_table(t_hash *hash, char *arg)
{
	while (hash)
	{
		if (hash != NULL && hash->exec != NULL &&
				ft_strcmp(hash->exec, arg) == 0)
		{
			hash->hit += 1;
			return (hash->path);
		}
		hash = hash->next;
	}
	return (NULL);
}

char				*fill_hash_table(char *path, char **arg)
{
	t_hash			**hash;
	int				key;
	char			*ans;

	ans = NULL;
	hash = NULL;
	hash = stock_hash(hash, 1);
	key = get_key_of_exec(arg[0]);
	if (hash == NULL)
	{
		hash = (t_hash**)malloc(sizeof(t_hash*) * 100);
		init_hash_links(hash);
		stock_hash(hash, 0);
	}
	else
		ans = search_exec_in_table(hash[key], arg[0]);
	if (ans != NULL)
		return (ans);
	ans = complete_hash_table(hash[key], arg[0], path);
	return (ans);
}

char				*check_path_hash(t_var **var, char **arg,
		int i, char *ans)
{
	char			**paths;
	t_hash			**hash;
	int				denied;
	char			**env;

	if ((denied = 0) == 0 && ft_strchr(arg[0], '/') != 0)
		return (absolute_path(arg[0]));
	if ((hash = stock_hash(NULL, 1)) != NULL &&
	(ans = search_exec_in_table(hash[get_key_of_exec(arg[0])], arg[0])) != NULL)
		return (ans);
	env = split_env(*var);
	paths = get_ide_paths(env);
	ft_free_tab(env);
	while (paths != NULL && paths[++i])
	{
		paths[i] = ft_strjoinf(paths[i], "/", 1);
		paths[i] = ft_strjoinf(paths[i], arg[0], 1);
		if (access(paths[i], F_OK) == 0 && access(paths[i], X_OK) == 0)
			return (path_found(paths, i, ans, arg));
		else if (access(paths[i], F_OK) == 0 && access(paths[i], X_OK) != 0)
			denied += 1;
	}
	if (denied != 0)
		return (path_denied(paths, arg));
	ft_free_tab(paths);
	return (NULL);
}
