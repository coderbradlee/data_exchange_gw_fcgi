/*
Navicat MySQL Data Transfer

Source Server         : 172.18.22.202
Source Server Version : 50615
Source Host           : 172.18.22.202:3306
Source Database       : apollo_os

Target Server Type    : MYSQL
Target Server Version : 50615
File Encoding         : 65001

Date: 2016-03-14 15:05:35
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for t_customer_master
-- ----------------------------
DROP TABLE IF EXISTS `t_customer_master`;
CREATE TABLE `t_customer_master` (
  `customer_master_id` char(20) NOT NULL COMMENT '/*主键*/',
  `customer_basic_id` char(20) NOT NULL COMMENT '/*客户基本档案id*/',
  `company_id` char(20) NOT NULL COMMENT '/*关联公司id*/',
  `owner_sales_sys_account_id` char(20) DEFAULT NULL COMMENT '/*归属销售代表系统帐号id*/',
  `credit_balance` decimal(20,8) NOT NULL DEFAULT '0.00000000' COMMENT '/*当前信用额度, 统计自信用收支(流水)*/',
  `default_currency_id` char(20) DEFAULT NULL COMMENT '/*默认币种id*/',
  `default_payment_term` char(100) DEFAULT NULL COMMENT '/*默认付款方式id*/',
  `default_tax_schedule_id` char(20) DEFAULT NULL COMMENT '/*默认税组id*/',
  `default_trade_term_id` char(20) DEFAULT NULL COMMENT ' /*默认贸易方式id*/',
  `default_ship_via_id` char(20) DEFAULT NULL COMMENT '/*默认运输方式id*/',
  `business_type` tinyint(4) DEFAULT NULL,
  `retailer_level` tinyint(4) DEFAULT NULL,
  `note` text COMMENT ' /*备注*/',
  `createAt` char(19) NOT NULL COMMENT '创建时间 YYYY-MM-DD HH:MM:SS',
  `createBy` char(20) DEFAULT NULL COMMENT '创建人',
  `updateAt` char(19) DEFAULT NULL COMMENT '最近修改时间 YYYY-MM-DD HH:MM:SS',
  `updateBy` char(20) DEFAULT NULL COMMENT '修改人',
  `deleteAt` char(19) DEFAULT NULL COMMENT '删除时间 YYYY-MM-DD HH:MM:SS',
  `deleteBy` char(20) DEFAULT NULL COMMENT '删除人',
  `dr` smallint(2) NOT NULL DEFAULT '0' COMMENT '逻辑删除标志 0:未删除;1:已删除',
  `data_version` int(11) NOT NULL DEFAULT '1' COMMENT '版本号 从0开始',
  PRIMARY KEY (`customer_master_id`),
  KEY `idx_t_customer_master_cstm_bs_id_comp_id` (`customer_basic_id`,`company_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='《客户管理档案》表';
