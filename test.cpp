#include "napi.h"
#include <iostream>
using namespace Napi;

Value doGet(const CallbackInfo &info) {
    size_t size = 200;

    if (info.Length() > 0 && info[0].IsNumber())
        size = info[0].ToNumber().Int64Value();

    uint8_t *data = new uint8_t[size];
    auto obj = Napi::Object::New(info.Env());

    std::cerr << "Allocated buffer of " << size << " bytes at " << (void*)data << "\n";
    obj["obj"] = Napi::Buffer<uint8_t>::New(info.Env(), data, size,
         [](Napi::Env env, uint8_t *d, uint8_t *hint) {
             std::cerr << "Releasing buffer at " << (void*) d << ", hint is " << (void*) hint << "\n";
             delete[] hint;
         }, data);
    return obj;
}
Object Init(Env env, Napi::Object exports) {
    exports["get"] = Function::New(env, doGet, "get");
    return exports;
}

// register module
NODE_API_MODULE(testNapi, Init);