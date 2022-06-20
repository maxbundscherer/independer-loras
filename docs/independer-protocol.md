## Independer Protocol

Application level protocol is based on the LoRaS Protocol \[P1\], \[P2\], and\[P3\].

### Based on Unsafe short message \[P2\]

#### Who is in my area? \[F2.1\]

This feature is used to find out which Actors and Gateways are nearby.

1. For this \[P2\] with `[to] *` is used and `[msg]` is set to `?`. 
2. Other devices respond randomly within 3 seconds and `[msg]` is set to `[battery-rssi]`

This is repeated twice to reach and receive more devices.

#### Is available? \[F2.2\]

This function is used to find out whether a specific actor or gateway is nearby. Used mainly before sending a message over LoRaS.

1. For this \[P2\] `[msg]` is set to `!`.
2. Other device respond immedatly and `[msg]` is set to `[battery-rssi]`

This function can be repeated.
