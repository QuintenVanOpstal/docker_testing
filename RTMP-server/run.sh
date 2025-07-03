#! /bin/bash
# Function to clean up containers
cleanup() {
  echo "Caught Ctrl+C! Stopping containers..."
  docker compose -f docker-compose.yml -f docker-compose-tailscale.yml down
  exit 1
}

# Trap SIGINT (Ctrl+C) and call cleanup()
trap cleanup SIGINT

if [[ $1 == "tailscale" ]]; then
  docker compose -f docker-compose.yml -f docker-compose-tailscale.yml up -d
else
  docker compose up -d
fi

tail -f /dev/null
