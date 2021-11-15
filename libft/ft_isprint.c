/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:21:10 by oboualla          #+#    #+#             */
/*   Updated: 2019/10/28 04:00:17 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(int arg)
{
	if (arg >= ' ' && arg <= '~')
		return (1);
	return (0);
}