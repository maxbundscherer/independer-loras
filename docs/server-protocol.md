## Server Protocol

JSON-API Independer Server.

- `<server-url>/v1/msg/<receiverId>` (GET): Get all messages

- `<server-url>/v1/msg` (POST): Write a message
    - `receiver`: Receiver of the message
    - `author`: Author of the message
    - `msg`: Content of the message
