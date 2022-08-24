#
import sys
import os

from pathlib import Path
import Utils

class VulkanConfig:
    requiredVulkanVersion = "1.3."
    installVulkanVersion = "1.3.216.0"
    vulkanDirectory = "./vendor/VulkanSDK"

    @classmethod
    def Validate(_me):
        if not _me.__IsVulkanSDKInstalled():
            print("Vulkan SDK is not installed correctly.")
            return False

        if not _me.__IsVulkanSDKDbgLibsInstalled():
            print("\nVulkan SDK debug libs not found, please re-run the installer and select all debug libs.")
            print("Debug configuration is disabled.")

        return True

    @classmethod
    def __IsVulkanSDKInstalled(_me):
        vulkanSDK = os.environ.get("VULKAN_SDK")
        if vulkanSDK is None:
            print("\nVulkan SDK is not installed or environment variable VULKAN_SDK is not set correctly.")
            _me.__InstallVulkanSDK()
            return False

        if _me.requiredVulkanVersion not in vulkanSDK:
            print(f"You don't have the correct Vulkan SDK version (required version: {_me.requiredVulkanVersion}).")
            _me.__InstallVulkanSDK()
            return False

        print(f"\nVulkanSDK is installed at {vulkanSDK}.")
        return True

    @classmethod
    def __IsVulkanSDKDbgLibsInstalled(_me):
        vulkanSDK = os.environ.get("VULKAN_SDK")
        shaderCLib = Path(f"{vulkanSDK}/Lib/shaderc_sharedd.lib")
        return shaderCLib.exists()

    @classmethod
    def __InstallVulkanSDK(_me):
        permissionGranted = False
        while not permissionGranted:
            reply = str(input("Would you like to install Vulkan SDK {0:s}? [Y/N]: ".format(_me.installVulkanVersion))).lower().strip()[:1]
            if reply == 'n':
                permissionGranted = False
                return
            if reply == 'y':
                permissionGranted = True

        vulkanInstallURL = f"https://sdk.lunarg.com/sdk/download/{_me.installVulkanVersion}/windows/VulkanSDK-{_me.installVulkanVersion}-Installer.exe"
        vulkanPath = f"{_me.vulkanDirectory}/VulkanSDK-{_me.installVulkanVersion}-Installer.exe"
        print("Downloading {0:s} to {1:s}..".format(vulkanInstallURL, vulkanPath))
        Utils.DownloadFile(vulkanInstallURL, vulkanPath)
        print("Running Vulkan SDK installer..")
        os.startfile(os.path.abspath(vulkanPath))
        print("Re-run this script after installation.")
        quit()

if __name__ == "__main__":
    VulkanConfig.Validate()