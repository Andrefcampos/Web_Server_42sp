/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:03:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/10 22:56:52 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template<typename StringType, typename CharType, typename ContainerType>
ContainerType split(const StringType& s, CharType delimiter);

template<typename T>
void putMap(T _request);

template<typename StringType, typename ContainerType>
ContainerType getLineErase(StringType &orin, StringType delimiter, bool erase);

template<typename T>
void putMapList(T _request);

template<typename String>
void trim(String &str);

#include "utils.tpp"