/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:03:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/08 03:08:22 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <sstream>
#include <list>
#include <iostream>
#include <algorithm>

template<typename T, typename C>
std::list<std::string>	split(T &s, C c){
	std::string							token;
	std::stringstream 					ss;
	std::istringstream					iss(s);
	std::list<std::string>				listToken;

	if (s.empty())
		return listToken;
	while (std::getline(iss, token, c)){
		if (!token.empty())
			listToken.push_back(token);
	}
	return (listToken);
}

template<typename T>
void putMap(T _request){
	typename T::iterator it;

	for(it = _request.begin(); it != _request.end(); it++){
		std::cout << it->first << " " << it->second << "\n";
	}
}
