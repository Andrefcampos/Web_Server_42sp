/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:14:23 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 19:49:00 by myokogaw         ###   ########.fr       */
/*                                                                             */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include "defines.hpp"
#include "Logger.hpp"
#include "Parser.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "Handler.hpp"
#include "Conf.hpp"
#include "Directive.hpp"

using namespace std;

void	Parser::open_file(Conf &cf) {
	cf.conf_file->file.open(cf.conf_file->pathname, ios::in | ios::binary | ios::ate);
	if (cf.conf_file->file.is_open() == false)
		throw (runtime_error(Logger::cf_file_err(cf.conf_file->pathname, strerror(errno))));
	cf.conf_file->file_size = cf.conf_file->file.tellg();
	cf.conf_file->file.seekg(0, ios::beg);
}

int		Parser::read_conf_token(Conf &cf) {
	char	ch = 0;
	int		len = 0;
	bool	sharp_comment = false, last_space = false, found = false;

	for (;;) {
		if (cf.curr >= cf.content.size()) {
			if (cf.conf_file->file.is_open() == false)
				return (CONF_FILE_DONE);
			size_t size = cf.conf_file->file_size - cf.conf_file->file.tellg();
			if (size > BUFFER_SIZE)
				size = BUFFER_SIZE;
			char buf[size + 1];
			std::memset(buf, 0, size + 1);
			cf.conf_file->file.read(buf, size);
			if (cf.conf_file->file.tellg() == cf.conf_file->file_size)
				cf.conf_file->file.close();
			cf.content.clear();
			cf.content.insert(0, buf);
			cf.init = 0;
			cf.curr = 0;
		}
		ch = cf.content[cf.curr++];

		if (ch == '\n') {
			cf.line++;
			if (sharp_comment)
				sharp_comment = false;
		}
		else if (sharp_comment)
			continue ;
		if (last_space) {
			if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')
				continue ;
			switch (ch) {
				case '#':
					sharp_comment = true;
					continue ;
				case '{':
					if (cf.args.size() == 0)
						throw (runtime_error(Logger::cf_syntax_err(cf, "{", "unexpected", cf.line)));
					return (CONF_BLOCK_START);
				case '}':
					if (cf.args.size() != 0)
						throw (runtime_error(Logger::cf_syntax_err(cf, "}", "unexpected", cf.line)));
					return (CONF_BLOCK_DONE);
				case ';':
					return (CONF_OK);
				default:
					last_space = false;
			}
		}
		else if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == ';' || ch == '{') {
				last_space = true;
				found = true;
		}
		if (found && len != 0) {
			stringstream ss(cf.content.substr(cf.curr - len, len));
			string token;
			ss >> token;
			if (token.size() != 0)
				cf.args.push_back(token);
			len = 0;
		}
		if (ch == ';') {
			return (CONF_OK);
		}
		if (ch == '{') {
			if (cf.args.size() == 0)
				throw (runtime_error(Logger::cf_syntax_err(cf, "{", "unexpected", cf.line)));
			return (CONF_BLOCK_START);
		}
		found = false;
		len++;
	}
}

void	Parser::conf_handler(Conf &cf, unsigned int last) {
	Handler *handler = cf.handlers[*cf.args.begin()];
	if (handler) {
		unsigned int type = handler->getType();
		if (!(type & CONF_BLOCK) && last != CONF_OK)
			throw (runtime_error(Logger::log_error(cf, "\"%s\" directive is not terminated by \";\"", cf.args.begin()->c_str())));
		if ((type & CONF_BLOCK) && last != CONF_BLOCK_START)
			throw (runtime_error(Logger::log_error(cf, "directive \"%s\" has no opening \"{\"", cf.args.begin()->c_str())));
		if (!(type & cf.ctx))
			throw (runtime_error(Logger::log_error(cf, "\"%s\" directive is not allowed here", cf.args.begin()->c_str())));
		if (type & CONF_NOARGS) {
			if (cf.args.size() != 1)
				throw (runtime_error(Logger::log_error(cf, "invalid number of arguments in \"%s\" directive", cf.args.begin()->c_str())));
		} else if (type & CONF_TAKE1) {
			if (cf.args.size() > 2 || cf.args.size() == 1)
				throw (runtime_error(Logger::log_error(cf, "invalid number of arguments in \"%s\" directive", cf.args.begin()->c_str())));
		} else if (type & CONF_1MORE) {
			if (cf.args.size() < 2)
				throw (runtime_error(Logger::log_error(cf, "invalid number of arguments in \"%s\" directive", cf.args.begin()->c_str())));
		} else if (type & CONF_2MORE) {
			if (cf.args.size() < 3)
				throw (runtime_error(Logger::log_error(cf, "invalid number of arguments in \"%s\" directive", cf.args.begin()->c_str())));
		}
		handler->process(cf);
	} else
		throw (runtime_error(Logger::log_error(cf, "\"%s\" unknown directive", cf.args.begin()->c_str())));
}

void	Parser::parser(Conf &cf, const char *pathname) {
	int rc = 0;

	if (pathname) {
		cf.conf_file->pathname = pathname;
		open_file(cf);
	}
	for (;;) {
		/*
			read_conf_token pode retornar
			CONF_OK  quando ';' é encontrado
			CONF_BLOCK_START quando '{' é encontrado
			CONF_BLOCK_DONE quando '}' é encontrado
			CONF_FILE_DONE quando end-of-file é alcançado
		*/
		rc = read_conf_token(cf);
		if (rc == CONF_BLOCK_DONE)
			return ;
		if (rc == CONF_FILE_DONE)
			return ;
		// if (rc == CONF_FILE_DONE)
		// 	throw (std::runtime_error())
		conf_handler(cf, rc);
	}
}