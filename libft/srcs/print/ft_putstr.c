/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:50:04 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/07 16:47:08 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_string.h"

void	ft_putstr(char const *s)
{
	size_t	size;

	if (!s)
		return ;
	size = ft_strlen(s);
	write(1, s, size);
}
