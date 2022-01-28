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

int handle_decode(struct qrtr_packet *pkt, unsigned* txid) {
	struct sensordaemon_sensor_client_resp qmi_resp = {};
	int ret;

	ret = qmi_decode_message(&qmi_resp, &txid, pkt, QMI_REQUEST,
			SNS_CLIENT_REQ, sensordaemon_sensor_client_req_ei);
	printf("qmi_resp: result: %d, err: %d, client_id_valid: %d, client_id: %lu, res_valid: %d, res: %d", qmi_resp.result.result, qmi_resp.result.error,
		qmi_resp.client_id_valid, qmi_resp.client_id, qmi_resp.res_valid, qmi_resp.res);
	return 0;
}

int main(int argc, char **argv)
{
	int sensor_fd, ret;
	unsigned char* buf;
	struct qrtr_packet resp;
	struct sockaddr_qrtr sq;
	socklen_t sl;
	unsigned int txid; // transaction id ?

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
	ret = qrtr_poll(sensor_fd, -1);
	printf("Got response from sensor_fd: %d\n", ret);
	ret = recvfrom(sensor_fd, buf, sizeof(buf), 0, (void *)&sq, &sl);
	if (ret < 0) {
		fprintf(stderr, "Failed to recv: %d\n", ret);
		free(buf);
		return ret;
	}
	ret = qrtr_decode(&resp, buf, sizeof(resp), &sq);
	if (ret < 0) {
		fprintf(stderr, "Failed to qrtr_decode: %d\n", ret);
		free(buf);
		return ret;
	}
	printf("type: %d, node: %d, port: %d, service: %d, version: %d, instance: %d, data_len: %lu\n",
		resp.type, resp.node, resp.port, resp.service, resp.version,
		resp.instance, resp.data_len);
	// for (size_t i = 0; i < resp.data_len; i++)
	// {
	// 	printf("0x%2x %s", *(uint8_t*)(resp.data + i),
	// 		i == resp.data_len-1 ? "\n": "");
	// }

	handle_decode(&resp, &txid);

	free(buf);
	return 0;
}
