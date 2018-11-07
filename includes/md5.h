/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:04:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/07 19:04:31 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_P		0b00001
# define MD5_Q		0b00010
# define MD5_R		0b00100
# define MD5_S		0b01000
# define MD5_END	0b10000

# include "libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <errno.h>

# include <sys/stat.h>

typedef struct	s_md5_flags
{
	uint8_t		flag;
	char		c;
}				t_md5_flags;

int		md5(int argc, char **argv);

#endif
