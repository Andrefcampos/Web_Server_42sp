/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:03:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/11 12:27:24 by myokogaw         ###   ########.fr       */
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

template<typename String>
std::string toUpper(String &str){
    typename String::iterator it, ite;
    std::string toUpper;
    ite = str.end();
    
    for(it = str.begin(); it != ite; ++it){
        toUpper += static_cast<unsigned char>(std::toupper(*it));
    }
    return toUpper;
}
#include "utils.tpp"
