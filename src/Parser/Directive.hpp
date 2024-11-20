/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:29:20 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 18:29:20 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <map>
# include <vector>
# include "Conf.hpp"

class Server;

class Directive {
	public:
		virtual ~Directive() = 0;
};

class ServerDirective : public Directive {
	private:
		std::vector<Server *> _servers;
	public:
		ServerDirective();
		virtual ~ServerDirective();
		void			appendServer(Server *server);
		Server			*back(void);
		const Server	&getServer(const std::string &host);
};

class ListenDirective : public Directive {
	private:
		const std::string _value;
	public:
		ListenDirective(const std::string &value);
		~ListenDirective();
};

class ServerNameDirective : public Directive {
	private:
		const std::string _value;
	public:
		ServerNameDirective(const std::string &value);
		~ServerNameDirective();
};

class ClientMaxBodySizeDirective : public Directive {
	private:
		const std::string _value;
	public:
		ClientMaxBodySizeDirective(const std::string &value);
		~ClientMaxBodySizeDirective();
};

class LocationDirective : public Directive {
	private:
		std::map<std::string, Directive *> _directives;
	public:
		void	setDirective(Conf &cf);
		LocationDirective();
		~LocationDirective();
};

class AllowMethodsDirective : public Directive {
	private:
		const std::string _value;
	public:
		AllowMethodsDirective(const std::string &value);
		~AllowMethodsDirective();
};

class RedirectDirective : public Directive {
	private:
		const std::string _value;
	public:
		RedirectDirective(const std::string &value);
		~RedirectDirective();
};

class RootDirective : public Directive {
	private:
		const std::string _value;
	public:
		RootDirective(const std::string &value);
		~RootDirective();
};

class AutoIndexDirective : public Directive {
	private:
		const std::string _value;
	public:
		AutoIndexDirective(const std::string &value);
		~AutoIndexDirective();
};

class IndexDirective : public Directive {
	private:
		const std::string _value;
	public:
		IndexDirective(const std::string &value);
		~IndexDirective();
};

class CgiDirective : public Directive {
	private:
		const std::string _value;
	public:
		CgiDirective(const std::string &value);
		~CgiDirective();
};

class UploadDirDirective : public Directive {
	private:
		const std::string _value;
	public:
		UploadDirDirective(const std::string &value);
		~UploadDirDirective();
};

class ErrorPageDirective : public Directive {
	private:
		const std::string _value;
	public:
		ErrorPageDirective(const std::string &value);
		~ErrorPageDirective();
};

void	initConf(void);