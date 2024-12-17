/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectiveVisitor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:40:34 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/15 15:40:34 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectiveVisitor.hpp"
#include "Directive.hpp"

// GetterVisitor::GetterVisitor() : _result(0) {}

// GetterVisitor::~GetterVisitor() {}

// void    GetterVisitor::visit(const ServerDirective *server) {
// 	this->_result = server; 
// }

// void	GetterVisitor::visit(const ListenDirective *listen) {
// 	this->_result = listen; 
// }

// void	GetterVisitor::visit(const ServerNameDirective *server_name) {
// 	this->_result = server_name; 
// }

// void	GetterVisitor::visit(const LocationDirective *location) {
// 	this->_result = location; 
// }

// void	GetterVisitor::visit(const ClientMaxBodySizeDirective *client_max_body_size) {
// 	this->_result = client_max_body_size; 
// }

// void	GetterVisitor::visit(const AllowMethodsDirective *allow_methods) {
// 	this->_result = allow_methods; 
// }

// void	GetterVisitor::visit(const RedirectDirective *redirect) {
// 	this->_result = redirect; 
// }

// void	GetterVisitor::visit(const RootDirective *root) {
// 	this->_result = root; 
// }

// void	GetterVisitor::visit(const AutoIndexDirective *auto_index) {
// 	this->_result = auto_index; 
// }

// void	GetterVisitor::visit(const IndexDirective *index) {
// 	this->_result = index; 
// }

// void	GetterVisitor::visit(const CgiDirective *cgi) {
// 	this->_result = cgi; 
// }

// void	GetterVisitor::visit(const UploadDirDirective *upload_dir) {
// 	this->_result = upload_dir; 
// }

// void	GetterVisitor::visit(const ErrorPageDirective *error_page) {
// 	this->_result = error_page; 
// }

// ConfigVisitor::ConfigVisitor(const int epoll_fd) : _epoll_fd(epoll_fd) {}

// ConfigVisitor::~ConfigVisitor() {}

// void	ConfigVisitor::visit(const ServerDirective *server) {
// 	struct epoll_event ev;
// 	ListenDirective *listen;
// 	GetterVisitor   getter;

// 	if (server.size() < 1)
// 		throw (runtime_error("webserv: no server configured"));
// 	for (vector<Server *>::iterator it = server._servers.begin(); it != server._servers.end(); ++it) {
// 		getter.visit((*it)->getDirective("listen"));    
// 		listen = getter.getResult<ListenDirective *>();
// 		(*it)->setSocketFd((*it)->initTCP(listen_obj->getPort().c_str(), 5, listen_obj->getIP().c_str()));
// 	}
// 	memset(&ev, 0, sizeof(ev));
// 	ev.events = EPOLLIN;
// 	for (vector<Server *>::iterator it = server._servers.begin(); it != server._servers.end(); ++it) {
// 		ev.data.fd = (*it)->getSocketFd();
// 		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
// 			throw (runtime_error("error: epoll_ctl()"));
// 	}
// }

// void	ConfigVisitor::visit(const ListenDirective *listen) {}

// void	ConfigVisitor::visit(const ServerNameDirective *server_name) {}

// void	ConfigVisitor::visit(const LocationDirective *location) {}

// void	ConfigVisitor::visit(const ClientMaxBodySizeDirective *client_max_body_size) {}

// void	ConfigVisitor::visit(const AllowMethodsDirective *allow_methods) {}

// void	ConfigVisitor::visit(const RedirectDirective *redirect) {}

// void	ConfigVisitor::visit(const RootDirective *root) {}

// void	ConfigVisitor::visit(const AutoIndexDirective *auto_index) {}

// void	ConfigVisitor::visit(const IndexDirective *index) {}

// void	ConfigVisitor::visit(const CgiDirective *cgi) {}

// void	ConfigVisitor::visit(const UploadDirDirective *upload_dir) {}

// void	ConfigVisitor::visit(const ErrorPageDirective *error_page) {}
