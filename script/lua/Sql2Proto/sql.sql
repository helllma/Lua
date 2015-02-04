-- Create table
create table TB_ITASSET
(
  ASSETID           NUMBER(9) not null,
  TRADEMARKID       NUMBER(9) not null,
  CLASSIFYID        NUMBER(9) not null,
  SELLERID          NUMBER(9) not null,
  MANUFACTORYID     NUMBER(9) not null,
  EQATTID           NUMBER(9) not null,
  BUYDATE           VARCHAR2(20),
  BATCHNO           VARCHAR2(30),
  CONTRACTNO        VARCHAR2(30),
  ITEMNAME          VARCHAR2(200),
  FEENAME           VARCHAR2(200),
  FEESOURCE         VARCHAR2(200),
  FINAASSETID       VARCHAR2(30),
  PRICE             NUMBER(14,2),
  UNITID            NUMBER(9),
  DEPTID            NUMBER(9),
  STATUS            NUMBER(2) default 0 not null,
  SN                VARCHAR2(30),
  RFID              VARCHAR2(128),
  USERNAME          VARCHAR2(20),
  TOUSEDATE         VARCHAR2(14),
  FINDCODE          VARCHAR2(30),
  COMMISSIONINGDATE VARCHAR2(20),
  LICENCE           VARCHAR2(100),
  WARRANTY          VARCHAR2(20),
  MANAGERID         NUMBER(9),
  TRANSACTIONID     VARCHAR2(30),
  LABEL             VARCHAR2(200),
  CREATERNAME       VARCHAR2(50),
  MEMO              VARCHAR2(200),
  OPID              NUMBER(9),
  OPTIME            VARCHAR2(20) default TO_CHAR(SYSDATE,'YYYYMMDDHH24MISS') not null,
  ALTERSUMMARY      VARCHAR2(2048),
  TEXT1             VARCHAR2(200),
  TEXT2             VARCHAR2(200),
  TEXT3             VARCHAR2(200),
  HISTIME           VARCHAR2(20) default TO_CHAR(SYSDATE,'YYYYMMDDHH24MISS'),
  ALTERFLAG         NUMBER(9) default -1 not null
)
tablespace ITSM
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 6
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column TB_ITASSET.ASSETID
  is '资产ID';
comment on column TB_ITASSET.TRADEMARKID
  is '品牌型号ID';
comment on column TB_ITASSET.CLASSIFYID
  is '对应流程类型分类表FLOWTYPEID=1004的CLASSIFID';
comment on column TB_ITASSET.SELLERID
  is '销售商ID';
comment on column TB_ITASSET.MANUFACTORYID
  is '生产厂家ID对应生产厂家表中的MANUFACTORYID';
comment on column TB_ITASSET.EQATTID
  is '设备属性ID';
comment on column TB_ITASSET.BUYDATE
  is '购置日期';
comment on column TB_ITASSET.BATCHNO
  is '主机/软件名称';
comment on column TB_ITASSET.CONTRACTNO
  is '合同号';
comment on column TB_ITASSET.ITEMNAME
  is '项目名称';
comment on column TB_ITASSET.FEENAME
  is '费用项目名称';
comment on column TB_ITASSET.FEESOURCE
  is '费用来源';
comment on column TB_ITASSET.FINAASSETID
  is '资产编号(财务资产编号)';
comment on column TB_ITASSET.PRICE
  is '单价';
comment on column TB_ITASSET.UNITID
  is '所属基层';
comment on column TB_ITASSET.DEPTID
  is '使用部门';
comment on column TB_ITASSET.STATUS
  is '设备状态';
comment on column TB_ITASSET.SN
  is '产品序号';
comment on column TB_ITASSET.RFID
  is '设备编码<只读>';
comment on column TB_ITASSET.USERNAME
  is '领用人';
comment on column TB_ITASSET.TOUSEDATE
  is '领用日期';
comment on column TB_ITASSET.FINDCODE
  is '虚拟资源池';
comment on column TB_ITASSET.COMMISSIONINGDATE
  is '投运日期';
comment on column TB_ITASSET.LICENCE
  is '许可证（License数量）';
comment on column TB_ITASSET.WARRANTY
  is '保修期';
comment on column TB_ITASSET.MANAGERID
  is '资产管理人ID';
comment on column TB_ITASSET.TRANSACTIONID
  is '工单编号，年月日加001（三位递增整数）';
comment on column TB_ITASSET.LABEL
  is '设备编号';
comment on column TB_ITASSET.CREATERNAME
  is '资产状态（常态或非常态）';
comment on column TB_ITASSET.MEMO
  is '备注';
comment on column TB_ITASSET.OPID
  is '操作员ID';
comment on column TB_ITASSET.OPTIME
  is '操作时间';
comment on column TB_ITASSET.ALTERSUMMARY
  is '变更提示';
comment on column TB_ITASSET.TEXT1
  is '负责人联系电话';
comment on column TB_ITASSET.TEXT2
  is '设备用途';
comment on column TB_ITASSET.TEXT3
  is '监控路径';
comment on column TB_ITASSET.HISTIME
  is '无用和历史表中统一';
comment on column TB_ITASSET.ALTERFLAG
  is '无用和temp表中统一';
-- Create/Recreate primary, unique and foreign key constraints 
alter table TB_ITASSET
  add constraint PK_TB_ITASSETID primary key (ASSETID)
  using index 
  tablespace ITSM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 832K
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate indexes 
create index INDEX_ITASSET_DEPTID on TB_ITASSET (DEPTID)
  tablespace ITSM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 640K
    minextents 1
    maxextents unlimited
  );
create index INDEX_ITASSET_EQATTID on TB_ITASSET (EQATTID)
  tablespace ITSM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 832K
    minextents 1
    maxextents unlimited
  );
create index INDEX_ITASSET_STATUS on TB_ITASSET (STATUS)
  tablespace ITSM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 640K
    minextents 1
    maxextents unlimited
  );
create index INDEX_ITASSET_TEXT2 on TB_ITASSET (TEXT2)
  tablespace ITSM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 320K
    minextents 1
    maxextents unlimited
  );
create index INDEX_ITASSET_UNITID on TB_ITASSET (UNITID)
  tablespace ITSM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 640K
    minextents 1
    maxextents unlimited
  );
