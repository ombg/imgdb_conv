__author__ = 'oliver'
import sys
print(sys.version_info)
assert sys.version_info >= (3,5) # Because we use new Glob features.

import os
import subprocess
import glob

### Adapt the following parameters before running the script
# Full path to the executable
binary = "/home/meyn_ol/git/imgdb_conv/preproc/release/preproc"
# Search pattern which looks for all annotation files
search_dir = '/home/meyn_ol/data/heads/imgdb2/*.txt'
#
#######################################
print('Search dir: {}'.format(search_dir))

for filename in glob.glob(search_dir, recursive=True):
  print('Image list: {}'.format(filename))
  # argument 1 [in]: full path to database
  # argument 2 [out]: full path to query result / image list
  # argument 3 [in]: patch size of output patches
  patchsize = str(32)
  bin_filename = filename[:-4] + '.bin'
  # Build executable command
  subprocess.call( [binary,
                    filename,
                    bin_filename,
                    patchsize] )

