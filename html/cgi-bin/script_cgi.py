#!/usr/bin/env python3

import os
import sys
#import cgi
#import cgitb

# Ativa o modo de debug para o CGI
#cgitb.enable()

# Função para processar requisições GET
def handle_get():
    print("<h2>Método: GET</h2>")
    query_string = os.environ.get("QUERY_STRING", "")
    if query_string:
        print(f"<p>Parâmetros recebidos: {query_string}</p>")
    else:
        print("<p>Nenhum parâmetro foi enviado.</p>")

# Função para processar requisições POST
def handle_post():
    print("<h2>Método: POST</h2>")
    content_length = os.environ.get("CONTENT_LENGTH")
    if content_length:
        post_data = sys.stdin.read(int(content_length))
        print(f"<p>Dados recebidos: {post_data}</p>")
    else:
        print("<p>Nenhum dado foi enviado.</p>")

# Função principal
def main():
    print("Content-Type: text/html\n")  # Cabeçalhos HTTP
    print("<html>")
    print("<head><title>Resultado CGI</title></head>")
    print("<body>")
    print("<h1>Resposta do servidor</h1>")

    # Determina o método da requisição
    request_method = os.environ.get("REQUEST_METHOD", "GET").upper()

    if request_method == "GET":
        handle_get()
    elif request_method == "POST":
        handle_post()
    else:
        print(f"<h2>Método {request_method} não suportado</h2>")

    print("</body>")
    print("</html>")

if __name__ == "__main__":
    main()
