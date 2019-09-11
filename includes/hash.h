/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 13:31:38 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 13:41:01 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "termcaps.h"
# include "builtin.h"
# define NB_KEY 100

typedef struct		s_hash
{
	char			*path;
	char			*exec;
	int				hit;
	struct s_hash	*next;
}					t_hash;

/*
**	HASH_C
*/

char				*check_path_hash(char **tab_var, char **arg, int i, char *ans);
char				*fill_hash_table(char *path, char **arg);
void				read_hash_table(t_hash **hash);

/*
**	HASH_TOOLS_C
*/

void				init_single_link(t_hash *hash, char *arg, char *path);
void				free_hash_table(void);
void				init_hash_links(t_hash **hash);
t_hash				**stock_hash(t_hash **to_stock, int usage);
unsigned short		get_key_of_exec(char *str);

#endif
