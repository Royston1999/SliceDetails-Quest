Param(
    [Parameter(Mandatory=$false)]
    [Switch] $no_gimmick,

    [Parameter(Mandatory=$false)]
    [Switch] $clean,

    [Parameter(Mandatory=$false)]
    [Switch] $help
)

if ($help -eq $true) {
    Write-Output "`"Build`" - Copiles your mod into a `".so`" or a `".a`" library"
    Write-Output "`n-- Arguments --`n"

    Write-Output "-Clean `t`t Deletes the `"build`" folder, so that the entire library is rebuilt"

    exit
}

# if user specified clean, remove all build files
if ($clean.IsPresent) {
    if (Test-Path -Path "build") {
        remove-item build -R
    }
}


if (($clean.IsPresent) -or (-not (Test-Path -Path "build"))) {
    new-item -Path build -ItemType Directory
} 

Invoke-Expression "cmake -G ""Ninja"" -DCMAKE_BUILD_TYPE=""RelWithDebInfo"" -DNO_GIMMICK=$no_gimmick -B build"
cmake --build ./build