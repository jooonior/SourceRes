# SourceRes

A plugin that lets you run Source Engine games at any resolution.

This is a reimplementation of [blue's old SourceRes plugin](https://github.com/MattMcNam/source-res),
with improved stability and compatibility (any Source SDK 2013 based game).

## Limitations

Custom resolutions only in windowed mode, as the native fullscreen renderer won't work with
anything it doesn't explicitly support.

## Commands

### `sr_list`
List all available resolutions. Initially these will be the ones you can change to normally.
### `sr_add <width> <height>`
Add a new custom resolution to the list of available resolutions. Skips duplicates.
### `sr_set <width> <height>`
Change the current resolution. Shortcut for `mat_setvideomode <width> <height> 1`,
therefore limited to available resolutions.
### `sr_force <width> <height>`
Set the current exact resolution. Equivalent to `sr_add` followed by `sr_set`.
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
