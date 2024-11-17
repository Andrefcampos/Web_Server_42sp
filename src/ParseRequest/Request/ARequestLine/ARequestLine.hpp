/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ARequestLine.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:58:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 11:34:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>

#define METHOD "Method"
#define PATH "Path"
#define VERSION "Version"

using namespace std;

class ARequestLine{
	private:
		static const string	_keyline[3];

		string	getKeyRequestLine(int index) const;
		void	setLine(string key, string value);
	
	protected:
		bool				_parsedRequestLine;
		map<string, string> _requestLine;

		virtual void	setRequestLine(string &buffer) = 0;
		virtual 		~ARequestLine(){};
		void			parseRequestLine(string requestLine);

	public:
		string	getMethod() const;
		string	getPath() const;
		string	getVersion() const;
};