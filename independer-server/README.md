## Independer App Server

Docker is required.

### Run and Install

#### PreStep: Generate SSL Certificate

- `openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -sha256 -nodes` (set CN/FQDN to hostname)
- (Move `key.pem` and `cert.perm` to `./`)

#### Run

- Run `./run-raspbery.sh` on Raspberry Pi
- Run `./run-linux.sh` on Linux, macOs, etc.

#### Add Data

- Add Users and Gateways in table `users` and `gateways`

### Status

- `docker ps -a`
- `docker compose ls`

### Stop and Clean

- Run `./clean-docker.sh`
