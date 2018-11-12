/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:01:21 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/12 13:15:16 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

int			sha256_addlength(t_sha256_context *context, uint32_t length)
{
	uint32_t	addtemp;

	addtemp = context->length_low;
	return (context->corrupted = ((context->length_low += length) < addtemp)
			&& (++context->length_high == 0) ?
				SHA256_INPUT_TOO_LONG : context->corrupted);
}

uint32_t	sha256_k(uint8_t idx)
{
	static const uint32_t	k[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
		0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
		0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
		0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
		0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
		0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
		0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
		0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
		0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
		0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	return (k[idx]);
}

void		sha256_pad_message(t_sha256_context *context, uint8_t pad_byte)
{
	if (context->message_block_index >= (SHA256_MESSAGE_BLOCK_SIZE - 8))
	{
		context->message_block[context->message_block_index++] = pad_byte;
		while (context->message_block_index < SHA256_MESSAGE_BLOCK_SIZE)
			context->message_block[context->message_block_index++] = 0;
		sha256_process_message_block(context);
	}
	else
		context->message_block[context->message_block_index++] = pad_byte;
	while (context->message_block_index < (SHA256_MESSAGE_BLOCK_SIZE - 8))
		context->message_block[context->message_block_index++] = 0;
	context->message_block[56] = (uint8_t)(context->length_high >> 24);
	context->message_block[57] = (uint8_t)(context->length_high >> 16);
	context->message_block[58] = (uint8_t)(context->length_high >> 8);
	context->message_block[59] = (uint8_t)(context->length_high);
	context->message_block[60] = (uint8_t)(context->length_low >> 24);
	context->message_block[61] = (uint8_t)(context->length_low >> 16);
	context->message_block[62] = (uint8_t)(context->length_low >> 8);
	context->message_block[63] = (uint8_t)(context->length_low);
	sha256_process_message_block(context);
}

void		sha256_finalize(t_sha256_context *context, uint8_t pad_byte)
{
	int i;

	sha256_pad_message(context, pad_byte);
	i = 0;
	while (i < SHA256_MESSAGE_BLOCK_SIZE)
	{
		context->message_block[i] = 0;
		i++;
	}
	context->length_high = 0;
	context->length_low = 0;
	context->computed = 1;
}
