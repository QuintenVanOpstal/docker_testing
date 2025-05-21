# Headscale Sender-Reciever Project

## overview
Secure container communication system using Headscale/Tailscale networking.

## Prerequisites

- Docker
- Headscale server (local or remote)

## Running the project

### 1. configure Environment reciever

```bash
cp reciever/.env.default reciever/.env
vim .env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
```

### 2. run the reciever

```bash
cd reciever
docker compose up
```

### 3. setup sender
```bash
docker exec -ti reciever-ts-reciever-1 tailscale ip # To get the ip of the reciever
cp sender/.env.default sender/.env
vim .env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
         # RECEIVER_IP=<THE_IP>
```

### 4. run the sender

```bash
cd sender
docker compose up
```

## Shuting down
press ctrl + c in both terminals

execute the following in both directories
```bash
docker compose down
```




