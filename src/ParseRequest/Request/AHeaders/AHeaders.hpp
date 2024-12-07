/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHeaders.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:05:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/04 17:40:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>
#include <cstring>
#include <cctype>

using namespace std;

#define HOST "Host"

class AHeaders{
	private:
		void	setLastHeader(string &headers);
		void	setHeaders(string &line);
		void	addNewElement(string key, string value);
		
	protected:
		map<string, list<string> >	_header;
		virtual void	setHeader(string &buffer) = 0;
		virtual 		~AHeaders(){};
		void			parseHeaders(string	&headers);

	public:
		string						getHost() const;
		list<string>				getHeader(string key) const;
		map<string, list<string> >	getAllHeader() const;
	
};