#ifndef __QMI_SENSORDAEMON_H__
#define __QMI_SENSORDAEMON_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

#define QMI_SD_RESULT_SUCCESS 0
#define QMI_SD_RESULT_FAILURE 1
#define QMI_SD_ERR_NONE 0
#define QMI_SD_ERR_INTERNAL 1
#define QMI_SD_ERR_MALFORMED_MSG 2
#define QMI_SD_CLIENT_REQ 32
#define QMI_SD_CLOSE 2
#define QMI_SD_RW_IOVEC 3
#define QMI_SD_ALLOC_BUFF 4
#define QMI_SD_GET_DEV_ERROR 5
#define QMI_SD_FORCE_SYNC_IND 6

struct sensordaemon_qmi_result {
	uint16_t result;
	uint16_t error;
};

struct sensordaemon_sensor_client_req {
	uint32_t payload_len;
	uint8_t payload[1000];
};

struct sensordaemon_sensor_client_resp {
	struct sensordaemon_qmi_result result;
	uint32_t payload_len;
	uint8_t payload[1000];
};

extern struct qmi_elem_info sensordaemon_sensor_client_req_ei[];
extern struct qmi_elem_info sensordaemon_sensor_client_resp_ei[];

#endif
