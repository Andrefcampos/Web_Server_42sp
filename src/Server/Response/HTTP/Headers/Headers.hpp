/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:32:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 14:35:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

class Headers{
	private:
		std::map<std::string, std::string>	_headers;
		static std::string					_keys[];		
		int		thereIsHeader(std::string KeyHeader);

	public:
		Headers();
		std::string	getBufferHeaders() const;			

		template<typename T>
		void	setHeaders(std::string headers, T value){
			std::ostringstream ss;
			ss << value;
			_headers[headers] = ss.str();
		}

};

std::ostream &operator<<(std::ostream &os, const Headers &headers);