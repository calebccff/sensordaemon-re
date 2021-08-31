#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <libqrtr.h>
#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "qmi_sensordaemon.h"
#include "sensordaemon.h"

int main(int argc, char **argv)
{
	int sensor_fd, ret;
	unsigned char* buf;
	struct qrtr_packet resp;
	struct sensordaemon_sensor_client_resp qmi_resp = {};
	struct sockaddr_qrtr sq;
	socklen_t sl;

	buf = malloc(65536);

	sensor_fd = qrtr_open(0);
	if (sensor_fd < 0) {
		fprintf(stderr, "Failed to create qrtr socket\n");
		return sensor_fd;
	}
	ret = qrtr_new_lookup(sensor_fd, SNS_CLIENT_QMI_SERVICE, 0, 0);
	if (sensor_fd < 0) {
		fprintf(stderr, "Failed to lookup service\n");
		return sensor_fd;
	}
	while ((ret = qrtr_poll(sensor_fd, -1)) >= 0) {
		printf("Got response from sensor_fd: %d\n", ret);
		ret = recvfrom(sensor_fd, buf, sizeof(buf), 0, (void *)&sq, &sl);
		if (ret < 0) {
			fprintf(stderr, "Failed to recv: %d", ret);
			free(buf);
			return ret;
		}
		ret = qrtr_decode(&resp, buf, sizeof(resp), &sq);
		if (ret < 0) {
			fprintf(stderr, "Failed to recv: %d", ret);
			free(buf);
			return ret;
		}
		printf("type: %d, node: %d, port: %d, service: %d, version: %d, instance: %d, data_len: %lu, data: ",
			resp.type, resp.node, resp.port, resp.service, resp.version,
			resp.instance, resp.data_len);
		for (size_t i = 0; i < resp.data_len; i++)
		{
			printf("0x%2x %s", *(uint8_t*)(resp.data + i),
				i == resp.data_len-1 ? "\n": "");
		}

		//ret = qmi_decode_message(&qmi_resp, 0, &resp, )
	}

	free(buf);
	return 0;
}
