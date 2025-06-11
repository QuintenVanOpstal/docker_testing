FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    ffmpeg \
    libx11-6 \
    libgl1 \
    xauth && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

ENV DISPLAY=:0

ENTRYPOINT ["ffplay"]

