{
  "targets": [
    {
      "target_name": "testNapi",
      "cflags!": [ "-fno-exceptions", "-fno-rtti" ],
      "cflags_cc!": [ "-fno-exceptions", "-fno-rtti" ],
      "cflags": [ "-std=c++14 -O3" ],
      "defines": [],
      "sources": [ "test.cpp" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
      'conditions': [
          ['OS=="mac"', {
            'xcode_settings': {
                'MACOSX_DEPLOYMENT_TARGET': '10.9',
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                'GCC_ENABLE_CPP_RTTI': 'YES'
            }
          }
        ]
      ]
    }
  ]
}
