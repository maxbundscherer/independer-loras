echo Please Enter versionTag - e.g. \'v.0.1.8\'
read versiontag
echo Set Tag to \'$versiontag\'
echo

rm -rf export
mkdir export

mv ./.pio/build/heltec-gateway-release-de-868MHz/firmware.bin "export/$versiontag-heltec-gateway-release-de-868MHz".bin
mv ./.pio/build/heltec-gateway-release-de-915MHz/firmware.bin "export/$versiontag-heltec-gateway-release-de-915MHz".bin
mv ./.pio/build/heltec-gateway-release-en-868MHz/firmware.bin "export/$versiontag-heltec-gateway-release-en-868MHz".bin
mv ./.pio/build/heltec-gateway-release-en-915MHz/firmware.bin "export/$versiontag-heltec-gateway-release-en-915MHz".bin

mv ./.pio/build/ttgo-gateway-release-de-868MHz/firmware.bin "export/$versiontag-ttgo-gateway-release-de-868MHz".bin
mv ./.pio/build/ttgo-gateway-release-de-915MHz/firmware.bin "export/$versiontag-ttgo-gateway-release-de-915MHz".bin
mv ./.pio/build/ttgo-gateway-release-en-868MHz/firmware.bin "export/$versiontag-ttgo-gateway-release-en-868MHz".bin
mv ./.pio/build/ttgo-gateway-release-en-915MHz/firmware.bin "export/$versiontag-ttgo-gateway-release-en-915MHz".bin

mv ./.pio/build/heltec-actor-release-de-868MHz/firmware.bin "export/$versiontag-heltec-actor-release-de-868MHz".bin
mv ./.pio/build/heltec-actor-release-de-915MHz/firmware.bin "export/$versiontag-heltec-actor-release-de-915MHz".bin
mv ./.pio/build/heltec-actor-release-en-868MHz/firmware.bin "export/$versiontag-heltec-actor-release-en-868MHz".bin
mv ./.pio/build/heltec-actor-release-en-915MHz/firmware.bin "export/$versiontag-heltec-actor-release-en-915MHz".bin

mv ./.pio/build/ttgo-actor-release-de-868MHz/firmware.bin "export/$versiontag-ttgo-actor-release-de-868MHz".bin
mv ./.pio/build/ttgo-actor-release-de-915MHz/firmware.bin "export/$versiontag-ttgo-actor-release-de-915MHz".bin
mv ./.pio/build/ttgo-actor-release-en-868MHz/firmware.bin "export/$versiontag-ttgo-actor-release-en-868MHz".bin
mv ./.pio/build/ttgo-actor-release-en-915MHz/firmware.bin "export/$versiontag-ttgo-actor-release-en-915MHz".bin
