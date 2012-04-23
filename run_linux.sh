#!/bin/bash

if [ $1 == "debug" ]; then
  ./bin/mojod > mojo.log 2>&1
else
  if [ $1 == "release" ]; then
    ./bin/mojo
  fi
fi

