## Independer App Server

Docker is required.

### Commands

#### Run and Install

- Generate SSL Certificate
    - `openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -sha256 -nodes`
    - (Move `key.pem` and `cert.perm` to `./`)
- `docker-compose up`
- Add Users and Gateways in table `users` and `gateways`

#### Status

- `docker ps -a`
- `docker compose ls`

#### Stop and Clean

- Run `./clean-docker.sh`
