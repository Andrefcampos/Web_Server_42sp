/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:39:00 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/11 23:39:01 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <cstdarg>
#include "Logger.hpp"
#include "Conf.hpp"

const std::string Logger::cf_file_err(const char *filename, const std::string &err) {
	std::ostringstream oss;
	oss << "webserv: configuration file error: " << filename << " (" << err << ")";
	return oss.str();
}

const std::string Logger::cf_syntax_err(Conf &cf, const std::string &wrongToken, const std::string &err, int line) {
	std::ostringstream oss;
	oss << "webserv: \"" << wrongToken << "\" " << err << " in " << cf.conf_file->pathname << ":" << line;
	return (oss.str());
}

const std::string	Logger::log_error(Conf &cf, const char *fmt, ...) {
	std::ostringstream oss;
	char buf[4096];
	va_list	args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);
	oss << "webserv: ";
	oss << buf;
	oss << " in " << cf.conf_file->pathname << ":" << cf.line;
	return (oss.str());
}