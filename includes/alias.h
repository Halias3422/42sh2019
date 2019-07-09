/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/11 16:17:46 by mateodelarb  #+#   ##    ##    #+#       */
/*   Updated: 2019/07/09 08:08:30 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H


# include "../libft/includes/ft_str.h"
# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_unix.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/ft_mem.h"
# include "../libft/includes/ft_printf_err.h"

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

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            free_file.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void        free_list(t_alias *alias);
void		free_ar(char **str);
void		free_all_the_ar(char ***array);
#endif