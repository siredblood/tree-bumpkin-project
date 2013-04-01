0023:.:0:3:14=48041e4b:16=47d21313:0023:.:0:3:14=48041e4b:16=47d21313:002D:msi:000000000:2:14=48041e4b:16=47d21313:002C:msi.py:0DC54:1:14=48041e4b:16=47d21313:# Python MSI Generator
# (C) 2003 Martin v. Loewis
# See "FOO" in comments refers to MSDN sections with the title FOO.
import msilib, schema, sequence, os, glob, time, re
from msilib import Feature, CAB, Directory, Dialog, Binary, add_data
import uisample
from win32com.client import constants
from distutils.spawn import find_executable
from uuids import product_codes

# Settings can be overridden in config.py below
# 0 for official python.org releases
# 1 for intermediate releases by anybody, with
# a new product code for every package.
snapshot = 1
# 1 means that file extension is px, not py,
# and binaries start with x
testpackage = 0
# Location of build tree
srcdir = os.path.abspath("../..")
# Text to be displayed as the version in dialogs etc.
# goes into file name and ProductCode. Defaults to
# current_version.day for Snapshot, current_version otherwise
full_current_version = None
# Is Tcl available at all?
have_tcl = True
# Where is sqlite3.dll located, relative to srcdir?
sqlite_dir = "../sqlite-source-3.3.4"

try:
    from config import *
except ImportError:
    pass

# Extract current version from Include/patchlevel.h
lines = open(srcdir + "/Include/patchlevel.h").readlines()
major = minor = micro = level = serial = None
levels = {
    'PY_RELEASE_LEVEL_ALPHA':0xA,
    'PY_RELEASE_LEVEL_BETA': 0xB,
    'PY_RELEASE_LEVEL_GAMMA':0xC,
    'PY_RELEASE_LEVEL_FINAL':0xF
    }
for l in lines:
    if not l.startswith("#define"):
        continue
    l = l.split()
    if len(l) != 3:
        continue
    _, name, value = l
    if name == 'PY_MAJOR_VERSION': major = value
    if name == 'PY_MINOR_VERSION': minor = value
    if name == 'PY_MICRO_VERSION': micro = value
    if name == 'PY_RELEASE_LEVEL': level = levels[value]
    if name == 'PY_RELEASE_SERIAL': serial = value

short_version = major+"."+minor
# See PC/make_versioninfo.c
FIELD3 = 1000*int(micro) + 10*level + int(serial)
current_version = "%s.%d" % (short_version, FIELD3)

# This should never change. The UpgradeCode of this package can be
# used in the Upgrade table of future packages to make the future
# package replace this one. See "UpgradeCode Property".
upgrade_code_snapshot='{92A24481-3ECB-40FC-8836-04B7966EC0D5}'
upgrade_code='{65E6DE48-A358-434D-AA4F-4AF72DB4718F}'
# This was added in 2.5.2, to support parallel installation of
# both 32-bit and 64-bit versions of Python on a single system.
upgrade_code_64='{6A965A0C-6EE6-4E3A-9983-3263F56311EC}'

# Determine the target architechture
dll_file = "python%s%s.dll" % (major, minor)
dll_path = os.path.join(srcdir, "PCBuild", dll_file)
msilib.set_arch_from_file(dll_path)

if snapshot:
    current_version = "%s.%s.%s" % (major, minor, int(time.time()/3600/24))
    product_code = msilib.gen_uuid()
else:
    product_code = product_codes[current_version]
    if msilib.Win64:
        # Bump the last digit of the code by one, so that 32-bit and 64-bit
        # releases get separate product codes
        digit = hex((int(product_code[-2],16)+1)%16)[-1]
        product_code = product_code[:-2] + digit + '}'

if full_current_version is None:
    full_current_version = current_version

extensions = [
    'bz2.pyd',
    'pyexpat.pyd',
    'select.pyd',
    'unicodedata.pyd',
    'winsound.pyd',
    '_elementtree.pyd',
    '_bsddb.pyd',
    '_socket.pyd',
    '_ssl.pyd',
    '_testcapi.pyd',
    '_tkinter.pyd',
    '_msi.pyd',
    '_ctypes.pyd',
    '_ctypes_test.pyd',
    '_sqlite3.pyd',
    '_hashlib.pyd'
]

# Well-known component UUIDs
# These are needed for SharedDLLs reference counter; if
# a different UUID was used for each incarnation of, say,
# python24.dll, an upgrade would set the reference counter
# from 1 to 2 (due to what I consider a bug in MSI)
# Using the same UUID is fine since these files are versioned,
# so Installer will always keep the newest version.
msvcr71_uuid = "{8666C8DD-D0B4-4B42-928E-A69E32FA5D4D}"
pythondll_uuid = {
    "24":"{9B81E618-2301-4035-AC77-75D9ABEB7301}",
    "25":"{2e41b118-38bd-4c1b-a840-6977efd1b911}"
    } [major+minor]

# Build the mingw import library, libpythonXY.a
# This requires 'nm' and 'dlltool' executables on your PATH
def build_mingw_lib(lib_file, def_file, dll_file, mingw_lib):
    warning = "WARNING: %s - libpythonXX.a not built"
    nm = find_executable('nm')
    dlltool = find_executable('dlltool')

    if not nm or not dlltool:
        print warning % "nm and/or dlltool were not found"
        return False

    nm_command = '%s -Cs %s' % (nm, lib_file)
    dlltool_command = "%s --dllname %s --def %s --output-lib %s" % \
        (dlltool, dll_file, def_file, mingw_lib)
    export_match = re.compile(r"^_imp__(.*) in python\d+\.dll").match

    f = open(def_file,'w')
    print >>f, "LIBRARY %s" % dll_file
    print >>f, "EXPORTS"

    nm_pipe = os.popen(nm_command)
    for line in nm_pipe.readlines():
        m = export_match(line)
        if m:
            print >>f, m.group(1)
    f.close()
    exit = nm_pipe.close()

    if exit:
        print warning % "nm did not run successfully"
        return False

    if os.system(dlltool_command) != 0:
        print warning % "dlltool did not run successfully"
        return False

    return True

# Target files (.def and .a) go in PCBuild directory
lib_file = os.path.join(srcdir, "PCBuild", "python%s%s.lib" % (major, minor))
def_