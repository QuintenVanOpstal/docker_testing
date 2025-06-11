# Use an official CMake-ready image
FROM ubuntu:22.04

# Install necessary tools
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    libboost-all-dev \
    libwebsocketpp-dev \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Create and set working directory
WORKDIR /receiver

# Copy your source code into the container
COPY . .

# Build commands (will be executed when container runs)
CMD mkdir -p build && \
    cd build && \
    cmake .. && \
    cmake --build . && \
    ./test_receiver
