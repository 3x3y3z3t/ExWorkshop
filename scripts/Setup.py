#
import os
import subprocess
import platform

from SetupPremake import PremakeConfiguration as PremakeRequirements
os.chdir('./') # Change from devtools/scripts directory to root

premakeInstalled = PremakeRequirements.Validate()

if (premakeInstalled):
    if platform.system() == "Windows":
        print("\nRunning premake...")
        subprocess.call([os.path.abspath("./vendor/premake/bin/premake5.exe"), "vs2017"])

    print("\nSetup completed!")
else:
    print("Hazel requires Premake to generate project files.")
