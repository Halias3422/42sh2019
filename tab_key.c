/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 10:24:34 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 12:26:32 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

/*
 ** return -1 ==> je fais rien
 ** return 0 ==> je cherche une commande
 ** return 1 ==> je cherche dans le dossier courant - 2 modes, 1 recherche avec ce qui est donne, sil sagit dun repo, on ouvre et on affiche le dossier, sinon on complete, si trop de choix, on affiche le dossier courant
 ** return 2 ==> je cherche dans les variables
 */


int		scan_pos_ans(t_pos *pos)
{
	int		i;
	int		word_number;

	i = 0;
	word_number = 0;
	if (pos->let_nb == 0)
		return (-1);
	while (pos->ans[i] == ' ')
		i += 1;
	if (i == pos->let_nb)
		return (-1);
	while (pos->ans[i] && i < pos->let_nb)
	{
		if (pos->ans[i] == ' ')
		{
			while (pos->ans[i] == ' ' && i < pos->let_nb)
				i += 1;
			if (pos->ans[i] != ' ')
				word_number += 1;
		}
		else if (ft_strncmp(pos->ans + i, "&&", 2) == 0 || ft_strncmp(pos->ans + i, "&", 1) == 0 || ft_strncmp(pos->ans + i, "||", 2) == 0)
		{
			word_number = 0;
			i += 1;
			while (pos->ans[i] == ' ' && i < pos->let_nb)
				i += 1;
			if (i == pos->let_nb)
				return (-1);
		}
		else
			i += 1;
	}
	if (word_number == 0)
		return (0);
	if (word_number > 0)
		return (1);
	return (1);
}

char		*get_full_search(t_pos *pos, char *search)
{
	int		i;
	int		len;

	i = pos->let_nb;
	if (i == 0)
		return (NULL);
	while (i > 0 && pos->ans[i - 1] != ' ')
		i -= 1;
	len = i;
	while (pos->ans[len + 1] && pos->ans[len] != ' ')
		len += 1;
	pos->debug2 = i;
	pos->debug3 = len;
	search = ft_strndup(pos->ans + i, len - i);
	return (search);
}

t_htab		*looking_for_all(t_pos *pos, t_htab *htab)
{
	(void)pos;
	return (htab);
}

t_htab		*looking_for_current(t_pos *pos, t_htab *htab)
{
	DIR				*dirp;
	struct dirent	*read;

	(void)dirp;
	(void)read;
	(void)pos;
	return (htab);
}

t_htab		*looking_for_var(t_pos *pos, t_htab *htab)
{
	(void)pos;
	return (htab);
}

void		print_htab(t_pos *pos, t_htab *htab)
{
	(void)pos;
	while (htab && htab->prev)
		htab = htab->prev;
	while (htab && htab->next)
	{
		ft_putstr(htab->content);
		htab = htab->next;
	}
}

void		input_is_tab(t_pos *pos)
{
	int		usage;
	t_htab	*htab;
	char	*search;

	htab = NULL;
	search = NULL;
	usage = scan_pos_ans(pos);
	pos->ans_printed = 1;
	pos->debug = usage;
	if (usage == -1)
		return ;
	search = get_full_search(pos, search);
	pos->debugchar = search;
	if (usage == 0)
		htab = looking_for_all(pos, htab);
	if (usage == 1)
		htab = looking_for_current(pos, htab);
	if (usage == 2)
		htab = looking_for_var(pos, htab);
	if (htab)
		print_htab(pos, htab);
//	free(search);
	return ;
}
