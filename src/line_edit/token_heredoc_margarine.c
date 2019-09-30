/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_heredoc_margarine.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 15:38:36 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 20:00:44 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

typedef struct			s_heredoc
{
	char				*to_find;
	int					current_index;
	char				*content;
	struct s_heredoc	*next;
	struct s_heredoc	*prev;
}						t_heredoc;

void			init_t_heredoc(t_heredoc *hdoc)
{
	hdoc->to_find = NULL;
	hdoc->current_index = 0;
	hdoc->content = NULL;
	hdoc->next = NULL;
	hdoc->prev = NULL;
}

t_heredoc		*add_list_back_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*new;

	new = NULL;
	if (!(new = (t_heredoc*)malloc(sizeof(t_heredoc))))
		return (NULL);
	if (heredoc == NULL)
	{
		init_t_heredoc(new);
		return (new);
	}
	while (heredoc->next != NULL)
		heredoc = heredoc->next;
	init_t_heredoc(new);
	heredoc->next = new;
	new->prev = heredoc;
	return (new);
}

// token_heredoc_creation.c

int				heredoc_found(t_pos *pos, int i, t_heredoc **hdoc)
{
	int		save;
	int		j;
//	char	*tmp;
//	char	*token;


	j = i;
	save = i;
	while (pos->ans[i] && pos->ans[i] != '<' && pos->ans[i] != '&' && pos->ans[i] != '|' && pos->ans[i] != '>' &&
			!(pos->ans[i] == '$' && pos->ans[i + 1] == '{') && (i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
		i++;
	while (pos->ans[j] && (pos->ans[j] == 32 || (pos->ans[j] >= 9 && pos->ans[j] <= 13)))
		j++;
	if (pos->ans[j] && (pos->ans[j] == '<' || pos->ans[j] == '>' || pos->ans[j] == '&' || pos->ans[j] == '|' || (pos->ans[j] == '$' && pos->ans[j + 1] == '{')) && (i == 0 || (i > 0 && pos->ans[i - 1] != 92)) && j == i)
		return (-1);
	*hdoc = add_list_back_heredoc(*hdoc);
	(*hdoc)->to_find = ft_strsub(pos->ans, j, i - j);
	j = ft_strlen((*hdoc)->to_find);
	while ((*hdoc)->to_find[--j] == 32)
		(*hdoc)->to_find[j] = '\0';
	ft_printf("\nhdoc->to_find = {%s}\n", (*hdoc)->to_find);
	return (1);
}

int				fill_hdoc_content(t_heredoc *hdoc, char *ans)
{
	int		i;
	int		j;

	i = ft_strlen(ans) - 1;
	while (i > 0 && ans[i] != '\n')
		i--;
	while (hdoc->next && hdoc->current_index == 1)
		hdoc = hdoc->next;
	if (ft_strcmp(ans + i + 1, hdoc->to_find) == 0)
	{
		hdoc->current_index = 1;
		ft_strdel(&ans);
		if (hdoc->next == NULL)
			return (1);
		return (0);
	}
	j = i;
	while (ans[++j])
	{
		if (ans[j] == 32)
			ans[j] = -1;
	}
	hdoc->content = ft_strjoinf(hdoc->content, ans + i + 1, 1);
	hdoc->content = ft_strjoinf(hdoc->content, " ", 1);
	ft_strdel(&ans);
	return (0);
}

// token_heredoc_margarine.c

void			free_hdoc(t_heredoc *hdoc)
{
	t_heredoc				*tmp;

	while (hdoc)
	{
		tmp = hdoc;
		hdoc = hdoc->next;
		ft_strdel(&tmp->content);
		ft_strdel(&tmp->to_find);
		free(hdoc);
	}
}

void			check_for_heredoc(t_pos *pos)
{
	int					i;
	char				open;
	static t_heredoc	*hdoc = NULL;

	i = 0;
	open = -1;
	if (hdoc == NULL)
	{
		while (pos->ans[i])
		{
			if (open != -1 && (pos->ans[i] == open || (open == '$' && pos->ans[i] == '}')) && pos->ans[i - 1] != 92)
				open = -1;
			else if (open == -1 && 
					(pos->ans[i] == '"' || pos->ans[i] == 39 || (pos->ans[i] == '$' && pos->ans[i + 1] == '{')) &&
					(i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
				open = pos->ans[i];
			if (pos->ans[i] == '<' && pos->ans[i + 1] == '<' && (i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
			{
				if (heredoc_found(pos, i + 2, &hdoc) == -1)
				{
					free_hdoc(hdoc);
					pos->is_complete = 1;
				}
			}
			i++;
		}
	}
	else
	{
		while (hdoc->prev)
			hdoc = hdoc->prev;
		if (fill_hdoc_content(hdoc, ft_strdup(pos->ans)))
		{
			pos->is_complete = 1;
			free_hdoc(hdoc);
			return ;
		}
	}
	if (hdoc)
		pos->is_complete = 0;
}
