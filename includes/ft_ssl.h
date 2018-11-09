/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:25:17 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 13:35:14 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

# include <string.h>

typedef struct	s_digest
{
	size_t		cmdlen;
	char		*cmd;
	int			(*exec)(int, char **);
}				t_digest;

int				md5(int argc, char **argv);
int				sha256(int argc, char **argv);

#endif
