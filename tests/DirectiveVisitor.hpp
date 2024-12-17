/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visitor.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:18:01 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/15 15:18:01 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ServerDirective;
class ListenDirective;
class ServerNameDirective;
class LocationDirective;
class ClientMaxBodySizeDirective;
class AllowMethodsDirective;
class RedirectDirective;
class RootDirective;
class AutoIndexDirective;
class IndexDirective;
class CgiDirective;
class UploadDirDirective;
class ErrorPageDirective;

class DirectiveVisitor {
	public:
		virtual ~DirectiveVisitor() {};

		virtual void	visit(const ServerDirective *server) = 0;
		virtual void	visit(const ListenDirective *listen) = 0;
		virtual void	visit(const ServerNameDirective *server_name) = 0;
		virtual void	visit(const LocationDirective *location) = 0;
		virtual void	visit(const ClientMaxBodySizeDirective *client_max_body_size) = 0;
		virtual void	visit(const AllowMethodsDirective *allow_methods) = 0;
		virtual void	visit(const RedirectDirective *redirect) = 0;
		virtual void	visit(const RootDirective *root) = 0;
		virtual void	visit(const AutoIndexDirective *auto_index) = 0;
		virtual void	visit(const IndexDirective *index) = 0;
		virtual void	visit(const CgiDirective *cgi) = 0;
		virtual void	visit(const UploadDirDirective *upload_dir) = 0;
		virtual void	visit(const ErrorPageDirective *error_page) = 0;
};

class GetterVisitor : public DirectiveVisitor {
	private:
		void	*_result;
	public:
		GetterVisitor();
		~GetterVisitor();

		void	visit(const ServerDirective *server);
		void	visit(const ListenDirective *listen);
		void	visit(const ServerNameDirective *server_name);
		void	visit(const LocationDirective *location);
		void	visit(const ClientMaxBodySizeDirective *client_max_body_size);
		void	visit(const AllowMethodsDirective *allow_methods);
		void	visit(const RedirectDirective *redirect);
		void	visit(const RootDirective *root);
		void	visit(const AutoIndexDirective *auto_index);
		void	visit(const IndexDirective *index);
		void	visit(const CgiDirective *cgi);
		void	visit(const UploadDirDirective *upload_dir);
		void	visit(const ErrorPageDirective *error_page);

		template<typename T>
		T* getResult(void) const {
			return (static_cast<T *>(_result));
		}
};

class ConfigVisitor : public DirectiveVisitor {
	private:
		int	_epoll_fd;
	public:
		ConfigVisitor(const int epoll_fd);
		~ConfigVisitor();

		void	visit(const ServerDirective *server);
		void	visit(const ListenDirective *listen);
		void	visit(const ServerNameDirective *server_name);
		void	visit(const LocationDirective *location);
		void	visit(const ClientMaxBodySizeDirective *client_max_body_size);
		void	visit(const AllowMethodsDirective *allow_methods);
		void	visit(const RedirectDirective *redirect);
		void	visit(const RootDirective *root);
		void	visit(const AutoIndexDirective *auto_index);
		void	visit(const IndexDirective *index);
		void	visit(const CgiDirective *cgi);
		void	visit(const UploadDirDirective *upload_dir);
		void	visit(const ErrorPageDirective *error_page);
};
