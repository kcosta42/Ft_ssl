/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_digest_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:00:01 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:16:16 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

uint32_t	md5_rotate_left(uint32_t x, uint32_t n)
{
	return (((x) << (n)) | ((x) >> (32 - (n))));
}

void		md5_encode(uint8_t *output, uint32_t *input, uint32_t len)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (uint8_t)(input[i] & 0xff);
		output[j + 1] = (uint8_t)((input[i] >> 8) & 0xff);
		output[j + 2] = (uint8_t)((input[i] >> 16) & 0xff);
		output[j + 3] = (uint8_t)((input[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void		md5_decode(uint32_t *output, uint8_t *input, uint32_t len)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8)
		| (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
		i++;
		j += 4;
	}
}

uint8_t		*md5_padding(void)
{
	static uint8_t	padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	return ((uint8_t*)padding);
}
