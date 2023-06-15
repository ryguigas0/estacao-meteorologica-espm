# Projeto Interdisciplinar III - Sistemas de Informação ESPM

<p align="center">
    <a href="https://www.espm.br/cursos-de-graduacao/sistemas-de-informacao/"><img src="https://raw.githubusercontent.com/tech-espm/misc-template/main/logo.png" alt="Sistemas de Informação ESPM" style="width: 375px;"/></a>
</p>

# Estacao Metereologica WHHU

### 2023-01

## Integrantes
- [Victor Machado](https://github.com/victorkeffer)
- [Guilherme Casagrande](https://github.com/ryguigas0/)

## Descrição do Projeto

O projeto consiste em uma estacao metereologica capaz de detectar a temperatura e a humidade do ambiente

## Como instalar o projeto

1. Crie o arquivo `.env` contendo:
   - `ADMIN_KEY`: valor da chave de autorização de utilização de endpoints
   - `DB_NAME`: nome do banco de dados que vai ficar na pasta `.data`, por padrão é `estacao`
   - `PORT`: porta de acesso do servidor, por padrão é `3000`
2. Rode `npm i`
3. Abra no navegador o link `localhost:PORT` ou faça uma requisição `GET` para `localhost:PORT/routes` (coleção de rotas do [Insomnia](https://insomnia.rest) no arquivo `insomnia_collection.json`)

## Como baixar o banco de dados

1. Fazer download do projeto no glitch
2. Extrair o arquivo `.tgz` na pasta
3. Baixar um [navegador de banco de dados sqlite](https://sqlitebrowser.org/dl/)
4. Usar o navegador de banco de dados sqlite para explorar o arquivo `.db` 

# Licença

Este projeto é licenciado sob a [MIT License](https://github.com/tech-espm/misc-template/blob/main/LICENSE).

<p align="right">
    <a href="https://www.espm.br/cursos-de-graduacao/sistemas-de-informacao/"><img src="https://raw.githubusercontent.com/tech-espm/misc-template/main/logo-si-512.png" alt="Sistemas de Informação ESPM" style="width: 375px;"/></a>
</p>

