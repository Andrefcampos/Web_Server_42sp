/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:05:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 22:21:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>
#include <cstring>
#include <cctype>

using namespace std;

class Headers{
	private:
		void setLastHeader(string &headers);
		void setHeaders(string &line);
		
	protected:
		map<string, list<string> >	_header;

	public:
		void						addNewElement(string key, string value);
		list<string>				getHeader(string key) const;
		map<string, list<string> >	getAllHeader() const;
		void						parseHeaders(string	&headers);
	
};