#include "napi.h"
#include <iostream>
using namespace Napi;

Value doGet(const CallbackInfo &info) {
    uint8_t *data = new uint8_t[200];
    std::cerr << "Allocated buffer of 200 bytes at " << (void*)data << "\n";
    return Napi::Buffer<uint8_t>::New(info.Env(), data, 200,
         [](Napi::Env env, uint8_t *d) {
             std::cerr << "Releasing buffer at " << (void*) d << "\n";
             delete[] d;
         });
}
Object Init(Env env, Napi::Object exports) {
    exports["get"] = Function::New(env, doGet, "get");
    return exports;
}

// register module
NODE_API_MODULE(testNapi, Init);