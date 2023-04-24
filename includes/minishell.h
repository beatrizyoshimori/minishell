/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/24 20:16:05 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
// # include <readline/history.h>

typedef struct s_ms
{
	
}	t_ms;

typedef struct s_cmd
{
	char			*cmd;
	char			type;
	struct s_cmd	*next;
}	t_cmd;

#endif