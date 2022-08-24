#
import os
import subprocess
import platform

from SetupPython import PythonConfig
PythonConfig.Validate()

from SetupVulkan import VulkanConfig
VulkanConfig.Validate()

print("\nUpdating submodules..")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

from SetupPremake import PremakeConfig
if not PremakeConfig.Validate():
    print("ExWorkshop requires Premake to generate projects")
else:
    if platform.system() == "Windows":
        print("\nRunning premake..")
        subprocess.call([os.path.abspath("./scripts/Win-GenProjects.bat"), "nopause"])

    print("\nSetup completed.")
