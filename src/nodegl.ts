const addon = require('../addon/build/Debug/nodegl');
var obj = new addon.NodeGLWindow(10);
console.log( obj.plusOne() ); // 11
console.log( obj.plusOne() ); // 12
console.log( obj.plusOne() ); // 13
console.log( obj.isShowing );
obj.show();
while(obj.isShowing) {}
console.log( obj.isShowing );
