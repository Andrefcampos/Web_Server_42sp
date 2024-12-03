/* ************************************************************************** */
/*                                                                            */

/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/12 19:46:16 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "Webserv.hpp"
#include "Parser.hpp"
#include "Conf.hpp"
#include "defines.hpp"
#include "Handler.hpp"
#include <map>

using namespace std;

int main(int ac, char **av)
{
	if (ac <= 2) {
		try {
			Conf cf;
			Parser::parser(cf, (ac == 1 ? "conf/default.conf": av[1]));
		} catch (const exception &e) {
			cerr << e.what() << endl;
		}
	} else {
		cerr << "usage: ./webserv <path to configuration file> or just ./webserv" << endl;
		return (FAIL);
	}
	// Webserv Web(Services); 
	// Web.loopingEvent();
	return (SUCCESS);
}