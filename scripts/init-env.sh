#!/bin/bash
set -e

source_dir=$(dirname "$(dirname "$(realpath "$BASH_SOURCE")")")
config_dir="config"
zmk_app_dir="/tmp/zmkenv"
workspace="${zmk_app_dir}/workspace"

mkdir -p "${workspace}/${config_dir}"
cp -R ${source_dir}/${config_dir}/west.yml "${workspace}/${config_dir}/"

if [ ! -d "${workspace}/.west" ]; then
     (cd "${workspace}" && west init -l "${config_dir}/")
fi
(cd "${workspace}" && west update --fetch-opt=--filter=tree:0)
(cd "${workspace}" && west zephyr-export)
