#!/usr/bin/env bash

set -e -o pipefail

source "$(dirname "$0")/setup-utils.sh"

KISSAT_DIR="${DEPS_DIR}/kissat"

rm -rf "${KISSAT_DIR}"

# Download and build Kissat
curl -o kissat.tar.xz -L http://fmv.jku.at/kissat/kissat-sc2020-039805f2.tar.xz
tar xf kissat.tar.xz
rm kissat.tar.xz
mv kissat-sc2020-039805f2 "${KISSAT_DIR}"
cd "${KISSAT_DIR}"

./configure -fPIC --quiet ${EXTRA_FLAGS}
make -j${NPROC}
install_lib build/libkissat.a
install_include src/kissat.h
