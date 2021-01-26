#!/bin/sh
rm -f small large
fallocate -l 10M small
fallocate -l 1G large
