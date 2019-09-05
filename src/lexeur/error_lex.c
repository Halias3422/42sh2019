#include "../../includes/check_error.h"
#include "../../includes/lexeur.h"

/*
int			error_before_lexer(char **str)
{
	int	i;
	int	j;
	int	token;

	token = -1;

	i = 0;
	while (str[i])
	{
		printf("%d: |%s|\n", i, str[i]);
		j = 0;
		while (str[i][j])
		{
			if (ft_strlen(str[i]))
				token = find_token(str[i], j);
			printf("->%d\n", token);
			j++;
		}
		i++;
	}
	return (0);
}
*/

int			token_verification(t_lexeur *lex)
{
	if (lex->word != NULL)
		return (0);
	if (lex->token > 3 && lex->token != 10)
		return (1);
	return (2);
}

int			error_lex(t_lexeur **lex)
{
	int i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (token_verification(lex[i]) == 2
			&& token_verification(lex[i+1]) == 2)
		{
			ft_printf_err("zsh: parse error near ");
			print_lexer(lex[i]);
			return (-1);
		}
		i++;
	}
	lex = NULL;
	return (0);
}
