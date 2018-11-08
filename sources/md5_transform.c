/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:43:13 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 19:00:58 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	md5_transform_1(t_md5_env *e)
{
	FF(e->a, e->b, e->c, e->d, e->x[ 0], S11, 0xd76aa478);
	FF(e->d, e->a, e->b, e->c, e->x[ 1], S12, 0xe8c7b756);
	FF(e->c, e->d, e->a, e->b, e->x[ 2], S13, 0x242070db);
	FF(e->b, e->c, e->d, e->a, e->x[ 3], S14, 0xc1bdceee);
	FF(e->a, e->b, e->c, e->d, e->x[ 4], S11, 0xf57c0faf);
	FF(e->d, e->a, e->b, e->c, e->x[ 5], S12, 0x4787c62a);
	FF(e->c, e->d, e->a, e->b, e->x[ 6], S13, 0xa8304613);
	FF(e->b, e->c, e->d, e->a, e->x[ 7], S14, 0xfd469501);
	FF(e->a, e->b, e->c, e->d, e->x[ 8], S11, 0x698098d8);
	FF(e->d, e->a, e->b, e->c, e->x[ 9], S12, 0x8b44f7af);
	FF(e->c, e->d, e->a, e->b, e->x[10], S13, 0xffff5bb1);
	FF(e->b, e->c, e->d, e->a, e->x[11], S14, 0x895cd7be);
	FF(e->a, e->b, e->c, e->d, e->x[12], S11, 0x6b901122);
	FF(e->d, e->a, e->b, e->c, e->x[13], S12, 0xfd987193);
	FF(e->c, e->d, e->a, e->b, e->x[14], S13, 0xa679438e);
	FF(e->b, e->c, e->d, e->a, e->x[15], S14, 0x49b40821);
}

static void md5_transform_2(t_md5_env *e)
{
	GG(e->a, e->b, e->c, e->d, e->x[ 1], S21, 0xf61e2562);
	GG(e->d, e->a, e->b, e->c, e->x[ 6], S22, 0xc040b340);
	GG(e->c, e->d, e->a, e->b, e->x[11], S23, 0x265e5a51);
	GG(e->b, e->c, e->d, e->a, e->x[ 0], S24, 0xe9b6c7aa);
	GG(e->a, e->b, e->c, e->d, e->x[ 5], S21, 0xd62f105d);
	GG(e->d, e->a, e->b, e->c, e->x[10], S22,  0x2441453);
	GG(e->c, e->d, e->a, e->b, e->x[15], S23, 0xd8a1e681);
	GG(e->b, e->c, e->d, e->a, e->x[ 4], S24, 0xe7d3fbc8);
	GG(e->a, e->b, e->c, e->d, e->x[ 9], S21, 0x21e1cde6);
	GG(e->d, e->a, e->b, e->c, e->x[14], S22, 0xc33707d6);
	GG(e->c, e->d, e->a, e->b, e->x[ 3], S23, 0xf4d50d87);
	GG(e->b, e->c, e->d, e->a, e->x[ 8], S24, 0x455a14ed);
	GG(e->a, e->b, e->c, e->d, e->x[13], S21, 0xa9e3e905);
	GG(e->d, e->a, e->b, e->c, e->x[ 2], S22, 0xfcefa3f8);
	GG(e->c, e->d, e->a, e->b, e->x[ 7], S23, 0x676f02d9);
	GG(e->b, e->c, e->d, e->a, e->x[12], S24, 0x8d2a4c8a);

}

static void	md5_transform_3(t_md5_env *e)
{
	HH(e->a, e->b, e->c, e->d, e->x[ 5], S31, 0xfffa3942);
	HH(e->d, e->a, e->b, e->c, e->x[ 8], S32, 0x8771f681);
	HH(e->c, e->d, e->a, e->b, e->x[11], S33, 0x6d9d6122);
	HH(e->b, e->c, e->d, e->a, e->x[14], S34, 0xfde5380c);
	HH(e->a, e->b, e->c, e->d, e->x[ 1], S31, 0xa4beea44);
	HH(e->d, e->a, e->b, e->c, e->x[ 4], S32, 0x4bdecfa9);
	HH(e->c, e->d, e->a, e->b, e->x[ 7], S33, 0xf6bb4b60);
	HH(e->b, e->c, e->d, e->a, e->x[10], S34, 0xbebfbc70);
	HH(e->a, e->b, e->c, e->d, e->x[13], S31, 0x289b7ec6);
	HH(e->d, e->a, e->b, e->c, e->x[ 0], S32, 0xeaa127fa);
	HH(e->c, e->d, e->a, e->b, e->x[ 3], S33, 0xd4ef3085);
	HH(e->b, e->c, e->d, e->a, e->x[ 6], S34, 0x04881d05);
	HH(e->a, e->b, e->c, e->d, e->x[ 9], S31, 0xd9d4d039);
	HH(e->d, e->a, e->b, e->c, e->x[12], S32, 0xe6db99e5);
	HH(e->c, e->d, e->a, e->b, e->x[15], S33, 0x1fa27cf8);
	HH(e->b, e->c, e->d, e->a, e->x[ 2], S34, 0xc4ac5665);

}

static void	md5_transform_4(t_md5_env *e)
{
	II(e->a, e->b, e->c, e->d, e->x[ 0], S41, 0xf4292244);
	II(e->d, e->a, e->b, e->c, e->x[ 7], S42, 0x432aff97);
	II(e->c, e->d, e->a, e->b, e->x[14], S43, 0xab9423a7);
	II(e->b, e->c, e->d, e->a, e->x[ 5], S44, 0xfc93a039);
	II(e->a, e->b, e->c, e->d, e->x[12], S41, 0x655b59c3);
	II(e->d, e->a, e->b, e->c, e->x[ 3], S42, 0x8f0ccc92);
	II(e->c, e->d, e->a, e->b, e->x[10], S43, 0xffeff47d);
	II(e->b, e->c, e->d, e->a, e->x[ 1], S44, 0x85845dd1);
	II(e->a, e->b, e->c, e->d, e->x[ 8], S41, 0x6fa87e4f);
	II(e->d, e->a, e->b, e->c, e->x[15], S42, 0xfe2ce6e0);
	II(e->c, e->d, e->a, e->b, e->x[ 6], S43, 0xa3014314);
	II(e->b, e->c, e->d, e->a, e->x[13], S44, 0x4e0811a1);
	II(e->a, e->b, e->c, e->d, e->x[ 4], S41, 0xf7537e82);
	II(e->d, e->a, e->b, e->c, e->x[11], S42, 0xbd3af235);
	II(e->c, e->d, e->a, e->b, e->x[ 2], S43, 0x2ad7d2bb);
	II(e->b, e->c, e->d, e->a, e->x[ 9], S44, 0xeb86d391);
}

void	md5_transform(uint32_t state[4], uint8_t block[64])
{
	t_md5_env	e;

	e.a = state[0];
	e.b = state[1];
	e.c = state[2];
	e.d = state[3];
	decode(e.x, block, 64);
	md5_transform_1(&e);
	md5_transform_2(&e);
	md5_transform_3(&e);
	md5_transform_4(&e);
	state[0] += e.a;
	state[1] += e.b;
	state[2] += e.c;
	state[3] += e.d;
	ft_memset ((uint8_t *)e.x, 0, sizeof(e.x));
}
