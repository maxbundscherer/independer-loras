## Server Protocol

JSON-API Independer Server. Please also visit [escape rules](escape-rules.md).

- `<server-url>/v1/register` (POST): Register Device
    - `id`: Independer-ID
    - `secret`: Secret
    - Response `OK-<deviceToken>` (string, no json)

- `<server-url>/v1/msg/<receiverId>` (GET): Get all messages
    - Response `OK` (string, no json)

- `<server-url>/v1/msg` (POST): Write a message
    - `receiver`: Receiver of the message
    - `author`: Author of the message
    - `msg`: Content of the message
    - Response `OK` (string, no json)

- `<server-url>/v1/clearmsg/<receiverId>` (GET): Clear all messages
    - Response `OK` (string, no json)
