/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:09:53 by andrefil          #+#    #+#             */
/*   Updated: 2024/12/05 13:29:50 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"
#include <stdexcept>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <sys/stat.h>


Cgi::Cgi(void) {}

Cgi::Cgi(Cgi const &obj) {
	*this = obj;
}

Cgi	&Cgi::operator=(Cgi const &obj) {
	if (this == &obj) {
		_scriptPath = obj._scriptPath;
		_body = obj._body;
		_headers = obj._headers;
	}
	return (*this);
}

Cgi::~Cgi(void) {}

Cgi::Cgi(std::string const &ScriptPath, std::map<std::string, std::string> const &Headers, std::string const &Body) : \
	_scriptPath(ScriptPath), _headers(Headers), _body(Body) {}

const std::string	&Cgi::getBody(void) const {
	return (_body);
}

const std::string	&Cgi::getSriptPath(void) const {
	return (_scriptPath);
}

const std::map<std::string, std::string> &Cgi::getHeader(void) const {
	return (_headers);
}

std::string Cgi::executeCgi(void) {
    int inPipe[2];  // Pipe para enviar dados para o script
    int outPipe[2]; // Pipe para receber a saída do script

    if (pipe(inPipe) == -1 || pipe(outPipe) == -1) {
        throw std::runtime_error("Failed pipe.");
    }

    pid_t pid = fork();

    if (pid < 0) {
        throw std::runtime_error("Failed Fork");
    } else if (pid == 0) {
        // Redireciona a entrada padrão para o pipe de entrada
        dup2(inPipe[0], STDIN_FILENO);
        close(inPipe[1]);

        // Redireciona a saída padrão para o pipe de saída
        dup2(outPipe[1], STDOUT_FILENO);
        close(outPipe[0]);

        // Monta os argumentos para o execv
        char *args[] = {const_cast<char *>(_scriptPath.c_str()), NULL};

        // Executa o script CGI
        execv(_scriptPath.c_str(), args);

        perror("execv fail");
        _exit(EXIT_FAILURE);
    } else {
        // Fecha a extremidade de leitura do pipe de entrada
        close(inPipe[0]);

        // Envia o corpo da requisição para o script pelo pipe
        if (!_body.empty()) {
            write(inPipe[1], _body.c_str(), _body.size());
        }
        close(inPipe[1]); // Fecha a extremidade de escrita após enviar os dados

        // Fecha a extremidade de escrita do pipe de saída
        close(outPipe[1]);

        // Lê a saída do script pelo pipe
        std::string result;
        char buffer[128];
        ssize_t bytesRead;
        while ((bytesRead = read(outPipe[0], buffer, sizeof(buffer))) > 0) {
            result.append(buffer, bytesRead);
        }
        close(outPipe[0]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            throw std::runtime_error("Script CGI error code.");
        }
        return result;
    }
}

void Cgi::initEnvp(void) {
	// Configura o método HTTP
	const std::string method = getHeader("REQUEST_METHOD");
	setenv("REQUEST_METHOD", method.c_str(), 1);

	// Configura o caminho da URL
	const std::string queryString = getHeader("QUERY_STRING");
	setenv("QUERY_STRING", queryString.c_str(), 1);

	// Configura o comprimento do corpo
	std::ostringstream contentLengthStream;
	contentLengthStream << _body.size();
	setenv("CONTENT_LENGTH", contentLengthStream.str().c_str(), 1);

	// Configura outras variáveis de ambiente comuns
	setenv("CONTENT_TYPE", getHeader("Content-Type").c_str(), 1);
	setenv("SCRIPT_NAME", getHeader("SCRIPT_NAME").c_str(), 1);
	setenv("SERVER_PROTOCOL", getHeader("SERVER_PROTOCOL").c_str(), 1);
}

std::string Cgi::getHeader(const std::string &key) {
	std::map<std::string, std::string>::const_iterator it = _headers.find(key);
	if (it != _headers.end()) {
		return it->second;
	}
	return ("");
}

void	Cgi::validateScriptPath(void) {
	if (_scriptPath.empty() || _scriptPath[0] != '/') {
		throw std::invalid_argument("O caminho do script deve ser absoluto.");
	}
	struct stat fileStat;
	if (stat(_scriptPath.c_str(), &fileStat) != 0) {
		throw std::invalid_argument("O script especificado não existe.");
	}
	if (!S_ISREG(fileStat.st_mode)) {
		throw std::invalid_argument("O caminho especificado não é um arquivo regular.");
	}
	if (!(fileStat.st_mode & S_IXUSR)) {
		throw std::invalid_argument("O script não tem permissão de execução.");
	}
}

void	Cgi::validateRequestBody(void) {
	// Limita o tamanho do corpo da requisição (exemplo: 1 MB)
	const size_t MAX_BODY_SIZE = 1024 * 1024; // 1 MB
	if (_body.size() > MAX_BODY_SIZE) {
		throw std::invalid_argument("O corpo da requisição é muito grande.");
	}

	for (char c : _body) {
		if (c < 32 && c != '\n' && c != '\r') {
			throw std::invalid_argument("O corpo da requisição contém caracteres inválidos.");
		}
	}
}

void	Cgi::validateInput(void) {
	validateScriptPath();
	validateRequestBody();
}

std::string Cgi::handleRequest(void) {
	// Valida o caminho do script e os dados recebidos
	validateInput();

	// Configura as variáveis de ambiente e executa o script
	initEnvp();
	return (executeCgi());
}
