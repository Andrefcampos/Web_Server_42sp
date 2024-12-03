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
};

class ServerDirective : public Directive {
	private:
		std::vector<Server *> _servers;
	public:
		ServerDirective();
		~ServerDirective();

		void			appendServer(Server *server);
		Server			*back(void) const;
		const Server	&getServer(const std::string &host);
};

class ListenDirective : public Directive {
	private:
		bool	_default_conf;
		std::string _host;
		std::string _port;
		in_addr_t _ip;
		in_port_t _port_value;
	public:
		ListenDirective();
		~ListenDirective();

		void				setDefaultConfBool(bool state);
		void				setHost(const std::string &host);
		void				setPort(const std::string &port);
		void				setIP(in_addr_t ip);
		void				setPortValue(in_port_t port);
		bool				getDefaultConfBool(void) const;
		const std::string	&getHost(void) const;
		const std::string	&getPort(void) const;
		const in_addr_t		&getIP(void) const;
		const in_port_t		&getPortValue(void) const;
};

class ServerNameDirective : public Directive {
	private:
		std::string _server_name;
	public:
		ServerNameDirective();
		~ServerNameDirective();

		void				setServerName(const std::string &server_name);
		const std::string	&getServerName(void) const;
};

class ClientMaxBodySizeDirective : public Directive {
	private:
		bool	_default_conf;
		long long int _size_max;
	public:
		ClientMaxBodySizeDirective();
		~ClientMaxBodySizeDirective();

		void			setDefaultConfBool(const bool state);
		void			setSizeMax(const long long int size_max);
		bool			getDefaultConfBool(void) const;
		long long int	getSizeMax(void) const;
};

class LocationDirective : public Directive {
	private:
		std::vector<Location *> _locations;
	public:
		LocationDirective();
		~LocationDirective();

		void		appendLocation(Location *location);
		Location	*back(void) const;
};

class AllowMethodsDirective : public Directive {
	private:
		bool	_default_conf;
		bool	_GET;
		bool	_POST;
		bool	_DELETE;
	public:
		AllowMethodsDirective();
		~AllowMethodsDirective();

		void	setDefaultConfBool(const bool state);
		void	setGetBool(const bool state);
		void	setPostBool(const bool state);
		void	setDeleteBool(const bool state);
		bool	getDefaultConfBool(void) const;
		bool	getGetBool(void) const;
		bool	getPostBool(void) const;
		bool	getDeleteBool(void) const;
		bool	isAllowed(const std::string &method) const;
};

class RedirectDirective : public Directive {
	private:
		std::string _redirect_route;
	public:
		RedirectDirective();
		~RedirectDirective();

		void				setRedirectRoute(const std::string &redirect_route);
		const std::string	&getRedirectRoute(void) const;
};

class RootDirective : public Directive {
	private:
		std::string _root;
	public:
		RootDirective();
		~RootDirective();

		void				setRoot(const std::string &root);
		const std::string	&getRoot(void) const;
};

class AutoIndexDirective : public Directive {
	private:
		bool _default_conf;
		bool _autoindex;
	public:
		AutoIndexDirective();
		~AutoIndexDirective();

		void	setDefaultConfBool(const bool state);
		void	setAutoIndex(const bool state);
		bool	getAutoIndex(void) const;
		bool	getDefaultConfBool(void) const;
};

class IndexDirective : public Directive {
	private:
		std::string _index;
	public:
		IndexDirective();
		~IndexDirective();

		friend class IndexHandler;
};

class CgiDirective : public Directive {
	private:
		std::vector<std::string> _exts;
	public:
		CgiDirective();
		~CgiDirective();

		friend class CgiHandler;
};

class UploadDirDirective : public Directive {
	private:
		std::string _upload_dir;
	public:
		UploadDirDirective();
		~UploadDirDirective();

		friend class UploadDirHandler;
};

class ErrorPageDirective : public Directive {
	private:
		std::vector<std::string> _codes;
		std::string	_files;
	public:
		ErrorPageDirective();
		~ErrorPageDirective();

		friend class ErrorPageHandler;
};

void	initConf(void);