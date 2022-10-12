## Server Protocol

JSON-API Independer Server. Please also visit [escape rules](escape-rules.md).

- `<server-url>/v1/register` (POST): Register Device
    - `id`: Independer-ID
    - `secret`: Secret
    - `version`: Version-String of Actor
    - Response `OK-<token>` (string, no json)

- `<server-url>/v1/getmsgs` (POST): Get all messages
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - Response (JSON-Array)
        - `receiver`: Receiver of the message
        - `author`: Author of the message
        - `msg`: Content of the message

- `<server-url>/v1/writemsg` (POST): Write a message
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - `receiver`: Receiver of the message
    - `msg`: Content of the message
    - Response `OK` (string, no json)

- `<server-url>/v1/clearmsgs` (POST): Clear all messages
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - Response `OK` (string, no json)

- `<server-url>/v1/gatewayregister` (POST): Check if Gateway is owned by the user
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - `gateway-id`: ID of Gateway
    - Response `OK` (string, no json) if allowed

- `<server-url>/v1/autosync` (POST): Get all messages
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - `version`: Version-String of Actor
    - `battery`: Battery mV of Actor
    - `time_before_sync`: Device time Actor before ntp sync
    - `time_after_sync`: Device time Actor after ntp sync
    - `dev_mode`: Dev mode activated
    - `is_actor`: IsActor
    - `wifi_ssid`: Wifi SSID
    - `boot_counts`: Boot Counts
    - Response (JSON-Array)
        - `num_msg`: Number of unread messages
        - `status_msg`: Status Broadcast
        - `act_version`: Independer-Version (last release) 
