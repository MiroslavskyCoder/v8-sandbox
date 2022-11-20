{
  "targets": [
    {
      "target_name": "sandbox",
      "sources": [
        "source/addon.cc",
        "source/sandbox.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
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
