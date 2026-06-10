<div align=center>

# Xshell

A terminal-centric command-line shell made in C23.

</div>

## Building

To build `Xshell`, you must have these dependencies installed in your system / development environment.

- A C compiler capable of compiling C23
- [meson](https://meson.build/)
- git

After acquiring those dependencies, you need to clone this repository to your system using `git`.

```bash
git clone https://github.com/quantumvoid0/Xshell && cd Xshell
```

When you're inside the `Xshell` directory, you would need to setup `meson`, and compile using it.

```bash
meson setup target -Dbuildtype=release
meson compile -C target
```

After the compilation process is done, you can find the `Xshell` binary inside `target/`

## License

This project is licensed under the [GNU General Public version 3](LICENSE).
