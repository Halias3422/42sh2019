/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bjuarez <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 08:51:54 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 10:50:54 by bjuarez     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct	s_token
{
	int		quote;
	int		dquote;
	int		bquote;
	int		cmdsubst;
	int		subsh;
	int		cursh;
	int		cmdand;
	int		cmdor;
	int		pipe;
}				t_token;

int				verif_inter(char *str);
int				find_last_inter(char *input);
int				find_err_quote(char *input, char c, char d);
char			*print_inter(char *inter, char *str, char *str2, int mode);
void			check_enter(t_pos *pos);

#endif
