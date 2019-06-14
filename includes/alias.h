/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/11 16:17:46 by mateodelarb  #+#   ##    ##    #+#       */
/*   Updated: 2019/06/14 10:42:31 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

typedef struct s_alias
{
	char			*data;
	struct s_alias	*next;
	struct s_alias	*prev;
} t_alias;


char		check_last_char(t_alias *alias, int j);
int			cnt_array(char **str);
void		fill_alias(char *str, t_alias *alias);
void		free_array(char ***array);
int			end(char **str);

#endif