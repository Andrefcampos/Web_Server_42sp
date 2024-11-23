/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:11:39 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/11 23:44:44 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Server.hpp"
#include "Conf.hpp"
#include "defines.hpp"
#include "Handler.hpp"

ConfFile::ConfFile() {
	this->file_size = 0;
}

Conf::Conf(void) : args(), content("") {
	static ConfFile conf_file;
	this->init = 0;
	this->curr = 0;
	this->line = 1;
	this->conf_file = &conf_file;
	this->args.clear();
	this->ctx = MAIN_CONF;
	initHandlerModules(*this);
}

Conf::~Conf(void) {
	for (std::map<std::string, Handler *>::iterator it=handlers.begin(); it != handlers.end(); ++it)
		delete it->second;
	handlers.clear();
}
