/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mateodelarbre <mateodelarbre@student.le    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/11 16:17:46 by mateodelarb  #+#   ##    ##    #+#       */
/*   Updated: 2019/06/11 17:41:13 by mateodelarb ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

typedef struct s_alias_tempo
{
	char					*data;
	struct s_alias_tempo	*next;
} t_alias;


char		check_last_char(char *str);
int			cnt_array(char **str);
void		fill_array(char ***res, char ***array);
void		free_array(char ***array);
int			end(char **str);

#endif