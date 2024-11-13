/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:16:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 19:48:52 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <map>
# include <vector>
# include <fstream>
# include "Handler.hpp"

class Server;
class Location;
class Directive;

namespace Parser {
	void	parser(Conf &cf, const char *pathname);
	void	open_file(Conf &cf);
	void	get_args(Conf &cf);
	void	conf_handler(Conf &cf, unsigned int last);
	int		read_conf_token(Conf &cf);
}
