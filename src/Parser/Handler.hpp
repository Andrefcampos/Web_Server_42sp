/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:12:48 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/12 14:29:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A classe Handler comtempla os métodos para preencher as estruturas de dados
// baseado no arquivo de configuração.

#pragma once

# include <string>
#include <cctype>
struct Conf;

class Handler {
	private:
		const std::string     _name;
		const unsigned int    _type;
	public:
		Handler(const std::string &name, const unsigned int type) : _name(name), _type(type) {};
		virtual ~Handler() {};

		unsigned int		getType(void);
		virtual void		process(Conf &cf) = 0;
		const std::string	&getName(void);
};

class ServerHandler : public Handler {
	public:
		ServerHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~ServerHandler() {};
		void	process(Conf &cf);
};

class ListenHandler : public Handler {
	public:
		ListenHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~ListenHandler() {};
		void	process(Conf &cf);
};

class ServerNameHandler : public Handler {
	public:
		ServerNameHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~ServerNameHandler() {};
		void	process(Conf &cf);
};

class ClientMaxBodySizeHandler : public Handler {
	public:
		ClientMaxBodySizeHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~ClientMaxBodySizeHandler() {};
		void	process(Conf &cf);
};

class LocationHandler : public Handler {
	public:
		LocationHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~LocationHandler() {};
		void	process(Conf &cf);
};

class AllowMethodsHandler : public Handler {
	public:
		AllowMethodsHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~AllowMethodsHandler() {};
		void	process(Conf &cf);
};

class RedirectHandler : public Handler {
	public:
		RedirectHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~RedirectHandler() {};
		void	process(Conf &cf);
};

class RootHandler : public Handler {
	public:
		RootHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~RootHandler() {};
		void	process(Conf &cf);
};

class AutoIndexHandler : public Handler {
	public:
		AutoIndexHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~AutoIndexHandler() {};
		void	process(Conf &cf);
};

class IndexHandler : public Handler {
	public:
		IndexHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~IndexHandler() {};
		void	process(Conf &cf);
};

class CgiHandler : public Handler {
	public:
		CgiHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~CgiHandler() {};
		void	process(Conf &cf);
};

class UploadDirHandler : public Handler {
	public:
		UploadDirHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~UploadDirHandler() {};
		void	process(Conf &cf);
};

class ErrorPageHandler : public Handler {
	public:
		ErrorPageHandler(const std::string &name, const unsigned int type) : Handler(name, type) {};
		~ErrorPageHandler() {};
		void	process(Conf &cf);
};

void	initHandlerModules(Conf &cf);
