# NomeDoProjeto

Descrição
- Projeto em C++ com estrutura típica para desenvolvimento e testes automatizados.
- Compatível com CLion 2025.2.4 (Windows) e linha de comando com CMake.

Pré-requisitos
- `CLion` (opcional) ou `cmake` \>= 3.20
- Compilador C++ com suporte a C++17/C++20 (MSVC, GCC, Clang)
- Gerador de build: `Ninja` ou `Visual Studio` (Windows)

Estrutura do repositório
- `CMakeLists.txt` - configuração do CMake
- `src/` - código-fonte
- `include/` - headers públicos
- `tests/` - testes unitários
- `build/` - diretório de build (gerado)

Build (linha de comando - multiplataforma)
1. Criar diretório de build:
   - `mkdir build`
   - `cd build`
2. Gerar os arquivos de build:
   - `cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..`
     (ou use o gerador de Visual Studio no Windows)
3. Compilar:
   - `cmake --build . --config Release`

Build com CLion (Windows)
- Abrir o projeto em `CLion` apontando para o `CMakeLists.txt`.
- Selecionar toolchain (\`MSVC\` ou \`MinGW\`), configurar gerador (`Ninja` recomendado).
- Build via Run | Build ou botão de build.

Execução
- Executável gerado em `build/` (ex.: `.\build\Release\NomeDoProjeto.exe` no Windows ou `./build/NomeDoProjeto` no Unix).
- Exemplo:
  - Windows: `.\build\Release\NomeDoProjeto.exe`
  - Unix: `./build/NomeDoProjeto`

Testes
- Se testes são configurados com CTest/GoogleTest:
  - Dentro de `build/`: `ctest --output-on-failure -C Release`
- Alternativamente executar o binário de testes em `build/tests/`

Como contribuir
- Abrir issue para discutir mudanças.
- Criar branch de feature/fix e submeter Pull Request.
- Seguir o padrão de estilo do projeto e adicionar/atualizar testes.

Boas práticas
- Usar `clang-tidy`/`cppcheck` para análise estática.
- Manter `CMakeLists.txt` simples e modular.
- Cobertura de testes mínima para funcionalidades críticas.

Licença
- Adicionar arquivo `LICENSE` (ex.: MIT) conforme necessidade.