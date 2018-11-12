/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:12:07 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/12 12:06:13 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static uint32_t	g_sha256_h0[SHA256_HASH_SIZE / 4] = {
	0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
	0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
};

int		sha256_rotr(uint32_t bits, uint32_t word)
{
	return ((((word) >> (bits)) | ((word) << (32 - (bits)))));
}

int		sha256_sigma0(uint32_t w)
{
	return (sha256_rotr(2, w) ^ sha256_rotr(13, w) ^ sha256_rotr(22, w));
}

int		sha256_sigma1(uint32_t w)
{
	return (sha256_rotr(6, w) ^ sha256_rotr(11, w) ^ sha256_rotr(25, w));
}

int		sha256_sigma2(uint32_t word)
{
	return (sha256_rotr(7, word) ^ sha256_rotr(18, word) ^ (word >> 3));
}

int		sha256_sigma3(uint32_t word)
{
	return (sha256_rotr(17, word) ^ sha256_rotr(19, word) ^ (word >> 10));
}

int				sha256_addlength(t_sha256_context *context, uint32_t length)
{
	uint32_t	addtemp;

	addtemp = context->length_low;
	return (context->corrupted = ((context->length_low += length) < addtemp)
			&& (++context->length_high == 0) ?
				SHA256_INPUT_TOO_LONG : context->corrupted);
}

int				sha256_reset(t_sha256_context *context)
{
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

static uint32_t	sha256_k(uint8_t idx)
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

static void		sha256_process_message_block(t_sha256_context *context)
{
	int				t;
	int				t4;
	uint32_t		temp1;
	uint32_t		temp2;
	t_sha256_env	e;

	t = 0;
	t4 = 0;
	while (t < 16)
	{
		e.w[t] = (((uint32_t)context->message_block[t4]) << 24) |
				(((uint32_t)context->message_block[t4 + 1]) << 16) |
				(((uint32_t)context->message_block[t4 + 2]) << 8) |
				(((uint32_t)context->message_block[t4 + 3]));
		t++;
		t4 += 4;
	}
	t = 16;
	while (t < 64)
	{
		e.w[t] = sha256_sigma3(e.w[t - 2]) + e.w[t - 7] + sha256_sigma2(e.w[t - 15]) + e.w[t - 16];
		t++;
	}
	e.a = context->intermediate_hash[0];
	e.b = context->intermediate_hash[1];
	e.c = context->intermediate_hash[2];
	e.d = context->intermediate_hash[3];
	e.e = context->intermediate_hash[4];
	e.f = context->intermediate_hash[5];
	e.g = context->intermediate_hash[6];
	e.h = context->intermediate_hash[7];
	t = 0;
	while (t < 64)
	{
		temp1 = e.h + sha256_sigma1(e.e) + ((e.e & e.f) ^ ((~e.e) & e.g)) + sha256_k(t) + e.w[t];
		temp2 = sha256_sigma0(e.a) + ((e.a & e.b) ^ (e.a & e.c) ^ (e.b & e.c));
		e.h = e.g;
		e.g = e.f;
		e.f = e.e;
		e.e = e.d + temp1;
		e.d = e.c;
		e.c = e.b;
		e.b = e.a;
		e.a = temp1 + temp2;
		t++;
	}
	context->intermediate_hash[0] += e.a;
	context->intermediate_hash[1] += e.b;
	context->intermediate_hash[2] += e.c;
	context->intermediate_hash[3] += e.d;
	context->intermediate_hash[4] += e.e;
	context->intermediate_hash[5] += e.f;
	context->intermediate_hash[6] += e.g;
	context->intermediate_hash[7] += e.h;
	context->message_block_index = 0;
}

int				sha256_input(t_sha256_context *context,
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

static void		sha256_pad_message(t_sha256_context *context, uint8_t pad_byte)
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

static void		sha256_finalize(t_sha256_context *context, uint8_t pad_byte)
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

int				sha256_finalbits(t_sha256_context *context,
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

int				sha256_result(t_sha256_context *context,
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
