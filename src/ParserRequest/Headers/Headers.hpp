/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:25:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 15:40:19 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <list>
#include <map>
#include <string>
#include "include.hpp"

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