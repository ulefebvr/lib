/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:55:35 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:55:35 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stdlib.h>

/*
** Get the offset of member in the type structure.
*/

# define OFFSETOF(TYPE, MEMBER)		((size_t) &((TYPE *)0)->MEMBER)
# define CONTAINEROF(ptr, t, m)		((t *)((char *)(ptr) - OFFSETOF(t, m)))

/*
** String structure.
*/

typedef struct						s_string
{
	char							*str;
	int								len;
}									t_string;

/*
** Get the string of the structure.
*/

# define STRING(x)					(CONTAINEROF((char **)x, t_string, str))

/*
** Initiate a new string.
*/

char								*string_new(char *str);

/*
** Concatenate a string.
*/

char								*string_cat(char *str, char *add);

/*
** Dup an existing string.
*/

char								*string_dup(char *str);

/*
** Delete a string.
*/

char								*string_del(char *str);

#endif
