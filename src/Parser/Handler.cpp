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
	manager._conf["server"]->append_server(new Server());
	cf.current_server = manager._conf["server"]->back();
	cf.ctx = SRV_CONF;
	cf.args.clear();
	Parser::parser(cf, NULL);
	cf.ctx = MAIN_CONF;
	cf.current_server = NULL;
}

void	ListenHandler::process(Conf &cf) {
	size_t found = cf.args.end->find_first_not_of("123456789.:");
	if (found != std::string::npos)
		std::runtime_error(Logger::log_error(cf, "invalid value in \"%s\" directive", cf.args.end()->c_str()));
	found = cf.args.end()->find(':');
	if (found) {
		std::string host = cf.args.end()->substr(0, found);
		std::string port = cf.args.end()->substr(found, cf.args.end()->length() - 1);
		if (host.size() == 0)
			throw (std::runtime_error(Logger::log_error(cf, "no host in \"%s\" of the \"%s\" directive", cf.args.end()->c_str(), cf.args.begin()->c_str())));
		else if (port.size() == 0)
			throw (std::runtime_error(Logger::log_error(cf, "invalid port in \"%s\" of the \"%s\" directive", cf.args.end()->c_str(), cf.args.begin()->c_str())));
		cf.current_server->setDirective(*cf.args.begin(), (host + " " + port));
		cf.args.clear();
		return ;
	}
	cf.current_server->setDirective(*cf.args.begin(), cf.args.end()->substr(0, cf.args.end()->length() - 1));
	cf.args.clear();
}

void	ServerNameHandler::process(Conf &cf) {
	
	cf.args.clear();
}

void	ClientMaxBodySizeHandler::process(Conf &cf) {
	cf.args.clear();
}

void	LocationHandler::process(Conf &cf) {
	cf.ctx = LOC_CONF;
	cf.args.clear();
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