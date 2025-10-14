#!/bin/bash
set -e

source_dir=$(dirname "$(dirname "$(realpath "$BASH_SOURCE")")")
output_dir="$source_dir/keymap-drawer"
mkdir -p "$output_dir"

keymap_config=${source_dir}/keymap_drawer.config.yaml

keymap -c ${keymap_config} parse -c 10 -z "$source_dir/config/charybdis.keymap" > "$output_dir/charybdis.yaml"
keymap -c ${keymap_config} draw "$output_dir/charybdis.yaml" -d "$source_dir/boards/shields/charybdis/charybdis_layouts.dtsi" > "$output_dir/charybdis.svg"

keymap -c ${keymap_config} parse -c 10 -z "$source_dir/config/eyelash_corne.keymap" > "$output_dir/eyelash_corne.yaml"
keymap -c ${keymap_config} draw "$output_dir/eyelash_corne.yaml" -d "$source_dir/boards/arm/eyelash_corne/eyelash_corne-layouts.dtsi" > "$output_dir/eyelash_corne.svg"
