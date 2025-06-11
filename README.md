# Headscale Sender-Reciever Project

## overview
Secure container communication system using Headscale/Tailscale networking.
And streaming a webcam to a RTMP-server

## Prerequisites

- Docker
- Headscale server (local or remote)

## Running a websocket and sending data to it via headscale

### 1. configure Environment reciever

```bash
cp receiver/.env.default reciever/.env
vim rceiver/.env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
```

### 2. run the receiver

```bash
cd receiver
docker compose up
```

### 3. setup sender
```bash
cp sender/.env.default sender/.env
vim sender/.env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
```

### 4. run the sender

```bash
cd sender
docker compose up
```

Now the sender wil send intigers to a websocket running on the recieving side. The intiger gets printed.

### Shuting down
press ctrl + c in both terminals

execute the following in both directories
```bash
docker compose down
```

## Setting up the camera

This section is detecated to setting up a RTMP server, livestreaming to it. And looking at the live stream. THis with minimal delay.

### starting the RTMP server (No Tailscale)

You can start the RTMP server by running:

```bash
cd RTMP-server
docker compose --profile standalone up nginx-rtmp
```

To exit it press ctrl + c

### Starting ffmpeg (No Tailscale)

To start the ffmpeg (capturing video) run:
```bash
cd webcam
cp .env.default .env
vim .env # change INPUT_DEVICE to your webcam
    # change LOCATION_RTMP to the ip of the RTMP server
docker compose -f docker-compose.yml up
```

To exit it press ctrl + c

### Starting ffplay (No Tailscale)

To start ffplay (display the video)

```bash
cd stream
cp .env.default .env
vim .env # change LOCATION_RTMP to the ip of the RTMP server
docker compose -f docker-compose.yml up
```

## setting up the camera with Tailscale

Setup the camera using Tailscale

### starting the RTMP server (Tailscale)

You can start the RTMP server by running:

```bash
cd RTMP-server
cp .env.default .env
vim .env # change HEADSCALE_AUTHKEY to the authentication key of your headscale/tailscale instance
    # change HEADSCALE_TAILNET to the url of the headscale server
    # chanhe HEADSCALE_TAG to the tag coresponding to the headscale_authkey (tag:rtmp)
docker compose --profile tailscale up nginx-rtmp-tailscale ts-rtmp
```

To exit it press ctrl + c

### Starting ffmpeg (Tailscale)

To start the ffmpeg (capturing video) run:
```bash
cd webcam
cp .env.default .env
vim .env # change INPUT_DEVICE to your webcam
    # change LOCATION_RTMP to the ip of the RTMP server
    # change HEADSCALE_AUTHKEY to the authentication key of your headscale/tailscale instance
    # change HEADSCALE_TAILNET to the url of the headscale server
    # chanhe HEADSCALE_TAG to the tag coresponding to the headscale_authkey (tag:rtmp)
docker compose -f docker-compose.yml -f docker-compose-tailscale.yml up
```

### Starting ffplay (No Tailscale)

To start ffplay (display the video)

```bash
cd stream
cp .env.default .env
vim .env # change LOCATION_RTMP to the ip of the RTMP server
    # change HEADSCALE_AUTHKEY to the authentication key of your headscale/tailscale instance
    # change HEADSCALE_TAILNET to the url of the headscale server
    # chanhe HEADSCALE_TAG to the tag coresponding to the headscale_authkey (tag:rtmp)
docker compose -f docker-compose.yml -f docker-compose-tailscale.yml up
```

To exit it press ctrl + c
