/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:04:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 19:05:32 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_P		0b00001
# define MD5_Q		0b00010
# define MD5_R		0b00100
# define MD5_S		0b01000
# define MD5_END	0b10000

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

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = rotate_left ((a), (s)); \
	(a) += (b); \
}

#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = rotate_left ((a), (s)); \
	(a) += (b); \
}

#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = rotate_left ((a), (s)); \
	(a) += (b); \
}

#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = rotate_left ((a), (s)); \
	(a) += (b); \
}

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

int				md5(int argc, char **argv);
char 			*md5_digest(char *str, size_t len);
void			md5_transform(uint32_t state[4], uint8_t block[64]);
void			encode(uint8_t *output, uint32_t *input, uint32_t len);
void			decode(uint32_t *output, uint8_t *input, uint32_t len);

uint32_t		rotate_left(uint32_t x, uint32_t n);

int				parse_args(int argc, char **argv);

int				manage_stdin(uint8_t *flags, uint8_t echo);
int				manage_file(uint8_t *flags, char *filename);
int				manage_string(uint8_t *flags, char *str, char *c, size_t len);

#endif
