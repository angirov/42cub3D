/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:36:24 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/15 16:37:06 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	rtd(double radians)
{
	return (radians * 180 / M_PI);
}

double	dtr(double degrees)
{
	return (degrees / 180 * M_PI);
}

double	ft_abs(double num)
{
	if (num >= 0)
		return (num);
	else
		return (-num);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
