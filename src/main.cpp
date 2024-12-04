/* ************************************************************************** */
/*                                                                            */

/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/14 08:06:22 by rbutzke          ###   ########.fr       */
/*   Updated: 2024/11/12 19:46:16 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Webserv.hpp"
#include "Server.hpp"
#include "Parser.hpp"
#include "Conf.hpp"
#include "Handler.hpp"
#include "defines.hpp"

using namespace std;

int main(int ac, char **av)
{
	if (ac <= 2) {
		try {
			Conf cf;
			Parser::parser(cf, (ac == 1 ? "conf/default.conf": av[1]));
			manager.setting();
			manager.loopingEvent();
		} catch (const exception &e) {
			cerr << e.what() << endl;
		}
	} else {
		cerr << "usage: ./webserv <path to configuration file> or just ./webserv" << endl;
		return (FAIL);
	}
	return (SUCCESS);
}