-- Create table
create table KF_HJTJB_10_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_10_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_10_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_10_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_10_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_10_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_10_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_10_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_10_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_10_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_10_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_10_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_10_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_10_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_10_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_10_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_10_2014
  add constraint PK_KF_HJTJB_10_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_11_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_11_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_11_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_11_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_11_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_11_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_11_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_11_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_11_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_11_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_11_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_11_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_11_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_11_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_11_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_11_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_11_2014
  add constraint PK_KF_HJTJB_11_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_12_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_12_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_12_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_12_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_12_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_12_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_12_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_12_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_12_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_12_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_12_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_12_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_12_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_12_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_12_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_12_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_12_2014
  add constraint PK_KF_HJTJB_12_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_13_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_13_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_13_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_13_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_13_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_13_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_13_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_13_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_13_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_13_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_13_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_13_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_13_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_13_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_13_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_13_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_13_2014
  add constraint PK_KF_HJTJB_13_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_14_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_14_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_14_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_14_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_14_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_14_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_14_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_14_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_14_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_14_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_14_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_14_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_14_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_14_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_14_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_14_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_14_2014
  add constraint PK_KF_HJTJB_14_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_15_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_15_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_15_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_15_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_15_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_15_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_15_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_15_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_15_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_15_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_15_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_15_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_15_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_15_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_15_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_15_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_15_2014
  add constraint PK_KF_HJTJB_15_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_16_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_16_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_16_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_16_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_16_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_16_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_16_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_16_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_16_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_16_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_16_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_16_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_16_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_16_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_16_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_16_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_16_2014
  add constraint PK_KF_HJTJB_16_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_17_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_17_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_17_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_17_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_17_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_17_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_17_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_17_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_17_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_17_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_17_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_17_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_17_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_17_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_17_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_17_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_17_2014
  add constraint PK_KF_HJTJB_17_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_18_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_18_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_18_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_18_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_18_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_18_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_18_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_18_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_18_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_18_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_18_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_18_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_18_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_18_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_18_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_18_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_18_2014
  add constraint PK_KF_HJTJB_18_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_19_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_19_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_19_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_19_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_19_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_19_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_19_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_19_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_19_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_19_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_19_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_19_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_19_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_19_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_19_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_19_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_19_2014
  add constraint PK_KF_HJTJB_19_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_20_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_20_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_20_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_20_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_20_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_20_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_20_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_20_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_20_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_20_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_20_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_20_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_20_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_20_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_20_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_20_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_20_2014
  add constraint PK_KF_HJTJB_20_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_21_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_21_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_21_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_21_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_21_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_21_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_21_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_21_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_21_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_21_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_21_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_21_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_21_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_21_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_21_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_21_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_21_2014
  add constraint PK_KF_HJTJB_21_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_22_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_22_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_22_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_22_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_22_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_22_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_22_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_22_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_22_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_22_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_22_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_22_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_22_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_22_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_22_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_22_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_22_2014
  add constraint PK_KF_HJTJB_22_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_23_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_23_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_23_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_23_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_23_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_23_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_23_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_23_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_23_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_23_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_23_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_23_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_23_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_23_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_23_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_23_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_23_2014
  add constraint PK_KF_HJTJB_23_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_24_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_24_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_24_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_24_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_24_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_24_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_24_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_24_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_24_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_24_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_24_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_24_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_24_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_24_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_24_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_24_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_24_2014
  add constraint PK_KF_HJTJB_24_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_25_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_25_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_25_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_25_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_25_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_25_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_25_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_25_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_25_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_25_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_25_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_25_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_25_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_25_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_25_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_25_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_25_2014
  add constraint PK_KF_HJTJB_25_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_26_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_26_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_26_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_26_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_26_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_26_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_26_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_26_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_26_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_26_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_26_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_26_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_26_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_26_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_26_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_26_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_26_2014
  add constraint PK_KF_HJTJB_26_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_27_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_27_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_27_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_27_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_27_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_27_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_27_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_27_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_27_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_27_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_27_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_27_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_27_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_27_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_27_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_27_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_27_2014
  add constraint PK_KF_HJTJB_27_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

-- Create table
create table KF_HJTJB_28_2014
(
  TDID   VARCHAR2(32) not null,
  YWBH   VARCHAR2(8) default '0' not null,
  YYWBH  VARCHAR2(8) default '0',
  KSHJRQ NUMBER(8) default 0 not null,
  KSHJSJ NUMBER(6) default 0 not null,
  ZXKSRQ NUMBER(8) default 0 not null,
  ZXKSSJ NUMBER(8) default 0 not null,
  JSHJRQ NUMBER(8) default 0 not null,
  JSHJSJ NUMBER(8) default 0 not null,
  ZJHM   VARCHAR2(20) not null,
  BJHM   VARCHAR2(20) not null,
  HJZT   NUMBER(4) default 0 not null,
  JGBM   VARCHAR2(5) not null,
  CZYH   NUMBER(6) default 0 not null,
  BMBM   VARCHAR2(5) default '0'
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column KF_HJTJB_28_2014.TDID
  is '唯一的通道标识符';
comment on column KF_HJTJB_28_2014.YWBH
  is '业务编号';
comment on column KF_HJTJB_28_2014.YYWBH
  is '这里放同组号';
comment on column KF_HJTJB_28_2014.KSHJRQ
  is '呼叫日期';
comment on column KF_HJTJB_28_2014.KSHJSJ
  is '呼叫时间';
comment on column KF_HJTJB_28_2014.ZXKSRQ
  is '坐席开始日期';
comment on column KF_HJTJB_28_2014.ZXKSSJ
  is '坐席开始时间';
comment on column KF_HJTJB_28_2014.JSHJRQ
  is '结束呼叫日期';
comment on column KF_HJTJB_28_2014.JSHJSJ
  is '结束呼叫时间';
comment on column KF_HJTJB_28_2014.ZJHM
  is '主叫号码';
comment on column KF_HJTJB_28_2014.BJHM
  is '被叫号码';
comment on column KF_HJTJB_28_2014.HJZT
  is '呼叫状态(1.呼出 2.呼入：自动语音不转坐席 3.呼入：转坐席，30秒内无应答，用户自动挂机（不算接通率）  4.呼入：转坐席，超过30秒无应答，无人接听用户自动挂机（算接通率）5.呼入：转坐席成功';
comment on column KF_HJTJB_28_2014.JGBM
  is '机构编码';
comment on column KF_HJTJB_28_2014.CZYH
  is 'Ippbx操作员号';
comment on column KF_HJTJB_28_2014.BMBM
  is '部门编码';
-- Create/Recreate primary, unique and foreign key constraints 
alter table KF_HJTJB_28_2014
  add constraint PK_KF_HJTJB_28_2014 primary key (TDID, YWBH)
  using index 
  tablespace USERS
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
    minextents 1
    maxextents unlimited
  );

