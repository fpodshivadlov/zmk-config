#!/bin/bash
set -e

source_dir=$(dirname "$(dirname "$(realpath "$BASH_SOURCE")")")
config_dir="config"
zmk_app_dir="/tmp/zmkenv"
workspace="${zmk_app_dir}/workspace"
include_file="${source_dir}/build.yaml"
artifacts_dir="${source_dir}/artifacts"
fallback_binary="bin"

mkdir -p "${workspace}/${config_dir}"
rm -rf ${workspace}/${config_dir}/*
cp -R ${source_dir}/${config_dir}/* "${workspace}/${config_dir}/"

mkdir -p "${artifacts_dir}"
rm -rf ${artifacts_dir}/*

for i in $(yq '.include | to_entries | .[].key' "${include_file}"); do
  board=$(yq ".include[$i].board // \"\"" "${include_file}")
  shield=$(yq ".include[$i].shield // \"\"" "${include_file}")
  snippet=$(yq ".include[$i].snippet // \"\"" "${include_file}")
  artifact_name=$(yq ".include[$i].artifact-name // \"\"" "${include_file}")
  cmake_args=$(yq ".include[$i].cmake-args // \"\"" "${include_file}")

  build_dir="$(mktemp -p ${zmk_app_dir} -d zmk-build-XXXXXX)"
  display_name=${shield:+$shield-}${board}
  echo "[${display_name}] Building to output ${build_dir}"

  if [ -n "${snippet}" ]; then
    echo "Using snippet: ${snippet}"
    extra_west_args="-S ${snippet}"
  fi

  if [ -e ${source_dir}/zephyr/module.yml ]; then
    zmk_load_arg=" -DZMK_EXTRA_MODULES='${source_dir}'"
  fi

  extra_west_args=${extra_west_args}
  extra_cmake_args=${shield:+-DSHIELD="$shield"}${zmk_load_arg}
  artifact_name=${artifact_name:-${shield:+$shield-}${board}-zmk}

  (cd "${workspace}" && west build -s zmk/app -d "${build_dir}" -b "${board}" ${extra_west_args} -- -DZMK_CONFIG=${workspace}/${config_dir} ${extra_cmake_args} ${cmake_args})

  echo "[${display_name}] Copying artifact"
  if [ -f "${build_dir}/zephyr/zmk.uf2" ]
  then
    cp "${build_dir}/zephyr/zmk.uf2" "${artifacts_dir}/${artifact_name}.uf2"
  elif [ -f "${build_dir}/zephyr/zmk.${fallback_binary}" ]
  then
    cp "${build_dir}/zephyr/zmk.${fallback_binary}" "${artifacts_dir}/${artifact_name}.${fallback_binary}"
  else
    echo "No artifact found for ${display_name}, skipping copy"
  fi

  echo ""
done
