/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:25:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 12:44:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <list>
#include <map>
#include <string>

typedef std::map<std::string, std::string> mapHeader;

class Headers{
	private:
		static const std::string			_delimit;
		std::list<std::string>				_requestHeaders;
		std::map<std::string, std::string>	_headers;
		std::list<std::string>::iterator	_it;
		void	setRequestHeaders(std::string header);

	protected:
		Headers(){};
		~Headers(){};
		mapHeader	setHeaders(std::list<std::string> tokens);
};