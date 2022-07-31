## Independer Protocol

Application level protocol is based on the [LoRaS Protocol](loras-protocol.md) \[P1\], \[P2\], and\[P3\]. Please also visit [escape rules](escape-rules.md).

### Based on Unsafe single message \[P3\]

#### Sleep Mode Gateway \[F3.1\]

This feature is used to set Gateway in sleep mode (Actor controlled).

1. For this Actor \[P3\] `[msg]` is set to `C;slp`. (send twice)

No available check before sending (\[F23.2\]). Gateway sends no response and goes into sleep mode.

#### Clear User Messages on Gateway \[F3.1\]

This feature is used to clear user messages from Gateway (Actor controlled).

1. For this Actor \[P3\] `[msg]` is set to `C;clmsg`. (send twice)

No available check before sending (\[F23.2\]). Gateway sends no response and clears user messages.

### Based on Safe message \[P1\]

#### Update Gateway \[F3.1\]

This feature is used to update Gateway via wifi (Actor controlled).

1. For this Actor \[P1\] `[msg]` is set to `C;up;$wifiSSID;$wifiPW`. Where `$wifiSSID` is ssid from wifi and `$wifiPW` is wifi password.

No available check before sending (\[F23.2\]). Gateway sends no response and goes into update mode.

### Based on Safe message \[P1\] and Unsafe single message \[P3\]

#### Send Message Actor to Gateway \[F13.1\]

This function is used to send messages via Gateway from Actor to Actor. This handles communication between Actor to Gateway (sending message).

1. For this Actor check if Gateway is available (\[F23.2\]).
2. If Gateway is available: Actor to Gateway \[P1\] `[msg]` is set to `M;$receiverId;$userMsg`. Where `$receiverId` is user-id from msg-receiver and `$userMsg` is actual message. Message author is derived from `[from]`.
3. Gateway to Actor \[P3\] `[msg]` is set to `A;ok`. (send twice)

If Actor does not receive a response from Gateway, Actor goes to step 2 (skip available check). This is repeated three times.

### Based on Unsafe single message \[P3\] and Safe message \[P1\]

#### Receive Messages Actor to Gateway to Actor \[F31.1\]

This function is used to send messages via Gateway from Actor to Actor. This handles communication between Actor to Gateway to Actor (receiving messages).

1. For this Actor \[P3\] `[msg]` is set to `Q;msg`. (send twice)
2. Gateway respond \[P1\] `[msg]` is set to `A;$numMessages;$msgAuthor1;$msgContent1;$msgAuthor2;$msgContent2;$msgAuthorN;$msgContentN`. Where `$numMessages` is number of message. If set `0` no messages are available. Messages with authors are appended to `[msg]` like `$msgAuthorN;$msgContentN`.  

No available check before sending (\[F23.2\]). This is repeated three times, if Actor receives no response from Gateway.

### Based on Unsafe short message \[P2\] and Unsafe single message \[P3\]

#### Who is in my area? \[F23.1\]

This function is used to find out which Actors and Gateways are nearby.

1. For this Actor \[P2\] `[to]` is set to `*` and `[msg]` is set to `?`.  (send twice)
2. Other devices (Actors and Gateways) respond randomly within 8 seconds \[P3\] and `[msg]` is set to `$battery-$rssi`. Where `$battery` is battery in mA and `$rssi` is rssi in dbi.

This is repeated threefold to reach and receive more devices. Designed for Actor background-job and Gateway.

#### Is available? \[F23.2\]

This function is used to find out whether a specific actor or gateway is nearby. Used mainly before sending a message over LoRaS.

1. For this Actor \[P2\] `[msg]` is set to `!`. (send twice)
2. Other device (Actors and Gateways) respond immedatly \[P3\] and `[msg]` is set to `$battery-$rssi`. Where `$battery` is battery in mA and `$rssi` is rssi in dbi. (send twice)

This function can be repeated. Designed for Actor background-job and Gateway.

### Based on Unsafe short message \[P2\], Safe message \[P1\] and Unsafe single message \[P3\]

#### Send Message Actor to Actor \[F213.2\]

This function is for sending messages directly between Actor A1 and Actor A2.

1. A1 (foreground) to A2 (background) \[P2\] `[msg]` is set to `T`. (send twice)
2. A2 reply to A1 \[P3\] `[msg]` is set to `S` and switch to foreground. (send twice)
3. A1 send data to A2 \[P1\] `[msg]` is set to `$msgContent`. Where `$msgContent` is content of message.
4. A2 replies to A1 \[P3\] `[msg]` is set to `N` and switch to background. (send twice)

Designed for Actor background-job. A1 tries whole process five times. A2 goes automatic in background if no data received from A1. If A2 receive data from step 1 - A2 reply \[P3\] to A1 `[msg]` is set to `S` again.
