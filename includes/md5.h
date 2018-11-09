/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:04:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:17:57 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_P		0b000001
# define MD5_Q		0b000010
# define MD5_R		0b000100
# define MD5_S		0b001000
# define MD5_END	0b010000
# define MD5_INPUT	0b100000

# define S11 7
# define S12 12
# define S13 17
# define S14 22
# define S21 5
# define S22 9
# define S23 14
# define S24 20
# define S31 4
# define S32 11
# define S33 16
# define S34 23
# define S41 6
# define S42 10
# define S43 15
# define S44 21

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

typedef struct	s_md5_ctx
{
	uint32_t	state[4];
	uint32_t	count[2];
	uint8_t		buffer[64];
}				t_md5_ctx;

typedef struct	s_md5_env
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	x[16];
}				t_md5_env;

char			*md5_digest(char *str, size_t len);
uint8_t			*md5_padding(void);

void			md5_transform(uint32_t state[4], uint8_t block[64]);
void			md5_ff(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac);
void			md5_gg(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac);
void			md5_hh(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac);
void			md5_ii(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac);

uint32_t		md5_rotate_left(uint32_t x, uint32_t n);
void			md5_encode(uint8_t *output, uint32_t *input, uint32_t len);
void			md5_decode(uint32_t *output, uint8_t *input, uint32_t len);

int				md5_parse_args(int argc, char **argv);

int				md5_manage_stdin(uint8_t *flags, uint8_t echo);
int				md5_manage_file(uint8_t *flags, char *filename);
int				md5_manage_string(uint8_t *f, char *str, char *c, size_t len);

#endif
