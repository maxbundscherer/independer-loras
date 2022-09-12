## Independer App Server

Docker is required.

### Run and Install

#### PreStep: Generate SSL Certificate

- `openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -sha256 -nodes` (set CN/FQDN to hostname)
- (Move `key.pem` and `cert.perm` to `./`)

#### Run

- Run `./run-raspbery.sh` on Raspberry Pi
- Run `./run-linux.sh` on Linux, macOs, etc.

##### Bugfix Raspberry TimeZone

If Postgres-Container does not sync time with Raspberry-Host - on Raspberry:

- `sudo vim /etc/apt/sources.list`
    - Add `deb http://raspbian.raspberrypi.org/raspbian/ testing main`
- `sudo apt-get update`
- `sudo apt-get install libseccomp2/testing`

#### Add Data

- Add Users and Gateways in table `users` and `gateways`

#### Config Network

- Config Router DNS to server (local ip)
- Config Router to forward port to server

### Status

- `docker ps -a`
- `docker compose ls`

### Stop and Clean

- Run `./clean-docker.sh`
