FROM ubuntu:24.04

WORKDIR /app

# Works, but when there is no winsock
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    ninja-build \
    libpq-dev \
    libpqxx-dev \
    libsodium-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN rm -rf build && \ 
    mkdir -p build && \
    cd build && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && \
    ninja

CMD ["./build/app"]