/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:40:31 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/12 12:46:05 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

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
