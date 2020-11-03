# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v1.0.0] - 2020-11-03

### Fixed

-   2nd octet of the IP-address in status response is wrong. [#150](https://github.com/XLabsProject/iw6x-client/issues/150)
-   Arxan exceptions cause performance issues [#144](https://github.com/XLabsProject/iw6x-client/issues/144)

### Added

-   Disable whitelist protection on /bind command on console. [#151](https://github.com/XLabsProject/iw6x-client/issues/151)

### Pull Requests

-   ScrCmd_SetSlowMotion patches [#157](https://github.com/XLabsProject/iw6x-client/pull/157) ([@skiff](https://github.com/skiff))
-   added binding [#152](https://github.com/XLabsProject/iw6x-client/pull/152) ([@Jemal](https://github.com/Jemal))
-   Server double clicks, discord presence fix and input module [#148](https://github.com/XLabsProject/iw6x-client/pull/148) ([@Jemal](https://github.com/Jemal))
-   Add clientkick and kick commands [#147](https://github.com/XLabsProject/iw6x-client/pull/147) ([@Joelrau](https://github.com/Joelrau))

## [v1.0.0-rc.1] - 2020-10-28

### Fixed

-   Dedis sometimes crash at 0x28046F420 [#104](https://github.com/XLabsProject/iw6x-client/issues/104)
-   A very long sv_hostname creates a lot of chaos [#102](https://github.com/XLabsProject/iw6x-client/issues/102)
-   Crash while typing message in chat [#99](https://github.com/XLabsProject/iw6x-client/issues/99)
-   steam_api64 is still being loaded by the game [#95](https://github.com/XLabsProject/iw6x-client/issues/95)
-   Discord integration displays own hostname, not the remote one [#94](https://github.com/XLabsProject/iw6x-client/issues/94)
-   Manage connecting from the main menu [#93](https://github.com/XLabsProject/iw6x-client/issues/93)
-   Changing password in private match crashes [#80](https://github.com/XLabsProject/iw6x-client/issues/80)
-   Exec bugged [#76](https://github.com/XLabsProject/iw6x-client/issues/76)
-   Dedicated server takes up a player slot [#75](https://github.com/XLabsProject/iw6x-client/issues/75)
-   Dedicated servers lag/run at double speed [#67](https://github.com/XLabsProject/iw6x-client/issues/67)
-   9-bangs and semtex's are bugged (Desc) [#39](https://github.com/XLabsProject/iw6x-client/issues/39)
-   New bounce command bugged [#25](https://github.com/XLabsProject/iw6x-client/issues/25)
-   Vsync 15FPS bug [#22](https://github.com/XLabsProject/iw6x-client/issues/22)
-   Ingame console is automatically opened in singleplayer [#7](https://github.com/XLabsProject/iw6x-client/issues/7)

### Added

-   Delay dedicated server commands until initialization is done [#98](https://github.com/XLabsProject/iw6x-client/issues/98)
-   Verify the game binary versions [#92](https://github.com/XLabsProject/iw6x-client/issues/92)
-   Add rcon and status commands [#91](https://github.com/XLabsProject/iw6x-client/issues/91)
-   Dealing with LFS limitations [#86](https://github.com/XLabsProject/iw6x-client/issues/86)
-   Load dedicated server configs [#85](https://github.com/XLabsProject/iw6x-client/issues/85)
-   Implement map rotate for dedis [#81](https://github.com/XLabsProject/iw6x-client/issues/81)
-   Dedicated Servers load .pak files [#71](https://github.com/XLabsProject/iw6x-client/issues/71)
-   Implement exec mycustom.cfg [#66](https://github.com/XLabsProject/iw6x-client/issues/66)
-   Implement basic server backend [#60](https://github.com/XLabsProject/iw6x-client/issues/60)
-   Implement minidump support [#59](https://github.com/XLabsProject/iw6x-client/issues/59)
-   Block changing name ingame [#57](https://github.com/XLabsProject/iw6x-client/issues/57)
-   Remove name colors from overhead names [#56](https://github.com/XLabsProject/iw6x-client/issues/56)
-   Implement dedicated servers [#29](https://github.com/XLabsProject/iw6x-client/issues/29)
-   Add working connect command [#28](https://github.com/XLabsProject/iw6x-client/issues/28)
-   Remove DTLS [#27](https://github.com/XLabsProject/iw6x-client/issues/27)
-   Get basic matchmaking working [#9](https://github.com/XLabsProject/iw6x-client/issues/9)
-   Dump latest publisher files [#8](https://github.com/XLabsProject/iw6x-client/issues/8)
-   Wai you no fully remove the most basic version of Arxan?!one! [#1](https://github.com/XLabsProject/iw6x-client/issues/1)

### Pull Requests

-   Add more dvars to require sv_cheats / cleaned pathes a little [#120](https://github.com/XLabsProject/iw6x-client/pull/120) ([@FragsAreUs](https://github.com/FragsAreUs))
-   Implement release process automation [#118](https://github.com/XLabsProject/iw6x-client/pull/118) ([@x-dev-urandom](https://github.com/x-dev-urandom))
-   Add IW6x version to game version strings [#116](https://github.com/XLabsProject/iw6x-client/pull/116) ([@x-dev-urandom](https://github.com/x-dev-urandom))
-   dvarDump show values & using enums for game_console::print [#114](https://github.com/XLabsProject/iw6x-client/pull/114) ([@iAmThatMichael](https://github.com/iAmThatMichael))
-   Add some functions [#110](https://github.com/XLabsProject/iw6x-client/pull/110) ([@Joelrau](https://github.com/Joelrau))
-   Unlock all camos [#108](https://github.com/XLabsProject/iw6x-client/pull/108) ([@zzzcarter](https://github.com/zzzcarter))
-   Added a simple ping counter [#105](https://github.com/XLabsProject/iw6x-client/pull/105) ([@halcyo-n](https://github.com/halcyo-n))
-   Display the proper hostname in discord presence [#103](https://github.com/XLabsProject/iw6x-client/pull/103) ([@Jemal](https://github.com/Jemal))
-   Patch Dvar_Command to print values if no values are given like CoD4 [#97](https://github.com/XLabsProject/iw6x-client/pull/97) ([@skiff](https://github.com/skiff))
-   rcon and status commands [#96](https://github.com/XLabsProject/iw6x-client/pull/96) ([@skiff](https://github.com/skiff))
-   Updated DPServer IP Address [#90](https://github.com/XLabsProject/iw6x-client/pull/90) ([@HexChaos](https://github.com/HexChaos))
-   Hook calls for cg_gun\_ dvars to remove flags [#89](https://github.com/XLabsProject/iw6x-client/pull/89) ([@skiff](https://github.com/skiff))
-   Fix map_rotation crash [#88](https://github.com/XLabsProject/iw6x-client/pull/88) ([@Joelrau](https://github.com/Joelrau))
-   Set up GitHub Actions [#87](https://github.com/XLabsProject/iw6x-client/pull/87) ([@x-dev-urandom](https://github.com/x-dev-urandom))
-   New artworks & resources [#84](https://github.com/XLabsProject/iw6x-client/pull/84) ([@sortileges](https://github.com/sortileges))
-   Implement sv_cheats [#82](https://github.com/XLabsProject/iw6x-client/pull/82) ([@skiff](https://github.com/skiff))
-   Small changes [#78](https://github.com/XLabsProject/iw6x-client/pull/78) ([@Joelrau](https://github.com/Joelrau))
-   Fix exec command patch [#77](https://github.com/XLabsProject/iw6x-client/pull/77) ([@skiff](https://github.com/skiff))
-   New icon, splash screen and banner [#70](https://github.com/XLabsProject/iw6x-client/pull/70) ([@sortileges](https://github.com/sortileges))
-   Allow exec to find custom cfg files on disk [#69](https://github.com/XLabsProject/iw6x-client/pull/69) ([@skiff](https://github.com/skiff))
-   Increased sv_max_fps to 1000 [#68](https://github.com/XLabsProject/iw6x-client/pull/68) ([@xerxes-at](https://github.com/xerxes-at))
-   Add Com_Error function [#64](https://github.com/XLabsProject/iw6x-client/pull/64) ([@Joelrau](https://github.com/Joelrau))
-   Block changing name in-game & remove colors from overhead names [#63](https://github.com/XLabsProject/iw6x-client/pull/63) ([@Jemal](https://github.com/Jemal))
-   "cg_gun\_" and dvar patches [#62](https://github.com/XLabsProject/iw6x-client/pull/62) ([@sortileges](https://github.com/sortileges))
-   cg_fovscale and cg_fov changes [#58](https://github.com/XLabsProject/iw6x-client/pull/58) ([@lizardpeter](https://github.com/lizardpeter))
-   Added bots [#55](https://github.com/XLabsProject/iw6x-client/pull/55) ([@Jemal](https://github.com/Jemal))
-   Patched r_fog [#53](https://github.com/XLabsProject/iw6x-client/pull/53) ([@OneFourOne](https://github.com/OneFourOne))
-   Discord integration [#52](https://github.com/XLabsProject/iw6x-client/pull/52) ([@Jemal](https://github.com/Jemal))
-   Added colors module [#48](https://github.com/XLabsProject/iw6x-client/pull/48) ([@Jemal](https://github.com/Jemal))
-   Scheduler addons [#47](https://github.com/XLabsProject/iw6x-client/pull/47) ([@skiff](https://github.com/skiff))
-   Fix SP not starting [#46](https://github.com/XLabsProject/iw6x-client/pull/46) ([@fedddddd](https://github.com/fedddddd))
-   Implemented server list feeder [#43](https://github.com/XLabsProject/iw6x-client/pull/43) ([@Jemal](https://github.com/Jemal))
-   Add setviewpos, setviewang commands, add viewpos to drawfps [#38](https://github.com/XLabsProject/iw6x-client/pull/38) ([@fedddddd](https://github.com/fedddddd))
-   Make stats look better [#36](https://github.com/XLabsProject/iw6x-client/pull/36) ([@FragsAreUs](https://github.com/FragsAreUs))

[Unreleased]: https://github.com/XLabsProject/iw6x-client/compare/v1.0.0...HEAD

[v1.0.0]: https://github.com/XLabsProject/iw6x-client/compare/v1.0.0-rc.1...v1.0.0

[v1.0.0-rc.1]: https://github.com/XLabsProject/iw6x-client/compare/22c834e0655795870621ce505ea189ae522e8223...v1.0.0-rc.1
