# Sistema de Gerenciamento Esportivo - Docker

Este projeto contém uma aplicação C++ para gerenciamento de torneios esportivos com suporte completo ao Docker.

## 📋 Pré-requisitos

- Docker instalado no sistema
- Git (opcional, para clonar o repositório)

## 🚀 Como executar

### Opção 1: Usando os scripts automatizados

#### No Windows (PowerShell):
```powershell
# Construir e executar a aplicação
.\docker-run.ps1 build-run

# Ou executar comandos separadamente
.\docker-run.ps1 build
.\docker-run.ps1 run

# Limpar containers e imagens
.\docker-run.ps1 clean
```

#### No Linux/macOS (Bash):
```bash
# Dar permissão de execução
chmod +x docker-run.sh

# Construir e executar a aplicação
./docker-run.sh build-run

# Ou executar comandos separadamente
./docker-run.sh build
./docker-run.sh run

# Limpar containers e imagens
./docker-run.sh clean
```

### Opção 2: Comandos Docker manuais

```bash
# Construir a imagem
docker build -t sport-management .

# Executar a aplicação
docker run -it --rm sport-management

# Executar com nome personalizado do container
docker run -it --rm --name sport-app sport-management
```

## 🏗️ Estrutura do Docker

O Dockerfile está configurado para:

1. **Base**: Ubuntu 22.04 com ferramentas de desenvolvimento
2. **Dependências**: CMake, G++, Ninja Build System
3. **Build**: Compilação automática usando CMake + Ninja
4. **Dados**: Copia arquivos CSV necessários automaticamente
5. **Execução**: Executa a aplicação diretamente

## 📁 Arquivos Docker

- `Dockerfile` - Configuração principal do container
- `.dockerignore` - Arquivos ignorados durante o build
- `docker-run.ps1` - Script PowerShell para Windows
- `docker-run.sh` - Script Bash para Linux/macOS

## 🛠️ Personalização

### Modificar porta (se aplicável):
```dockerfile
EXPOSE 8080
```

### Adicionar volumes para persistência:
```bash
docker run -it --rm -v $(pwd)/data:/app/data sport-management
```

### Executar em modo debug:
```bash
docker run -it --rm --entrypoint /bin/bash sport-management
```

## 🐛 Troubleshooting

### Problema com permissões no Windows:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Container não inicia:
```bash
# Verificar logs
docker logs sport-app

# Entrar no container
docker run -it --rm --entrypoint /bin/bash sport-management
```

### Reconstruir após mudanças:
```bash
# Limpar cache
docker system prune -f

# Reconstruir sem cache
docker build --no-cache -t sport-management .
```

## 📊 Recursos da Aplicação

- Gerenciamento de jogadores
- Criação e organização de equipes
- Sistema de torneios
- Ranking automático
- Persistência de dados em CSV
- Interface interativa de console

## 🏆 Features do Docker

- ✅ Build automático com CMake
- ✅ Otimizado para C++20
- ✅ Copia dados necessários
- ✅ Limpeza automática
- ✅ Scripts de conveniência
- ✅ Suporte multiplataforma
