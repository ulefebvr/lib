/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:55:22 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:55:22 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

char			*string_cat(char *str, char *add)
{
	char *tmp;

	tmp = STRING(str)->str;
	STRING(str)->str = str_join(STRING(str)->str, add);
	STRING(str)->len = str_len(STRING(str)->str);
	free(tmp);
	return ((char *)&STRING(str)->str);
}
