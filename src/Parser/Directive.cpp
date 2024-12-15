/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:32:48 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 18:32:48 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstddef>
#include <netinet/in.h>
#include <inttypes.h>
#include <sys/epoll.h>
#include "Location.hpp"
#include "Logger.hpp"
#include "Directive.hpp"
#include "Server.hpp"
#include "ErrorPage.hpp"
#include "utils.hpp"
#include "Client.hpp"

using namespace std;

Directive::Directive(const std::string &name) : _name(name) {}

const std::string &Directive::getName(void) const {
	return (this->_name);
}

ServerDirective::ServerDirective() : Directive("server"), _servers() {}

ServerDirective::~ServerDirective() {
	for (vector<Server *>::iterator it=_servers.begin(); it != _servers.end(); ++it)
		delete *it;
	_servers.clear();
}

void    ServerDirective::appendServer(Server *server) {
	_servers.push_back(server);
}

Server  *ServerDirective::back(void) const {
	return(_servers.back());
}

void	ServerDirective::initServers(void) {
	ListenDirective *listen_obj;
	for (vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++it) {
		listen_obj = const_cast<ListenDirective *>(static_cast<const ListenDirective *>((*it)->getDirective("listen")));
		(*it)->setSocketFd((*it)->initTCP(listen_obj->getPort().c_str(), 5, listen_obj->getIP().c_str()));
	}
}

int		ServerDirective::size(void) const {
	return (this->_servers.size());
}

int	ServerDirective::isNewClient(int fd, int epoll_fd, std::list<Client*> &_client) {
	struct epoll_event			ev;
	int							fdClient;
	vector<Server *>::iterator	itServer;
	
	memset(&ev, 0, sizeof(ev));

	for(itServer = _servers.begin(); itServer != _servers.end(); ++itServer) {
		if (fd == (*itServer)->getSocketFd()) {
			fdClient = accept((*itServer)->getSocketFd(), 0, 0);
			if (fdClient == -1)
				throw (runtime_error("error: epoll_ctl()"));
			Client *client = new Client(*itServer, fdClient);
			client->setMaxSize((*itServer)->getSizeMax());
			_client.push_back(client);
			ev.data.ptr = reinterpret_cast<void *>(client);
			ev.events = EPOLLIN;
			if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fdClient, &ev) == -1)
				throw (runtime_error("error: epoll_ctl()"));
			return (true);
		}
	}
	return (false);
}

void	ServerDirective::addSocketsToEpoll(int epoll_fd) {
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;
	for (vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++it) {
		ev.data.fd = (*it)->getSocketFd();
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
			throw (runtime_error("error: epoll_ctl()"));
	}
}

void	ServerDirective::print(void) const {
	for (vector<Server *>::const_iterator it = _servers.begin(); it != _servers.end(); ++it) {
		cout << endl << "Server Directive: " << endl;
		(*it)->print();
	}
}

ListenDirective::ListenDirective() : Directive("listen"), _default_conf(true), _ip("0.0.0.0"), _host("0.0.0.0"), _port("8080") {}

ListenDirective::~ListenDirective() {}

void	ListenDirective::setDefaultConfBool(bool state) {
	this->_default_conf = state;
}

void	ListenDirective::setHost(const string &host) {
	this->_host = host;
}

void	ListenDirective::setPort(const string &port) {
	this->_port = port;
}

void	ListenDirective::setIP(const std::string &ip) {
	this->_ip = ip;
}

bool	ListenDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

const string &ListenDirective::getHost(void) const {
	return (this->_host);
}

const string &ListenDirective::getPort(void) const {
	return (this->_port);
}

const string &ListenDirective::getIP(void) const {
	return (this->_ip);
}

void	ListenDirective::print(void) const {
	cout << "Listen Directive: IP: " << _ip << "	PORT: " << _port << "	HOST:" << _host << endl;
}

ServerNameDirective::ServerNameDirective() : Directive("server_name") {}

ServerNameDirective::~ServerNameDirective() {}

void	ServerNameDirective::setServerName(const string &server_name) {
	this->_server_name = server_name;
}

const string &ServerNameDirective::getServerName(void) const {
	return (this->_server_name);
}

void	ServerNameDirective::print(void) const {
	cout << "ServerName Directive: " << _server_name << endl;
}

ClientMaxBodySizeDirective::ClientMaxBodySizeDirective() : Directive("client_max_body_size"), _default_conf(true), _size_max(1 * (1 << 20)) {}

ClientMaxBodySizeDirective::~ClientMaxBodySizeDirective() {}

void	ClientMaxBodySizeDirective::setSizeMax(const long long int size_max) {
	this->_size_max = size_max;
}

long long int ClientMaxBodySizeDirective::getSizeMax(void) const {
	return (this->_size_max);
}

void	ClientMaxBodySizeDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

bool	ClientMaxBodySizeDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

void	ClientMaxBodySizeDirective::print(void) const {
	cout << "ClientMaxBodySize Directive: " << _size_max << endl;
}

LocationDirective::LocationDirective() : Directive("location"), _locations() {}

LocationDirective::~LocationDirective() {
	for (vector<Location *>::iterator it = _locations.begin(); it != _locations.end(); ++it)
		delete *it;
	_locations.clear();
}

void    LocationDirective::appendLocation(Location *location) {
	_locations.push_back(location);
}

Location  *LocationDirective::back(void) const {
	return(_locations.back());
}

Location	*LocationDirective::getLocation(const string &uri) {
	size_t				prev_span(0), span(0);
	string				cur_loc;
	string				prefix(uri.substr(0, uri.rfind('/')));
	Location			*location = NULL;
	string::iterator	it_pre, it_cur;

	if (prefix.empty())
		return (_locations.front());
	for (vector<Location *>::iterator it = _locations.begin(); it != _locations.end(); ++it) {
		cur_loc = (*it)->getRoute();
		it_cur = cur_loc.begin();
		it_pre = prefix.begin();
		span = 0;
		while (it_pre != prefix.end() && it_cur != cur_loc.end() && *it_pre == *it_cur) {
			span++;
			it_pre++;
			it_cur++;
		}
		if (prev_span < span) {
			prev_span = span;
			location = *it;
		}
	}
	return (location);
}

void	LocationDirective::print(void) const {
	for (vector<Location *>::const_iterator it = _locations.begin(); it != _locations.end(); ++it) {
		cout << endl << "Location Directive: " << (*it)->getRoute() << endl;
		(*it)->print();
	}
}

AllowMethodsDirective::AllowMethodsDirective() : Directive("allow_methods"), _default_conf(true), _GET(true), _POST(false), _DELETE(false) {}

AllowMethodsDirective::~AllowMethodsDirective() {}

void	AllowMethodsDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

void	AllowMethodsDirective::setGetBool(const bool state) {
	this->_GET = state;
}

void	AllowMethodsDirective::setPostBool(const bool state) {
	this->_POST = state;
}

void	AllowMethodsDirective::setDeleteBool(const bool state) {
	this->_DELETE = state;
}

bool	AllowMethodsDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

bool	AllowMethodsDirective::getGetBool(void) const {
	return (this->_GET);
}

bool	AllowMethodsDirective::getPostBool(void) const {
	return (this->_POST);
}

bool	AllowMethodsDirective::getDeleteBool(void) const {
	return (this->_DELETE);
}

bool AllowMethodsDirective::isAllowed(const string &method) const {
	if (method.compare("GET") == 0 && _GET == true)
		return (true);
	else if (method.compare("POST") == 0 && _POST == true)
		return (true);
	else if (method.compare("DELETE") == 0 && _DELETE == true)
		return (true);
	return (false);
}

void	AllowMethodsDirective::print(void) const {
	cout << "Allow Methods Directive: GET: " << ((_GET == true) ? "true" : "false") << "	POST: " <<
	((_POST == true) ? "true" : "false") << "	DELETE: " << ((_DELETE == true) ? "true" : "false") << "	" << endl; 
}

RedirectDirective::RedirectDirective() : Directive("redirect") {}

RedirectDirective::~RedirectDirective() {}

void	RedirectDirective::setRedirectRoute(const string &redirect_route) {
	this->_redirect_route = redirect_route;
}

const string &RedirectDirective::getRedirectRoute(void) const {
	return (this->_redirect_route);
}

void	RedirectDirective::print(void) const {
	cout << "Redirect Directive: " << _redirect_route << endl;
}

RootDirective::RootDirective() : Directive("root") {}

RootDirective::~RootDirective() {}

void	RootDirective::setRoot(const string &root) {
	this->_root = root;
}

const string &RootDirective::getRoot(void) const {
	return (this->_root);
}

void	RootDirective::print(void) const {
	cout << "Root Directive: " << _root << endl;
}

AutoIndexDirective::AutoIndexDirective() : Directive("autoindex"), _default_conf(true), _autoindex(false) {}

AutoIndexDirective::~AutoIndexDirective() {}

void	AutoIndexDirective::setAutoIndex(const bool state) {
	this->_autoindex = state;
}

void	AutoIndexDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

bool	AutoIndexDirective::getAutoIndex(void) const {
	return (this->_autoindex);
}

bool	AutoIndexDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

void	AutoIndexDirective::print(void) const {
	cout << "AutoIndex Directive: " << ((_autoindex == true) ? "true" : "false") << endl;
}

IndexDirective::IndexDirective() : Directive("index"), _default_conf(true), _index("/index.html") {}

IndexDirective::~IndexDirective() {}

void	IndexDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

void	IndexDirective::setIndex(const string &index) {
	this->_index = index;
}

bool	IndexDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

const string	&IndexDirective::getIndex(void) const {
	return (this->_index);
}

void	IndexDirective::print(void) const {
	cout << "Index Directive: " << _index << endl;
}

CgiDirective::CgiDirective() : Directive("cgi"), _default_conf(true), _exts() {}

CgiDirective::~CgiDirective() {}

void	CgiDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

bool	CgiDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

void	CgiDirective::appendExt(const string &ext) {
	_exts.push_back(ext);
}

bool	CgiDirective::isAllowed(const string &ext) const {
	for (vector<string>::const_iterator it=_exts.begin(); it != _exts.end(); ++it) {
		if (*it == ext)
			return (true);
	}
	return (false);
}

void	CgiDirective::print(void) const {
	cout << "CGI directives extensions:";
	for (vector<string>::const_iterator it = _exts.begin(); it != _exts.end(); ++it) {
		cout << "	" << *it;
	}
	cout << endl;
}

UploadDirDirective::UploadDirDirective() : Directive("upload_dir") {}

UploadDirDirective::~UploadDirDirective() {}

void	UploadDirDirective::setUploadDir(const string &upload_dir) {
	this->_upload_dir = upload_dir;
}

const string	&UploadDirDirective::getUploadDir(void) const {
	return (this->_upload_dir);
}

void	UploadDirDirective::print(void) const {
	cout << "Upload Dir Directive value: " << endl;
	cout << this->_upload_dir << endl;
};

ErrorPageDirective::ErrorPageDirective() : Directive("error_page"), _error_pages() {}

ErrorPageDirective::~ErrorPageDirective() {
	for (vector<ErrorPage *>::iterator it = _error_pages.begin(); it != _error_pages.end(); ++it)
		delete *it;
	_error_pages.clear();
}

void	ErrorPageDirective::appendErrorPage(ErrorPage *error_page) {
	this->_error_pages.push_back(error_page);
}

ErrorPage *ErrorPageDirective::back(void) const {
	return (this->_error_pages.back());
}

void	ErrorPageDirective::print(void) const {
	for (vector<ErrorPage *>::const_iterator it = _error_pages.begin(); it != _error_pages.end(); ++it) {
		(*it)->print();
	}
	return ;
}