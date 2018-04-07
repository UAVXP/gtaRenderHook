# GTA rendering hook
GTA SA rendering hook
Implements DirectX11 rendering API to GTA San Andreas(possible to GTA VC and GTA 3 someday) as well as totally new rendering pipeline.
We have discord server(https://discord.gg/rsZEUNW), come and help to improve it!
## Current requirements to build development source code
1) Windows 7+ with Visual Studio Community 2017
2) DK22Pac's Plugin SDK repository(https://github.com/DK22Pac/plugin-sdk)
3) tinyxml2 repository(https://github.com/leethomason/tinyxml2)
4) AntTweakBar(http://anttweakbar.sourceforge.net)
## Build instructions
1) Go to View/Property Manager, open DependencyPaths.props, select User Macros and change paths to your own 
2) Build in release or debug configuration.
3) Run, test and report bugs and incompatibilities!
## Tips
1) If you encounter bug please report it, and attach debug.log file to bugreport
2) To enable more debug info set debuglevel higher(0-2) in autogenerated settings.xml
3) To enable in-game menu press F12
4) Currently there is experimental feature: Physically Based Rendering Materials, to put it simply render hook loads textures and material info from materials folder in executable directory. To add material you have to create materials.txd inside materials folder, and .mat file named after some in-game texture with specular texture name inside it. Specular texture should be added to materials.txd, red channel of specular texture is intensity, while green channel is glossiness.