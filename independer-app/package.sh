echo Please Enter versionTag - e.g. \'v.0.1.8\'
read versiontag
echo Set Tag to \'$versiontag\'
echo

rm -rf export
mkdir export

mv ./.pio/build/ttgo-gateway-release/firmware.bin "export/$versiontag-ttgo-gateway-release".bin
mv ./.pio/build/ttgo-gateway-developer/firmware.bin "export/$versiontag-ttgo-gateway-developer".bin

mv ./.pio/build/heltec-actor-developer/firmware.bin "export/$versiontag-heltec-actor-developer".bin
mv ./.pio/build/heltec-gateway-release/firmware.bin "export/$versiontag-heltec-gateway-release".bin

mv ./.pio/build/heltec-actor-release/firmware.bin "export/$versiontag-heltec-actor-release".bin
mv ./.pio/build/heltec-gateway-developer/firmware.bin "export/$versiontag-heltec-gateway-developer".bin
