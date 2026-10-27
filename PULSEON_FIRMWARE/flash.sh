#!/usr/bin/env bash
cd "$(dirname "$0")"
pio run -t upload 2>&1 | tee /tmp/flash.log | grep -E "error|SUCCESS|FAILED" || true
grep -q SUCCESS /tmp/flash.log || { echo "Build or flash failed. First errors:"; grep -m5 -E "error" /tmp/flash.log; exit 1; }
pio device monitor --filter time --filter log2file
