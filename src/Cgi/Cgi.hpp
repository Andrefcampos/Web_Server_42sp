/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:15:12 by andrefil          #+#    #+#             */
/*   Updated: 2024/12/05 13:26:56 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <map>

class	Cgi {
	private:
		std::string _scriptPath;
		std::map<std::string, std::string> _headers;
		std::string _body;
	
		Cgi(void);
		Cgi(Cgi const &obj);
		Cgi &operator=(Cgi const &obj);

        void	validateScriptPath(void);
        void	validateRequestBody(void);
		void	validateInput(void);
		void	initEnvp(void);
		std::string	getHeader(const std::string &key);
		std::string	executeCgi(void);
		const	std::string &getSriptPath(void) const;
		const	std::string &getBody(void) const;
		const	std::map<std::string, std::string> &getHeader(void) const;

	public:
		Cgi(std::string const &ScriptPath, std::map<std::string, std::string> const &Headers, std::string const &Body);

		~Cgi(void);

		std::string	handleRequest(void);
};


