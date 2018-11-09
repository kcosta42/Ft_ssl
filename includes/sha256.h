/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:04:00 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 17:58:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <errno.h>

# include <sys/stat.h>

# define SHA256_P		0b000001
# define SHA256_Q		0b000010
# define SHA256_R		0b000100
# define SHA256_S		0b001000
# define SHA256_END		0b010000
# define SHA256_INPUT	0b100000

# define SHA256_HASH_SIZE			32
# define SHA256_MESSAGE_BLOCK_SIZE	64

# define SHA256_SUCCESS			0
# define SHA256_NULL			1
# define SHA256_INPUT_TOO_LONG	2
# define SHA256_STATE_ERROR		3
# define SHA256_BAD_PARAM		4

#define SHA_Ch(x,y,z)	(((x) & (y)) ^ ((~(x)) & (z)))
#define SHA_Maj(x,y,z)	(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define SHA256_SHR(bits,word)	((word) >> (bits))
#define SHA256_ROTL(bits,word)	(((word) << (bits)) | ((word) >> (32-(bits))))
#define SHA256_ROTR(bits,word)	(((word) >> (bits)) | ((word) << (32-(bits))))

#define SHA256_SIGMA0(word)	(SHA256_ROTR( 2,word) ^ SHA256_ROTR(13,word) ^ SHA256_ROTR(22,word))
#define SHA256_SIGMA1(word)	(SHA256_ROTR( 6,word) ^ SHA256_ROTR(11,word) ^ SHA256_ROTR(25,word))
#define SHA256_sigma0(word)	(SHA256_ROTR( 7,word) ^ SHA256_ROTR(18,word) ^ SHA256_SHR( 3,word))
#define SHA256_sigma1(word)	(SHA256_ROTR(17,word) ^ SHA256_ROTR(19,word) ^ SHA256_SHR(10,word))

static uint32_t addTemp;
#define sha256_addlength(context, length)               \
  (addTemp = (context)->length_low, (context)->corrupted = \
    (((context)->length_low += (length)) < addTemp) &&     \
    (++(context)->length_high == 0) ? SHA256_INPUT_TOO_LONG :    \
                                      (context)->corrupted )

typedef struct	s_sha256_flags
{
	uint8_t		flag;
	char		c;
}				t_sha256_flags;

typedef struct	s_sha256_context
{
	uint32_t	intermediate_hash[SHA256_HASH_SIZE / 4];
	uint32_t	length_high;
	uint32_t	length_low;
	uint16_t	message_block_index;
	uint8_t		message_block[SHA256_MESSAGE_BLOCK_SIZE];
	int			computed;
	int			corrupted;
}				t_sha256_context;

typedef struct	s_sha256_env
{
	uint32_t	w[64];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}				t_sha256_env;

char			*sha256_digest(char *str, size_t len);

int				sha256_parse_args(int argc, char **argv);

int				sha256_manage_stdin(uint8_t *flags, uint8_t echo);
int				sha256_manage_file(uint8_t *flags, char *filename);
int				sha256_manage_string(uint8_t *f, char *s, char *c, size_t l);
#endif
