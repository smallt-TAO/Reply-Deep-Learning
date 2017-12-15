# coding = utf-8
##20171211
begin the ali health index project.
--INSERT OVERWRITE TABLE alijk_bigdata.adm_health_index_med_snk_score partition (ds='${bizdate}')
SELECT CAST(a.buyer_id AS STRING) AS user_id
        ,CASE WHEN b.medicine < 0 THEN b.medicine
             ELSE 0 
        END AS medicine
        ,b.medicine_rank
        ,CASE WHEN c.snack < 0 THEN c.snack
             ELSE 0 
        END AS snack
        ,c.snack_rank
        ,CASE WHEN d.diagnose < 0 THEN d.diagnose
             ELSE 0 
        END AS diagnose
        ,d.diagnose_rank
        ,TO_CHAR(DATEADD(TO_DATE('${bizdate}', 'yyyymmdd'), - 7, 'dd'), 'yyyymmdd')
FROM    ( 
        SELECT buyer_id
        FROM alijk_bigdata.ods_phr_user_ord
        GROUP BY buyer_id 
        ) a
--medicine score 
LEFT OUTER JOIN (
        SELECT buyer_id
               ,PERCENT_RANK() OVER(ORDER BY price_med desc) AS medicine_rank
               ,medicine
        FROM (
                SELECT buyer_id
                        ,SUM(item_price) AS price_med
                        ,CASE WHEN COUNT(item_id)>0 THEN -30.0
                              ELSE 0.0 
                        END AS medicine
                FROM alijk_bigdata.ods_phr_user_ord
                WHERE cate_level1_name = 'OTC药品/医疗器械/计生用品'
                AND cate_level2_name = 'OTC药品'
                AND ds >= DATEADD(TO_DATE('${bizdate}', 'yyyymmdd'), - 7, 'dd')
                GROUP BY buyer_id
        ) b_temp
        ) b 
ON a.buyer_id = b.buyer_id

--snacks score
LEFT OUTER JOIN (
        SELECT buyer_id
               ,PERCENT_RANK() OVER(ORDER BY price_snk desc) AS snack_rank
               ,snack 
        FROM (
                SELECT buyer_id
                    ,SUM(item_price) AS price_snk
                    ,CASE WHEN COUNT(item_id) > 1 
                                AND SUM(item_price)/(MAX(ds)-MIN(ds)+1)>130 THEN -30
                            WHEN COUNT(item_id) = 1
                                AND SUM(item_price) > 200 THEN -30
                            ELSE 0
                    END AS snack 
                FROM alijk_bigdata.ods_phr_user_ord
                WHERE cate_level1_name = '零食/坚果/特产'
                AND ds >= DATEADD(TO_DATE('${bizdate}', 'yyyymmdd'), - 7, 'dd')
                GROUP BY buyer_id
        ) c_temp
        ) c 
ON a.buyer_id = c.buyer_id

--diag score
LEFT OUTER JOIN (
        SELECT user_id
                ,diagnose 
                ,PERCENT_RANK() OVER(ORDER BY diag_cnt desc) AS diagnose_rank
        FROM (
                SELECT user_id
                        ,COUNT(depart_id) AS diag_cnt
                        ,CASE WHEN COUNT(depart_id) > 0 THEN -30
                            ELSE 0
                        END AS diagnose 
                FROM health_dc.qwz_analysis_cache
                WHERE ds >= DATEADD(TO_DATE('${bizdate}', 'yyyymmdd'), - 7, 'dd')
                GROUP BY user_id
        ) d_temp
        ) d 
ON a.buyer_id = d.user_id
LIMIT 100;

##20171212
Re in ODPS SQL.
SELECT  buyer_id
        ,item_title
        ,commodity_name
        ,item_title like '%g%' -- true
        ,regexp_extract('鼓浪屿乐口享黑米面包 奶酪沙拉切片面包袋50元 保质期8天', '([[:digit:]]*)袋') 
        ,regexp_extract('鼓浪屿乐口享黑米面包 奶酪沙拉切片面包 30袋50元 保质期8天', '([[:digit:]]*)袋') 
        ,regexp_extract('麦干烙蛋糕铁板鸡蛋煎饼干休闲零食整箱批发1500g/4kg', '([[:digit:]]*)g') 
        ,cast(regexp_extract('鼓浪屿乐口享黑米面包 奶酪沙拉切片面包 30袋50元 保质期8天', '([[:digit:]]*)袋') as double) * 80
FROM alijk_bigdata.ods_phr_user_ord
WHERE cate_level1_name = '零食/坚果/特产'
AND ds > 20171100
AND buyer_id = 13090141
LIMIT 50
;

##20171214
TENNEL upload the data

##20171215
MAPJOIN in ODPS SQL

