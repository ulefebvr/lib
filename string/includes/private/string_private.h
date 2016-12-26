/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:55:38 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:59:42 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_PRIVATE_H
# define STRING_PRIVATE_H

/*
** Return the len a of the given argument.
*/

int						str_len(char *str);

/*
** Allocate and join the two given arguments.
*/

char					*str_join(char *str1, char *str2);

/*
** Concatenate the two given arguments.
*/

char					*str_cat(char *str1, char *str2);

#endif
