/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ARequestLine.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:58:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 12:31:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>

#define METHOD "Method"
#define PATH "Path"
#define VERSION "Version"
#define GET "GET"
#define POST "POST"
#define DELETE "DELETE"
#define VERSION_HTTP "HTTP/1.1"

using namespace std;

class ARequestLine{
	private:
		static const string	_keyline[3];
		static const string	_method[3];
		static const string	_versionHttp;

		string	getKeyRequestLine(int index) const;
		void	setLine(string key, string value);
	
	protected:
		int				validMethod(std::string method);
		int				validVersion(std::string version);
		int				validSize(list<string> tokens);
		int				validRequestLine();
	
		map<string, string> _requestLine;
		int					_requestLineError;

		virtual int		setRequestLine(string &buffer) = 0;
		virtual 		~ARequestLine(){};
		int				parseRequestLine(string requestLine);

	public:
		string	getMethod() const;
		string	getPath() const;
		string	getVersion() const;
		int		getRequestLineError() const;
		void	setRequestLineError(int error);
};