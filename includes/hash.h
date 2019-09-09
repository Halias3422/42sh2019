/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 13:31:38 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 15:45:44 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

#include "termcaps.h"

typedef struct		s_hash
{
	char			*path;
	char			*exec;
	int				hit;
	struct s_hash	*next;
}					t_hash;

void	fill_hash_table(char **tab_var, char *path, char **arg);
void	check_path_hash(char **tab_var, char *path, char **arg);

#endif
