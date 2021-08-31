#ifndef __QMI_SENSORDAEMON_H__
#define __QMI_SENSORDAEMON_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

#define SNS_CLIENT_QMI_SERVICE 400
#define QMI_RESULT_SUCCESS 0
#define QMI_RESULT_FAILURE 1
#define QMI_ERR_NONE 0
#define QMI_ERR_INTERNAL 1
#define QMI_ERR_MALFORMED_MSG 2
#define SNS_CLIENT_REQ 32
#define SNS_CLIENT_RESP 32
#define SNS_CLIENT_REPORT 34

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
	bool client_id_valid;
	uint64_t client_id;
	bool res_valid;
	uint32_t res;
};

struct sensordaemon_sensor_client_ind {
	uint64_t client_id;
	uint32_t payload_len;
	uint8_t payload[1000];
};

extern struct qmi_elem_info sensordaemon_sensor_client_req_ei[];
extern struct qmi_elem_info sensordaemon_sensor_client_resp_ei[];
extern struct qmi_elem_info sensordaemon_sensor_client_ind_ei[];

#endif
