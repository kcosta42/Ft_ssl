/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:11:12 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/07 16:46:52 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_string.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	size;

	if (!s)
		return ;
	size = ft_strlen(s);
	write(fd, s, size);
}
