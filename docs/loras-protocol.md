## LoRaS Protocol

This protocol is based on the **LoRa radio standard** and the transmission is currently **encrypted** with AES. The goal will be an **asymmetric protocol like GPG**. Attention has always been paid to **low overhead**, **transmission security** and **energy saving**. The three protocols in this section are for LoRa receive and transmit (non-application level).

Currently the frequency **868 MHz** is used, but in the future the frequency **433 MHz** will also be usable. The frequencies are currently designed for the German area, but **can be freely selected**. Possible legal restrictions, such as the specified duty cycle and transmit power, can be taken into account, for example, using the *Send quota* and *Send gain* settings.

`[from]` and `[to]` in this section are realated to hardware-IDs, not application IDs. 

\[P1\] and \[P3\] are not suitable for background processing on actors.

### Safe message \[P1\]

*Send message with hashcode-check*: Default protocol for e.g. Application messages.

`[num_packets]`, `[current_packet]`, and `[hashcode_msg]` are int-values.

- `[from]:[to]:+:[num_packets]`
- `[from]:[to]:[current_packet]:[part_of_msg]`
- `[from]:[to]:-:[hashcode_msg]`

### Unsafe short message \[P2\]

*Send short message without hashcode-check*: Default protocol for e.g. Who is in my area? or Is available?

Setting `[to]` to `*` addresses all devices in the environment.

- `[from]:[to]:s:[msg]`

### Unsafe single message \[P3\]

*Send single message without hashcode-check*: Default protocol for e.g. Respond to Who is in my area? and Is available?.

- `[from]:[to]:!:[msg]`
