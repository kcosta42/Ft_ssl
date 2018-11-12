/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:12:07 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/12 13:04:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static int		sha256_reset(t_sha256_context *context)
{
	static uint32_t	g_sha256_h0[SHA256_HASH_SIZE / 4] = {
		0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
		0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
	};

	if (!context)
		return (SHA256_NULL);
	context->length_high = 0;
	context->length_low = 0;
	context->message_block_index = 0;
	context->intermediate_hash[0] = g_sha256_h0[0];
	context->intermediate_hash[1] = g_sha256_h0[1];
	context->intermediate_hash[2] = g_sha256_h0[2];
	context->intermediate_hash[3] = g_sha256_h0[3];
	context->intermediate_hash[4] = g_sha256_h0[4];
	context->intermediate_hash[5] = g_sha256_h0[5];
	context->intermediate_hash[6] = g_sha256_h0[6];
	context->intermediate_hash[7] = g_sha256_h0[7];
	context->computed = 0;
	context->corrupted = SHA256_SUCCESS;
	return (SHA256_SUCCESS);
}

static int		sha256_input(t_sha256_context *context,
	const uint8_t *message_array, unsigned int length)
{
	if (!context)
		return (SHA256_NULL);
	if (!length)
		return (SHA256_SUCCESS);
	if (!message_array)
		return (SHA256_NULL);
	if (context->computed)
		return (context->corrupted = SHA256_STATE_ERROR);
	if (context->corrupted)
		return (context->corrupted);
	while (length--)
	{
		context->message_block[context->message_block_index++] = *message_array;
		if ((sha256_addlength(context, 8) == SHA256_SUCCESS)
			&& (context->message_block_index == SHA256_MESSAGE_BLOCK_SIZE))
			sha256_process_message_block(context);
		message_array++;
	}
	return (context->corrupted);
}

static int		sha256_finalbits(t_sha256_context *context,
	uint8_t message_bits, unsigned int length)
{
	static uint8_t masks[8] = {
		0x00, 0x80, 0xC0, 0xE0,
		0xF0, 0xF8, 0xFC, 0xFE
	};
	static uint8_t markbit[8] = {
		0x80, 0x40, 0x20, 0x10,
		0x08, 0x04, 0x02, 0x01
	};

	if (!context)
		return (SHA256_NULL);
	if (!length)
		return (SHA256_SUCCESS);
	if (context->corrupted)
		return (context->corrupted);
	if (context->computed)
		return (context->corrupted = SHA256_STATE_ERROR);
	if (length >= 8)
		return (context->corrupted = SHA256_BAD_PARAM);
	sha256_addlength(context, length);
	sha256_finalize(context,
		(uint8_t)((message_bits & masks[length]) | markbit[length]));
	return (context->corrupted);
}

static int		sha256_result(t_sha256_context *context,
	uint8_t message_digest[SHA256_HASH_SIZE])
{
	int i;

	if (!context)
		return (SHA256_NULL);
	if (!message_digest)
		return (SHA256_NULL);
	if (context->corrupted)
		return (context->corrupted);
	if (!context->computed)
		sha256_finalize(context, 0x80);
	i = 0;
	while (i < SHA256_HASH_SIZE)
	{
		message_digest[i] = (uint8_t)
			(context->intermediate_hash[i >> 2] >> 8 * (3 - (i & 0x03)));
		i++;
	}
	return (SHA256_SUCCESS);
}

char			*sha256_digest(char *str, size_t len)
{
	t_sha256_context	context;
	uint8_t				message_digest[SHA256_HASH_SIZE];
	uint8_t				i;

	sha256_reset(&context);
	sha256_input(&context, (uint8_t *)str, len);
	sha256_finalbits(&context, 0, 0);
	sha256_result(&context, message_digest);
	i = 0;
	while (i < SHA256_HASH_SIZE)
	{
		ft_printf("%02x", message_digest[i]);
		i++;
	}
	return (NULL);
}
