/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:25:17 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 12:06:39 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

# include "md5.h"
# include "sha256.h"

# include <string.h>

typedef struct	s_digest
{
	size_t		cmdlen;
	char		*cmd;
	int			(*exec)(int, char **);
}				t_digest;

#endif
