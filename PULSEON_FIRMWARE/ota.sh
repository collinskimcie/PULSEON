#!/usr/bin/env bash
cd "$(dirname "$0")"
PASS=$(sed -n 's/^#define OTA_PASSWORD "\(.*\)"/\1/p' include/wifi_secrets.h)
[ -z "$PASS" ] && { echo "OTA_PASSWORD not found in include/wifi_secrets.h"; exit 1; }
[ -n "$1" ] && echo "$1" > .ota_ip
IP=$(cat .ota_ip 2>/dev/null)
[ -z "$IP" ] && { echo "First run: ./ota.sh <watch IP shown on the Update page>"; exit 1; }
export PULSEON_OTA_PASS="$PASS"

echo "== Building (watch Wi-Fi stays off) =="
pio run -e esp32-s3-ota || exit 1

echo
echo "Build done. On the watch: Apps > Update > Start, wait for Ready."
read -r -p "Press Enter when the watch shows Ready (IP $IP)... "

if ! ping -c 1 -W 2 "$IP" >/dev/null 2>&1; then
  echo "Note: no ping reply from $IP. Trying the upload anyway."
fi
pio run -e esp32-s3-ota -t nobuild -t upload --upload-port "$IP"
