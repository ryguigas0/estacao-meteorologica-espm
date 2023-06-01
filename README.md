# Servidor da estacao Metereologica WHHU - ESPM

Repositório com o código do servidor estação metereológica feita para o projeto interdisciplinar 3 da ESPM

## Setup

1. Crie o arquivo `.env` contendo:
   - `ADMIN_KEY`: valor da chave de autorização de utilização de endpoints
   - `DB_NAME`: nome do banco de dados que vai ficar na pasta `.data`, por padrão é `estacao`
   - `PORT`: porta de acesso do servidor, por padrão é `3000`
2. Rode `npm i`
3. Abra no navegador o link `localhost:PORT` ou faça uma requisição `GET` para `localhost:PORT/routes` (coleção de rotas do Insomnia no arquivo `insomnia_collection.json`)

## Baixando o banco de dados

1. Fazer download do projeto no glitch
2. Extrair o arquivo `.tgz` na pasta
3. Baixar um [navegador de banco de dados sqlite](https://sqlitebrowser.org/dl/)
4. Usar o navegador de banco de dados sqlite para explorar o arquivo `estacao.db`
