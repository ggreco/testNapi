# testNapi

test (the missing) garbage collection of node buffers created from a NAPI native module in the electron renderer.

To build:

`npm install`

Tested to leak both on linux and macOS (both with electron 10.x and 11.x).

to run the test:

`npm start`

Press "leak" and see the memory being exhausted by the electron renderer.

... you can also see the (correct) behaviour of the module in node.js:

`npm test`

