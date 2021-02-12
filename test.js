const native = require("./build/Release/testNapi.node");

function tick() {
    return new Promise(resolve => setImmediate(resolve));
}

async function callGC() {
    if (global.gc) {
        console.log("MANUALLY calling GC...")
        global.gc()
    }
    // the tick alone is enough to call gc automatically if not exposed with --expose-gc
    // use --max-old-space-size=XX (MB) to pilot the frequency
    await tick()
}

async function main() {
    console.log("Starting...")

    for (let i = 1; i < 12; ++i) {
        const res = native.get(1024 * 1024 * 100);
        console.log("Got ", res.obj.byteLength , "total allocations ", native.allocated());

        // give some time to node to do garbage collection
        if ((i % 3) === 0) {
            await callGC();
        }
    }
    console.log("Terminated");
}

main();