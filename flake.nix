{
  description = "Chip-8 Nix Flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;

      build =
        { lib
        , stdenv
        , clang-tools
        , cmake
        , ninja
        , releaseMode
        , enableSanitizers ? false
        , enableGgdb ? false
        }:
        stdenv.mkDerivation (finalAttrs:
        let
          cmakeBuildProfiles = {
            debug = {
              flag = "Debug";
              symbols = true;
            };
            release = {
              flag = "Release";
              symbols = false;
            };
            relWithDebInfo = {
              flag = "RelWithDebInfo";
              symbols = true;
            };
          };
        in
        {
          name = "${finalAttrs.pname}-${finalAttrs.version}-${finalAttrs.system}";
          pname = "chip-8";
          version = "0.0.1";
          system = "x86_64-linux";
          src = ./.;

          dontStrip = cmakeBuildProfiles.${releaseMode}.symbols;

          nativeBuildInputs = [
            clang-tools
            cmake
            ninja
          ];

          buildInputs = [ ];
          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=${cmakeBuildProfiles.${releaseMode}.flag}"
            (lib.cmakeBool "ENABLE_SANITIZE" enableSanitizers)
            (lib.cmakeBool "ENABLE_GGDB" enableGgdb)
          ];
        });
    in
    {
      formatter.x86_64-linux = pkgs.nixpkgs-fmt;

      packages.x86_64-linux = {
        debug = pkgs.callPackage build {
          stdenv = pkgs.gcc16Stdenv;
          releaseMode = "debug";
          enableGgdb = true;
          enableSanitizers = true;
        };
        release = pkgs.callPackage build { stdenv = pkgs.gcc16Stdenv; releaseMode = "release"; };
        relWithDebInfo = pkgs.callPackage build { stdenv = pkgs.gcc16Stdenv; releaseMode = "relWithDebInfo"; };
      };

      devShells.x86_64-linux.default = pkgs.mkShell.override { stdenv = pkgs.gcc16Stdenv; } {
        packages = with pkgs; [ gef strace ];
        inputsFrom = [ self.packages.x86_64-linux.debug ];

        CMAKE_EXPORT_COMPILE_COMMANDS = "ON";

        shellHook = ''
          echo "Entering chip-8 shell!"
        '';
      };
    };
}
