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
#define QMI_SD_OPEN 1
#define QMI_SD_CLOSE 2
#define QMI_SD_RW_IOVEC 3
#define QMI_SD_ALLOC_BUFF 4
#define QMI_SD_GET_DEV_ERROR 5
#define QMI_SD_FORCE_SYNC_IND 6

struct sensordaemon_qmi_result {
	uint16_t result;
	uint16_t error;
};

struct sensordaemon_open_req {
	uint32_t path_len;
	char path[256];
};

struct sensordaemon_open_resp {
	struct sensordaemon_qmi_result result;
	bool caller_id_valid;
	uint32_t caller_id;
};

struct sensordaemon_close_req {
	uint32_t caller_id;
};

struct sensordaemon_close_resp {
	struct sensordaemon_qmi_result result;
};

struct sensordaemon_alloc_buf_req {
	uint32_t caller_id;
	uint32_t buff_size;
};

struct sensordaemon_alloc_buf_resp {
	struct sensordaemon_qmi_result result;
	bool buff_address_valid;
	uint64_t buff_address;
};

struct sensordaemon_dev_error_req {
	uint32_t caller_id;
};

struct sensordaemon_dev_error_resp {
	struct sensordaemon_qmi_result result;
	bool status_valid;
	uint8_t status;
};

struct sensordaemon_force_sync {
	uint32_t caller_id_len;
	uint32_t caller_id[10];
};

extern struct qmi_elem_info sensordaemon_open_req_ei[];
extern struct qmi_elem_info sensordaemon_open_resp_ei[];
extern struct qmi_elem_info sensordaemon_close_req_ei[];
extern struct qmi_elem_info sensordaemon_close_resp_ei[];
extern struct qmi_elem_info sensordaemon_alloc_buf_req_ei[];
extern struct qmi_elem_info sensordaemon_alloc_buf_resp_ei[];
extern struct qmi_elem_info sensordaemon_dev_error_req_ei[];
extern struct qmi_elem_info sensordaemon_dev_error_resp_ei[];
extern struct qmi_elem_info sensordaemon_force_sync_ei[];

#endif
