# Headscale Sender-Reciever Project

## overview
Secure container communication system using Headscale/Tailscale networking.
And streaming a webcam to a RTMP-server

## Prerequisites

- Docker
- Headscale server (local or remote)

## Running a websocket and sending data or UDP communication (via headscale)

To remove the certificates completly from the docker cache (necessary when a new cert is generated)
execute:
```bash
docker rmi [container name]
```

### 1. configure receiver

This step is not necessary if you don't want to run the setup in headscale

```bash
cd receiver
cp .env.default .env
vim .env # Edit these values
         # HEADSSCALE_TAILNET=your-headscale-ip (currently configured for a local container)
         # HEADSCALE_AUTHKEY=your-sender-key
         # HEADSCALE_TAG=tag:receiver
         # WS_SERVER_PORT=8080
```

If you want to run TCP communication, change add_executable(test_receiver src/test_udp.cpp) in the CmakeList.txt to:
add_executable(test_receiver src/test.cpp) 

### 2. run the receiver
Without tailscale
```bash
./run.sh
```
With tailscale
```bash
./build.sh #copies the certificate from /usr/local/share/ca-certificates/ca.crt
./run.sh tailscale
```

### 3. setup sender
```bash
cd sender
cp .env.default .env
vim .env # Edit these values
         # HEADSSCALE_TAILNET=http://your-headscale-ip:8080 (currently configured for a local container) (only if you want to use HEADSCALE)
         # HEADSCALE_AUTHKEY=your-sender-key (only if you want to use HEADSCALE)
         # HEADSCALE_TAG=tag:sender (only if you want to use HEADSCALE)
         # WS_SERVER_IP= Ip or domain name of the reciever
         # WS_SERVER_PORT = port that the UDP server is listening to (8080)
```

### 4. run the sender
Without tailscale
```bash
./run.sh
```
With tailscale
```bash
./build.sh #copies the certificate from /usr/local/share/ca-certificates/ca.crt
./run.sh tailscale
```
If you want to run TCP communication, change add_executable(test_sender src/test_udp.cpp) in the CmakeList.txt to:
add_executable(test_sender src/test.cpp) 

Now the sender wil send integers to the recieving side. The integer gets printed.

You can check if the reciever is working by executing:
```bash
docker logs --follow receiver-cmake-app-1
```

### Shuting down
press ctrl + c in both terminals

## Setting up the camera

To remove the certificates completly from the docker cache (necessary when a new cert is generated)
execute:
```bash
docker rmi [container name]

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
./build.sh #copies the certificate from /usr/local/share/ca-certificates/ca.crt
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
./build.sh #copies the certificate from /usr/local/share/ca-certificates/ca.crt
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
./build.sh #copies the certificate from /usr/local/share/ca-certificates/ca.crt
./run.sh tailscale
```

To exit it press ctrl + c
