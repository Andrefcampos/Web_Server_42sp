/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:10:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/11 23:11:06 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <fstream>
# include <string>
# include <vector>
# include <map>

class Location;
class Server;
class Handler;

struct ConfFile {
	const char		*pathname;
	std::streampos	file_size;
	std::ifstream	file;
	ConfFile();
};

struct Conf {
	ConfFile					*conf_file;
	Server						*current_server;
	Location					*current_location;
	std::vector<std::string>	args;
	std::map<std::string, Handler *> handlers;
	size_t						init;
	size_t						curr;
	std::string					content;
	unsigned int				line;
	unsigned int				ctx;
	Conf();
	~Conf();
};
