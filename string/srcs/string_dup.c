/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:55:17 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:56:02 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*string_dup(char *str)
{
	return (string_new(STRING(str)->str));
}
