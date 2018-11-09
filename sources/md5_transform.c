/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:43:13 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:16:39 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	md5_transform_1(t_md5_env *e)
{
	md5_ff(e, e->x[0], S11, 0xd76aa478);
	md5_ff(e, e->x[1], S12, 0xe8c7b756);
	md5_ff(e, e->x[2], S13, 0x242070db);
	md5_ff(e, e->x[3], S14, 0xc1bdceee);
	md5_ff(e, e->x[4], S11, 0xf57c0faf);
	md5_ff(e, e->x[5], S12, 0x4787c62a);
	md5_ff(e, e->x[6], S13, 0xa8304613);
	md5_ff(e, e->x[7], S14, 0xfd469501);
	md5_ff(e, e->x[8], S11, 0x698098d8);
	md5_ff(e, e->x[9], S12, 0x8b44f7af);
	md5_ff(e, e->x[10], S13, 0xffff5bb1);
	md5_ff(e, e->x[11], S14, 0x895cd7be);
	md5_ff(e, e->x[12], S11, 0x6b901122);
	md5_ff(e, e->x[13], S12, 0xfd987193);
	md5_ff(e, e->x[14], S13, 0xa679438e);
	md5_ff(e, e->x[15], S14, 0x49b40821);
}

static void	md5_transform_2(t_md5_env *e)
{
	md5_gg(e, e->x[1], S21, 0xf61e2562);
	md5_gg(e, e->x[6], S22, 0xc040b340);
	md5_gg(e, e->x[11], S23, 0x265e5a51);
	md5_gg(e, e->x[0], S24, 0xe9b6c7aa);
	md5_gg(e, e->x[5], S21, 0xd62f105d);
	md5_gg(e, e->x[10], S22, 0x2441453);
	md5_gg(e, e->x[15], S23, 0xd8a1e681);
	md5_gg(e, e->x[4], S24, 0xe7d3fbc8);
	md5_gg(e, e->x[9], S21, 0x21e1cde6);
	md5_gg(e, e->x[14], S22, 0xc33707d6);
	md5_gg(e, e->x[3], S23, 0xf4d50d87);
	md5_gg(e, e->x[8], S24, 0x455a14ed);
	md5_gg(e, e->x[13], S21, 0xa9e3e905);
	md5_gg(e, e->x[2], S22, 0xfcefa3f8);
	md5_gg(e, e->x[7], S23, 0x676f02d9);
	md5_gg(e, e->x[12], S24, 0x8d2a4c8a);
}

static void	md5_transform_3(t_md5_env *e)
{
	md5_hh(e, e->x[5], S31, 0xfffa3942);
	md5_hh(e, e->x[8], S32, 0x8771f681);
	md5_hh(e, e->x[11], S33, 0x6d9d6122);
	md5_hh(e, e->x[14], S34, 0xfde5380c);
	md5_hh(e, e->x[1], S31, 0xa4beea44);
	md5_hh(e, e->x[4], S32, 0x4bdecfa9);
	md5_hh(e, e->x[7], S33, 0xf6bb4b60);
	md5_hh(e, e->x[10], S34, 0xbebfbc70);
	md5_hh(e, e->x[13], S31, 0x289b7ec6);
	md5_hh(e, e->x[0], S32, 0xeaa127fa);
	md5_hh(e, e->x[3], S33, 0xd4ef3085);
	md5_hh(e, e->x[6], S34, 0x04881d05);
	md5_hh(e, e->x[9], S31, 0xd9d4d039);
	md5_hh(e, e->x[12], S32, 0xe6db99e5);
	md5_hh(e, e->x[15], S33, 0x1fa27cf8);
	md5_hh(e, e->x[2], S34, 0xc4ac5665);
}

static void	md5_transform_4(t_md5_env *e)
{
	md5_ii(e, e->x[0], S41, 0xf4292244);
	md5_ii(e, e->x[7], S42, 0x432aff97);
	md5_ii(e, e->x[14], S43, 0xab9423a7);
	md5_ii(e, e->x[5], S44, 0xfc93a039);
	md5_ii(e, e->x[12], S41, 0x655b59c3);
	md5_ii(e, e->x[3], S42, 0x8f0ccc92);
	md5_ii(e, e->x[10], S43, 0xffeff47d);
	md5_ii(e, e->x[1], S44, 0x85845dd1);
	md5_ii(e, e->x[8], S41, 0x6fa87e4f);
	md5_ii(e, e->x[15], S42, 0xfe2ce6e0);
	md5_ii(e, e->x[6], S43, 0xa3014314);
	md5_ii(e, e->x[13], S44, 0x4e0811a1);
	md5_ii(e, e->x[4], S41, 0xf7537e82);
	md5_ii(e, e->x[11], S42, 0xbd3af235);
	md5_ii(e, e->x[2], S43, 0x2ad7d2bb);
	md5_ii(e, e->x[9], S44, 0xeb86d391);
}

void		md5_transform(uint32_t state[4], uint8_t block[64])
{
	t_md5_env	e;

	e.a = state[0];
	e.b = state[1];
	e.c = state[2];
	e.d = state[3];
	md5_decode(e.x, block, 64);
	md5_transform_1(&e);
	md5_transform_2(&e);
	md5_transform_3(&e);
	md5_transform_4(&e);
	state[0] += e.a;
	state[1] += e.b;
	state[2] += e.c;
	state[3] += e.d;
	ft_memset((uint8_t *)e.x, 0, sizeof(e.x));
}
