/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:47:43 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/12 13:37:12 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static void	sha256_process_1(t_sha256_env *e, t_sha256_context *context)
{
	int				t;

	t = 16;
	while (t < 64)
	{
		e->w[t] = sha256_sigma3(e->w[t - 2]) + e->w[t - 7];
		e->w[t] += sha256_sigma2(e->w[t - 15]) + e->w[t - 16];
		t++;
	}
	e->a = context->intermediate_hash[0];
	e->b = context->intermediate_hash[1];
	e->c = context->intermediate_hash[2];
	e->d = context->intermediate_hash[3];
	e->e = context->intermediate_hash[4];
	e->f = context->intermediate_hash[5];
	e->g = context->intermediate_hash[6];
	e->h = context->intermediate_hash[7];
}

static void	sha256_process_2(t_sha256_env *e)
{
	int				t;
	uint32_t		temp1;
	uint32_t		temp2;

	t = 0;
	while (t < 64)
	{
		temp1 = e->h + sha256_sigma1(e->e) + ((e->e & e->f) ^ ((~e->e) & e->g));
		temp1 += sha256_k(t) + e->w[t];
		temp2 = sha256_sigma0(e->a);
		temp2 += ((e->a & e->b) ^ (e->a & e->c) ^ (e->b & e->c));
		e->h = e->g;
		e->g = e->f;
		e->f = e->e;
		e->e = e->d + temp1;
		e->d = e->c;
		e->c = e->b;
		e->b = e->a;
		e->a = temp1 + temp2;
		t++;
	}
}

void		sha256_process_message_block(t_sha256_context *context)
{
	int				t;
	int				t4;
	t_sha256_env	e;

	t = -1;
	t4 = 0;
	while (++t < 16)
	{
		e.w[t] = (((uint32_t)context->message_block[t4]) << 24) |
				(((uint32_t)context->message_block[t4 + 1]) << 16) |
				(((uint32_t)context->message_block[t4 + 2]) << 8) |
				(((uint32_t)context->message_block[t4 + 3]));
		t4 += 4;
	}
	sha256_process_1(&e, context);
	sha256_process_2(&e);
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
