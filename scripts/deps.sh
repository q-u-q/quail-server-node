#!/bin/bash
SCRIPT=`pwd`/$0
FILENAME=`basename $SCRIPT`
PATHNAME=`dirname $SCRIPT`
ROOT=$PATHNAME/..
INSTALL_PATH=$ROOT/deps

SUDO=""
if [[ $EUID -ne 0 ]]; then
   SUDO="sudo -E"
fi

# exit when any command fails
set -e

install_quail(){
  echo "- install_quail."

  if [ ! -d $INSTALL_PATH/quail-server ] ; then
    pushd $INSTALL_PATH
    git clone https://github.com/q-u-q/quail-server.git
    pushd quail-server

    bash ./scripts/install.sh

    popd
    popd
  else
      echo "quail-server already installed." && return 0
  fi 
}

if [ ! -d $INSTALL_PATH ]; then
  mkdir -p $INSTALL_PATH
fi

install_quail

