## Independer Protocol

Application level protocol is based on the LoRaS Protocol \[P1\], \[P2\], and\[P3\].

### Based on Unsafe single message \[P3\]

#### Sleep Mode Gateway \[F3.1\]

This feature is used to set Gateway in sleep mode (Actor controlled).

1. For this Actor \[P3\] `[msg]` is set to `cmd_sleep`.

No available check before sending. Gateway sends no response and goes into sleep mode.

### Based on Safe message \[P1\]

#### Send Message Actor to Gateway via. LoRaS \[F1.1\]

...

### Based on Unsafe short message \[P2\] and Unsafe single message \[P3\]

#### Who is in my area? \[F23.1\]

This feature is used to find out which Actors and Gateways are nearby.

1. For this Actor \[P2\] with `[to] *` is used and `[msg]` is set to `?`. 
2. Other devices (Actors and Gateways) respond randomly within 6 seconds \[P3\] and `[msg]` is set to `[battery-rssi]`

This is repeated threefold to reach and receive more devices. Designed for Actor background-job and Gateway.

#### Is available? \[F23.2\]

This function is used to find out whether a specific actor or gateway is nearby. Used mainly before sending a message over LoRaS.

1. For this Actor \[P2\] `[msg]` is set to `!`.
2. Other device (Actors and Gateways) respond immedatly \[P3\] and `[msg]` is set to `[battery-rssi]`

This function can be repeated. Designed for Actor background-job and Gateway.
