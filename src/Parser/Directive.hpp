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

// A classe Directive comtempla os métodos para processar a requisição

#pragma once

# include <netinet/in.h>
# include <inttypes.h>
# include <string>
# include <map>
# include <vector>
# include "Conf.hpp"

class Server;

class Directive {
	public:
		Directive() {};
		virtual ~Directive() {};

		friend class Handler;
};

class ServerDirective : public Directive {
	private:
		std::vector<Server *> _servers;
	public:
		ServerDirective();
		virtual ~ServerDirective();
		void			appendServer(Server *server);
		Server			*back(void) const;
		const Server	&getServer(const std::string &host);

		friend class ServerHandler;
};

class ListenDirective : public Directive {
	private:
		std::string _host;
		std::string _port;
		in_addr_t _ip;
		in_port_t _port_value;
	public:
		ListenDirective();
		~ListenDirective();

		void	setHost(const std::string &host);
		void	setPort(const std::string &port);
		void	setIP(unsigned int &ip);
		const std::string &getHost(void) const;
		const std::string &getPort(void) const;
		const unsigned int &getIP(void) const;
		friend class ListenHandler;
};

class ServerNameDirective : public Directive {
	private:
		std::string _server_name;
	public:
		ServerNameDirective();
		~ServerNameDirective();

		void	setServerName(const std::string &server_name);
		const std::string &getServerName(void) const;
		
		friend class ServerNameHandler;
};

class ClientMaxBodySizeDirective : public Directive {
	private:
		long long int _size_max;
	public:
		ClientMaxBodySizeDirective();
		~ClientMaxBodySizeDirective();

		void	setSizeMax(const long long int size_max);
		long long int	getSizeMax(void) const;

		friend class ClientMaxBodySizeHandler;
};

class LocationDirective : public Directive {
	private:
		std::map<std::string, Directive *> _directives;
	public:
		void	setDirective(Conf &cf);
		LocationDirective();
		~LocationDirective();

		friend class LocationHandler;
};

class AllowMethodsDirective : public Directive {
	private:
		const std::string _value;
	public:
		AllowMethodsDirective(const std::string &value);
		~AllowMethodsDirective();

		friend class AllowMethodsHandler;
};

class RedirectDirective : public Directive {
	private:
		const std::string _value;
	public:
		RedirectDirective(const std::string &value);
		~RedirectDirective();

		friend class RedirectHandler;
};

class RootDirective : public Directive {
	private:
		const std::string _value;
	public:
		RootDirective(const std::string &value);
		~RootDirective();

		friend class RootHandler;
};

class AutoIndexDirective : public Directive {
	private:
		const std::string _value;
	public:
		AutoIndexDirective(const std::string &value);
		~AutoIndexDirective();

		friend class AutoIndexHandler;
};

class IndexDirective : public Directive {
	private:
		const std::string _value;
	public:
		IndexDirective(const std::string &value);
		~IndexDirective();

		friend class IndexHandler;
};

class CgiDirective : public Directive {
	private:
		const std::string _value;
	public:
		CgiDirective(const std::string &value);
		~CgiDirective();

		friend class CgiHandler;
};

class UploadDirDirective : public Directive {
	private:
		const std::string _value;
	public:
		UploadDirDirective(const std::string &value);
		~UploadDirDirective();

		friend class UploadDirHandler;
};

class ErrorPageDirective : public Directive {
	private:
		const std::string _value;
	public:
		ErrorPageDirective(const std::string &value);
		~ErrorPageDirective();

		friend class ErrorPageHandler;
};

void	initConf(void);