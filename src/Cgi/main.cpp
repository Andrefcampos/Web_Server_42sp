#include "Cgi.hpp"
#include <iostream>
#include <map>

int main() {
    try {
        // Configurações de teste
        std::string scriptPath = "/../../html/cgi-bin/run_get_cgi.sh"; // Atualize com o caminho real do script
        std::map<std::string, std::string> headers;
		headers["REQUEST_METHOD"] = "GET";
		headers["QUERY_STRING"] = "param1=value1&param2=value2";
		headers["Content-Type"] = "application/json";
		headers["SCRIPT_NAME"] = "script_cgi.py";
		headers["SERVER_PROTOCOL"] = "HTTP/1.1";
        std::string body = "{\"key\":\"value\"}";

        // Cria o objeto CGI
        Cgi cgi(scriptPath, headers, body);

        // Chama o método handleRequest
        std::string responseBody = cgi.handleRequest();

        // Exibe a saída do CGI
        std::cout << "Resposta do script CGI:\n" << responseBody << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
