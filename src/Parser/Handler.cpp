/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:14:15 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 20:28:39 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <cstdlib>
#include "Webserv.hpp"
#include "Handler.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "Conf.hpp"
#include "Parser.hpp"
#include "defines.hpp"

void	initHandlerModules(Conf &cf) {
	cf.handlers["server"] = new ServerHandler("server", MAIN_CONF|CONF_BLOCK|CONF_NOARGS);
	cf.handlers["listen"] = new ListenHandler("listen", SRV_CONF|CONF_TAKE1);
	cf.handlers["server_name"] = new ServerNameHandler("server_name", SRV_CONF|CONF_TAKE1);
	cf.handlers["client_max_body_size"] = new ClientMaxBodySizeHandler("client_max_body_size", SRV_CONF|CONF_TAKE1);
	cf.handlers["location"] = new LocationHandler("location", SRV_CONF|CONF_BLOCK|CONF_TAKE1);
	cf.handlers["allow_methods"] = new AllowMethodsHandler("allow_methods", LOC_CONF|CONF_1MORE);
	cf.handlers["redirect"] = new RedirectHandler("redirect", LOC_CONF|CONF_TAKE1);
		cf.handlers["root"] = new RootHandler("root", LOC_CONF|CONF_TAKE1);
	cf.handlers["autoindex"] = new AutoIndexHandler("autoindex", LOC_CONF|CONF_TAKE1);
	cf.handlers["index"] = new IndexHandler("index", LOC_CONF|CONF_TAKE1);
	cf.handlers["cgi"] = new CgiHandler("cgi", LOC_CONF|CONF_1MORE);
	cf.handlers["upload_dir"] = new UploadDirHandler("upload_dir", LOC_CONF|CONF_TAKE1);
	cf.handlers["error_page"] = new ErrorPageHandler("error_page", SRV_CONF|CONF_2MORE);
}

const std::string &Handler::getName(void) {
	return (_name);
}

unsigned int Handler::getType(void) {
	return (_type);
}

void	ServerHandler::process(Conf &cf) {
	static_cast<ServerDirective *>(manager._conf["server"])->appendServer(new Server());
	cf.current_server = static_cast<ServerDirective *>(manager._conf["server"])->back();
	cf.ctx = SRV_CONF;
	cf.args.clear();
	Parser::parser(cf, NULL);
	cf.ctx = MAIN_CONF;
	cf.current_server = NULL;
}

void	ListenHandler::process(Conf &cf) {
	std::string value;
	std::string host;
	std::string port;
	std::string::size_type found;
	struct sockaddr hints;
	ListenDirective *listen_obj = cf.current_server->_directives["location"];
	if (listen_obj)
		throw (std::runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	value = cf.args.back();
	found = value.find(':');
	if (found) {
		host = value.substr(0, found);
		port = value.substr(found + 1, value.length());
		if (host.size() == 0)
			throw (std::runtime_error(Logger::log_error(cf, "no host in \"%s\" of the \"%s\" directive", value.c_str(), cf.args.begin()->c_str())));
		else if (port.size() == 0)
			throw (std::runtime_error(Logger::log_error(cf, "invalid port in \"%s\" of the \"%s\" directive", value.c_str(), cf.args.begin()->c_str())));
		int n = std::strtol(port.c_str(), NULL, 10);
		if (errno || n < 1 || n > 65535)
			throw (std::runtime_error(Logger::log_error(cf, "invalid port in \"%s\" of the \"%s\" directive", value.c_str(), cf.args.begin()->c_str())));

		listen_obj->setHost(host);
		listen_obj->setPort(port);
		listen_obj->setPortValue(static_cast<in_port_t>(n));

		cf.args.clear();
		return ;
	}
	else if (cf.args.back().find('.')) {
		host = cf
	}
	// cf.current_server->setDirective(listen_obj);
	cf.args.clear();
}

void	ServerNameHandler::process(Conf &cf) {
	Directive *server_name_obj = cf.current_server->_directives["server_name"];
	if (server_name_obj)
		throw (std::runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	server_name_obj = new ServerNameDirective();
	static_cast<ServerNameDirective *>(server_name_obj)->setServerName(cf.args.back().substr(0, cf.args.back().length() - 1));
	std::cout << static_cast<ServerNameDirective *>(server_name_obj)->getServerName() << std::endl;
	cf.current_server->_directives["server_name"] = server_name_obj;
	cf.args.clear();
}

// Sets the maximum allowed size of the client request body.
// If the size in a request exceeds the configured value, the 413 (Request Entity Too Large)
// error is returned to the client. Please be aware that browsers cannot
// correctly display this error. Setting size to 0 disables checking of client request body size.

void	ClientMaxBodySizeHandler::process(Conf &cf) {
	long long int size_max;
	char *unit;
	std::string value;
	std::string::size_type found;
	ClientMaxBodySizeDirective *client_max_body_size_obj = static_cast<ClientMaxBodySizeDirective *>(cf.current_server->_directives["client_max_body_size"]);
	if (client_max_body_size_obj)
		throw (std::runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	value = cf.args.back();
	found = value.find_first_not_of("0123456789mMkK;");
	client_max_body_size_obj = new ClientMaxBodySizeDirective();
	if (found != std::string::npos)
		throw (std::runtime_error(Logger::log_error(cf, "invalid size \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
	size_max = std::strtoll(value.c_str(), &unit, 10);
	if (errno == ERANGE)
		throw (std::runtime_error(Logger::log_error(cf, "invalid size \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
	if (*unit == 'm' || *unit == 'M')
		size_max *= (1 << 20);
	else if (*unit == 'k' || *unit == 'K')
		size_max *= (1 << 10);
	else
		throw (std::runtime_error(Logger::log_error(cf, "invalid size \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
	client_max_body_size_obj->setSizeMax(size_max);
	std::cout << client_max_body_size_obj->getSizeMax() << std::endl;
	cf.current_server->_directives["client_max_body_size"] = client_max_body_size_obj;
	cf.args.clear();
}

void	LocationHandler::process(Conf &cf) {
	cf.current_location = new LocationDirective();
	if (std::strchr(cf.args.back().c_str(), '/')) {
		cf.current_location->setRoute(cf.args.back());
		cf.ctx = LOC_CONF;	
		cf.args.clear();
		Parser::parser(cf, NULL);
		cf.ctx = SRV_CONF;
	} else
		throw (std::runtime_error(Logger::log_error(cf, "invalid route \"%s\" for directive \"%s\"", cf.args.back().c_str(), cf.args.front().c_str())));
	return ;
}

void	AllowMethodsHandler::process(Conf &cf) {

	cf.args.clear();
}

void	RedirectHandler::process(Conf &cf) {
	cf.args.clear();
}

void	RootHandler::process(Conf &cf) {
	cf.args.clear();
}

void	AutoIndexHandler::process(Conf &cf) {
	cf.args.clear();
}

void	IndexHandler::process(Conf &cf) {
	cf.args.clear();
}

void	CgiHandler::process(Conf &cf) {
	cf.args.clear();
}

void	UploadDirHandler::process(Conf &cf) {
	cf.args.clear();
}

void	ErrorPageHandler::process(Conf &cf) {
	cf.args.clear();
}