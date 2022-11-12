{
  "targets": [
    {
      "target_name": "sandbox",
      "sources": [
        "source/addon.cc",
        "source/sandbox.cc",
        "source/baton.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
			],
      "libraries": [
        "Ws2_32.lib"
      ],
      "msvs_settings": {
        'VCCLCompilerTool': {
          "ExceptionHandling": 1,
          "AdditionalOptions": [
            "-std:c++latest"
          ]
        }
      }
    }
  ],
}
