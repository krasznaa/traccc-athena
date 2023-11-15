# Package building traccc as part of the project

This package sets up the build of
[traccc](https://github.com/acts-project/traccc) as a part of an "ATLAS project"
on top of Athena. In such a way that other packages would be able to make use
of the built libraries through the normal CMake targets, like `vecmem::core`,
`traccc::cuda`, etc.
