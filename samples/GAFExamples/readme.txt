Generic Animation Format
=========

Introduction
-----------------------

GAF stands for Generic Animation Format. GAF is designed to store Flash animations in an open cross platform format for further playback in a multitude of game development frameworks and devices. GAF enables artists and animators to use Flash CS for creating complex animations and seamlessly use them with various game development frameworks.

Supported Platforms
-----------------------
- Windows - Cocos2d-x v3.3
- iOS - Cocos2d-x v3.3
- Android - Cocos2d-x v3.3
- Windows Phone 8 - Cocos2d-x v3.3
- *Upcoming Linux project*

Benefits
-----------------------
GAF Converter analyzes the bytecode of each SWF file and creates a GAF file which provides the following benefits:
### Smaller size.
**The traditional animation conversion process generates an image for each frame of the animation thus greatly increasing overall file size. However the GAF animation file stores only unique parts of the animation in a texture atlas and a highly compressed binary config file describing object positions and transformations.**
###Art requirements.
**GAF supports 99% of what can be created in Flash so your artists and animators don’t need any special planning or preparations of their SWF files before converting.**
###High performance. 
**The GAF conversion process involves numerous optimizations to increase playback performance across all platforms and frameworks. Performance of GAF runtimes is much better than that of the Flash player.**