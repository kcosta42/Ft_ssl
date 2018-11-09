/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:43:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:16:34 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static uint32_t	md5_rotate(uint32_t a, uint32_t b, uint32_t s)
{
	a = md5_rotate_left(a, s);
	a += b;
	return (a);
}

void			md5_ff(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac)
{
	static	uint8_t	idx = 0;

	if (idx == 0 || idx == 4 || idx == 8 || idx == 12)
	{
		e->a += ((e->b & e->c) | (~(e->b) & e->d)) + x + ac;
		e->a = md5_rotate(e->a, e->b, s);
	}
	if (idx == 1 || idx == 5 || idx == 9 || idx == 13)
	{
		e->d += ((e->a & e->b) | (~(e->a) & e->c)) + x + ac;
		e->d = md5_rotate(e->d, e->a, s);
	}
	if (idx == 2 || idx == 6 || idx == 10 || idx == 14)
	{
		e->c += ((e->d & e->a) | (~(e->d) & e->b)) + x + ac;
		e->c = md5_rotate(e->c, e->d, s);
	}
	if (idx == 3 || idx == 7 || idx == 11 || idx == 15)
	{
		e->b += ((e->c & e->d) | (~(e->c) & e->a)) + x + ac;
		e->b = md5_rotate(e->b, e->c, s);
	}
	idx = ++idx > 15 ? 0 : idx;
}

void			md5_gg(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac)
{
	static	uint8_t	idx = 0;

	if (idx == 0 || idx == 4 || idx == 8 || idx == 12)
	{
		e->a += ((e->b & e->d) | (e->c & ~(e->d))) + x + ac;
		e->a = md5_rotate(e->a, e->b, s);
	}
	if (idx == 1 || idx == 5 || idx == 9 || idx == 13)
	{
		e->d += ((e->a & e->c) | (e->b & ~(e->c))) + x + ac;
		e->d = md5_rotate(e->d, e->a, s);
	}
	if (idx == 2 || idx == 6 || idx == 10 || idx == 14)
	{
		e->c += ((e->d & e->b) | (e->a & ~(e->b))) + x + ac;
		e->c = md5_rotate(e->c, e->d, s);
	}
	if (idx == 3 || idx == 7 || idx == 11 || idx == 15)
	{
		e->b += ((e->c & e->a) | (e->d & ~(e->a))) + x + ac;
		e->b = md5_rotate(e->b, e->c, s);
	}
	idx = ++idx > 15 ? 0 : idx;
}

void			md5_hh(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac)
{
	static	uint8_t	idx = 0;

	if (idx == 0 || idx == 4 || idx == 8 || idx == 12)
	{
		e->a += (e->b ^ e->c ^ e->d) + x + ac;
		e->a = md5_rotate(e->a, e->b, s);
	}
	if (idx == 1 || idx == 5 || idx == 9 || idx == 13)
	{
		e->d += (e->a ^ e->b ^ e->c) + x + ac;
		e->d = md5_rotate(e->d, e->a, s);
	}
	if (idx == 2 || idx == 6 || idx == 10 || idx == 14)
	{
		e->c += (e->d ^ e->a ^ e->b) + x + ac;
		e->c = md5_rotate(e->c, e->d, s);
	}
	if (idx == 3 || idx == 7 || idx == 11 || idx == 15)
	{
		e->b += (e->c ^ e->d ^ e->a) + x + ac;
		e->b = md5_rotate(e->b, e->c, s);
	}
	idx = ++idx > 15 ? 0 : idx;
}

void			md5_ii(t_md5_env *e, uint32_t x, uint32_t s, uint32_t ac)
{
	static	uint8_t	idx = 0;

	if (idx == 0 || idx == 4 || idx == 8 || idx == 12)
	{
		e->a += (e->c ^ (e->b | ~(e->d))) + x + ac;
		e->a = md5_rotate(e->a, e->b, s);
	}
	if (idx == 1 || idx == 5 || idx == 9 || idx == 13)
	{
		e->d += (e->b ^ (e->a | ~(e->c))) + x + ac;
		e->d = md5_rotate(e->d, e->a, s);
	}
	if (idx == 2 || idx == 6 || idx == 10 || idx == 14)
	{
		e->c += (e->a ^ (e->d | ~(e->b))) + x + ac;
		e->c = md5_rotate(e->c, e->d, s);
	}
	if (idx == 3 || idx == 7 || idx == 11 || idx == 15)
	{
		e->b += (e->d ^ (e->c | ~(e->a))) + x + ac;
		e->b = md5_rotate(e->b, e->c, s);
	}
	idx = ++idx > 15 ? 0 : idx;
}
