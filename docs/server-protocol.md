## Server Protocol

JSON-API Independer Server. Please also visit [escape rules](escape-rules.md).

- `<server-url>/v1/msg/<receiverId>` (GET): Get all messages
    - Response `OK`

- `<server-url>/v1/msg` (POST): Write a message
    - `receiver`: Receiver of the message
    - `author`: Author of the message
    - `msg`: Content of the message

- `<server-url>/v1/clearmsg/<receiverId>` (GET): Clear all messages
    - Response `OK`
