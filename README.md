# Headscale Sender-Reciever Project

## overview
Secure container communication system using Headscale/Tailscale networking.
And streaming a webcam to a RTMP-server

## Prerequisites

- Docker
- Headscale server (local or remote)

## Running a websocket and sending data (via headscale)

### 1. configure receiver

This step is not necesaery if you don't want to run the setup in headscale

```bash
cd receiver
cp .env.default .env
vim .env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
         # HEADSCALE_TAG=tag:receiver
```

### 2. run the receiver
Without tailscale
```bash
./run.sh
```
With tailscale
```bash
./run.sh tailscale
```

### 3. setup sender
```bash
cd sender
cp .env.default .env
vim .env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
         # HEADSCALE_TAG=tag:sender
         # WS_SERVER_IP= Ip or domain name of the reciever
         # WS_SERVER_PORT = port that the websocket is listening to (5000)
```

### 4. run the sender
Without tailscale
```bash
./run.sh
```
With tailscale
```bash
./run.sh tailscale
```

Now the sender wil send integers to a websocket running on the recieving side. The intiger gets printed.

### Shuting down
press ctrl + c in both terminals

## Setting up the camera

This section is detecated to setting up a RTMP server, livestreaming to it. And looking at the live stream. THis with minimal delay.

### starting the RTMP server

Without tailscale
```bash
cd RTMP-server
./run.sh
```
With tailscale
This needs some setup:

```bash
cd RTMP-server
cp .env.default .env
vim .env # change HEADSCALE_AUTHKEY to the authentication key of your headscale/tailscale instance
    # change HEADSCALE_TAILNET to the url of the headscale server
    # chanhe HEADSCALE_TAG to the tag coresponding to the headscale_authkey (tag:rtmp)
./run.sh tailscale
```

To exit it press ctrl + c

### Starting ffmpeg

To start the ffmpeg (capturing video) without tailscale:
```bash
cd webcam
cp .env.default .env
vim .env # change INPUT_DEVICE to your webcam
    # change LOCATION_RTMP to the ip of the RTMP server
./run.sh
```

With tailscale
```bash
cd webcam
cp .env.default .env
vim .env # change INPUT_DEVICE to your webcam
    # change LOCATION_RTMP to the ip of the RTMP server
    # change HEADSCALE_AUTHKEY to the authentication key of your headscale/tailscale instance
    # change HEADSCALE_TAILNET to the url of the headscale server
    # chanhe HEADSCALE_TAG to the tag coresponding to the headscale_authkey (tag:rtmp)
./run.sh tailscale
```

To exit it press ctrl + c

### Starting ffplay

To start ffplay (display the video) without tailscale:

```bash
cd stream
cp .env.default .env
vim .env # change LOCATION_RTMP to the ip of the RTMP server
xhost +local:docker
./run.sh
```

With tailscale:
```bash
cd stream
cp .env.default .env
vim .env # change LOCATION_RTMP to the ip of the RTMP server
    # change HEADSCALE_AUTHKEY to the authentication key of your headscale/tailscale instance
    # change HEADSCALE_TAILNET to the url of the headscale server
    # chanhe HEADSCALE_TAG to the tag coresponding to the headscale_authkey (tag:rtmp)
xhost +local:docker
./run.sh tailscale
```

To exit it press ctrl + c
