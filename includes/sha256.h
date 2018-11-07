/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:04:00 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/07 18:10:57 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# define SHA256_P 0x01
# define SHA256_Q 0x02
# define SHA256_R 0x03
# define SHA256_S 0x04

# include "libft.h"

int		sha256(int argc, char **argv);

#endif
