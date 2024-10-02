#! /usr/bin/env python

import os, sys, re, string

HERE = os.path.dirname(os.path.realpath(__file__))
BISON_INSTALL_PREFIX=os.path.join(HERE, 'bison-install')
FLEX_INSTALL_PREFIX=os.path.join(HERE, 'flex-install')

if len(sys.argv) < 2:
    print ("usage make.py genreset or make.py genreverse")
    sys.exit(1)
    
os.system("make " + sys.argv[1])

# First make bison and flex (FF depends on specific versions)
if (not os.path.exists(FLEX_INSTALL_PREFIX)):
    os.system(f"cd flex/src/flex/2.5.4a/flex-2.5.4a;./configure --prefix={FLEX_INSTALL_PREFIX};make;make install;cd ../../../../..")

if (not os.path.exists(BISON_INSTALL_PREFIX)):
    os.system(f"cd bison;./configure --prefix={BISON_INSTALL_PREFIX};make;make install;cd ..")

os.system("cd FF-mod;make;cp ff ../ffmod;cd ..")
os.system("cd FF-v2.3;make;cp ff ../.;cd ..")
