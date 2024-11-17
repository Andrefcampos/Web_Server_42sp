/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:03:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 12:08:18 by rbutzke          ###   ########.fr       */
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

/* template<typename StringType, typename ContainerType>
ContainerType getLine(StringType &orin, StringType delimiter){
    std::size_t     find;
    ContainerType   line;

    if (delimiter.empty() || orin.empty()){
        return "";
    }
    find = orin.find(delimiter);
    if (find == std::string::npos){
        return "";
    }
    line = orin.substr(0, find);
	orin.erase(0, find + delimiter.length());
	return line;
} */

template<typename StringType, typename ContainerType>
ContainerType getLineErase(StringType &orin, StringType delimiter, bool erase){
    std::size_t     find;
    ContainerType   line;

    if (delimiter.empty() || orin.empty()){
        return "";
    }
    find = orin.find(delimiter);
    if (find == std::string::npos){
        return "";
    }
    line = orin.substr(0, find);
    if (erase == true)
	    orin.erase(0, find + delimiter.length());
	return line;
}

template<typename T>
void putMapList(T _request){
	typename T::iterator it;
    std::list<std::string>::iterator l_IT;

	for(it = _request.begin(); it != _request.end(); it++){
		std::cout << it->first << " ";
        l_IT = it->second.begin();
        for (; l_IT != it->second.end(); l_IT++){
            std::cout << *l_IT << " ";   
        }
        std::cout << "\n";
	}
}

template<typename String>
void trim(String &str){
    
    while(str.size() > 0 && std::isspace(static_cast<unsigned char>(str[0]))){
    	str.erase(0, 1);
    }
	while(str.size() > 0 && std::isspace(static_cast<unsigned char>(str[str.size() -1]))){
		str.erase(str.size() - 1, 1);
    }
}

