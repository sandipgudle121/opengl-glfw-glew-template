# OGL-GLFW Template

A small Windows C++ starter project for creating an OpenGL application with GLFW, GLEW, and MSVC. The current program opens an 800 x 600 window and draws a red indexed quad using GLSL 4.60 shaders.

## Project layout

```text
.
|-- Build.bat              Compile, link, and run the application
|-- main.cpp               GLFW initialization and render loop
|-- include/               OpenGL wrapper and utility headers
|-- source/                Wrapper and shader implementations
|   |-- shaders/           Vertex and fragment shaders
|   `-- imgui/             Dear ImGui source files (not used by the current build)
|-- resource/              Windows application resources
`-- build/                 Generated object and resource files (ignored by Git)
```

The buffer wrappers (`VertexArray`, `VertexBuffer`, and `IndexBuffer`) own their OpenGL objects and release them when destroyed. The element buffer is set up while its vertex array is bound because that binding is part of the vertex-array state.

## Requirements

- Windows and Visual Studio 2022 C++ build tools, including `cl.exe`, `link.exe`, and `rc.exe`
- GLFW 3.4 and GLEW 2.1.0
- A graphics driver that supports an OpenGL 4.6 core context

`Build.bat` expects GLFW and GLEW at these locations:

- `C:\glfw-3.4`
- `C:\glew-2.1.0`

If they are installed elsewhere, update the include and library paths in `Build.bat`.

## Build and run

Open an x64 Native Tools Command Prompt for Visual Studio, then run these commands from the project directory:

```bat
if not exist build mkdir build
Build.bat
```

The batch file compiles the C++ sources, compiles the Windows resource, links `main.exe`, and runs it. Run it from the project directory so the relative shader paths resolve correctly. Press **Esc** to close the window.

The program writes `log.txt` while it runs. Build outputs, the log, the ImGui settings file, and local VS Code settings are excluded by `.gitignore`.
