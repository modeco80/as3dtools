## As3dTools

Tools for working with the Air Strike 3D games. Mostly written in C++ for the time being, but I'm investigating other languages (read: Rust).


## Building

```bash
$ git clone https://github.com/modeco80/as3dtools.git
$ cd as3dtools
$ cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
$ cmake --build build -j $(nproc)
# ... profit?
```

## The Libraries

### `libas3d`

Provides IO readers and writers for data files, along with the structures.

Structure documentation is seperately managed as a .hexpat in [/hexpat](https://github.com/modeco80/as3dtools/tree/master/hexpat).

## The Tools

### `as3dpak`

Swiss army knife for packfiles.

Can create, extract, and show info on them.

