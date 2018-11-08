/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_digest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:38:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 18:48:20 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static uint8_t	PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void	md5_init(t_md5_ctx *context)
{
  context->count[0] = 0;
  context->count[1] = 0;

  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

void	md5_update(t_md5_ctx *context, uint8_t	*input, uint32_t inputLen)
{
	uint32_t	i;
	uint32_t	index;
	uint32_t	partLen;

	index = (uint32_t)((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += (inputLen << 3)) < (inputLen << 3))
		context->count[1]++;
	context->count[1] += (inputLen >> 29);
	partLen = 64 - index;
	if (inputLen >= partLen)
	{
		ft_memcpy((uint8_t*)&context->buffer[index], (uint8_t*)input, partLen);
 		md5_transform (context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			md5_transform (context->state, &input[i]);

		index = 0;
	}
	else
		i = 0;
	ft_memcpy((uint8_t*)&context->buffer[index], (uint8_t*)&input[i], inputLen - i);
}

void	md5_final(uint8_t digest[16], t_md5_ctx *context)
{
	uint8_t bits[8];
	uint32_t index, padLen;

	encode (bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	md5_update (context, PADDING, padLen);
	md5_update (context, bits, 8);
	encode (digest, context->state, 16);
	ft_memset ((uint8_t*)context, 0, sizeof(*context));
}

static void md5_print (unsigned char digest[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
		ft_printf("%02x", digest[i]);
}

char 	*md5_digest(char *str, size_t len)
{
	t_md5_ctx	context;
	uint8_t		digest[16];

	md5_init(&context);
	md5_update(&context, (uint8_t *)str, len);
	md5_final(digest, &context);

	md5_print(digest);
	return (NULL);
}
