/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operculesanguinaire <operculesanguinair    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:36:11 by kevyn             #+#    #+#             */
/*   Updated: 2022/03/07 14:13:40 by operculesan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	get_error(int i)
{
	if (i == 1)
		write(2, ERROR1, ft_strlen(ERROR1));
	if (i == 2)
		write(2, ERROR2, ft_strlen(ERROR2));
	if (i == 3)
		write(2, ERROR3, ft_strlen(ERROR3));
	exit(0);
}
