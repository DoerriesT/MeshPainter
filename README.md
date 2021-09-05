# MeshPainter
A proof of concept tool for painting textures in 3D, written in C++/Qt/OpenGL. The tool allows to paint a set of PBR ttextures of a single mesh. Since it is only a proof of concept, it currently only supports a single material and UV set per mesh. This is a list of the features:

- Paint albedo, metallic, roughness, ambient occlusion, emissive and displacement textures
- Import and save textures
- Different colors and stroke widths
- Wireframe visualization
- UV visualization
- Support for Wavefront OBJ models

# Controls
- Left click + mouse paints on the model
- Right click + mouse rotates the camera
- Holding down the middle mouse button lets you translate the camera
- Mouse scroll to zoom in or out

# Usage
1) Click "File -> Open Model" to import a Wavefront OBJ model.
2) Click "Edit -> Active Texture" to select the texture to paint into.
3) Click "Edit -> Set Stroke Width" or "Edit -> Set Paint" to configure the brush.
4) Draw on the model with your mouse.
5) Click "File -> Save All Textures" or "File -> Save Texture" to save all or only a specific texture as PNG.

# Requirements
- GPU with support for OpenGL 3.3 or better

# How does it work?
It works by writing out the UVs of the rendered model to a render target and reading back the values hovered by the mouse. These UV values are then used to draw line segments with the selected color into the currently selected texture. The line segments are implemented as a series of splatted quads with an alpha falloff to simulate smooth lines.

# How to build
The project comes as a Visual Studio 2017 solution and requires Qt 5.11.1 and likely also the Visual Studio Plugin "Qt VS Tools". The project must be built as x64.

# Credits
- Qt 5.11.1
- stb_image, stb_image_write https://github.com/nothings/stb
- GLM https://github.com/g-truc/glm
- GLI https://github.com/g-truc/gli
