# Script PowerShell para construir e executar a aplicação Docker
# Sistema de Gerenciamento Esportivo

param(
    [Parameter(Mandatory=$true)]
    [ValidateSet("build", "run", "build-run", "clean")]
    [string]$Action
)

# Nome da imagem Docker
$ImageName = "sport-management"
$ContainerName = "sport-app"

Write-Host "==================================================" -ForegroundColor Cyan
Write-Host "  Sistema de Gerenciamento Esportivo - Docker" -ForegroundColor Cyan
Write-Host "==================================================" -ForegroundColor Cyan

function Build-Image {
    Write-Host "🔨 Construindo imagem Docker..." -ForegroundColor Yellow
    docker build -t $ImageName .
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ Imagem construída com sucesso!" -ForegroundColor Green
    } else {
        Write-Host "❌ Erro ao construir imagem!" -ForegroundColor Red
        exit 1
    }
}

function Run-Container {
    Write-Host "🚀 Executando aplicação..." -ForegroundColor Yellow
    docker run -it --rm --name $ContainerName $ImageName
}

function Clean-Docker {
    Write-Host "🧹 Limpando containers e imagens..." -ForegroundColor Yellow
    docker stop $ContainerName 2>$null
    docker rm $ContainerName 2>$null
    docker rmi $ImageName 2>$null
    Write-Host "✅ Limpeza concluída!" -ForegroundColor Green
}

switch ($Action) {
    "build" {
        Build-Image
    }
    "run" {
        Run-Container
    }
    "build-run" {
        Build-Image
        Run-Container
    }
    "clean" {
        Clean-Docker
    }
}
