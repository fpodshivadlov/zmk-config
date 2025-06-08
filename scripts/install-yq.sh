#!/bin/bash
set -e

# Install yq
YQ_VERSION=v4.45.4
YQ_BINARY=yq_linux_amd64
wget https://github.com/mikefarah/yq/releases/download/${YQ_VERSION}/${YQ_BINARY}.tar.gz -O - |\
  tar xz && sudo mv ${YQ_BINARY} /usr/local/bin/yq
chmod +x /usr/local/bin/yq
