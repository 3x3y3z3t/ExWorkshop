#
import sys
import os

from pathlib import Path
import Utils

class PremakeConfig:
    premakeVersion = "5.0.0-alpha16"
    premakeZipUrls = f"https://github.com/premake/premake-core/releases/download/v{premakeVersion}/premake-{premakeVersion}-windows.zip"
    premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
    premakeDir = "./vendor/premake/bin"

    @classmethod
    def Validate(_me):
        if not _me.__IsPremakeInstalled():
            print("Premake is not installed")
            return False

        print(f"Premake is installed at {os.path.abspath(_me.premakeDir)}")
        return True

    @classmethod
    def __IsPremakeInstalled(_me):
        premakeExe = Path(f"{_me.premakeDir}/premake5.exe")
        if not premakeExe.exists():
            return _me.__InstallPremake()

        return True

    @classmethod
    def __InstallPremake(_me):
        permissionGranted = False
        while not permissionGranted:
            reply = str(input("Premake not found. Would you like to download Premake {0:s}? [Y/N]: ".format(_me.premakeVersion))).lower().strip()[:1]
            if reply == 'n':
                permissionGranted = False
                return False
            if reply == 'y':
                permissionGranted = True

        premakePath = f"{_me.premakeDir}/premake-{_me.premakeVersion}-windows.zip"
        print("Downloading {0:s} to {1:s}..".format(_me.premakeZipUrls, premakePath))
        Utils.DownloadFile(_me.premakeZipUrls, premakePath)
        print("Extracting {0:s}..".format(premakePath))
        Utils.UnzipFile(premakePath, True)
        print(f"Premake {_me.premakeVersion} has been downloaded to '{_me.premakeDir}'")
            
        premakeLicensePath = f"{_me.premakeDir}/LICENSE.txt"
        print("Downloading {0:s} to {1:s}".format(_me.premakeLicenseUrl, premakeLicensePath))
        Utils.DownloadFile(_me.premakeLicenseUrl, premakeLicensePath)
        print(f"Premake License file has been downloaded to '{_me.premakeDir}'")

        return True
