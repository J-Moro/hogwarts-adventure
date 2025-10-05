@echo off
setlocal enabledelayedexpansion

set FILES=
REM Arquivos na raiz
set FILES=!FILES! main.cpp GerenciadorDeCenas.cpp

REM Caminhos explícitos para os Models
REM Ajuste estes caminhos se sua estrutura for diferente
set FILES=!FILES! Models/Cenas/Cena.cpp
set FILES=!FILES! Models/Cenas/CenaDeCombate.cpp
set FILES=!FILES! Models/Cenas/CenaDeTexto.cpp

set FILES=!FILES! Models/Personagens/personagens.cpp
set FILES=!FILES! Models/Personagens/Monstro.cpp
set FILES=!FILES! Models/Personagens/Jogador.cpp

set FILES=!FILES! Models/Itens/Item.cpp
set FILES=!FILES! Models/Itens/Arma.cpp
set FILES=!FILES! Models/Itens/Armadura.cpp
set FILES=!FILES! Models/Itens/ItemComum.cpp
set FILES=!FILES! Models/Itens/ItemMagico.cpp
REM Adicione quaisquer outros arquivos .cpp que estejam faltando aqui!

g++ -std=c++17 !FILES! -o main.exe

if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

main.exe