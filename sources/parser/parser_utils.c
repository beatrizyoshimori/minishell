/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:30:57 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/01 20:31:17 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(t_token **token_list, t_ms **ms, char c)
{
	printf("bilu: syntax error near unexpected token ");
	if (c == '\n')
		printf("'newline'\n");
	else
		printf("'%c'\n", c);
	exit_program(token_list, ms);
}