/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:07:58 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 12:06:24 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static int	usage(void)
{
	ft_putendl("sha256: option requires an argument -- s");
	ft_putendl("Usage: sha256 [-pqrtx] [-s string] [files ...]");
	return (0);
}

int			sha256(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	usage();
	return (0);
}
