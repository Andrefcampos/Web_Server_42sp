/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:14:15 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/02 21:01:48 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cerrno>
#include <cstdlib>
#include "Webserv.hpp"
#include "Handler.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "Conf.hpp"
#include "Parser.hpp"
#include "defines.hpp"
#include "Location.hpp"

using namespace std;

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

const string &Handler::getName(void) {
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
	string value;
	string::size_type found;
	stringstream ss;
	ListenDirective *listen_obj = static_cast<ListenDirective *>(cf.current_server->_directives["listen"]);
	if (listen_obj->getDefaultConfBool() == false)
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	ss.str(cf.args.back());
	ss >> value;
	found = value.find(':');
	// cout << "Defaul conf listen" << endl;
	// cout << "ip: "<< listen_obj->getIP() << endl;
	// cout << "host: " << listen_obj->getHost() << endl;
	// cout << "port: " << listen_obj->getPort() << endl;
	// cout << "port value: " << listen_obj->getPortValue() << endl << endl;
	if (found != string::npos) {
		struct addrinfo hints;
		struct addrinfo *res;
		struct in_addr	inp;
		int rc;
		long n;
		string host = value.substr(0, found);
		++found;
		string port = value.substr(found, value.find(';') - found);
		if (host.length() == 0)
			throw (runtime_error(Logger::log_error(cf, "invalid host in directive \"listen\"")));
		if (port.length() == 0)
			throw (runtime_error(Logger::log_error(cf, "invalid port in directive \"listen\"")));
		n = strtol(port.c_str(), NULL, 10);
		if (errno == ERANGE || n < 1 || n > 65535)
			throw (runtime_error(Logger::log_error(cf, "invalid port \"%s\" in directive \"listen\"")), port.c_str());
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		rc = getaddrinfo(host.c_str(), port.c_str(), &hints, &res);
		if (rc != 0)
			throw (runtime_error(Logger::log_error(cf, "getaddrinfo: \"%s\"", gai_strerror(rc))));
		rc = inet_aton(res->ai_addr->sa_data, &inp);
		if (rc != 0)
			throw (runtime_error(Logger::log_error(cf, "inet_aton: \"%s\"", gai_strerror(rc))));
		listen_obj->setHost(host);
		listen_obj->setPort(port);
		listen_obj->setIP(inp.s_addr);
		listen_obj->setPortValue(static_cast<in_port_t>(n));
		freeaddrinfo(res);
	} else if (value.find('.') != string::npos) {
		struct addrinfo hints;
		struct addrinfo *res;
		struct in_addr	inp;
		int rc;
		string host = value.substr(0, value.find(';'));
		if (host.length() == 0)
			throw (runtime_error(Logger::log_error(cf, "invalid host in directive \"listen\"")));
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		rc = getaddrinfo(host.c_str(), NULL, &hints, &res);
		if (rc != 0)
			throw (runtime_error(Logger::log_error(cf, "getaddrinfo: \"%s\"", gai_strerror(rc))));
		rc = inet_aton(res->ai_addr->sa_data, &inp);
		if (rc != 0)
			throw (runtime_error(Logger::log_error(cf, "inet_aton: \"%s\"", gai_strerror(rc))));
		listen_obj->setHost(host);
		listen_obj->setIP(inp.s_addr);
		freeaddrinfo(res);
	} else {
		string port = value.substr(0, value.find(';'));
		long n;
		if (port.length() == 0)
			throw (runtime_error(Logger::log_error(cf, "invalid port in directive \"listen\"")));
		if (port.find_first_not_of("0123456789") != string::npos)
			throw (runtime_error(Logger::log_error(cf, "invalid port \"%s\" in directive \"listen\"", port.c_str())));
		n = strtol(port.c_str(), NULL, 10);
		if (errno == ERANGE || n < 1 || n > 65535)
			throw (runtime_error(Logger::log_error(cf, "invalid port \"%s\" in directive \"listen\"")), port.c_str());
		listen_obj->setPort(port);
		listen_obj->setPortValue(static_cast<in_port_t>(n));
	}
	// cout << "After parser listen directive" << endl;
	// cout << "ip: "<< listen_obj->getIP() << endl;
	// cout << "host: " << listen_obj->getHost() << endl;
	// cout << "port: " << listen_obj->getPort() << endl;
	// cout << "port value: " << listen_obj->getPortValue() << endl << endl;;
	listen_obj->setDefaultConfBool(false);
	cf.args.clear();
}

void	ServerNameHandler::process(Conf &cf) {
	ServerNameDirective *server_name_obj = static_cast<ServerNameDirective *>(cf.current_server->_directives["server_name"]);
	if (server_name_obj)
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	server_name_obj = new ServerNameDirective();
	server_name_obj->setServerName(cf.args.back().substr(0, cf.args.back().length() - 1));
	// cout << server_name_obj->getServerName() << endl;
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
	string value;
	string::size_type found;
	ClientMaxBodySizeDirective *client_max_body_size_obj = static_cast<ClientMaxBodySizeDirective *>(cf.current_server->_directives["client_max_body_size"]);
	if (client_max_body_size_obj->getDefaultConfBool() == false)
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	value = cf.args.back();
	found = value.find_first_not_of("0123456789mMkK;");
	// client_max_body_size_obj = new ClientMaxBodySizeDirective();
	if (found != string::npos)
		throw (runtime_error(Logger::log_error(cf, "invalid size \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
	size_max = strtoll(value.c_str(), &unit, 10);
	if (errno == ERANGE)
		throw (runtime_error(Logger::log_error(cf, "invalid size \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
	if (*unit == 'm' || *unit == 'M')
		size_max *= (1 << 20);
	else if (*unit == 'k' || *unit == 'K')
		size_max *= (1 << 10);
	else
		throw (runtime_error(Logger::log_error(cf, "invalid size \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
	client_max_body_size_obj->setSizeMax(size_max);
	// cout << client_max_body_size_obj->getSizeMax() << endl;
	cf.current_server->_directives["client_max_body_size"] = client_max_body_size_obj;
	cf.args.clear();
}

void	LocationHandler::process(Conf &cf) {
	if (strchr(cf.args.back().c_str(), '/')) {
		cf.current_location = new Location();
		cf.ctx = LOC_CONF;
		cf.args.clear();
		Parser::parser(cf, NULL);
		cf.ctx = SRV_CONF;
		static_cast<LocationDirective *>(cf.current_server->_directives["location"])->appendLocation(cf.current_location);
	} else
		throw (runtime_error(Logger::log_error(cf, "invalid route \"%s\" for directive \"%s\"", cf.args.back().c_str(), cf.args.front().c_str())));
	return ;
}

void	AllowMethodsHandler::process(Conf &cf) {
	AllowMethodsDirective *allow_methods_obj = static_cast<AllowMethodsDirective *>(cf.current_location->_directives["allow_methods"]);
	// cout << "DEFAULT CONF " << allow_methods_obj->getDefaultConfBool() << endl;
	// cout << "GET " <<allow_methods_obj->getGetBool() << endl;
	// cout << "POST " << allow_methods_obj->getPostBool() << endl;
	// cout << "DELETE " << allow_methods_obj->getDeleteBool() << endl;
	if (allow_methods_obj->getDefaultConfBool()) {
		stringstream ss;
		string::size_type found;
		string token;
		for (vector<string>::iterator it = ++cf.args.begin(); it != cf.args.end(); ++it) {
			ss.str(*it);
			ss >> token;
			found = token.find(';');
			// cout << token << endl;
			if (found)
				token = token.substr(0, found);
			if (token.compare("GET") == 0)
				allow_methods_obj->setGetBool(true);
			else if (token.compare("POST") == 0)
				allow_methods_obj->setPostBool(true);
			else if (token.compare("DELETE") == 0)
				allow_methods_obj->setDeleteBool(true);
			ss.clear();
		}
		allow_methods_obj->setDefaultConfBool(false);
	}
	else
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	// cout << "DEFAULT CONF " << allow_methods_obj->getDefaultConfBool() << endl;
	// cout << "GET " << allow_methods_obj->getGetBool() << endl;
	// cout << "POST " << allow_methods_obj->getPostBool() << endl;
	// cout << "DELETE " << allow_methods_obj->getDeleteBool() << endl;
	cf.args.clear(); 
}

void	RedirectHandler::process(Conf &cf) {
	RedirectDirective *redirect_obj = static_cast<RedirectDirective *>(cf.current_location->_directives["redirect"]);
	if (redirect_obj)
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	redirect_obj = new RedirectDirective();
	redirect_obj->setRedirectRoute(cf.args.back().substr(0, cf.args.back().find(';')));
	cout << redirect_obj->getRedirectRoute() << endl;
	cf.current_location->_directives["redirect"] = redirect_obj;
	cf.args.clear();
}

void	RootHandler::process(Conf &cf) {
	RootDirective *root_obj = static_cast<RootDirective *>(cf.current_location->_directives["root"]);
	if (root_obj)
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	root_obj = new RootDirective();
	root_obj->setRoot(cf.args.back().substr(0, cf.args.back().find(';')));
	cout << root_obj->getRoot() << endl;
	cf.current_location->_directives["root"] = root_obj;
	cf.args.clear();
}

void	AutoIndexHandler::process(Conf &cf) {
	string value;
	AutoIndexDirective *auto_index_obj = static_cast<AutoIndexDirective *>(cf.current_location->_directives["autoindex"]);
	if (auto_index_obj->getDefaultConfBool() == false)
		throw (runtime_error(Logger::log_error(cf, "directive \"%s\" is already set", cf.args.front().c_str())));
	value = cf.args.back().substr(0, cf.args.back().find(';'));
	if (value.compare("on") == 0)
		auto_index_obj->setAutoIndex(true);
	else if (value.compare("off") == 0)
		auto_index_obj->setAutoIndex(true);
	else
		throw (runtime_error(Logger::log_error(cf, "invalid value \"%s\" in directive \"%s\"", value.c_str(), cf.args.front().c_str())));
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