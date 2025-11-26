#!/bin/bash

# Script para construir e executar a aplicação Docker
# Sistema de Gerenciamento Esportivo

echo "=================================================="
echo "  Sistema de Gerenciamento Esportivo - Docker"
echo "=================================================="

# Nome da imagem Docker
IMAGE_NAME="sport-management"
CONTAINER_NAME="sport-app"

# Função para construir a imagem
build_image() {
    echo "🔨 Construindo imagem Docker..."
    docker build -t $IMAGE_NAME .
    if [ $? -eq 0 ]; then
        echo "✅ Imagem construída com sucesso!"
    else
        echo "❌ Erro ao construir imagem!"
        exit 1
    fi
}

# Função para executar o container
run_container() {
    echo "🚀 Executando aplicação..."
    docker run -it --rm --name $CONTAINER_NAME $IMAGE_NAME
}

# Função para limpar containers e imagens
clean() {
    echo "🧹 Limpando containers e imagens..."
    docker stop $CONTAINER_NAME 2>/dev/null || true
    docker rm $CONTAINER_NAME 2>/dev/null || true
    docker rmi $IMAGE_NAME 2>/dev/null || true
    echo "✅ Limpeza concluída!"
}

# Menu principal
case "$1" in
    "build")
        build_image
        ;;
    "run")
        run_container
        ;;
    "build-run")
        build_image
        run_container
        ;;
    "clean")
        clean
        ;;
    *)
        echo "Uso: $0 {build|run|build-run|clean}"
        echo ""
        echo "Comandos disponíveis:"
        echo "  build     - Constrói a imagem Docker"
        echo "  run       - Executa a aplicação"
        echo "  build-run - Constrói e executa"
        echo "  clean     - Remove containers e imagens"
        echo ""
        echo "Exemplo: $0 build-run"
        exit 1
        ;;
esac
