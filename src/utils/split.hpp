/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:03:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 13:33:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <sstream>
#include <list>
#include <iostream>
#include <algorithm>

template<typename StringType, typename CharType, typename ContainerType>
ContainerType split(const StringType& s, CharType delimiter) {
    ContainerType	listToken;
    std::string		token;
    std::istringstream iss(s);

    while (std::getline(iss, token, delimiter)) {
        if (!token.empty()) {
            listToken.push_back(token);
        }
    }
    return listToken;
}

template<typename T>
void putMap(T _request){
	typename T::iterator it;

	for(it = _request.begin(); it != _request.end(); it++){
		std::cout << it->first << " " << it->second << "\n";
	}
}