/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:21:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/11 22:07:28 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <map>
#include <iostream>
#include <unistd.h>
#include "Webserv.hpp"
#include "Directive.hpp"
#include "Request.hpp"
#include "utils.hpp"
#include "ABody.hpp"
#include "DataBody.hpp"
#include "defines.hpp"
#include "Server.hpp"

using namespace std;

Webserv manager;

Webserv::Webserv() : ParseRequest(), _nfds(0) {
	for(int i = 0; i < 80; i++)
		memset(&_events[i], 0, sizeof(_events[i]));
	memset(&_ev, 0, sizeof(_ev));
	if ((_epollFd = epoll_create1(EPOLL_CLOEXEC)) == -1)
		throw (runtime_error("error: epoll_create1()"));
	_conf["server"] = new ServerDirective();
};

Webserv::~Webserv() {
	for (map<string, Directive *>::iterator it = _conf.begin(); it != _conf.end(); ++it)
		delete it->second;
	_conf.clear();
};

void	Webserv::setting(void) {
	ServerDirective *server_directive = static_cast<ServerDirective *>(_conf["server"]);
	if (server_directive->size() < 1)
		throw (runtime_error("webserv: no server configured"));
	server_directive->initServers();
	server_directive->addSocketsToEpoll(_epollFd);
}

void	Webserv::loopingEvent() {
	while(true) {
		_nfds = epoll_wait(_epollFd, _events, MAX_EVENTS, 1000);
		if (_nfds == 0){
			checkTimeOut();
		}
		for(int index_epoll = 0; index_epoll < _nfds; index_epoll++){
			if (static_cast<ServerDirective *>(_conf["server"])->isNewClient(_events[index_epoll].data.fd, _epollFd, _client))
				continue ;
			Client *client = (Client *)_events[index_epoll].data.ptr;
			if (not client->getRequest()){
				Request *request = setBufferSocketFd(client->getFdClient());
				if (request){
					client->setRequest((void*)request);
					epoll_CTRL(client->getFdClient(), EPOLLOUT, EPOLL_CTL_MOD, (void*)(client));
				}
			}else{
				responseClient((Request*)client->getRequest(), client);
			}
		}
	}
}

void exemploRequestParseado(Request *request);

int	Webserv::responseClient(Request *request, Client *client){
	int	error = request->getParserError();
	if (error){
		cout << "Number Error: " << error << "\n";
		delete request;
		_socket.erase(client->getFdClient());
		epoll_CTRL(client->getFdClient(), EPOLLOUT, EPOLL_CTL_DEL, NULL);
		close(client->getFdClient());
		delete client;
		return (0);
	}
	Server *server = client->getServer();
	server->sendResponse(client->getFdClient(), request);
	exemploRequestParseado(request);
	delete request;
	_socket.erase(client->getFdClient());
	epoll_CTRL(client->getFdClient(), EPOLLOUT, EPOLL_CTL_DEL, NULL);
	close(client->getFdClient());
	delete client;
	return (0);
}

void exemploRequestParseado(Request *request){
	cout << "Method: " << request->getMethod() << "\n";
	cout << "Host: " << request->getHost() << "\n";
	cout << "Path: " << request->getPath() << "\n";
	cout << "Version: " << request->getVersion() << "\n";

	putMapList(request->getAllHeader());
	cout << "\n";
 	ABody *ptr = request->getBody();
	if (ptr != NULL){
		list<DataBody>	body;
	 	body = ptr->getDataBody();
		for (list<DataBody>::iterator it = body.begin(); it != body.end(); it++){
			putMapList(it->getAllHeaders());
			list<string> temp = it->getHeaders("Content-Type");
			if (not temp.empty()){
				list<string> t = it->getHeaders("Content-Disposition");
				list<string>::iterator i = t.end();
				i--;
				i->erase(0, 10);
				i->erase(i->size()-1, 1);
				ofstream	outfile(i->c_str());
				if (!outfile.is_open())
					cout << "nao abriu\n";
				if(it->getContent().length() > 60)
					outfile << it->getContent();
			}
		}
	}
}

void	Webserv::epoll_CTRL(int clientFd, int event, int flagCTLR, void *ptr){
	struct epoll_event ev;

	ev.data.ptr = ptr;
	ev.events = event;
	if (epoll_ctl(_epollFd, flagCTLR, clientFd, &ev) == -1)
		throw (runtime_error("error: epoll_ctl()"));
}

void	Webserv::checkTimeOut(){
	std::list<Client*>::iterator it = _client.begin();;

	while (it != _client.end()){
		if ((*it)->timeOutRequest()){
			Request *request = (Request *)(*it)->getRequest();
			Server *server = (Server *)(*it)->getServer();
			removeFD((*it)->getFdClient());
			close((*it)->getFdClient());
			if (request)
				delete request;
			if (server)
				delete server;
			it = _client.erase(it);
		}else
			it++;
	}
}
