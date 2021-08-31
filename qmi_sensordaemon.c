#include <errno.h>
#include <string.h>
#include "qmi_sensordaemon.h"

struct qmi_elem_info sensordaemon_qmi_result_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct sensordaemon_qmi_result, result),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct sensordaemon_qmi_result, error),
	},
	{}
};

struct qmi_elem_info sensordaemon_sensor_client_req_ei[] = {
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 1,
		.offset = offsetof(struct sensordaemon_sensor_client_req, payload_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1000,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 1,
		.offset = offsetof(struct sensordaemon_sensor_client_req, payload),
	},
	{}
};

struct qmi_elem_info sensordaemon_sensor_client_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct sensordaemon_qmi_result),
		.tlv_type = 2,
		.offset = offsetof(struct sensordaemon_sensor_client_resp, result),
		.ei_array = sensordaemon_qmi_result_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct sensordaemon_sensor_client_resp, client_id_valid),
	},
	{
		.data_type = QMI_UNSIGNED_8_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint64_t),
		.tlv_type = 16,
		.offset = offsetof(struct sensordaemon_sensor_client_resp, client_id),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct sensordaemon_sensor_client_resp, res_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 17,
		.offset = offsetof(struct sensordaemon_sensor_client_resp, res),
	},
	{}
};

struct qmi_elem_info sensordaemon_sensor_client_ind_ei[] = {
	{
		.data_type = QMI_UNSIGNED_8_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint64_t),
		.tlv_type = 1,
		.offset = offsetof(struct sensordaemon_sensor_client_ind, client_id),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 2,
		.offset = offsetof(struct sensordaemon_sensor_client_ind, payload_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1000,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 2,
		.offset = offsetof(struct sensordaemon_sensor_client_ind, payload),
	},
	{}
};

