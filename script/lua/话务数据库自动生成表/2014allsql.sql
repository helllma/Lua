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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_10_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_10_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_10_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_10_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_10_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_10_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_10_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_10_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_10_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_10_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_10_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_10_2014.JGBM
  is '��������';
comment on column KF_HJTJB_10_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_10_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_11_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_11_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_11_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_11_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_11_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_11_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_11_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_11_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_11_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_11_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_11_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_11_2014.JGBM
  is '��������';
comment on column KF_HJTJB_11_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_11_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_12_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_12_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_12_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_12_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_12_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_12_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_12_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_12_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_12_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_12_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_12_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_12_2014.JGBM
  is '��������';
comment on column KF_HJTJB_12_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_12_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_13_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_13_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_13_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_13_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_13_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_13_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_13_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_13_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_13_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_13_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_13_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_13_2014.JGBM
  is '��������';
comment on column KF_HJTJB_13_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_13_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_14_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_14_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_14_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_14_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_14_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_14_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_14_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_14_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_14_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_14_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_14_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_14_2014.JGBM
  is '��������';
comment on column KF_HJTJB_14_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_14_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_15_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_15_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_15_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_15_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_15_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_15_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_15_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_15_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_15_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_15_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_15_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_15_2014.JGBM
  is '��������';
comment on column KF_HJTJB_15_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_15_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_16_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_16_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_16_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_16_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_16_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_16_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_16_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_16_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_16_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_16_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_16_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_16_2014.JGBM
  is '��������';
comment on column KF_HJTJB_16_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_16_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_17_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_17_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_17_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_17_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_17_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_17_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_17_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_17_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_17_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_17_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_17_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_17_2014.JGBM
  is '��������';
comment on column KF_HJTJB_17_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_17_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_18_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_18_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_18_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_18_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_18_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_18_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_18_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_18_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_18_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_18_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_18_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_18_2014.JGBM
  is '��������';
comment on column KF_HJTJB_18_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_18_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_19_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_19_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_19_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_19_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_19_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_19_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_19_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_19_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_19_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_19_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_19_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_19_2014.JGBM
  is '��������';
comment on column KF_HJTJB_19_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_19_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_20_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_20_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_20_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_20_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_20_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_20_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_20_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_20_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_20_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_20_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_20_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_20_2014.JGBM
  is '��������';
comment on column KF_HJTJB_20_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_20_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_21_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_21_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_21_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_21_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_21_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_21_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_21_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_21_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_21_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_21_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_21_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_21_2014.JGBM
  is '��������';
comment on column KF_HJTJB_21_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_21_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_22_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_22_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_22_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_22_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_22_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_22_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_22_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_22_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_22_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_22_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_22_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_22_2014.JGBM
  is '��������';
comment on column KF_HJTJB_22_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_22_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_23_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_23_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_23_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_23_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_23_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_23_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_23_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_23_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_23_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_23_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_23_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_23_2014.JGBM
  is '��������';
comment on column KF_HJTJB_23_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_23_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_24_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_24_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_24_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_24_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_24_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_24_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_24_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_24_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_24_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_24_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_24_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_24_2014.JGBM
  is '��������';
comment on column KF_HJTJB_24_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_24_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_25_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_25_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_25_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_25_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_25_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_25_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_25_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_25_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_25_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_25_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_25_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_25_2014.JGBM
  is '��������';
comment on column KF_HJTJB_25_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_25_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_26_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_26_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_26_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_26_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_26_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_26_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_26_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_26_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_26_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_26_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_26_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_26_2014.JGBM
  is '��������';
comment on column KF_HJTJB_26_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_26_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_27_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_27_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_27_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_27_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_27_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_27_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_27_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_27_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_27_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_27_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_27_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_27_2014.JGBM
  is '��������';
comment on column KF_HJTJB_27_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_27_2014.BMBM
  is '���ű���';
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
  is 'Ψһ��ͨ����ʶ��';
comment on column KF_HJTJB_28_2014.YWBH
  is 'ҵ����';
comment on column KF_HJTJB_28_2014.YYWBH
  is '�����ͬ���';
comment on column KF_HJTJB_28_2014.KSHJRQ
  is '��������';
comment on column KF_HJTJB_28_2014.KSHJSJ
  is '����ʱ��';
comment on column KF_HJTJB_28_2014.ZXKSRQ
  is '��ϯ��ʼ����';
comment on column KF_HJTJB_28_2014.ZXKSSJ
  is '��ϯ��ʼʱ��';
comment on column KF_HJTJB_28_2014.JSHJRQ
  is '������������';
comment on column KF_HJTJB_28_2014.JSHJSJ
  is '��������ʱ��';
comment on column KF_HJTJB_28_2014.ZJHM
  is '���к���';
comment on column KF_HJTJB_28_2014.BJHM
  is '���к���';
comment on column KF_HJTJB_28_2014.HJZT
  is '����״̬(1.���� 2.���룺�Զ�������ת��ϯ 3.���룺ת��ϯ��30������Ӧ���û��Զ��һ��������ͨ�ʣ�  4.���룺ת��ϯ������30����Ӧ�����˽����û��Զ��һ������ͨ�ʣ�5.���룺ת��ϯ�ɹ�';
comment on column KF_HJTJB_28_2014.JGBM
  is '��������';
comment on column KF_HJTJB_28_2014.CZYH
  is 'Ippbx����Ա��';
comment on column KF_HJTJB_28_2014.BMBM
  is '���ű���';
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

