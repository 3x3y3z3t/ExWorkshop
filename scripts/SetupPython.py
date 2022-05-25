#
import sys
import subprocess
import importlib.util as importlib_util

class PythonConfig:
    @classmethod
    def Validate(_me):
        if not _me.__ValidatePython():
            return

        for pkgName in ["requests"]:
            if not _me.__ValidatePackage(pkgName):
                return

    @classmethod
    def __ValidatePython(_me, _verMajor = 3, _verMinor = 3):
        if sys.version is not None:
            print("Python version {0:d}.{1:d}.{2:d} detected".format(sys.version_info.major, sys.version_info.minor, sys.version_info.micro))
            
            if sys.version_info.major < _verMajor or (sys.version_info.major == _verMajor and sys.version_info.minor < _verMinor):
                print("ExWorkshop Setup requires Python version {0:d}.{1:d} or higher".format(_verMajor, _verMinor))
                return False
            return True

    @classmethod
    def __ValidatePackage(_me, _pkgName):
        if importlib_util.find_spec(_pkgName) is None:
            return _me.__InstallPackage(_pkgName)
        return True

    @classmethod
    def __InstallPackage(_me, _pkgName):
        permissionGranted = False
        while not permissionGranted:
            reply = str(input("Would you like to install Python package '{0:s}'? [Y/N]: ".format(_pkgName))).lower().strip()[:1]
            if reply == 'n':
                permissionGranted = False
                return False
            if reply == 'y':
                permissionGranted = True

        print(f"Installing {_pkgName} module..")
        subprocess.check_call(['python', '-m', 'pip', 'install', _pkgName])

        return _me.__ValidatePackage(_pkgName)

if __name__ == "__main__":
    PythonConfig.Validate()
