## Server Protocol

JSON-API Independer Server. Please also visit [escape rules](escape-rules.md).

- `<server-url>/v1/register` (POST): Register Device
    - `id`: Independer-ID
    - `secret`: Secret
    - Response `OK-<token>` (string, no json)

- `<server-url>/v1/msg/<receiverId>` (POST): Get all messages
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - Response (JSON-Array)
        - `receiver`: Receiver of the message
        - `author`: Author of the message
        - `msg`: Content of the message

- `<server-url>/v1/msg` (POST): Write a message
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - `receiver`: Receiver of the message
    - `author`: Author of the message
    - `msg`: Content of the message
    - Response `OK` (string, no json)

- `<server-url>/v1/clearmsg/<receiverId>` (POST): Clear all messages
    - `auth-id`: Independer-ID
    - `auth-token`: Token
    - Response `OK` (string, no json)
