/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:29:20 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 18:29:20 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>

class Directive {
	public:
		virtual ~Directive() {};
};

class ServerDirective : public Directive {
	private:
		std::vector<Server *> _servers;
	public:
		ServerDirective();
		~ServerDirective();
		void			appendServer(const Server &server);
		Server			*back(void);
		const Server	&getServer(const std::string &host);
};

class ListenDirective : public Directive {
	private:
		const std::string _value;
	public:
		ListenDirective(const std::string &value);
		~ListenDirective() {};
};

class ServerNameDirective : public Directive {
	public:
		~ServerNameDirective() {};
};

class ClientMaxBodySizeDirective : public Directive {
	public:
		~ClientMaxBodySizeDirective() {};
};

class LocationDirective : public Directive {
	public:
		~LocationDirective() {};
};

class AllowMethodsDirective : public Directive {
	public:
		~AllowMethodsDirective() {};
};

class RedirectDirective : public Directive {
	public:
		~RedirectDirective() {};
};

class RootDirective : public Directive {
	public:
		~RootDirective() {};
};

class AutoIndexDirective : public Directive {
	public:
		~AutoIndexDirective() {};
};

class IndexDirective : public Directive {
	public:
		~IndexDirective() {};
};

class CgiDirective : public Directive {
	public:
		~CgiDirective() {};
};

class UploadDirDirective : public Directive {
	public:
		~UploadDirDirective() {};
};

class ErrorPageDirective : public Directive {
	public:
		~ErrorPageDirective() {};
};

void	initConf(void);