/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/10 09:39:47 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/10 16:22:55 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

t_htab        *looking_for_var(t_pos *pos, t_htab *htab)
{
	(void)pos;
	return (htab);
}

// content_type --> fichier/exe 4, dossier 8

void	complete_with_space(t_htab *htab, t_pos *pos)
{
	int		i;

	(void)pos;
	i = ft_strlen(htab->content);
	while (i++ < htab->lenght_max)
		write(1, " ", 1);
}

t_htab        *looking_for_all(t_pos *pos, t_htab *htab)
{
	(void)pos;
	return (htab);
}

void		init_t_htab(t_htab *htab)
{
	htab->content = NULL;
	htab->content_no = 0;
	htab->content_type = -1;
	htab->lenght_max = 0;
	htab->next = NULL;
	htab->prev = NULL;
}

t_htab		*add_list_back_htab(t_htab *htab)
{
	t_htab    *new;

	new = NULL;
	if (!(new = (t_htab*)malloc(sizeof(t_htab))))
		return (NULL);
	if (htab == NULL)
	{
		init_t_htab(new);
		return (new);
	}
	else
	{
		while (htab->next != NULL)
			htab = htab->next;
		init_t_htab(new);
		new->prev = htab;
		htab->next = new;
		return (new);
	}
	free(new);
	return (NULL);
}

int        scan_pos_ans(t_pos *pos)
{
	int        i;
	int        word_number;

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

char        *get_full_path(t_pos *pos, char *search)
{
	int        i;
	int        len;

	i = pos->let_nb;
	if (i == 0)
		return (NULL);
	while (i > 0 && pos->ans[i - 1] != ' ')
		i -= 1;
	len = i;
	while (pos->ans[len] && pos->ans[len] != ' ')
		len += 1;
	search = ft_strndup(pos->ans + i, len - i);
	return (search);
}

char		*get_correct_path(char *path)
{

	int		i;
	char	*name;
	DIR		*test;

	name = NULL;
	if ((test = opendir(path)) != NULL)
	{
		closedir(test);
		return (name);
	}
	i = ft_strlen(path) - 1;
	if (i == -1)
		return (NULL);
	while (i >= 0 && path[i] != '/')
		i -= 1;
	if (i < 0)
		return (NULL);
	name = ft_strdup(path + i + 1);
	path[i + 1] = '\0';
	return (name);
}

void		add_slash_on_ans(t_pos *pos)
{
	int		i;

	i = ft_strlen(pos->ans) - 1;
	pos->debug = i;
	if (i == -1)
		return ;
	if (pos->ans[i] == '/')
		return ;
	pos->debug5 += 1;
	input_is_printable_char(pos, "/");
}

t_htab        *looking_for_current(t_pos *pos, t_htab *htab, char **path, char **name)
{
	DIR				*dirp;
	struct dirent	*read;
	char			*pwd;

	(void)pos;
	(void)read;
	(void)name;
	pwd = malloc(1000);
	ft_bzero(pwd, 999);
//	ft_printf("\n name = -%s-\n path = -%s-\n", *name, *path);
//	exit(0);
	pos->debugchar = ft_strdup(*path);
	pos->debugchar2 = ft_strdup(*name);
	if ((dirp = opendir(*path)) != NULL)
	{
		pos->debug2 += 1;
		ft_strcpy(pwd, *path);
		if (*name == NULL)
		{
			pos->debug5 += 1;
			add_slash_on_ans(pos);
		}
	//	*name = ft_strjoinf(*path, *name, 2);
	//	*path = ft_secure_free(*path);
	}
	else
	{
//		*path = ft_strjoinf(*path, *name, 1);
		pwd = getcwd(pwd, 1000);
		dirp = opendir(pwd);
	}
	while ((read = readdir(dirp)) != NULL)
	{
			htab = add_list_back_htab(htab);
			htab->content = ft_strdup(read->d_name);
			htab->content_no = htab->prev == NULL ? 0 : htab->prev->content_no + 1;
			if (htab->prev == NULL)
				htab->lenght_max = ft_strlen(htab->content);
			else
				htab->lenght_max = htab->prev->lenght_max < ft_strlen(htab->content) ? ft_strlen(htab->content) : htab->prev->lenght_max;
			htab->content_type = (int)read->d_type;
	}
	closedir(dirp);
	free(pwd);
	while (htab)
	{
		htab->lenght_max = htab->next == NULL ? htab->lenght_max : htab->next->lenght_max;
	//	ft_printf("\n--> content = %s // num = %d // type = %d // lenghtmax = %d", htab->content, htab->content_no, htab->content_type, htab->lenght_max);
		if (htab->prev == NULL)
			break ;
		htab = htab->prev;
	}
	return (htab);
}

void	print_htab(t_pos *pos, t_htab *htab)
{
	t_htab	*tmp;
	int		i;
	int		max_word;

	tmp = htab;
	i = 0;
	max_word = pos->max_co / (htab->lenght_max + 4);
	pos->debug4 = max_word;
	write(1, "\n", 1);
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->content_type == 4)
			ft_printf("{T.cyan.}%s{eoc}    ", tmp == NULL ? NULL : tmp->content);
		else
			ft_printf("%s    ", tmp == NULL ? NULL : tmp->content);
		complete_with_space(tmp, pos);
		if ((tmp->content_no + 1) % max_word == 0)
			write(1, "\n", 1);
		i++;
		tmp = tmp->next;
	}
	write(1, "\n", 1);
	print_prompt(pos);
	get_cursor_info(pos, &pos->act_li, &pos->act_co);
	pos->start_li = pos->act_li;
	pos->act_co = pos->len_prompt + ft_strlen(pos->ans);
	write(1, pos->ans, ft_strlen(pos->ans));
	pos->navigation = 2;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		input_is_tab(t_pos *pos)
{
	int		usage;
	char	*path;
	char	*name;

	t_htab	*htab;

	htab = NULL;
	path = NULL;
	name = NULL;
	usage = scan_pos_ans(pos);
	pos->ans_printed = 1;
	if (usage == -1)
		return ;
	path = get_full_path(pos, path);
	name = get_correct_path(path);
	if (usage == 0)
		htab = looking_for_all(pos, htab);
	if (usage == 1)
		htab = looking_for_current(pos, htab, &path, &name);
	if (usage == 2)
		htab = looking_for_var(pos, htab);
	if (htab && name == NULL)
		print_htab(pos, htab);

	//    free(search);
	print_info(pos);
}
