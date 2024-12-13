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

// A classe Directive contempla os métodos para processar a requisição

#pragma once

# include <netinet/in.h>
# include <inttypes.h>
# include <string>
# include <map>
# include <vector>
# include <list>
# include "Conf.hpp"

class Server;
class ErrorPage;
class Client;

class Directive {
	private:
		const std::string _name;

	public:
		Directive(const std::string &name);
		virtual ~Directive() {};
		virtual void		print(void) const = 0;
		const std::string	&getName(void) const;
};

class ServerDirective : public Directive {
	private:
		std::vector<Server *> _servers;

	public:
		ServerDirective();
		~ServerDirective();
		int				isNewClient(int fd, int epoll_fd, std::list<Client *> &_client);
		void			addSocketsToEpoll(int epoll_fd);
		void			initServers(void);
		void			appendServer(Server *server);
		int				size(void) const;
		Server			*back(void) const;
		const Server	&getServer(const std::string &host);
		void			print(void) const;
};

class ListenDirective : public Directive {
	private:
		bool		_default_conf;
		std::string _ip;
		std::string	_host;
		std::string	_port;

	public:
		ListenDirective();
		~ListenDirective();

		void				setDefaultConfBool(bool state);
		void				setHost(const std::string &host);
		void				setPort(const std::string &port);
		void				setIP(const std::string &ip);
		bool				getDefaultConfBool(void) const;
		const std::string	&getHost(void) const;
		const std::string	&getPort(void) const;
		const std::string	&getIP(void) const;
		void				print(void) const;
};

class ServerNameDirective : public Directive {
	private:
		std::string _server_name;

	public:
		ServerNameDirective();
		~ServerNameDirective();

		void				setServerName(const std::string &server_name);
		const std::string	&getServerName(void) const;
		void				print(void) const;
};

class ClientMaxBodySizeDirective : public Directive {
	private:
		bool			_default_conf;
		long long int	_size_max;

	public:
		ClientMaxBodySizeDirective();
		~ClientMaxBodySizeDirective();

		void			setDefaultConfBool(const bool state);
		void			setSizeMax(const long long int size_max);
		bool			getDefaultConfBool(void) const;
		long long int	getSizeMax(void) const;
		void			print(void) const;
};

class LocationDirective : public Directive {
	private:
		std::vector<Location *> _locations;

	public:
		LocationDirective();
		~LocationDirective();

		void			appendLocation(Location *location);
		Location		*back(void) const;
		Location		*getLocation(const std::string &uri);
		void			print(void) const;
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
		void	print(void) const;
};

class RedirectDirective : public Directive {
	private:
		std::string _redirect_route;
	public:
		RedirectDirective();
		~RedirectDirective();

		void				setRedirectRoute(const std::string &redirect_route);
		const std::string	&getRedirectRoute(void) const;
		void				print(void) const;
};

class RootDirective : public Directive {
	private:
		std::string _root;
	public:
		RootDirective();
		~RootDirective();

		void				setRoot(const std::string &root);
		const std::string	&getRoot(void) const;
		void				print(void) const;
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
		void	print(void) const;
};

class IndexDirective : public Directive {
	private:
		bool		_default_conf;
		std::string	_index;
	public:
		IndexDirective();
		~IndexDirective();

		void				setDefaultConfBool(const bool state);
		void				setIndex(const std::string &index);
		bool				getDefaultConfBool(void) const;
		const std::string	&getIndex(void) const;
		void				print(void) const;
};

class CgiDirective : public Directive {
	private:
		bool						_default_conf;
		std::vector<std::string>	_exts;
	public:
		CgiDirective();
		~CgiDirective();

		void	setDefaultConfBool(const bool state);
		bool	getDefaultConfBool(void) const;
		void	appendExt(const std::string &ext);
		bool	isAllowed(const std::string &ext) const;
		void	print(void) const;
};

class UploadDirDirective : public Directive {
	private:
		std::string _upload_dir;
	public:
		UploadDirDirective();
		~UploadDirDirective();

		void				setUploadDir(const std::string &upload_dir);
		const std::string	&getUploadDir(void) const;
		void				print(void) const;
};

class ErrorPageDirective : public Directive {
	private:
		std::vector<ErrorPage *>	_error_pages;

	public:
		ErrorPageDirective();
		~ErrorPageDirective();

		void		appendErrorPage(ErrorPage *error_page);
		ErrorPage	*back(void) const;
		void		print(void) const;
};
