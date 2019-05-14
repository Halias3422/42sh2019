/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/10 09:39:47 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/14 11:34:50 by rlegendr    ###    #+. /#+    ###.fr     */
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
	htab->matching_index = -1;
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

int				check_simple_dot(char *path)
{
	int		i;

	i = ft_strlen(path) - 1;
	if ((i == 0 && path[i] == '.') || (i > 0 && path[i] == '.' && path[i - 1] == '/'))
		return (0);
	return (1);
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
	if ((dirp = opendir(*path)) != NULL)// && check_simple_dot(*path))
	{
		ft_strcpy(pwd, *path);
		if (*name == NULL)
			add_slash_on_ans(pos);
	}
	else
	{
		pos->debug3 = *path[0];
		if (*path && *path[0] != 0)
			*name = ft_strjoinf(*path, *name, 2);
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
	print_info(pos);
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
	write(1, pos->ans, ft_strlen(pos->ans));
	get_cursor_info(pos, &pos->act_li, &pos->act_co);
	pos->act_co -= pos->len_prompt;
	pos->let_nb = ft_strlen(pos->ans);
	pos->len_ans = ft_strlen(pos->ans) + pos->len_prompt;
	if (pos->act_li == pos->max_li)
		pos->start_li = pos->act_li - get_len_with_lines(pos) / pos->max_co;
	else
		pos->start_li = pos->act_li;
	pos->debug4 = get_len_with_lines(pos);
//	if (pos->act_li != pos->start_li)
//		pos->act_co -= pos->len_prompt;
	pos->navigation = 2;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		free_htab(t_htab *htab)
{
	t_htab *tmp;

	while (htab->prev)
		htab = htab->prev;
	tmp = htab;
	while (htab)
	{
		htab = htab->next;
		free(tmp->content);
		free(tmp);
		tmp = htab;
	}
}

int		is_the_same_letter_unsensitive(char a, char b)
{
	if ((a >= 65 && a <= 90 && a + 32 == b) ||
		(a >= 97 && a <= 122 && a - 32 == b) || a == b)
		return (1);
	return (0);
}

int		ft_strstr_case_unsensitive(char *str, char *tofind)
{
	int		j;
	int		i;
	char	*s;

	i = 0;
	s = (char*)str;
	ft_printf("\n analyse\nstr = %s\ntofind = %s", str, tofind);
	if (tofind[0] == '\0')
		return (0);
	while (s[i])
	{
		j = 0;
		while (tofind[j] && is_the_same_letter_unsensitive(s[i + j], (tofind[j])))
			j++;
		if (tofind[j] == '\0')
			return (i + j);
		i++;
	}
	return (-1);
}

t_htab		*get_current_match(t_pos *pos, t_htab *htab, char *name)
{
	t_htab		*new;
	int			match;

	new = NULL;
	while (htab)
	{
		match = ft_strstr_case_unsensitive(htab->content, name);
		ft_printf(" /// resultat analyse --> %d", match);
		if (match != -1)
		{
			new = add_list_back_htab(new);
			new->content = ft_strdup(htab->content);
			new->content_type = htab->content_type;
			new->lenght_max = ft_strlen(new->content);
			new->content_no = new->prev == NULL ? 0 : new->prev->content_no + 1;
			new->matching_index = match;
		}
		if (htab->next == NULL)
			break ;
		htab = htab->next;
	}
	if (new == NULL)
	{
		pos->debug2 += 1;
		return (htab);
	}
	pos->debug4 += 1;
	while (new->prev)
		new = new->prev;
	while (new)
	{
	//	ft_printf("\ncontent matched = %s, content_no = %d", new->content, new->content_no);
		if (new->next == NULL)
			break ;
		new = new->next;
	}
	return (new);
}

int			reduce_ans(t_pos *pos, t_htab *htab)
{
	int		pos_i;
	int		search_i;

	pos_i = htab->matching_index;
	search_i = ft_strlen(htab->content) - 1;
	ft_printf("\n depart\npos->ans = %s -- index = %d\nhtab->content = %s -- index = %d", pos->ans, pos_i, htab->content, search_i);
//	while (htab->content[search_i] != pos->ans[pos_i])
//		search_i -= 1;
	while (htab->content[search_i] == pos->ans[pos_i])
	{
		ft_printf("\npos[%d] = %c - %c = htabcontent[%d]", pos_i, pos->ans[pos_i], htab->content[search_i], search_i);
		pos->ans[pos_i] = pos->ans[pos_i + 1];
		pos_i -= 1;
		search_i -= 1;
	}
	return (pos_i);
}

void		auto_complete(t_pos *pos, t_htab *htab)
{
	int		len;
	int		test;

	test = reduce_ans(pos, htab);
	ft_printf("\ntest = %d\n", test);
	exit(0);
	ft_strjoin_insert(&pos->ans, htab->content, test);
//	pos->ans[ft_strlen(pos->ans) - htab->matching_index] = '\0';
	pos->ans = ft_strjoinf(pos->ans, htab->content, 1);
	pos->let_nb = ft_strlen(pos->ans);
	pos->len_ans = ft_strlen(pos->ans) + pos->len_prompt;
	len = get_len_with_lines(pos);
	short_update(pos, len);
	clean_at_start(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
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
	else if (htab)
	{
		htab = get_current_match(pos, htab, name);
		pos->debug = htab->content_no;
		if (htab->content_no == 0)
			auto_complete(pos, htab);
		else
			print_htab(pos, htab);
	}
	pos->debugchar2 = ft_strdup(name);
	//    free(search);
	print_info(pos);
}
