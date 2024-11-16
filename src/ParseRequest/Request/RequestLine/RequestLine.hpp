/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:58:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 18:23:40 by rbutzke          ###   ########.fr       */
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

class RequestLine{
	private:
		static const string	_keyline[3];	
		string	getKeyRequestLine(int index) const;
		void	setLine(string key, string value);
	
	protected:
		map<string, string> _requestLine;
		RequestLine();
		~RequestLine();

	public:
		void	setRequestLine(string requestLine);
		string	getMethod() const;
		string	getPath() const;
		string	getVersion() const;
};