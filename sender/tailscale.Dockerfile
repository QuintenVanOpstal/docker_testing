FROM tailscale/tailscale:latest

USER root

# Copy your self-signed certificate into container
COPY ca.crt /usr/local/share/ca-certificates/ca.crt

# Install CA certificates tools and trust it
RUN apk add --no-cache \
    ca-certificates \
    curl \
    openssl && \
    update-ca-certificates --verbose
