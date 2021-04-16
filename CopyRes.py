### COPYRES.PY
## Copies Engine Resources directory to the build folder.
## This directory contains all needed shaders/textures/models loaded at runtime
## because of this, they aren't compiled with the executable

from distutils.dir_util import copy_tree

fromDir = "./res/"
toDir = "./Builds/res"

copy_tree(fromDir, toDir)