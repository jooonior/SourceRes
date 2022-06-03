# SourceRes

A plugin that lets you run Source Engine games at any resolution.

This is a reimplementation of [blue's old SourceRes plugin](https://github.com/MattMcNam/source-res),
with improved stability and compatibility (any Source SDK 2013 based game).

## Limitations

Custom resolutions work only in windowed mode. In fullscreen, you get no video output.
I'm not aware of any way to fix this.

## Commands

### `sr_force <width> <height>`
Register and change to given resolution. Equivalent to `sr_add` followed by `sr_set`.
### `sr_list`
List all registered resolutions.
### `sr_add <width> <height>`
Register a new custom resolution.
### `sr_set <width> <height>`
Change to a registered resolution. Shortcut for `mat_setvideomode <width> <height> 1`.
### `sr_purge`
Remove all registered resolutions except for one currently in use.
In case you manage to hit the resolution list length limit.

## Building

First you need [Source SDK 2013](https://developer.valvesoftware.com/wiki/Source_SDK_2013),
then you can generate a solution with:
```
cmake -DHL2SDK="C:\path\to\source-sdk-2013\mp\src" -S . -B build
```
This will create `build\SourceRes.sln` which you can build in Visual Studio or with MSBuild.

Also when testing in-game you can use `-insert_search_path "C:\path\to\SourceRes\mod"`
as a launch option instead of copying files over to the game's directory.
