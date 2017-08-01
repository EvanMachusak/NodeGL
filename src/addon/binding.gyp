{
    "targets": [
        {
            "target_name": "nodegl",
            "sources": [ "addon.cpp", "NodeGLWindow.cpp" ],
            "include_dirs": ["<!(node -e \"require('nan')\")"],
            "libraries": [
                '-lglfw3',
                '-lGLEW',
                '-ldl', 
                '-lGL',
                '-lGLU',
                '-lXrandr',
                '-lXext',
                '-lX11',
                '-lXcursor', 
                '-lXi',
                '-lpthread', 
                '-lXinerama'
            ]
        }
    ]
}