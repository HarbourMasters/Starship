#!/bin/bash
HERE="$(dirname "$(readlink -f "${0}")")"/../..

export PATH="$HERE"/bin:"$HERE"/usr/bin:"$PATH"
export LD_LIBRARY_PATH="$HERE"/usr/lib:"$LD_LIBRARY_PATH"
export ZENITY=$(command -v zenity)

if [ -z ${SHIP_HOME+x} ]; then
export SHIP_HOME=$PWD
fi

if [ -z ${SHIP_BIN_DIR+x} ]; then
export SHIP_BIN_DIR="$HERE/usr/bin"
fi

if [[ ! -e "$SHIP_HOME"/mods ]]; then
    mkdir -p "$SHIP_HOME"/mods
    touch "$SHIP_HOME"/mods/custom_mod_files_go_here.txt
fi

while [[ (! -e "$SHIP_HOME"/sf64.otr) ]]; do
    for romfile in "$SHIP_HOME"/*.*64
    do
        if [[ -e "$romfile" ]] || [[ -L "$romfile" ]]; then
            export ASSETDIR="$(mktemp -d /tmp/assets-XXXXX)"
            cp -r "$SHIP_BIN_DIR"/{assets,include,config.yml,torch} "$ASSETDIR"
            export OLDPWD="$PWD"
            mkdir -p "$ASSETDIR"/tmp
            if [[ -e "$romfile" ]]; then
                cp -r "$romfile" "$ASSETDIR"/tmp/rom.z64
            else
                ORIG_ROM_PATH=$(readlink "$romfile")
                cp -r "$ORIG_ROM_PATH" "$ASSETDIR"/tmp/rom.z64
            fi
            cd "$ASSETDIR"
            ROMHASH=$(sha1sum -b "$ASSETDIR"/tmp/rom.z64 | awk '{ print $1 }')

            if [ -n "$ZENITY" ]; then
            	(echo "# 25%"; echo "25"; sleep 2; echo "# 50%"; echo "50"; sleep 3; echo "# 75%"; echo "75"; sleep 2; echo "# 100%"; echo "100"; sleep 3) | zenity --progress --title="OTR Generating..." --timeout=10 --percentage=0 --icon=logo.png --height=80 --width=400 &
            else
                 echo "Processing..."
            fi
			"$ASSETDIR"/torch otr "$ASSETDIR"/tmp/rom.z64 > /dev/null 2>&1
            cp "$ASSETDIR"/sf64.otr "$SHIP_HOME"
            rm -r "$ASSETDIR"
                
            # Remap v64 and n64 hashes to their z64 hash equivalent
            # ZAPD will handle converting the data into z64 format

            case "$ROMHASH" in
            09f0d105f476b00efa5303a3ebc42e60a7753b7a) # v64
                #if [[ ! -e "$SHIP_HOME"/sf64.otr ]]; then
                    ROM=baserom.us.rev1.z64
                    continue
                #fi
                ;;
            d8b1088520f7c5f81433292a9258c1184afa1457) # v64
                #if [[ ! -e "$SHIP_HOME"/sf64.otr ]]; then
                    ROM=baserom.us.z64
                    continue
                #fi
                ;;
            *)
                echo -e "\n$romfile - $ROMHASH rom hash does not match\n"
                continue;;
            esac

        else
            if [[ (! -e "$SHIP_HOME"/sf64.otr) ]]; then
                if [ -n "$ZENITY" ]; then
                    zenity --error --timeout=5 --text="Place ROM in $SHIP_HOME" --title="Missing ROM file" --width=500 --width=200
                else
                    echo -e "\nPlace ROM in this folder\n"
                fi
                exit
            fi
        fi
    done
    if [[ (! -e "$SHIP_HOME"/sf64.otr) ]]; then
        if [ -n "$ZENITY" ]; then
            zenity --error  --text="No valid ROMs were provided, No OTR was generated." --title="Incorrect ROM file" --width=500 --width=200 # --timeout=10
        else
            echo "No valid roms provided, no OTR was generated."
        fi
        rm -r "$ASSETDIR"
        exit
    else
        (cd "$SHIP_BIN_DIR"; ./Starship)
        exit
    fi
    rm -r "$ASSETDIR"
done
    (cd "$SHIP_BIN_DIR"; ./Starship)
exit
