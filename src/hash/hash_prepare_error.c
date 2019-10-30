/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_prepare_error.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 15:06:52 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 13:44:13 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

void				hash_is_on_middle_link(t_hash *hash, t_hash *prev)
{
	hash = hash->next;
	free(prev->next);
	prev->next = hash;

}

char				*remove_old_entry_in_hash(t_hash **ghash, char *ans,
					char *arg, t_var **var)
{
	t_hash	*prev;
	t_hash	*hash;

	hash = ghash[get_key_of_exec(arg)];
	prev = NULL;
	while (hash && ft_strcmp(arg, hash->exec) != 0)
	{
		if (hash->next && ft_strcmp(arg, hash->next->exec) == 0)
			prev = hash;
		hash = hash->next;
	}
	if (hash == NULL)
		return (ans);
	ft_strdel(&hash->path);
	ft_strdel(&hash->exec);
	hash->hit = 0;
	if (prev == NULL && hash->next != NULL)
	{
			ghash[get_key_of_exec(arg)] = hash->next;
			free(hash);
	}
	else
		hash_is_on_middle_link(hash, prev);
	free(ans);
	return (check_path_hash(var, ft_strdup(arg), 0, NULL));
}

void		prepare_error_message_for_hash(int error, char *str)
{
	t_process	*p;

	p = to_stock(NULL, 3);
	if (p->hash_error)
		return ;
	p->hash_error = ft_strnew(0);
	p->hash_error = ft_strjoinf(p->hash_error, "42sh: ", 1);
	if (str)
		p->hash_error = ft_strjoinf(p->hash_error, str, 1);
	if (error == 1)
		p->hash_error = ft_strjoinf(p->hash_error, ": is a directory\n", 1);
	else if (error == 2)
		p->hash_error = ft_strjoinf(p->hash_error,
				": No such file or directory\n", 1);
	else if (error == 3)
		p->hash_error = ft_strjoinf(p->hash_error, ": permission denied\n", 1);
	else if (error == 4)
		p->hash_error = ft_strjoinf(p->hash_error, ": command not found\n", 1);
}
