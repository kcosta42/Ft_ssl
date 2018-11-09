/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_digest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:38:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:16:27 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	md5_print(unsigned char digest[16])
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
}

static void	md5_init(t_md5_ctx *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

static void	md5_update(t_md5_ctx *context, uint8_t *input, uint32_t input_len)
{
	uint32_t	i;
	uint32_t	index;
	uint32_t	part_len;

	index = (uint32_t)((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += (input_len << 3)) < (input_len << 3))
		context->count[1]++;
	context->count[1] += (input_len >> 29);
	part_len = 64 - index;
	if (input_len >= part_len)
	{
		ft_memcpy((uint8_t*)&context->buffer[index], input, part_len);
		md5_transform(context->state, context->buffer);
		i = part_len;
		while (i + 63 < input_len)
		{
			md5_transform(context->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy((uint8_t*)&context->buffer[index], &input[i], input_len - i);
}

static void	md5_final(uint8_t digest[16], t_md5_ctx *context)
{
	uint8_t		bits[8];
	uint32_t	index;
	uint32_t	pad_len;

	md5_encode(bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, md5_padding(), pad_len);
	md5_update(context, bits, 8);
	md5_encode(digest, context->state, 16);
	ft_memset((uint8_t*)context, 0, sizeof(*context));
}

char		*md5_digest(char *str, size_t len)
{
	t_md5_ctx	context;
	uint8_t		digest[16];

	md5_init(&context);
	md5_update(&context, (uint8_t *)str, len);
	md5_final(digest, &context);
	md5_print(digest);
	return (NULL);
}
