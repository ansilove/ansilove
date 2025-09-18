# Repository Guidelines

## Project Structure & Module Organization
AnsiLove/C keeps the CLI in `src/` (`ansilove.c`, `sauce.c`, helpers such as `strtolower.c`). Portable fallbacks sit in `compat/` and are pulled in by `CMakeLists.txt` when the host lacks pledge or strtonum. Test fixtures for the regression suite live in `tests/`, and user-facing docs live in `man/`, `examples/`, and `ChangeLog`. Add new sources next to their headers and register them in `CMakeLists.txt` so every build configuration picks them up.

## Build, Test, and Development Commands
Configure once with `cmake -S . -B build [-DENABLE_SECCOMP=1]` to create a dedicated build tree. Compile via `cmake --build build`, which links against the system-provided `libansilove`. Run the binary locally with `build/ansilove foo.ans` to spot option regressions quickly. Exercise the suite using `ctest --test-dir build --output-on-failure`, covering ANSI, Artworx, BIN, PCBoard, Tundra, XBin, retina scaling, and SAUCE parsing.

### Nix workflow
- `nix develop` drops into a shell that wires `CMAKE_PREFIX_PATH`, `CMAKE_LIBRARY_PATH`, and `PKG_CONFIG_PATH` so CMake can find `libansilove`, `gd`, `libpng`, and `zlib` without Homebrew.
- `nix run . -- -h` (or `nix run github:effect-native/ansilove -- -h`) uses the flake-provided package/app and skips manual builds.
- `nix build .#default` produces the CLI in `./result/bin/ansilove`; git ignores `result`, `.cache`, `.direnv`, and the test PNGs.
- `nix flake check --all-systems` succeeds after adding meta for the app; run it when touching the flake.

## Coding Style & Naming Conventions
Stick to C99 and mirror the existing tab-based indentation with 80-column discipline. Functions use lower_snake_case, macros and constants stay in SCREAMING_SNAKE_CASE, and typedefs are declared in `types.h`. Keep include blocks grouped logically, prefer standard functions before adding compat variants, and respect the warning flags already set in `CMakeLists.txt`. Favor small, focused patches so reviewers can validate logic against the pedantic build.

## Testing Guidelines
New behavior should be covered by extending `add_test` entries in `CMakeLists.txt` with fixtures under `tests/`. When touching rendering paths, update or duplicate the bs-alove samples so `ctest` observes the change. Validate metadata work with `ansilove -s tests/sauce.txt` and ensure stdout noise is controlled via the `-q` flag. Document any manual image comparisons in the PR description when automation cannot assert the result.

## Commit & Pull Request Guidelines
Commits follow short, sentence-cased summaries ending with a period (see `git log`). Reference related issues or upstream discussions in the message body when context is useful. PRs should outline what changed, why it matters, and how you verified it (e.g., `ctest`, sample renders). Attach screenshots only when visual diffs are essential, and call out dependency or security toggles like seccomp in both the description and release notes draft.
