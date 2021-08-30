# QRTR / QMI sensor daemon

# Device setup (pmos)

## Install deps
```bash
sudo apk add alpine-sdk sshfs eudev-dev qrtr-dev
```

## Mount build dir
First on host setup USB network gadget: `at-usbnet`

```bash
sudo modprobe fuse
mkdir sensordaemon
sshfs -o allow_other cas@172.16.42.2:/home/cas/pmos/enchilada/sensors/sensordaemon sensordaemon
```
