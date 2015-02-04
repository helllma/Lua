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
  is '�ʲ�ID';
comment on column TB_ITASSET.TRADEMARKID
  is 'Ʒ���ͺ�ID';
comment on column TB_ITASSET.CLASSIFYID
  is '��Ӧ�������ͷ����FLOWTYPEID=1004��CLASSIFID';
comment on column TB_ITASSET.SELLERID
  is '������ID';
comment on column TB_ITASSET.MANUFACTORYID
  is '��������ID��Ӧ�������ұ��е�MANUFACTORYID';
comment on column TB_ITASSET.EQATTID
  is '�豸����ID';
comment on column TB_ITASSET.BUYDATE
  is '��������';
comment on column TB_ITASSET.BATCHNO
  is '����/�������';
comment on column TB_ITASSET.CONTRACTNO
  is '��ͬ��';
comment on column TB_ITASSET.ITEMNAME
  is '��Ŀ����';
comment on column TB_ITASSET.FEENAME
  is '������Ŀ����';
comment on column TB_ITASSET.FEESOURCE
  is '������Դ';
comment on column TB_ITASSET.FINAASSETID
  is '�ʲ����(�����ʲ����)';
comment on column TB_ITASSET.PRICE
  is '����';
comment on column TB_ITASSET.UNITID
  is '��������';
comment on column TB_ITASSET.DEPTID
  is 'ʹ�ò���';
comment on column TB_ITASSET.STATUS
  is '�豸״̬';
comment on column TB_ITASSET.SN
  is '��Ʒ���';
comment on column TB_ITASSET.RFID
  is '�豸����<ֻ��>';
comment on column TB_ITASSET.USERNAME
  is '������';
comment on column TB_ITASSET.TOUSEDATE
  is '��������';
comment on column TB_ITASSET.FINDCODE
  is '������Դ��';
comment on column TB_ITASSET.COMMISSIONINGDATE
  is 'Ͷ������';
comment on column TB_ITASSET.LICENCE
  is '���֤��License������';
comment on column TB_ITASSET.WARRANTY
  is '������';
comment on column TB_ITASSET.MANAGERID
  is '�ʲ�������ID';
comment on column TB_ITASSET.TRANSACTIONID
  is '������ţ������ռ�001����λ����������';
comment on column TB_ITASSET.LABEL
  is '�豸���';
comment on column TB_ITASSET.CREATERNAME
  is '�ʲ�״̬����̬��ǳ�̬��';
comment on column TB_ITASSET.MEMO
  is '��ע';
comment on column TB_ITASSET.OPID
  is '����ԱID';
comment on column TB_ITASSET.OPTIME
  is '����ʱ��';
comment on column TB_ITASSET.ALTERSUMMARY
  is '�����ʾ';
comment on column TB_ITASSET.TEXT1
  is '��������ϵ�绰';
comment on column TB_ITASSET.TEXT2
  is '�豸��;';
comment on column TB_ITASSET.TEXT3
  is '���·��';
comment on column TB_ITASSET.HISTIME
  is '���ú���ʷ����ͳһ';
comment on column TB_ITASSET.ALTERFLAG
  is '���ú�temp����ͳһ';
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
