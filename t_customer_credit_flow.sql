/*
Navicat MySQL Data Transfer

Source Server         : 172.18.22.202
Source Server Version : 50615
Source Host           : 172.18.22.202:3306
Source Database       : apollo_os

Target Server Type    : MYSQL
Target Server Version : 50615
File Encoding         : 65001

Date: 2016-03-11 16:22:31
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for t_customer_credit_flow
-- ----------------------------
DROP TABLE IF EXISTS `t_customer_credit_flow`;
CREATE TABLE `t_customer_credit_flow` (
  `customer_credit_flow_id` char(20) NOT NULL COMMENT ' /*主键*/',
  `company_id` char(20) NOT NULL COMMENT ' /*公司id*/',
  `customer_master_id` char(20) NOT NULL COMMENT '/*客户管理档案id*/',
  `transaction_no` varchar(128) NOT NULL COMMENT '/*交易流水号*/',
  `transaction_type` tinyint(4) NOT NULL COMMENT ' /*交易类型, 0:信用开户; 1:信用销户; 2:信用支出; 3:信用存入*/',
  `insurer_id` char(20) DEFAULT NULL COMMENT ' /*保险商id*/',
  `effective_date` char(19) DEFAULT NULL COMMENT '/*生效日期*/',
  `expire_date` char(19) DEFAULT NULL COMMENT ' /*失效日期*/',
  `transaction_amount` decimal(20,8) NOT NULL COMMENT ' /*交易金额*/',
  `credit_days` smallint(6) DEFAULT NULL COMMENT '/*帐期, 当transaction_type为’0’时填写*/',
  `invoice_no` varchar(128) DEFAULT NULL COMMENT '/*发票编码*/',
  `ar_voucher_no` varchar(128) DEFAULT NULL COMMENT ' /*收款凭证编码*/',
  `ar_accountant_id` char(20) DEFAULT NULL COMMENT ' /*收款会计id*/',
  `balance` decimal(20,8) NOT NULL COMMENT '/*信用余额*/',
  `transaction_date` char(19) NOT NULL COMMENT ' /*交易日期*/',
  `note` text COMMENT ' /*备注*/',
  `createAt` char(19) NOT NULL COMMENT '/*创建时间, YYYY-MM-DD HH:MM:SS*/',
  `createBy` char(20) DEFAULT NULL COMMENT '/*创建人*/',
  `updateAt` char(19) DEFAULT NULL COMMENT '/*最近修改时间, YYYY-MM-DD HH:MM:SS*/',
  `updateBy` char(20) DEFAULT NULL COMMENT '/*修改人*/',
  `deleteAt` char(19) DEFAULT NULL COMMENT '/*删除时间, YYYY-MM-DD HH:MM:SS*/',
  `deleteBy` char(20) DEFAULT NULL COMMENT '/*删除人*/',
  `dr` smallint(2) NOT NULL DEFAULT '0' COMMENT '/*逻辑删除标志 0:未删除;1:已删除*/',
  `data_version` int(11) NOT NULL DEFAULT '1' COMMENT '/*版本号, 从0开始*/',
  PRIMARY KEY (`customer_credit_flow_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='《客户信用流水》表';
