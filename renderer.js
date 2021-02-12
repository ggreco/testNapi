const native = require("./build/Release/testNapi.node");

let request = null;
let lastFrame = null;

function leak() {
    lastFrame = native.get(1024 * 1024 * 10);
    console.log("Got frame of ", lastFrame.obj.byteLength, " allocated: ", native.allocated());
    request = window.requestAnimationFrame(leak);
}

function startLeaking() {
    if (!request) {
        console.log("Start leaking memory, yeah!");
        request = window.requestAnimationFrame(leak);
    } else
        alert("Already leaking!");
}

function stopLeaking() {
    console.log("Stop leaking memory, allocated buffers are: ", native.allocated());
    if (request) {
        window.cancelAnimationFrame(request);
        request = null;
    }
}