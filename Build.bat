cls

:: Compile
cl.exe /c /EHsc /MT ^
/I include ^
/I C:\glfw-3.4\include ^
/I C:\glew-2.1.0\include ^
/Fo:build\ ^
main.cpp ^
source\VertexArray.cpp ^
source\VertexBuffer.cpp ^
source\IndexBuffer.cpp ^
source\Shader.cpp ^
source\stb_image.cpp ^
source\Texture.cpp

:: Resource
rc.exe /Fo build\main.res resource\main.rc

:: Link
link.exe ^
build\main.obj ^
build\VertexArray.obj ^
build\VertexBuffer.obj ^
build\IndexBuffer.obj ^
build\Shader.obj ^
build\stb_image.obj ^
build\Texture.obj ^
build\main.res ^
/OUT:main.exe ^
/LIBPATH:C:\glfw-3.4\lib-vc2022 ^
/LIBPATH:C:\glew-2.1.0\lib\Release\x64 ^
opengl32.lib ^
glfw3_mt.lib ^
glew32.lib ^
user32.lib ^
gdi32.lib ^
shell32.lib ^
comdlg32.lib

:: Run
main.exe
