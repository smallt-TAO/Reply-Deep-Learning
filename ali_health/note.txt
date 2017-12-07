## 20171124
First day of intern of AliHealth. Tuxiang is my boss.

## 20171127
Today, use the IDEA handle the recommend system. Review the code of the work ago.
Learning the maven, maven is the kit for construct the project.
Learning the OPDS, Open procecss distribute system for Ali.
SQL query code. Simple code.
/Users/smalltao/Library/Logs/IntelliJIdea2017.2 IDEA.log.

## 20171129
sudo pip install requests -i http://mirrors.aliyun.com/pypi/simple --trusted-host mirrors.aliyun.com
This code is for origin python in MAC
Maven setting for the all the projects in IEDA.
ODPS SQL: code example: select * from TABLE limit 10;

## 20171201
ODPS upload and down file via tunnel kit:
code example: 
	whoami; 
	tunnel upload log.txt test_project.test_table/p1="b1",p2="b2";
	tunnel download test_project.test_table/p1="b1",p2="b2" log.txt;
DEBUG:end_point=http://service-corp.odps.aliyun-inc.com/api

## 20171204
IGraph: KV, KKV(PKey, SKey, value)
AtomicSearch, JoinSearch, MergeSearch, AndSearch, AndNotSearch
search {table=friend & keys=u1 & filter=gender='female'} join {joinfield=name} search {table=shoppong & filter=buytime}
ODPS open data processing service
SWIFT: queue of the query message.

## 20171205
CREATE TABLE if NOT EXISTS alijk_bigdata.lintao_test_edw_phr (
    user_id bigint,
	lintao bigint,
	item_id string
	)
PARTITIONED BY (
	ds bigint
	)
lifecycle 3;

INSERT OVERWRITE TABLE alijk_bigdata.lintao_test_edw_phr PARTITION(ds=20171127)
SELECT a.user_id, ROW_NUMBER() OVER(PARTITION BY user_id ORDER BY item_id) AS lintao, a.item_id
FROM alijk_bigdata.edw_phr_usr_disease a
WHERE a.ds=20171127;

# 20171207
select * from heyf_t10 \G; DEBUG in SQL.
--@extra_output=
--@extra_input=
--odps sql 
--********************************************************************--
--author:侠涛
--create time:2017-11-29 15:04:17
--input table:
--output table:
--function: 功能描述
--********************************************************************--

SELECT buyer_id
       ,CASE WHEN COUNT(item_id)>0 THEN -30
             ELSE 0
        END AS med_cnt
       ,SUM(item_price)/(MAX(ds)-MIN(ds)+1) AS med_per_price
FROM alijk_bigdata.ods_phr_user_ord
WHERE cate_level1_name = 'OTC药品/医疗器械/计生用品'
AND ds > 20171200
GROUP BY buyer_id
LIMIT 100;

--snacks_
SELECT buyer_id
       ,SUM(item_price)/(MAX(ds)-MIN(ds)+1) AS cal_per_price
       ,MAX(ds) AS lately_rod
       ,CASE WHEN SUM(item_price)/(MAX(ds)-MIN(ds)+1)>100 THEN -30
             ELSE 0
        END AS is_high_cal 
FROM alijk_bigdata.ods_phr_user_ord
WHERE cate_level1_name = '零食/坚果/特产'
AND ds > 20171200
GROUP BY buyer_id
LIMIT 100;
