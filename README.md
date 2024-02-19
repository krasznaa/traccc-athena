# traccc <-> Athena Integration Example

This is a demonstrator for using
[traccc](https://github.com/acts-project/traccc) with/in
[Athena](https://gitlab.cern.ch/atlas/athena).

At the time of writing, in order to use the CUDA support of traccc in the
Athena runtime environment, do something like the following:

```
setupATLAS -c centos7 --runtimeOpt="apptainer|--nv" --runtimeOpt="singularity|--nv" --runtimeOpt="docker|--gpus all" --runtimeOpt="podman| --gpus all"
asetup Athena,main,latest
cmake -S traccc-athena -B build
cmake --build build
```
