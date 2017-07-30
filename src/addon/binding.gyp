{
    "targets": [
        {
            "target_name": "nodegl",
            "sources": [ "addon.cpp", "NodeGLWindow.cpp" ],
            "include_dirs": ["<!(node -e \"require('nan')\")"]
        }
    ],

}