/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:11:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/23 23:20:44 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	repport_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (-1);
}
/*
int	repport_err_clear_strtab(char ***tab)
{
	if (tab)
		strtab_clear(&tab);
	return (repport_error());
}
*/
