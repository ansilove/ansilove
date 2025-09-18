{
  description = "AnsiLove/C development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        inherit (pkgs) lib;
        libansilove = pkgs.libansilove;
        gd = pkgs.gd;
        libs = map lib.getLib [ libansilove gd pkgs.libpng pkgs.zlib ];
        devs = map lib.getDev [ libansilove gd pkgs.libpng pkgs.zlib ];
        cmakeTools = with pkgs; [
          cmake
          ninja
          pkg-config
          clang
          clang-tools
        ];
      in rec {
        packages = rec {
          ansilove = pkgs.stdenv.mkDerivation {
            pname = "ansilove";
            version = self.shortRev or "dev";
            src = self;

            nativeBuildInputs = cmakeTools;
            buildInputs = devs ++ libs;

            cmakeFlags = [ "-DENABLE_SECCOMP=0" ];

            meta = with lib; {
              description = "ANSI and ASCII art to PNG converter";
              homepage = "https://www.ansilove.org";
              license = licenses.bsd2;
              mainProgram = "ansilove";
              platforms = platforms.unix;
            };
          };

          default = ansilove;
        };

        apps.default = {
          type = "app";
          program = "${packages.default}/bin/ansilove";
          meta = packages.default.meta;
        };

        devShells.default = pkgs.mkShell {
          nativeBuildInputs = cmakeTools;
          buildInputs = devs ++ libs;
          CMAKE_PREFIX_PATH = lib.makeSearchPath "" devs;
          CMAKE_LIBRARY_PATH = lib.makeSearchPath "lib" libs;
          PKG_CONFIG_PATH = lib.makeSearchPath "lib/pkgconfig" devs;
        };
      });
}
