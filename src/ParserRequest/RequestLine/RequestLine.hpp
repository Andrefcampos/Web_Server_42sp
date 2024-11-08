/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:24:56 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 12:44:12 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>

class RequestLine{
	private:
		static const std::string			_keyLine[3];
		static const std::string			_delimit;
		std::list<std::string>				_tokens;
		std::map<std::string, std::string>	_requestLine;

	protected:
		RequestLine(){};
		~RequestLine(){};
		std::map<std::string, std::string>	setRequestLine(std::string line);
		
};