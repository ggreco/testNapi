const native = require("./build/Release/testNapi.node");

console.log("Starting...")
for (let i = 1; i < 100; ++i) {
    const res = native.get();
    console.log("Got ", res.byteLength);
    if ((i % 10) === 0) {
        console.log("Calling GC...")
        global.gc();
        console.log("GC completed");
    }
}
console.log("Terminated");