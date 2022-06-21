## Independer Protocol

Application level protocol is based on the LoRaS Protocol \[P1\], \[P2\], and\[P3\].

### Based on Unsafe single message \[P3\]

#### Sleep Mode Gateway \[F3.1\]

This feature is used to set Gateway in sleep mode (Actor controlled).

1. For this Actor \[P3\] `[msg]` is set to `(C)(sleep)`.

No available check before sending (\[F23.2\]). Gateway sends no response and goes into sleep mode.

### Based on Safe message \[P1\] and Unsafe single message \[P3\]

#### Send Message Actor to Gateway \[F13.1\]

This function is used to send messages via Gateway from Actor to Actor. This handles communication between Actor to Gateway (sending message).

1. For this Actor check if Gateway is available (\[F23.2\]).
2. If Gateway is available: Actor to Gateway \[P1\] `[msg]` is set to `(M)($receiverId)($userMsg)`. Where `$receiverId` is user-id from msg-receiver and `$userMsg` is actual message. Message author is derived from `[from]`.
3. Gateway to Actor \[P3\] `[msg]` is set to `(A)(ok)`.

If Actor does not receive a response from Gateway, Actor goes to step 2 (skip available check). This is repeated three times.

### Based on Unsafe single message \[P3\] and Safe message \[P1\]

#### Receive Messages Actor to Gateway to Actor \[F31.1\]

This function is used to send messages via Gateway from Actor to Actor. This handles communication between Actor to Gateway to Actor (receiving messages).

1. For this Actor \[P3\] `[msg]` is set to `(Q)(msg)`.
2. Gateway respond \[P1\] `[msg]` is set to `(A)($numMessages)($msgAuthor1)($msgContent1)($msgAuthor2)($msgContent2)($msgAuthorN)($msgContentN)`. Where `$numMessages` is number of message. If set `0` no messages are available. Messages with authors are appended to `[msg]` like `($msgAuthorN)($msgContentN)`.  

No available check before sending (\[F23.2\]). This is repeated three times, if Actor receives no response from Gateway.

### Based on Unsafe short message \[P2\] and Unsafe single message \[P3\]

#### Who is in my area? \[F23.1\]

This function is used to find out which Actors and Gateways are nearby.

1. For this Actor \[P2\] `[to]` is set to `*` and `[msg]` is set to `?`. 
2. Other devices (Actors and Gateways) respond randomly within 6 seconds \[P3\] and `[msg]` is set to `[$battery-$rssi]`. Where `$battery` is battery in mA and `$rssi` is rssi in dbi.

This is repeated threefold to reach and receive more devices. Designed for Actor background-job and Gateway.

#### Is available? \[F23.2\]

This function is used to find out whether a specific actor or gateway is nearby. Used mainly before sending a message over LoRaS.

1. For this Actor \[P2\] `[msg]` is set to `!`.
2. Other device (Actors and Gateways) respond immedatly \[P3\] and `[msg]` is set to `[$battery-$rssi]`. Where `$battery` is battery in mA and `$rssi` is rssi in dbi.

This function can be repeated. Designed for Actor background-job and Gateway.
