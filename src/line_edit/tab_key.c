/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/10 09:39:47 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/15 16:36:35 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

t_htab			*looking_for_var(t_pos *pos, t_htab *htab)
{
	(void)pos;
	return (htab);
}

// content_type --> fichier/exe 4, dossier 8

void			complete_with_space(t_htab *htab)
{
	int			i;

	i = ft_strlen(htab->content);
	while (i++ < htab->lenght_max)
		write(1, " ", 1);
}

t_htab			*looking_for_all(t_pos *pos, t_htab *htab)
{
	(void)pos;
	return (htab);
}

void			init_t_htab(t_htab *htab)
{
	htab->content = NULL;
	htab->content_no = 0;
	htab->content_type = -1;
	htab->lenght_max = 0;
	htab->matching_index = -1;
	htab->next = NULL;
	htab->prev = NULL;
}

t_htab			*add_list_back_htab(t_htab *htab)
{
	t_htab		*new;

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

int				scan_pos_ans(t_pos *pos)
{
	int			i;
	int			word_number;

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

char			*get_full_path(t_pos *pos, char *search)
{
	int			i;
	int			len;

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

char			*get_correct_path(char *path)
{

	int			i;
	char		*name;
	DIR			*test;

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

void			add_slash_on_ans(t_pos *pos)
{
	int			i;

	i = ft_strlen(pos->ans) - 1;
	if (i == -1)
		return ;
	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != ' ')
		pos->let_nb += 1;
	if (pos->ans[pos->let_nb - 1] != '/')
		input_is_printable_char(pos, "/");
}

int					check_simple_dot(char *path)
{
	int			i;

	i = ft_strlen(path) - 1;
	if ((i == 0 && path[i] == '.') || (i > 0 && path[i] == '.' && path[i - 1] == '/'))
		return (0);
	return (1);
}

t_htab				*looking_for_current(t_pos *pos, t_htab *htab, char **path, char **name)
{
	DIR				*dirp;
	struct dirent	*read;
	char			*pwd;

	pwd = malloc(1000);
	ft_bzero(pwd, 999);
	if ((dirp = opendir(*path)) != NULL)// && check_simple_dot(*path))
	{
		ft_strcpy(pwd, *path);
		if (*name == NULL)
			add_slash_on_ans(pos);
	}
	else
	{
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
	while (htab->prev)
		htab = htab->prev;
	return (htab);
}

void			print_htab(t_htab *htab, t_pos *pos)
{
	int			max_word;

	max_word = pos->max_co / (htab->lenght_max + 4);
	write(1, "\n", 1);
	while (htab->prev)
		htab = htab->prev;
	while (htab)
	{
		if (htab->content_type == 4)
			ft_printf("{B.T.red.}%s{eoc}    ", htab == NULL ? NULL : htab->content);
		else
			ft_printf("%s    ", htab == NULL ? NULL : htab->content);
		complete_with_space(htab);
		if ((htab->content_no + 1) % max_word == 0)
			write(1, "\n", 1);
		htab = htab->next;
	}
	write(1, "\n", 1);
}

void			prepare_to_print_htab(t_pos *pos, t_htab *htab)
{
	int			len;

	print_htab(htab, pos);
	get_cursor_info(pos, &pos->start_li, &pos->start_co);
	print_prompt(pos);
	write(1, pos->ans, ft_strlen(pos->ans));
	len = go_to_let_nb(pos);
	short_update(pos, len);
	pos->navigation = 2;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void			free_htab(t_htab *htab)
{
	t_htab		*tmp;

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

int				is_the_same_letter_unsensitive(char a, char b)
{
	if ((a >= 65 && a <= 90 && a + 32 == b) ||
			(a >= 97 && a <= 122 && a - 32 == b) || a == b)
		return (1);
	return (0);
}

int				ft_strstr_case_unsensitive(char *str, char *tofind)
{
	int			j;
	int			i;
	char		*s;

	i = 0;
	s = str;
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

t_htab			*get_current_match(t_htab *htab, char *name)
{
	t_htab		*new;
	int			match;

	new = NULL;
	while (htab)
	{
		match = ft_strstr_case_unsensitive(htab->content, name);
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
		return (htab);
	free_htab(htab);
	return (new);
}

int				get_word_index(t_pos *pos)
{
	int			i;


	if (pos->let_nb == ft_strlen(pos->ans))
		return (pos->let_nb - 1);
	i = pos->let_nb;
	if (pos->ans[i] == 32)
		i -= 1;
	while (pos->ans[i + 1] != 32 && pos->ans[i + 1])
		i += 1;
	return (i);
}

void			reduce_ans(t_pos *pos, char *name)
{
	int			search_i;

	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != 32)
		right_arrow(pos);
	search_i = ft_strlen(name) - 1;
	while (search_i >= 0 && pos->let_nb + 1 >= 0 && is_the_same_letter_unsensitive(name[search_i], pos->ans[pos->let_nb - 1]))
	{
		input_is_backspace(pos);
		search_i -= 1;
	}
}

int				is_a_directory(char *path, t_pos *pos)
{
	DIR			*dirp;
	int			i;
	char		*to_open;
	int			word_index;


	word_index = get_word_index(pos);
	i = word_index;
	while (i - 1 >= 0 && path[i - 1] != 32)
		i -= 1;
	to_open = malloc(word_index - i + 2);
	to_open[word_index - i + 1] = '\0';
	ft_strncpy(to_open, path + i, word_index - i + 1);
	if ((dirp = opendir(to_open)) == NULL)
	{
		free(to_open);
		return (0);
	}
	free(to_open);
	closedir(dirp);
	return (1);
}

void			input_is_a_string_of_printable_char(t_pos *pos, char *to_add)
{
	int			j;
	char		buf[2];

	j = 0;
	buf[1] = '\0';
	while (to_add[j])
	{
		buf[0] = to_add[j];
		input_is_printable_char(pos, buf);
		j += 1;
	}
}

void			auto_complete(t_pos *pos, t_htab *htab, char *name)
{
	reduce_ans(pos, name);
	input_is_a_string_of_printable_char(pos, htab->content);
	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != 32)
		pos->let_nb += 1;
	if (is_a_directory(pos->ans, pos))
		add_slash_on_ans(pos);
	else if (pos->let_nb == ft_strlen(pos->ans))
		input_is_printable_char(pos, " ");
	else
		right_arrow(pos);
	clean_at_start(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co , pos->act_li), 1, ft_putchar);
}

int				ft_strncmp_case_unsensitive(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (is_the_same_letter_unsensitive(s1[i], s2[i]) && i < n && s1[i] && s2[i])
		i++;
	if (s1[i] != s2[i] && i < n)
		return (s1[i] - s2[i]);
	return (0);
}

t_htab			*get_intelligent_match(t_htab *htab, char *name)
{
	t_htab	*new;
	int		compare;

	new = NULL;
	while (htab->prev)
		htab = htab->prev;
	while (htab)
	{
		compare = ft_strncmp_case_unsensitive(htab->content, name, ft_strlen(name));
		if (compare == 0)
		{
			new = add_list_back_htab(new);
			new->content = ft_strdup(htab->content);
			new->content_type = htab->content_type;
			new->lenght_max = ft_strlen(new->content);
			new->content_no = new->prev == NULL ? 0 : new->prev->content_no + 1;
		}
		if (htab->next == NULL)
			break ;
		htab = htab->next;
	}
	if (new == NULL)
		return (htab);
	free_htab(htab);
	return (new);
}

void			input_is_tab(t_pos *pos)
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
	else if (usage == 1)
		htab = looking_for_current(pos, htab, &path, &name);
	else if (usage == 2)
		htab = looking_for_var(pos, htab);
	if (htab && name == NULL)
		prepare_to_print_htab(pos, htab);
	else if (htab)
	{
		htab = get_current_match(htab, name);
		htab = get_intelligent_match(htab, name);
		if (htab->content_no == 0)
			auto_complete(pos, htab, name);
		else
			prepare_to_print_htab(pos, htab);
	}
	free(path);
	free(name);
	free_htab(htab);
	print_info(pos);
}
