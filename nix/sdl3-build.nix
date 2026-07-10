{ lib 
, stdenv
, fetchFromGitHub
, cmake
, ninja
, pkg-config
, wayland
, wayland-protocols
, wayland-scanner
, libGL
, udev
, libxkbcommon
, system
, releaseMode
}: 

stdenv.mkDerivation (finalAttrs: let
  cmakeBuildProfiles = import ./cmake-profiles.nix;
in {
  name = "${finalAttrs.pname}-${finalAttrs.version}-${finalAttrs.system}";
  pname = "sdl3";
  version = "3.4.12";
  inherit system;
  
  src = fetchFromGitHub {
    owner = "libsdl-org";
    repo = "SDL";
    tag = "release-3.4.12";
    hash = "sha256-b6l3HgdhqIe9LazJmLivbCJgbKPAS8S54fuB9xvgalI=";
    fetchSubmodules = false;
  };

  dontStrip = cmakeBuildProfiles.${releaseMode}.symbols;

  nativeBuildInputs = [ 
    cmake 
    ninja 
    pkg-config
    wayland-scanner
  ];
  
  buildInputs = [
    wayland
    wayland-protocols
    libGL
    udev
    libxkbcommon
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=${cmakeBuildProfiles.${releaseMode}.flag}"
    (lib.cmakeBool "SDL_SHARED" false)
    (lib.cmakeBool "SDL_STATIC" true)
    (lib.cmakeBool "SDL_TESTS" false)
    
    # X11 Flags:
    (lib.cmakeBool "SDL_X11" false)
    (lib.cmakeBool "SDL_X11_SHARED" false)
    (lib.cmakeBool "SDL_X11_XCURSOR" false)
    (lib.cmakeBool "SDL_X11_XBDE" false)
    (lib.cmakeBool "SDL_X11_XFIXES" false)
    (lib.cmakeBool "SDL_X11_XINPUT" false)
    (lib.cmakeBool "SDL_X11_XRANDR" false)
    (lib.cmakeBool "SDL_X11_XSCRNSAVER" false)
    (lib.cmakeBool "SDL_X11_XSHAPE" false)
    (lib.cmakeBool "SDL_X11_XSYNC" false)
    (lib.cmakeBool "SDL_X11_XTEST" false)
  ];
})

