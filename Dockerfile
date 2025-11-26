# Use Ubuntu as base image with build tools
FROM ubuntu:22.04

# Set metadata
LABEL authors="User"
LABEL description="Sistema de Gerenciamento Esportivo - Aplicação C++"

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY CMakeLists.txt .
COPY main.cpp .
COPY src/ ./src/

# Create build directory and build the application
RUN mkdir build && cd build && \
    cmake .. -G Ninja && \
    ninja

# Copy any necessary data files
COPY cmake-build-debug/*.csv ./build/ 2>/dev/null || true

# Set the working directory to build for execution
WORKDIR /app/build

# Run the application
CMD ["./sport"]
